// Created by amoylel on 17/03/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBSEXT_PATHTRANSFER_F5089CC4_51A8_4448_BB3D_04242220BFA0_H__
#define LIBSEXT_PATHTRANSFER_F5089CC4_51A8_4448_BB3D_04242220BFA0_H__







#include <transfer/RunnableTransfer.hpp>
namespace amo {

    class path;
    class PathTransfer
        : public RunnableTransfer
        , public amo::singleton<PathTransfer> {
    public:
    
        PathTransfer();
        PathTransfer(const std::string& ansiPath);
        ~PathTransfer();
        
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override;
        virtual Transfer* getInterface(const std::string& name) override;
        
        Any toString(IPCMessage::SmartType msg);
        Any isExsit(IPCMessage::SmartType msg);
        Any append(IPCMessage::SmartType msg);
        Any removeFileSpec(IPCMessage::SmartType msg);
        
        
        // ¾²Ì¬º¯Êý
        Any getFullAppDir(IPCMessage::SmartType msg);
        Any getFullAppName(IPCMessage::SmartType msg);
        
        Any fileExsit(IPCMessage::SmartType msg);
        Any remove(IPCMessage::SmartType msg);
        Any removeAll(IPCMessage::SmartType msg);
        
        
    public:
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(PathTransfer, RunnableTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(toString, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isExsit, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(append, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeFileSpec,
                                      TransferFuncNormal | TransferExecSync)
                                      
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getFullAppDir,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getFullAppName,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(fileExsit, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(remove, TransferFuncStatic | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeAll,
                                      TransferFuncStatic | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        std::shared_ptr<amo::path>  m_pPath;
        
    };
}

#endif //LIBSEXT_PATHTRANSFER_F5089CC4_51A8_4448_BB3D_04242220BFA0_H__