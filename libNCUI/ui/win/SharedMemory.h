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
        // ����:    ImeSharedMemory::GetInstanceCount
        // ����:    ��ȡʵ����
        // ����:    public
        // ����:    char
        // ����:
        //
        // ˵��:
        //
        //------------------------------------------------------------------------------
        char GetInstanceCount();
        
    protected:
        //------------------------------------------------------------------------------
        // ����:    ImeSharedMemory::IncInstanceCount
        // ����:    ʵ���Լ�1
        // ����:    protected
        // ����:    void
        // ����:
        //
        // ˵��:
        //
        //------------------------------------------------------------------------------
        void IncInstanceCount();
        
        //------------------------------------------------------------------------------
        // ����:    ImeSharedMemory::DecInstanceCount
        // ����:    ʵ���Լ�1
        // ����:    protected
        // ����:    void
        // ����:
        //
        // ˵��:
        //
        //------------------------------------------------------------------------------
        void DecInstanceCount();
    private:
    
    };
    
}
#endif // AMO_SHAREDMEMORY_H__
