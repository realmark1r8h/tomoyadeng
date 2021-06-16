#ifndef AMO_TIMER_HPP__
#define AMO_TIMER_HPP__

	 
#include <amo/chrono.hpp>

namespace amo
{
	class timer
	{
	public:
		timer()
		{
			restart();
		}

		void restart()                      // 执行之后: elapsed()==0 
		{
			start = amo::chrono::system_clock::now();
		}

		template<typename T>
		uint64_t elapsed() const                // 以毫秒为单位，返回流逝的时间
		{
			amo::chrono::time_point<amo::chrono::system_clock> now = amo::chrono::system_clock::now();
			return amo::chrono::duration_cast<T>(now.time_since_epoch()).count()
			   - amo::chrono::duration_cast<T>(start.time_since_epoch()).count();
		 
		}

		
		uint64_t elapsed() const
		{
			amo::chrono::time_point<amo::chrono::system_clock> now = amo::chrono::system_clock::now();
			return amo::chrono::duration_cast<amo::chrono::milliseconds>(now.time_since_epoch()).count()
				- amo::chrono::duration_cast<amo::chrono::milliseconds>(start.time_since_epoch()).count();
		}

		template<typename T>
		static int64_t now()
		{
			amo::chrono::time_point<amo::chrono::system_clock> now = amo::chrono::system_clock::now();
			return amo::chrono::duration_cast<T>(now.time_since_epoch()).count();
		}

		static int64_t now()
		{
			amo::chrono::time_point<amo::chrono::system_clock> now = amo::chrono::system_clock::now();
			return amo::chrono::duration_cast<amo::chrono::milliseconds>(now.time_since_epoch()).count();
		}
		
	private:
		amo::chrono::time_point<amo::chrono::system_clock>  start;
	};
}


#endif // AMO_TIMER_HPP__