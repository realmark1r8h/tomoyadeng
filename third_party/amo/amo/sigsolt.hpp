#ifndef AMO_SIGSOLT_HPP__
#define AMO_SIGSOLT_HPP__
 
#include <set>
#include <amo/any.hpp>
#include <amo/functional.hpp>
#include <amo/stdint.hpp>
#include <amo/uid.hpp>
#include <amo/unordered_map.hpp>
#include <amo/signals2.hpp>
#include <amo/smart_ptr.hpp>
#include <amo/template_macro.hpp>
#include <amo/optional.hpp>
#include <amo/logger.hpp>
 
#define SIGSLOT_EMIT_CLASS_GEN(val)\
template<TEMPLATE_PARAM_TYPE##val>\
class emit##val\
{\
public:\
	emit##val(amo::any obj)\
	{\
		m_fn = obj;\
	}\
	 \
	amo::optional<R> emit(const int64_t& event_id COMMA##val FUNC_PARAM##val)\
	{\
		amo::optional<R> ret;\
		try\
		{\
			ret = amo::any_cast<amo::shared_ptr<amo::signals2::signal<R(FUNC_PARAM_TYPE##val)> > >(m_fn)->operator()(FUNC_PARAM_VAL##val);\
			return ret;\
		}\
		catch (amo::bad_any_cast& e)\
		{\
			amo::cerr << __FUNCTION__ << e.what() << amo::endl;\
			return ret;\
		}\
	}\
	amo::any m_fn;\
};\
template<NORETURN_TEMPLATE_PARAM_TYPE##val>\
class emit##val<amo::nil COMMA##val FUNC_PARAM_TYPE##val>\
{\
public:\
	emit##val(amo::any obj)\
	{\
		m_fn = obj;\
	}\
	amo::optional<amo::nil> emit(const int64_t& event_id COMMA##val FUNC_PARAM##val)\
	{\
		amo::optional< amo::nil> ret;\
		try\
		{\
			amo::any_cast<amo::shared_ptr<amo::signals2::signal<void(FUNC_PARAM_TYPE##val)> > >(m_fn)->operator()(FUNC_PARAM_VAL##val);\
			return ret;\
		}\
		catch (amo::bad_any_cast& e)\
		{\
			amo::cerr << __FUNCTION__ << e.what() << amo::endl;\
			return ret;\
		}\
	}\
	amo::any m_fn;\
};

#include <amo/av/smart_frame.hpp>

template<typename R, typename P1>
class emit1
{
public:
	emit1(amo::any obj)
	{
		m_fn = obj;
	}
	 
	amo::optional<R> emit(const int64_t& event_id , P1 p1)
	{
		amo::optional<R> ret;
		try
		{
			/*amo::cdevel << typeid(R).name() << amo::endl;
			amo::cdevel << typeid(P1).name() << amo::endl;*/
			ret = amo::any_cast<amo::shared_ptr<amo::signals2::signal<R(P1)> > >(m_fn)->operator()(p1);
			//ret = amo::any_cast<amo::shared_ptr<amo::signals2::signal<R(FUNC_PARAM_TYPE##val)> > >(m_fn)->operator()(FUNC_PARAM_VAL##val); 
			return ret;
		}
		catch (amo::bad_any_cast& e)
		{
			amo::cerr << __FUNCTION__ << e.what() << amo::endl;
			return ret;
		}
		return ret;
	}
	amo::any m_fn;
};
template<typename P1>
class emit1<amo::nil, P1>
{
public:
	emit1(amo::any obj)
	{
		m_fn = obj;
	}
	amo::optional<amo::nil> emit(const int64_t& event_id , P1 p1)
	{
		amo::optional< amo::nil> ret;
		try
		{
			amo::any_cast<amo::shared_ptr<amo::signals2::signal<void(P1)> > >(m_fn)->operator()(p1);
			return ret;
		}
		catch (amo::bad_any_cast& e)
		{
			amo::cerr << __FUNCTION__ << e.what() << amo::endl;
			return ret;
		}
	}
	amo::any m_fn;
};

#define SIGSLOT_EMIT_FUNC_GEN(val)\
template<TEMPLATE_PARAM_TYPE##val>\
amo::optional<R> emit(const int64_t& event_id COMMA##val FUNC_PARAM##val)\
{\
	amo::optional<R> ret;\
	for (std::set<slot*>::iterator it = m_slt.begin();\
		it != m_slt.end(); ++it)\
	{\
		SignalsType& signals_ = (*it)->get_signals();\
		SignalsType::iterator iter = signals_.find(event_id);\
		if (iter == signals_.end()) return ret;\
		ret = emit##val<R COMMA##val FUNC_PARAM_TYPE##val>(iter->second).emit(event_id COMMA##val FUNC_PARAM_VAL##val);\
	}\
	return ret;\
}

namespace amo
{
	class slot
	{
	public:
		typedef amo::unordered_map<int64_t, amo::any> SignalMap;
		typedef amo::unordered_map<int64_t, amo::any> SignalsType;

	public:
		template<typename Functor>
		void listen(const int64_t& event_id, amo::function<Functor> slt)
		{
			SignalsType& signals_ = get_signals();
			SignalsType::iterator iter = signals_.find(event_id);
			 
			if (iter == signals_.end())
			{
				amo::shared_ptr<amo::signals2::signal<Functor> > sig(new amo::signals2::signal<Functor>());
				sig->connect(slt);
				signals_[event_id] = sig;
				amo::any_cast<amo::shared_ptr<amo::signals2::signal<Functor> >>(signals_[event_id]);
			}
			else
			{
				try
				{
					amo::any_cast<amo::shared_ptr<amo::signals2::signal<Functor> >>(iter->second)->connect(slt);
				}
				catch (amo::bad_any_cast& e)
				{
					amo::cerr << __FUNCTION__ << e.what() << amo::endl;
					return;
				}
			}
		}
		
		SignalsType& get_signals()
		{
			return signals_;
		}

	private:
		
		SignalsType signals_;
	};


	class signal
	{
	public:
		typedef amo::unordered_map<int64_t, amo::any> SignalMap;
		typedef amo::unordered_map<int64_t, amo::any> SignalsType;
	public:
		void connect(slot* slt)
		{
			if (slt == NULL) return;
			m_slt.insert(slt);
		}
		
		void disconnect(slot* slt)
		{
			if (slt == NULL) return;
			m_slt.erase(slt);
		}
 
		SIGSLOT_EMIT_FUNC_GEN(0)
		SIGSLOT_EMIT_FUNC_GEN(1)
		SIGSLOT_EMIT_FUNC_GEN(2)
		SIGSLOT_EMIT_FUNC_GEN(3)
		SIGSLOT_EMIT_FUNC_GEN(4)
		SIGSLOT_EMIT_FUNC_GEN(5)
		SIGSLOT_EMIT_FUNC_GEN(6)
		SIGSLOT_EMIT_FUNC_GEN(7)
		SIGSLOT_EMIT_FUNC_GEN(8)
		SIGSLOT_EMIT_FUNC_GEN(9)
		SIGSLOT_EMIT_FUNC_GEN(10)
		SIGSLOT_EMIT_FUNC_GEN(11)
		SIGSLOT_EMIT_FUNC_GEN(12)
		SIGSLOT_EMIT_FUNC_GEN(13)
		SIGSLOT_EMIT_FUNC_GEN(14)
		SIGSLOT_EMIT_FUNC_GEN(15)
		SIGSLOT_EMIT_FUNC_GEN(16)
		SIGSLOT_EMIT_FUNC_GEN(17)
		SIGSLOT_EMIT_FUNC_GEN(18)
		SIGSLOT_EMIT_FUNC_GEN(19)
		SIGSLOT_EMIT_FUNC_GEN(20)
	private:
		SIGSLOT_EMIT_CLASS_GEN(0)
		//SIGSLOT_EMIT_CLASS_GEN(1)
		SIGSLOT_EMIT_CLASS_GEN(2)
		SIGSLOT_EMIT_CLASS_GEN(3)
		SIGSLOT_EMIT_CLASS_GEN(4)
		SIGSLOT_EMIT_CLASS_GEN(5)
		SIGSLOT_EMIT_CLASS_GEN(6)
		SIGSLOT_EMIT_CLASS_GEN(7)
		SIGSLOT_EMIT_CLASS_GEN(8)
		SIGSLOT_EMIT_CLASS_GEN(9)
		SIGSLOT_EMIT_CLASS_GEN(10)
		SIGSLOT_EMIT_CLASS_GEN(11)
		SIGSLOT_EMIT_CLASS_GEN(12)
		SIGSLOT_EMIT_CLASS_GEN(13)
		SIGSLOT_EMIT_CLASS_GEN(14)
		SIGSLOT_EMIT_CLASS_GEN(15)
		SIGSLOT_EMIT_CLASS_GEN(16)
		SIGSLOT_EMIT_CLASS_GEN(17)
		SIGSLOT_EMIT_CLASS_GEN(18)
		SIGSLOT_EMIT_CLASS_GEN(19)
		SIGSLOT_EMIT_CLASS_GEN(20)

	protected:
		std::set<slot*> m_slt;
	};

	class sigslot : public signal, public slot
	{
	public:

	};
}
#endif // AMO_SIGSOLT_HPP__
