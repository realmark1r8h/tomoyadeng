// Created by amoylel on 11/18/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_BIGSTRING_175D0A11_ABEA_4E40_AF06_FF55E69E1329_H__
#define AMO_BIGSTRING_175D0A11_ABEA_4E40_AF06_FF55E69E1329_H__



#include <amo/singleton.hpp>
#include <amo/blob.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {

    /*!
    * @class	desktop
    *
    * @extend Object
    *
    * @brief	���ڻ�ȡ����Ļ�����Ϣ.<br>
    * 			�����߳�:**UI�߳�**.
    */
    
    class BigStringTransfer
        : public ClassTransfer
        , public amo::singleton < BigStringTransfer > {
    public:
        BigStringTransfer();
        BigStringTransfer(const std::string& str, const int32_t delay_destroy);
        Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override;
        virtual Transfer* getInterface(const std::string& name) override;
        
        Any getData(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(BigStringTransfer, ClassTransfer)
        // ��Ա����
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getData, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
    
    
    
    };
}

#endif // AMO_BIGSTRING_175D0A11_ABEA_4E40_AF06_FF55E69E1329_H__

