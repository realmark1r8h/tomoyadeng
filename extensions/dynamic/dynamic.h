// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DYNAMIC_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DYNAMIC_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef DYNAMIC_EXPORTS
#define DYNAMIC_API __declspec(dllexport)
#else
#define DYNAMIC_API __declspec(dllimport)
#endif

#include "transfer/ClassTransfer.hpp"

extern "C" {
    DYNAMIC_API int fndynamic(void);
    DYNAMIC_API bool registerTransfer(int nBrowserID, std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fn);
}

namespace amo {



    class DynamicTransfer : public ClassTransfer {
    public:
    
        DynamicTransfer();
        ~DynamicTransfer();
        amo::Any foo1(IPCMessage::SmartType anyMessage);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DynamicTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(foo1, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
    };
}