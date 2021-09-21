#ifndef PathTransfer_h__
#define PathTransfer_h__


#include <transfer/ClassTransfer.hpp>
namespace amo {

    class path;
    class PathTransfer : public ClassTransfer {
    public:
    
        PathTransfer();
        PathTransfer(const std::string& ansiPath);
        ~PathTransfer();
        
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        
        
        Any toString(IPCMessage::SmartType msg);
        Any isExsit(IPCMessage::SmartType msg);
        Any append(IPCMessage::SmartType msg);
        Any removeFileSpec(IPCMessage::SmartType msg);
        
        
        // ��̬����
        Any getFullAppDir(IPCMessage::SmartType msg);
        Any getFullAppName(IPCMessage::SmartType msg);
        
        
    public:
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(PathTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(toString, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isExsit, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(append, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeFileSpec, TransferFuncNormal | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getFullAppDir, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getFullAppName, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        std::shared_ptr<amo::path>  m_pPath;
        
    };
}

#endif // PathTransfer_h__