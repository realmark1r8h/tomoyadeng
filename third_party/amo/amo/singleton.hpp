#ifndef AMO_SINGLETON_HPP__
#define AMO_SINGLETON_HPP__


#include <amo/noncopyable.hpp>
#include <amo/memory.hpp>
#include <amo/object.hpp>

namespace amo {

	template<typename T>
	class singleton : public amo::noncopyable
		, public amo::object {
	public:
		static amo::shared_ptr<T> get_instance() {
			static amo::shared_ptr<T> m_instance(new T());
			return m_instance;
		}

		static amo::shared_ptr<T> getInstance() {
			return get_instance();
		}
	};
}

#endif // AMO_SINGLETON_HPP__