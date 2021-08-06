#include "stdafx.h"

#include "ui/win/SharedMemory.h"

namespace amo {



    SharedMemory::~SharedMemory() {
        decInstanceCount();
    }
    
    SharedMemory::SharedMemory() : amo::file_mapping("ImeInstanceCount") {
        init_file_mapping();
        incInstanceCount();
    }
    
    char SharedMemory::getInstanceCount() {
        char count;
        read(&count, 1, 0);
        return count;
    }
    
    void SharedMemory::incInstanceCount() {
        char count = getInstanceCount();
        ++count;
        write(&count, 1, 0);
    }
    
    void SharedMemory::decInstanceCount() {
        char count = getInstanceCount();
        --count;
        write(&count, 1, 0);
    }
}