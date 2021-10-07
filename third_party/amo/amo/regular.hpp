// Created by amoylel on 11/07/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_REGULAR_HPP__
#define AMO_REGULAR_HPP__

#include <string>
#include <regex>

namespace amo {
    class regular {
    public:
        regular(const std::string str)
            : m_str(str) {
            
        }
        
        bool is_number() {
            return  std::regex_match(m_str, std::regex("^\\d+$"));
        }
        
        bool is_qq_number() {
            // QQºÅ5µ½11Î»
            return  std::regex_match(m_str, std::regex("^[1-9]\\d{4,10}$"));
        }
        
    private:
        std::string m_str;
    };
}


#endif // AMO_REGULAR_HPP__