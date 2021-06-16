#include "stdafx.h"

#include "ui/win/SharedMemory.h"

namespace amo {



    ImeSharedMemory::~ImeSharedMemory() {
        DecInstanceCount();
    }
    
    ImeSharedMemory::ImeSharedMemory() : amo::file_mapping("ImeInstanceCount") {
        init_file_mapping();
        IncInstanceCount();
    }
    
    char ImeSharedMemory::GetInstanceCount() {
        char count;
        read(&count, 1, 0);
        return count;
    }
    
    void ImeSharedMemory::IncInstanceCount() {
        char count = GetInstanceCount();
        ++count;
        write(&count, 1, 0);
    }
    
    void ImeSharedMemory::DecInstanceCount() {
        char count = GetInstanceCount();
        --count;
        write(&count, 1, 0);
    }
}