// Created by amoylel on 08/29/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SHAREDMEMORY_H__
#define AMO_SHAREDMEMORY_H__





#include <amo/singleton.hpp>
#include <amo/file_mapping.hpp>

namespace amo {


    class ImeSharedMemory : public amo::file_mapping
        , public amo::singleton < ImeSharedMemory > {
    public:
        ImeSharedMemory();
        
        ~ImeSharedMemory();
        
        //------------------------------------------------------------------------------
        // 方法:    ImeSharedMemory::GetInstanceCount
        // 功能:    获取实例数
        // 访问:    public
        // 返回:    char
        // 参数:
        //
        // 说明:
        //
        //------------------------------------------------------------------------------
        char GetInstanceCount();
        
    protected:
        //------------------------------------------------------------------------------
        // 方法:    ImeSharedMemory::IncInstanceCount
        // 功能:    实例自加1
        // 访问:    protected
        // 返回:    void
        // 参数:
        //
        // 说明:
        //
        //------------------------------------------------------------------------------
        void IncInstanceCount();
        
        //------------------------------------------------------------------------------
        // 方法:    ImeSharedMemory::DecInstanceCount
        // 功能:    实例自减1
        // 访问:    protected
        // 返回:    void
        // 参数:
        //
        // 说明:
        //
        //------------------------------------------------------------------------------
        void DecInstanceCount();
    private:
    
    };
    
}
#endif // AMO_SHAREDMEMORY_H__
