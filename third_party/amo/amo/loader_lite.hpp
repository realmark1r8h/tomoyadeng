// Created by amoylel on 11/23/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_LOADER_LITE_HPP__
#define AMO_LOADER_LITE_HPP__

#include <string>
#include <windows.h>

namespace amo {
    class loader_lite {
    public:
        loader_lite() {
            lib_handle = NULL;
        }
        
        ~loader_lite() {
            unload();
        }
        
        bool has_symbol(const std::string& func_name) {
            return  load_symbol(func_name) != NULL;
        }
        
        
        bool load(const std::string& lib_name) {
        
            lib_handle = LoadLibraryExA(lib_name.c_str(),
                                        NULL,
                                        LOAD_WITH_ALTERED_SEARCH_PATH);
                                        
            return lib_handle != NULL;
        }
        
        void unload() {
            if (!is_loaded()) {
                return;
            }
            
            
            FreeLibrary((HMODULE)lib_handle);
            
            lib_handle = NULL;
        }
        
        
        void* load_symbol(const std::string& fun_name) {
            return (void *)GetProcAddress((HMODULE)lib_handle,
                                          fun_name.c_str());
        }
        
        bool is_loaded() const {
            return lib_handle != NULL;
        }
        
    private:
        void* lib_handle;
    };
    
    
}

#endif // AMO_LOADER_LITE_HPP__