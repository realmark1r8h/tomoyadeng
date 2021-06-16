#ifndef AMO_UID_HPP__
#define AMO_UID_HPP__


#include <sstream>

#include <amo/stdint.hpp>
#include <amo/chrono.hpp>
#include <amo/thread.hpp>
#include <amo/network.hpp>
#include <amo/functional.hpp>
#include <amo/atomic.hpp>

namespace amo {
    class uid {
    public:
        uid() {
            id = generate_uid();
        }
        
        uid(const int64_t& rhs) : id(rhs) {
        
        }
        
        uid(const uid& rhs) : id(rhs.id) {
        
        }
        
        operator int64_t() const {
            return id;
        }
        
        std::string to_string() const {
            std::stringstream stream;
            stream << id;
            return stream.str();
        }
        
        static uid nil() {
            return 0;
        }
        
        static int64_t timestamp_nanoseconds() {
            tm then_tm;
            then_tm.tm_year = 1970 - 1900;
            then_tm.tm_mon = 0; //1月
            then_tm.tm_mday = 1;
            then_tm.tm_hour = 0;
            then_tm.tm_min = 0;
            then_tm.tm_sec = 0;
            time_t timetThen = mktime(&then_tm); //得到时间的整数值
            amo::chrono::system_clock::time_point start_time = amo::chrono::system_clock::from_time_t(timetThen);
            return amo::chrono::duration_cast<amo::chrono::nanoseconds>(start_time.time_since_epoch()).count();
            
        }
        
        //static int64_t generate_uid()
        //{
        //	static int64_t ii = 0;
        //	static amo::mutex m_mutex;
        //	static int64_t epoch_ = timestamp_nanoseconds();//amo::chrono::duration_cast<amo::chrono::nanoseconds>(amo::chrono::system_clock::now().time_since_epoch()).count();
        //	static int32_t  sequence_ = 0;
        //	static int64_t mac = amo::get_any_mac48();
        //	amo::unique_lock<amo::mutex> lock_(m_mutex);
        //
        //	//return ++ii;
        //	int64_t val = 0;
        //	int64_t now = amo::chrono::duration_cast<amo::chrono::nanoseconds>(amo::chrono::system_clock::now().time_since_epoch()).count();
        //	int64_t time = now - epoch_;
        //	//std::cout << mac << std::endl;
        //	val = 0x7fffffffffffffff & (time << 22); //保留后41位时间,保证符号位为0
        //	val |= (mac & 0x3FF) << 12; //中间十位是机器代码
        //	val |= sequence_++ & 0xFFF;	//最后12位是squenceID
        //	if (sequence_ == 0x1000){
        //		sequence_ = 0;
        //	}
        //	return val;
        //}
        
        static int64_t generate_uid() {
            static int64_t epoch_ = timestamp_nanoseconds();
            static amo::atomic<int64_t>  sequence_(0);
            static int64_t mac = amo::get_any_mac48();
            int64_t sq = ++sequence_;
            //return sq;
            int64_t now = amo::chrono::duration_cast<amo::chrono::nanoseconds>(amo::chrono::system_clock::now().time_since_epoch()).count();
            int64_t time = now - epoch_;
            
            int64_t val = 0x7fffffffffffffff & (time << 32);					//保留后32位时间,保证符号位为0
            val |= (mac & 0x3FF) << 22;											//中间十位是机器代码
            val |= sq & 0x3FFFFF;												//最后22位是squenceID
            
            return val;
        }
        friend std::size_t hash_value(const uid& p) {
            amo::hash<int64_t> hs;
            return hs(p.id);
        }
    private:
    
        int64_t id;
        
    };
}


namespace std {
    template <>
    struct hash<amo::uid> {
        size_t operator()(amo::uid const & x) const {
            std::hash<uint64_t> hs;
            return hs((uint64_t)x);
        }
    };
}
//
//namespace boost
//{
//	template <>
//	struct hash<amo::uid>
//	{
//		size_t operator()(amo::uid const & x) const
//		{
//			amo::hash<int64_t> hs;
//			return hs((int64_t)x);
//		}
//	};
//}

/*
namespace boost
{
template <> struct hash<type> \
	: public std::unary_function<type, std::size_t> \
{ \
std::size_t operator()(type const& v) const \
{ \
return boost::hash_value(v); \
} \
};
}*/


#endif // AMO_UID_HPP__
