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
        
        
        static  void addAnyToJsonArray(amo::json& json, const Any& val)   {
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
        
        static  void addAnyToJson(amo::json& json, const std::string& key,
                                  const Any& val)   {
            switch (val.type()) {
            case  AnyValueType<Undefined>::value: {
                amo::json child = val.toJson();
                child.put("a02c2b36-3d70-44f6-9456-85dab0e0ddb5", 0);
                json.put(key, child);
                break;
            }
            
            case  AnyValueType<Nil>::value: {
                amo::json child = val.toJson();
                child.put("a02c2b36-3d70-44f6-9456-85dab0e0ddb5", 1);
                json.put(key, child);
                break;
            }
            
            
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
        
        static Any jsonToAny(const amo::json& json)   {
            if (json.is_bool()) {
                return json.get<bool>();
            } else if (json.is_int()) {
                return json.get<int>();
            }  else if (json.is_int64()) {
                return json.get<int64_t>();
            } else if (json.is_double()) {
                return json.get<double>();
            } else if (json.is_string()) {
                return json.get<std::string>();
            } else if (json.is_object()) {
                return json;
            } else {
                return Undefined();
            }
        }
        static  Any jsonToAny(const amo::json& json, const std::string& key)  {
            amo::json val = json.getJson(key);
            return jsonToAny(val);
            
        }
    };
    
}

#endif // AMO_UTILITY_HPP2__

