#ifndef AMO_LOOPER_EXECUTOR_HPP__
#define AMO_LOOPER_EXECUTOR_HPP__

#include <strstream>
#include <queue>
#include <exception>
#include <string>
#include <iostream>

#include <amo/chrono.hpp>
#include <amo/thread.hpp>
#include <amo/functional.hpp>
#include <amo/memory.hpp>
#include <amo/logger.hpp>
#include <amo/atomic.hpp>



namespace amo{

	class runnable
	{
	public:
		typedef  amo::chrono::time_point<amo::chrono::system_clock> time_point;
		typedef amo::function<void()> executor;
	public:
		runnable(executor run_, uint64_t runnable_index, uint64_t delay = 0)
		{
			time_point now = amo::chrono::system_clock::now();
			execute_time_point_ = now + amo::chrono::milliseconds(delay);
			insert_time_point_ = runnable_index;
			runnable_ = run_;
		}

		runnable(executor run_, uint64_t runnable_index, time_point execute_time = amo::chrono::system_clock::now())
		{
			execute_time_point_ = execute_time;
			insert_time_point_ = runnable_index;
			runnable_ = run_;
		}

		runnable(const runnable& rhs)
			: runnable_(rhs.runnable_),
			execute_time_point_(rhs.execute_time_point_),
			insert_time_point_(rhs.insert_time_point_)
		{

		}

		operator time_point() const
		{
			return execute_time_point_;
		}

		operator executor() const
		{
			return runnable_;
		}

		void operator () () 
		{
			runnable_();
		}

		friend bool operator > (const runnable& lhs, const runnable& rhs) 
		{	
			if(lhs.execute_time_point_ == rhs.execute_time_point_)
			{
				return lhs.insert_time_point_ > rhs.insert_time_point_;
			}
			return lhs.execute_time_point_ > rhs.execute_time_point_;
		} 
	private:
		time_point execute_time_point_;
		executor runnable_;
		uint64_t insert_time_point_;
	};


	class looper_executor
	{
	public:
		typedef std::priority_queue<runnable, std::vector<runnable>, std::greater<runnable> > handler;
		typedef amo::chrono::time_point<amo::chrono::system_clock> time_point;
		typedef amo::function<void()> executor;
	public:
		const static uint64_t empty_queue = 4070880000000;
	public: 
		looper_executor(int buffer_size = 100) : m_buffer_size(buffer_size)
		{
			m_running = false;
			m_runnable_index = 0;
			
			std::tm timeinfo = std::tm();
			timeinfo.tm_year = 199;												//!< year: 2099
			timeinfo.tm_mon = 0;												//!< month: january
			timeinfo.tm_mday = 1;												//!< day: 1st
			std::time_t tt = std::mktime(&timeinfo);
			m_empty_queue_time = amo::chrono::system_clock::from_time_t(tt);

			start();
		}

		~looper_executor()
		{
			stop();
		}

		void check_if_called_on_valid_thread()
		{
			if (!check_on_looper_thread()) 
			{
				throw std::runtime_error("method is not called on valid thread");
			}
		}

		bool check_on_looper_thread()
		{
			return (amo::this_thread::get_id() == m_thread_id);
		}

		void push(executor runnable_, uint64_t delay = 0)
		{
			return execute(runnable_, delay);
		}

		void push(executor runnable_, time_point execute_time)
		{
			return execute(runnable_, execute_time);
		}

		void execute(executor runnable_, uint64_t delay = 0)
		{
			time_point execute_time = amo::chrono::system_clock::now() + amo::chrono::milliseconds(delay);
			if (delay == empty_queue)
			{
				time_point execute_time = m_empty_queue_time;
			}
			
			return execute(runnable_, execute_time);
		}

