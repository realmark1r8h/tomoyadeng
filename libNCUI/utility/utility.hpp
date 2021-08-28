// Created by amoylel on 08/05/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_UTILITY_HPP2__
#define AMO_UTILITY_HPP2__

#include <string>
#include <sstream>
#include <amo/string.hpp>



namespace amo {

    class util {
    public:
        static amo::string getUrlFromUtf8(const std::string& url) {
            std::string ss = url;
            std::string sd;
            
            while (!ss.empty()) {
                int index = ss.find_first_of('%');
                
                if (index == -1) {
                    sd += ss;
                    ss = "";
                } else {
                    sd += ss.substr(0, index);
                    ss = ss.substr(index + 1);
                    std::stringstream str;
                    str << std::hex << ss.substr(0, 2);
                    std::string sc = str.str();
                    int b = 0;
                    
                    str >> b;
                    sd += (char)(b & 0xff);
                    ss = ss.substr(2);
                    std::cout << b << std::endl;
                }
            }
            
            return amo::string(sd, true);
        }
        
        static bool isDevUrl(const std::string& url) {
            return url == "chrome-devtools://devtools/inspector.html";
        }
    };
    
}

#endif // AMO_UTILITY_HPP__

