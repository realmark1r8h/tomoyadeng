// Created by amoylel on 11/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DATE_TIME_HPP__
#define AMO_DATE_TIME_HPP__



#include <ctime>
#include <string>
#include <stdint.h>
#include <amo/format.hpp>

namespace amo {
    using namespace std;
    
    class year;
    class month;
    class day;
    class hour;
    class minute;
    class second;
    
    class year {
    public:
        year(uint16_t year_) : _year(year_) {}
        uint16_t _year;
    };
    
    class month {
    public:
        month(uint16_t month_) : _month(month_) {}
        uint16_t _month;
    };
    class day {
    public:
        day(uint16_t day) : _day(day) {}
        uint16_t _day;
    };
    class hour {
    public:
        hour(uint16_t hour_) : _hour(hour_) {}
        uint16_t _hour;
    };
    class minute {
    public:
        minute(uint16_t minute_) : _minute(minute_) {}
        uint16_t _minute;
    };
    class second {
    public:
        second(uint16_t second_) : _second(second_) {}
        uint16_t _second;
    };
    
    class date_time {
    public:
    
        date_time(time_t seconds_ = 0) : _seconds(seconds_) {
            if (_seconds == 0) {
                time(&_seconds);
            }
        }
        date_time(struct tm time_tm) {
            _seconds = mktime(&time_tm);
        }
        date_time(int year_,
                  int month_ = 0,
                  int day = 0,
                  int hour_ = 0,
                  int minute_ = 0,
                  int second_ = 0) {
            struct tm time_tm;
            //time_t seconds_;
            time_tm.tm_year = year_ - 1900;
            time_tm.tm_mon = month_ - 1;
            time_tm.tm_mday = day;
            time_tm.tm_hour = hour_;
            time_tm.tm_min = minute_;
            time_tm.tm_sec = second_;
            time_tm.tm_isdst = 0;
            _seconds = mktime(&time_tm);
        }
        date_time(const string& datetimeStr) {
            if (datetimeStr.length() == 19) {
                struct tm time_tm;
                sscanf(datetimeStr.c_str(),
                       "%d-%d-%d %d:%d:%d",
                       &time_tm.tm_year,
                       &time_tm.tm_mon,
                       &time_tm.tm_mday,
                       &time_tm.tm_hour,
                       &time_tm.tm_min,
                       &time_tm.tm_sec);
                time_tm.tm_year -= 1900;
                time_tm.tm_mon -= 1;
                _seconds = mktime(&time_tm);
            } else if (datetimeStr.length() == 8) {
                struct tm time_tm;
                sscanf(datetimeStr.c_str(),
                       "%4d%2d%2d",
                       &time_tm.tm_year,
                       &time_tm.tm_mon,
                       &time_tm.tm_mday);
                time_tm.tm_year -= 1900;
                time_tm.tm_mon -= 1;
                time_tm.tm_hour = 0;
                time_tm.tm_min = 0;
                time_tm.tm_sec = 0;
                _seconds = mktime(&time_tm);
            } else {
                _seconds = 0;
            }
        }
        
        int seconds() const {
            return to_tm().tm_sec;
        }
        int minutes()  const {
            return to_tm().tm_min;
        }
        int hours()  const {
            return to_tm().tm_hour;
        }
        
        int month_day() const {
            return to_tm().tm_mday;
        }
        
        int months() const {
            return to_tm().tm_mon + 1;
        }
        
        int years() const {
            return to_tm().tm_year + 1900;
        }
        
        int week_day() const {
            return to_tm().tm_wday;
        }
        
        int year_day()  const {
            return to_tm().tm_yday;
        }
        
        bool isLeap(uint16_t year_)  const {
            if (year_ % 4 == 0 && year_ % 100 != 0 || year_ % 400 == 0) {
                return true;
            }
            
            return false;
        }
        