		void execute(executor runnable_, time_point execute_time)
		{
			amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
			if (!m_running) return;
			 
			if (check_on_looper_thread() && execute_time <= amo::chrono::system_clock::now())
			{
				lock.unlock();
				return runnable_();
			}

			m_not_full.wait(lock, amo::bind(&looper_executor::is_not_full, this, m_buffer_size));
			if (execute_time == m_empty_queue_time)
			{
				m_is_empty.wait(lock, amo::bind(&looper_executor::is_empty, this));
				execute_time = amo::chrono::system_clock::now();
			}
				
			if (!m_running) return;
			m_handler.push(runnable(runnable_, m_runnable_index++, execute_time));
			m_not_empty.notify_all();
		}

		void clear()
		{
			amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
			while (!m_handler.empty())
			{
				m_handler.pop();
			}
		}
		void run()
		{
			m_thread_id = amo::this_thread::get_id();
			try
			{
				while (m_running)
				{
					amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
					m_not_empty.wait(lock, amo::bind(&looper_executor::is_not_empty, this));
					if (!m_running) return;

					runnable runnable_ = m_handler.top();
					uint64_t now = amo::chrono::duration_cast<amo::chrono::milliseconds>(amo::chrono::system_clock::now().time_since_epoch()).count();
					time_point execute_time_point = runnable_;
					uint64_t execute_time = amo::chrono::duration_cast<amo::chrono::milliseconds>(execute_time_point.time_since_epoch()).count();
					uint64_t delay = 0;
					if (now < execute_time) delay = execute_time - now;
					m_handler.pop();
					if (m_correct.wait_for(lock, amo::chrono::milliseconds(delay)) == amo::cv_status::timeout)
					{
						m_not_full.notify_all();
						if (m_handler.empty()) m_is_empty.notify_all();
						lock.unlock();
						runnable_();
					}
					else
					{
						amo::cwarn << "looper executor interrupt" << amo::endl;
						return;
					}
					 

				}
			}
			catch (std::exception& e)
			{
				amo::cfatal("[{0}][{1}]{2}", m_thread_id, m_thread_name, e.what());
				/*m_running = false;
				return;*/
			}
		}

		void set_name(const std::string& thread_name)
		{
			m_thread_name = std::string(" [") + thread_name + std::string("] ");
		}

		std::string get_name() const
		{
			return m_thread_name;
		}

	

		void start()
		{
			amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
			if (m_running) return;
			m_running = true;
			clear();
			m_work_thread = amo::thread(amo::bind(&looper_executor::run, this));
		}

		void stop()
		{ 
			amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
			if (!m_running) return;
			m_running = false;
			m_not_empty.notify_all();
			m_not_full.notify_all();
			lock.unlock();
			
			// 向线程发送中断请求 
#ifdef BOOST_NO_CXX11_HDR_THREAD
			m_work_thread.interrupt();
#endif // BOOST_NO_CXX11_HDR_THREAD

			//join函数，作用是等待直到线程执行结束；可不加，但不能保证退出Destroy函数前线程被终结 
			if (m_work_thread.joinable()) m_work_thread.join();
		}
	private:
		bool is_not_full(int64_t buffer_size = 100)
		{
			amo::unique_lock<amo::recursive_mutex> lock(m_mutex); 
			return (m_handler.size() < buffer_size) || !m_running ;
		}

		bool is_not_empty()
		{
			amo::unique_lock<amo::recursive_mutex> lock(m_mutex); 
			return (m_handler.size() > 0) || !m_running;
		}

		bool is_empty()
		{
			amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
			return (m_handler.empty()) || !m_running;
		}
		 
		
	private:
		amo::recursive_mutex  m_mutex;  
		amo::condition_variable_any m_not_empty;     
		amo::condition_variable_any m_is_empty;
		amo::condition_variable_any m_not_full;
		amo::condition_variable_any m_correct; 
		handler m_handler;
		amo::atomic<bool> m_running;
		amo::thread m_work_thread;
		amo::thread::id m_thread_id;
		uint64_t m_runnable_index;												// 插入索引，如果两个任务的执行时间相同，会根据任务插入的先后顺序执行
		int m_buffer_size;
		std::string m_thread_name;
		time_point m_empty_queue_time;											//!< The empty queue time
	};


	 

}

#endif // AMO_LOOPER_EXECUTOR_HPP__
