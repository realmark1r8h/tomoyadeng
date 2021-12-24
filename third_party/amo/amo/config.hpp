#ifndef AMO_CONFIG_HPP__
#define AMO_CONFIG_HPP__

#if defined(_WIN32) || defined(_WIN64) ||defined(WIN32) || defined(WIN64)
#	include <WinSock2.h>
#   include <windows.h>
#endif
//��������Ҫ����ʹ��
//- atomic : building
//- chrono : building
//- container : building
//- context : building
//- coroutine : building
//- coroutine2 : building
//- date_time : building
//- exception : building
//- filesystem : building
//- graph : building
//- graph_parallel : building
//- iostreams : building
//- locale : building
//- log : building
//- math : building
//- mpi : building
//- program_options : building
//- python : building
//- random : building
//- regex : building
//- serialization : building
//- signals : building
//- system : building
//- test : building
//- thread : building
//- timer : building
//- type_erasure : building
//- wave : building

#ifdef AMO_NO_BOOST
#include <amo/boost/config.hpp>
#include <amo/boost/any.hpp>
#include <amo/boost/function.hpp>
#include <amo/boost/bind.hpp>
#include <amo/boost/unordered_map.hpp>
#include <amo/boost/unordered_set.hpp>
#include <amo/boost/signals2.hpp>
#include <amo/boost/ref.hpp>
#include <amo/boost/array.hpp>
#include <amo/boost/lexical_cast.hpp>
#include <amo/boost/limits.hpp>
#include <amo/boost/shared_ptr.hpp>
#include <amo/boost/make_shared.hpp>
#include <amo/boost/scoped_array.hpp>
#include <amo/boost/enable_shared_from_this.hpp>
#include <amo/boost/pointer_cast.hpp>
#include <amo/boost/ratio.hpp>
#include <amo/boost/cstdint.hpp>
#include <amo/boost/logic/tribool.hpp>
#include <amo/boost/tuple/tuple.hpp>
#include <amo/boost/aligned_storage.hpp>
#include <amo/boost/optional/optional.hpp>
#include <amo/boost/variant.hpp>
#include <amo/boost/foreach.hpp>
#include <amo/boost/scoped_ptr.hpp>
#include <amo/boost/intrusive_ptr.hpp>
#include <amo/boost/dynamic_bitset.hpp>
#include <amo/boost/bimap.hpp>
#include <amo/boost/utility.hpp>
#include <amo/boost/program_options.hpp>
#include <amo/boost/tokenizer.hpp>
#include <amo/boost/token_functions.hpp>
#include <amo/boost/random.hpp>
#include <amo/boost/random/random_device.hpp>
#include <amo/boost/thread.hpp>
#include <amo/boost/thread/mutex.hpp>
#include <amo/boost/thread/condition_variable.hpp>
#include <amo/boost/thread/future.hpp>
#include <amo/boost/optional.hpp>
#else
#include <boost/config.hpp>
#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/convert.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/signals2.hpp>
#include <boost/ref.hpp>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/limits.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/scoped_array.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/ratio.hpp>
#include <boost/cstdint.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/aligned_storage.hpp>
#include <boost/optional/optional.hpp>
#include <boost/variant.hpp>
#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/bimap.hpp>
#include <boost/utility.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/future.hpp>
#include <boost/optional.hpp>
#endif

#if defined(_WIN32) || defined(_WIN64) ||defined(WIN32) || defined(WIN64)
#	include <WinSock2.h>
#   include <windows.h>
#   include <process.h>
#   include <iphlpapi.h>
#   pragma comment(lib,"iphlpapi.lib")
#   define $windows $yes
#elif defined(__FreeBSD__) || defined(__NetBSD__) || \
	defined(__OpenBSD__) || defined(__MINT__) || defined(__bsdi__)
#   include <ifaddrs.h>
#   include <net/if_dl.h>
#   include <sys/socket.h>
#   include <sys/time.h>
#   include <sys/types.h>
#   define $bsd $yes
#elif (defined(__APPLE__) && defined(__MACH__))
#   include <ifaddrs.h>
#   include <net/if_dl.h>
#   include <sys/socket.h>
#   include <sys/time.h>
#   include <sys/types.h>
#   include <unistd.h>
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#   define $osx $yes
#elif defined(__linux__)
#   include <arpa/inet.h>
#   include <net/if.h>
#   include <netinet/in.h>
#   include <sys/ioctl.h>
#   include <sys/socket.h>
#   include <sys/sysinfo.h>
#   include <sys/time.h>
#   include <unistd.h>
#   define $linux $yes
#else //elif defined(__unix__)
#   if defined(__VMS)
#      include <ioctl.h>
#      include <inet.h>
#   else
#      include <sys/ioctl.h>
#      include <arpa/inet.h>
#   endif
#   if defined(sun) || defined(__sun)
#      include <sys/sockio.h>
#   endif
#   include <net/if.h>
#   include <net/if_arp.h>
#   include <netdb.h>
#   include <netinet/in.h>
#   include <sys/socket.h>
#   include <sys/time.h>
#   include <sys/types.h>
#   include <unistd.h>
#   if defined(__VMS)
namespace {
    enum { MAXHOSTNAMELEN = 64 };
}
#   endif
#   define $unix $yes
#endif
#include <iostream>

#ifdef _MSC_VER
#   define $msvc  $yes
#endif

#if defined(__GNUC__) && (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ <= 40902 )
namespace std {
    static std::string put_time(const std::tm* tmb, const char* fmt) {
        std::string s(128, '\0');
        
        while (!strftime(&s[0], s.size(), fmt, tmb)) {
            s.resize(s.size() + 128);
        }
        
        return s;
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////////



#ifdef  $windows
#define $welse   $no
#else
#define $windows $no
#define $welse   $yes
#endif

#ifdef  $bsd
#define $belse   $no
#else
#define $bsd     $no
#define $belse   $yes
#endif

#ifdef  $linux
#define $lelse   $no
#else
#define $linux   $no
#define $lelse   $yes
#endif

#ifdef  $unix
#define $uelse   $no
#else
#define $unix    $no
#define $uelse   $yes
#endif

#ifdef  $osx
#define $oelse   $no
#else
#define $osx     $no
#define $oelse   $yes
#endif

#ifdef  $msvc
#define $melse   $no
#else
#define $msvc    $no
#define $melse   $yes
#endif

#define $yes(...) __VA_ARGS__
#define $no(...)


#endif // AMO_CONFIG_HPP__
