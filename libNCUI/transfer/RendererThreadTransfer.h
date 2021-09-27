// Created by amoylel on 10/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_RENDERERTHREADTRANSFER_H__
#define AMO_RENDERERTHREADTRANSFER_H__

#include "transfer/ThreadTransfer.hpp"

namespace amo {

    class RendererThreadTransfer : public ThreadTransfer<ThreadRenderer> {
    public:
        RendererThreadTransfer();
        Any onCreateClass(IPCMessage::SmartType msg);
    };
    
}

#endif AMO_RENDERERTHREADTRANSFER_H__