        uint16_t lastDayOfMonth(uint16_t year_, uint16_t month_) {
            if (month_ == 0 || month_ > 12) {
                return 0;
            }
            
            short leep_year[2][12] = {
                { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
                { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
            };
            return leep_year[isLeap(year_)][month_ - 1];
        }
        
        uint16_t lastDayOfMonth() {
            return lastDayOfMonth(years(), months());
        }
        
        date_time operator+(const year& year_) {
            return operator+(month(12));
        }
        
        date_time operator+(const month& month_) {
            struct tm time_tm = to_tm();
            time_tm.tm_year += (time_tm.tm_mon + month_._month) / 12;
            time_tm.tm_mon = (time_tm.tm_mon + month_._month) % 12;
            
            uint16_t last_day = lastDayOfMonth(time_tm.tm_year + 1900,
                                               time_tm.tm_mon + 1);
                                               
            if (time_tm.tm_mday > last_day) {
                time_tm.tm_mday = last_day;
            }
            
            return date_time(mktime(&time_tm));
        }
        
        date_time operator+(const day& day) {
            return date_time(_seconds + 24 * 60 * 60 * day._day);
        }
        
        date_time operator+(const hour& hour_) {
            return date_time(_seconds + 60 * 60 * hour_._hour);
        }
        
        date_time operator+(const minute& minute_) {
            return date_time(_seconds + 60 * minute_._minute);
        }
        
        date_time operator+(const second& second_) {
            return date_time(_seconds + second_._second);
        }
        
        date_time operator-(const year& year_) {
            return operator-(month(12));
        }
        
        date_time operator-(const month& month_) {
            struct tm time_tm = to_tm();
            
            if (month_._month <= time_tm.tm_mon) {
                time_tm.tm_mon -= month_._month;
            } else {
                time_tm.tm_year -= ((month_._month - time_tm.tm_mon) / 12 + 1);
                time_tm.tm_mon = 12 - (month_._month - time_tm.tm_mon) % 12;
            }
            
            uint16_t last_day = lastDayOfMonth(time_tm.tm_year + 1900,
                                               time_tm.tm_mon + 1);
                                               
            if (time_tm.tm_mday > last_day) {
                time_tm.tm_mday = last_day;
            }
            
            return date_time(mktime(&time_tm));
        }
        
        date_time operator-(const day& day) {
            return date_time(_seconds - 24 * 60 * 60 * day._day);
        }
        
        date_time operator-(const hour& hour_) {
            return date_time(_seconds - 60 * 60 * hour_._hour);
        }
        
        date_time operator-(const minute& minute_) {
            return date_time(_seconds - 60 * minute_._minute);
        }
        
        date_time operator-(const second& second_) {
            return date_time(_seconds - second_._second);
        }
        
        bool operator>(const date_time& rv) {
            return _seconds > rv._seconds;
        }
        
        bool operator==(const date_time& rv) {
            return _seconds == rv._seconds;
        }
        
        bool operator<(const date_time& rv) {
            return _seconds < rv._seconds;
        }
        
        bool operator>=(const date_time& rv) {
            return _seconds >= rv._seconds;
        }
        
        bool operator<=(const date_time& rv) {
            return _seconds <= rv._seconds;
        }
        
        bool operator!=(const date_time& rv) {
            return _seconds != rv._seconds;
        }
        
        string to_string(const string& format = "") const {
            /* char buffer[40] = { 0 };
             struct tm time_tm;
             localtime_s(&time_tm, &_seconds);
             strftime(buffer, sizeof(buffer), format.c_str(), &time_tm);
            return string(buffer);*/
            return amo::format("{0}-{1}-{2} {3}:{4}:{5}",
                               this->years(),
                               this->months(),
                               this->month_day(),
                               this->hours(),
                               this->minutes(),
                               this->seconds());
                               
        }
        
        string to_num_string(short len) {
        
            char buffer[20] = { 0 };
            struct tm time_tm;
            localtime_s(&time_tm, &_seconds);
            snprintf(buffer,
                     sizeof(buffer),
                     "%04d%02d%02d%02d%02d%02d",
                     time_tm.tm_year + 1900,
                     time_tm.tm_mon + 1,
                     time_tm.tm_mday,
                     time_tm.tm_hour,
                     time_tm.tm_min,
                     time_tm.tm_sec);
            return string(buffer).substr(0, len);
        }
        
        struct tm to_tm()  const {
            struct tm time_tm;
            
            localtime_s(&time_tm, &_seconds);
            return time_tm;
        }
        
        time_t to_time()  const {
            return _seconds;
        }
        
        
        static date_time from_string(const std::string& str) {
            char *cha = (char*)str.data();										// 将string转换成char*。
            tm tm_;																// 定义tm结构体。
            int year_, month_, day_, hour_, minute_, second_;							// 定义时间的各个int临时变量。
            sscanf(cha,
                   "%d-%d-%d %d:%d:%d",
                   &year_,
                   &month_,
                   &day_,
                   &hour_,
                   &minute_,
                   &second_);														// 将string存储的日期时间，转换为int临时变量。
            tm_.tm_year = year_ - 1900;											// 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
            tm_.tm_mon = month_ - 1;												// 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
            tm_.tm_mday = day_;													// 日。
            tm_.tm_hour = hour_;													// 时。
            tm_.tm_min = minute_;												// 分。
            
            tm_.tm_sec = second_;												//秒
            tm_.tm_isdst = 0;													// 非夏令时。
            time_t t_ = mktime(&tm_);											// 将tm结构体转换成time_t格式。
            return date_time(t_);												// 返回值。
        }
        
        
    private:
        time_t _seconds;//自1970-01-01 08:00:00起的秒数;
    };
    
    
}
#endif // AMO_DATE_TIME_HPP__