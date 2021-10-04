// Created by amoylel on 10/31/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_REGISTRY_HPP__
#define AMO_REGISTRY_HPP__

#include <string>

namespace amo {
    class registry_key {
    
    };
    class registry {
    public:
        const static registry_key ClassesRoot;
    public:
        template<typename R>
        R read(const std::string& keyName, const std::string& valueName, R defaultValue = R()) {
            return defaultValue;
        }
        
        template<typename T>
        void write(const std::string& keyName, const std::string valueName, const T& value) {
            return;
        }
        
    };
}
#endif // AMO_REGISTRY_HPP__