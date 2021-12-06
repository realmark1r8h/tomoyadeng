// Created by amoylel on 08/05/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_UTILITY_HPP2__
#define AMO_UTILITY_HPP2__

#include <string>
#include <sstream>
#include <amo/string.hpp>
#include <ipc/Any.hpp>
#include <amo/json.hpp>

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
        
        
        void addAnyToJsonArray(amo::json& json, const Any& val) const  {
            switch (val.type()) {
            case  AnyValueType<Undefined>::value:
            case  AnyValueType<Nil>::value:
                json.push_back(val.toJson());
                break;
                
            case  AnyValueType<bool>::value:
                json.push_back(val.As<bool>());
                break;
                
            case  AnyValueType<int>::value:
                json.push_back(val.As<int>());
                break;
                
            case  AnyValueType<double>::value:
                json.push_back(val.As<double>());
                break;
                
            case  AnyValueType<std::string>::value:
                json.push_back(val.As<std::string>());
                break;
                
            case  AnyValueType<amo::json>::value:
                json.push_back(val.As<amo::json>());
                break;
                
            default:
                break;
            }
            
            return;
        }
        
        void addAnyToJson(amo::json& json, const std::string& key, const Any& val) const  {
            switch (val.type()) {
            case  AnyValueType<Undefined>::value:
            case  AnyValueType<Nil>::value:
                json.put(key, val.toJson());
                break;
                
            case  AnyValueType<bool>::value:
                json.put(key, val.As<bool>());
                break;
                
            case  AnyValueType<int>::value:
                json.put(key, val.As<int>());
                break;
                
            case  AnyValueType<double>::value:
                json.put(key, val.As<double>());
                break;
                
            case  AnyValueType<std::string>::value:
                json.put(key, val.As<std::string>());
                break;
                
            case  AnyValueType<amo::json>::value:
                json.put(key, val.As<amo::json>());
                break;
                
            case  AnyValueType<std::vector<Any> >::value: {
                amo::json arr;
                arr.set_array();
                std::vector<Any> vec = val;
                
                for (size_t i = 0; i < vec.size(); ++i) {
                    addAnyToJsonArray(arr, vec[i]);
                }
                
                json.put(key, arr);
            }
            
            break;
            
            default:
                break;
            }
            
        }
        
    };
    
}

#endif // AMO_UTILITY_HPP2__

