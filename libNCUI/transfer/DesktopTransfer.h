// Created by amoylel on 08/20/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DESKTOPTRANSFER_H__
#define AMO_DESKTOPTRANSFER_H__



#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {

    /*!
     * @class	desktop
     *
     * @brief	���ڻ�ȡ����Ļ�����Ϣ.
     */
    
    class DesktopTransfer
        : public ClassTransfer
        , public amo::singleton < DesktopTransfer > {
    public:
        DesktopTransfer();
        
        
        
        /*!
         * @fn	Any DesktopTransfer::getScreenInfo(IPCMessage::SmartType msg);
         *
         * @tag sync static
         *
         * @brief	��ȡ��Ļ��Ϣ,������Ļ��С�͹��������С.
         *
         * @return	#JsonObject.
         *
         * 			|#Int width  ������
         * 			|#Int height ����߶�
         * 			|#JsonObject rcWork ���湤��������Ϣ
         * 				||#Int left �����������Ͻ�����X
         * 				||#Int top �����������Ͻ�����Y
         * 				||#Int right �����������½�����X
         * 				||#Int bottom �����������½�����Y
         * 				||#Int width ����������
         * 				||#Int height ��������߶�
         *
         * @example
         *
        			 ```
        				include('desktop');
        				var desktopInfo = desktop.getScreenInfo();
        				console.log(desktopInfo);
        			 ```
         */
        
        Any getScreenInfo(IPCMessage::SmartType msg);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DesktopTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getScreenInfo, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
    };
}

#endif // AMO_DESKTOPTRANSFER_H__

