#ifndef AMO_LOGGER_HPP__
#define AMO_LOGGER_HPP__

#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif

#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif

#include <amo/config.hpp>
#include <sstream>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/dist_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <amo/logger/raw_daily_file_sink.h>

#include <amo/format.hpp>
#include <amo/string.hpp>

#ifndef AMO_LOG_TRACE_OFF
#define $cdevel(format, ...) amo::cdevel(format, ##__VA_ARGS__)
#else
#define $cdevel(format, ...)
#endif

#ifndef AMO_LOG_DEBUG_OFF
#define $cdebug(format, ...) amo::cdebug(format, ##__VA_ARGS__)
#else
#define $cdebug(format, ...)
#endif

#ifndef AMO_LOG_INFO_OFF
#define $cinfo(format, ...) amo::cinfo(format, ##__VA_ARGS__)
#else
#define $cinfo(format, ...)
#endif


#ifndef AMO_LOG_WARN_OFF
#define $cwarn(format, ...) amo::cwarn(format, ##__VA_ARGS__)
#else
#define $cwarn(format, ...)
#endif

#ifndef AMO_LOG_ERR_OFF
#define $cerr(format, ...) amo::cerr(format, ##__VA_ARGS__)
#else
#define $cerr(format, ...)
#endif

#ifndef AMO_LOG_CRITICAL_OFF
#define $cfatal(format, ...) amo::cfatal(format, ##__VA_ARGS__)
#else
#define $cfatal(format, ...)
#endif

#ifndef AMO_LOG_MACRO_OFF
#define $log(...) __VA_ARGS__
#else
#define $log(...)
#endif


#define file_orient (std::string("[") + amo::short_file_name(__FILE__) + std::string(":") + amo::long_to_string(__LINE__) + "] ")

#define func_orient (std::string("[") + std::string(__FUNCTION__) + std::string(":") + amo::long_to_string(__LINE__) + "] ")

#define log_separator ("--------------------------------------------------------------------------------\n")

#define log_asterisk_separator ("********************************************************************************\n")




namespace amo {
    enum flag {
        endl = 0,		//��־д���־
        separator = 1,	//�ָ���
        blank_line = 2,	//����
    };
    
    static std::string short_file_name(std::string file_name) {
    
        file_name = file_name.substr(file_name.find_last_of('\\') + 1);
        file_name = file_name.substr(file_name.find_last_of('/') + 1);
        return file_name;
    }
    
    static std::string bracket(std::string str) {
        std::string rec = "(";
        rec += str;
        rec += ") ";
        return rec;
    }
    
    static std::string long_to_string(long val) {
        std::stringstream stream;
        stream << val;
        return stream.str();
    }
    
    namespace log {
        using namespace spdlog;
        
        static std::shared_ptr<spdlog::logger> logger() {
            return spdlog::get("default");
        }
        
        static std::shared_ptr<spdlog::sinks::dist_sink_mt> sink() {
            static std::shared_ptr<spdlog::sinks::dist_sink_mt> ptr;
            
            if (!ptr) {
                ptr = std::make_shared<spdlog::sinks::dist_sink_mt>();
            }
            
            return ptr;
        }
        
        static void add_sink(std::shared_ptr<spdlog::sinks::sink> sk) {
            sink()->add_sink(sk);
        }
        
        static void remove_sink(std::shared_ptr<spdlog::sinks::sink> sk) {
            sink()->remove_sink(sk);
        }
        
        static void set_level(amo::log::level::level_enum l) {
            logger()->set_level(l);
        }
        
        static bool should_log(amo::log::level::level_enum l) {
            return logger()->should_log(l);
        }
        
        static amo::log::level::level_enum get_level() {
            return logger()->level();
        }
        
        static const std::string& name() {
            return logger()->name();
        }
        
        static void set_pattern(const std::string& str) {
            logger()->set_pattern(str);
        }
        
        static void write(const std::string& str) {
            logger()->log(spdlog::level::level_enum::critical, str);
        }
        
        static bool initialize() {
            try {
                if (logger()) {
                    return true;
                }
                
                auto ptr = spdlog::create("default", sink());
                
                if (!ptr) {
                    return false;
                }
                
                return true;
            } catch (const spdlog::spdlog_ex& ex) {
                std::cout << "Log init failed: " << ex.what() << std::endl;
                return false;
            }
        }
        
        static void finalize() {
            spdlog::drop_all();
        }
        
        class unit {
        public:
            unit(spdlog::level::level_enum l)
                : m_level(l) {
                
            }
            
            template <typename... Args>
            inline void operator()(const char* fmt, const Args&... args) {
                if (!m_logger) {
                    m_logger = logger();
                }
                
                if (!m_logger) {
                    return;
                }
                
                m_logger->log(m_level, fmt, args...);
            }
            
            unit& operator << (amo::flag val) {
                switch (val) {
                case endl:
                    write_buffer();
                    break;
                    
                case separator:
                    write_buffer();
                    break;
                    
                case blank_line:
                    write_buffer();
                    break;
                    
                default:
                    break;
                }
                
                return *this;
            }
            
            template<typename T>
            unit& operator << (const T& val) {
                buffer << val;
                return *this;
            }
            
            unit& operator << (const amo::string& val) {
                buffer << val.to_ansi();
                return *this;
            }
            
            void write_buffer() {
                std::string str = buffer.str();
                buffer.clear();
                
                if (str.empty()) {
                    return;
                }
                
                if (!m_logger) {
                    m_logger = logger();
                }
                
                if (!m_logger) {
                    return;
                }
                
                m_logger->log(m_level, str);
            }
            
        private:
            spdlog::level::level_enum m_level;
            amo::memory_writer buffer;
            std::shared_ptr<spdlog::logger> m_logger;
        };
    }
    
    
    
    class log_utils {
    public:
        static amo::log::unit& get_default_devel_unit() {
            static amo::log::unit unt_(amo::log::level::trace);
            return unt_;
        }
        
        static amo::log::unit& get_default_debug_unit() {
            static amo::log::unit unt_(amo::log::level::debug);
            return unt_;
        }
        
        static amo::log::unit& get_default_info_unit() {
            static amo::log::unit unt_(amo::log::level::info);
            return unt_;
        }
        
        static amo::log::unit& get_default_warn_unit() {
            static amo::log::unit unt_(amo::log::level::warn);
            return unt_;
        }
        
        static amo::log::unit& get_default_rerror_unit() {
            static amo::log::unit unt_(amo::log::level::err);
            return unt_;
        }
        
        static amo::log::unit& get_default_fatal_unit() {
            static amo::log::unit unt_(amo::log::level::critical);
            return unt_;
        }
    };
    
    static amo::log::unit&	cdevel	= log_utils::get_default_devel_unit();
    static amo::log::unit&	cdebug	= log_utils::get_default_debug_unit();
    static amo::log::unit&	cinfo	= log_utils::get_default_info_unit();
    static amo::log::unit&	cwarn	= log_utils::get_default_warn_unit();
    static amo::log::unit&	cerr	= log_utils::get_default_rerror_unit();
    static amo::log::unit&	cfatal	= log_utils::get_default_fatal_unit();
    
}

#endif // AMO_LOGGER_HPP__