// Created by amoylel on 07/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_FRAMETRANSFER_H__
#define AMO_FRAMETRANSFER_H__

#include <amo/singleton.hpp>
#include "handler/CefHeader.hpp"
#include "transfer/ClassTransfer.hpp"


namespace amo {

    /*!
     * @class	Frame
     *
     * @chapter cef
     *
     * @extend Object
     *
     * @brief	CEF Frame ��װ.<br>
     * 			�����̣߳�**UI�߳�**.
     */
    
    class FrameTransfer
        : public ClassTransfer
        , public amo::singleton < FrameTransfer > {
    public:
        FrameTransfer();
        FrameTransfer(CefRefPtr<CefFrame> pFrame);
        
        Any current(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::injectSrcipt(IPCMessage::SmartType msg);
         *
         * @brief	��ҳ��ע��JS����.
         *
         * @param	#String JS����.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any injectSrcipt(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::injectCSS(IPCMessage::SmartType msg);
         *
         * @brief	��ҳ��ע��CSS����.
         *
         * @param	#String CSS����.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any injectCSS(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::IsValid(IPCMessage::SmartType msg);
         *
         * @brief	��ǰҳ���Ƿ���Ч.
         *
         *
         * @return	#Boolean true��Ч/false��Ч.
         */
        
        Any IsValid(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Undo(IPCMessage::SmartType msg);
         *
         * @brief	����.
         *
         * @return	��.
         */
        
        Any Undo(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Redo(IPCMessage::SmartType msg);
         *
         * @brief	����.
         *
         * @return	��.
         */
        
        Any Redo(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Cut(IPCMessage::SmartType msg);
         *
         * @brief	����.
         *
         *
         * @return	��.
         */
        
        Any Cut(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Copy(IPCMessage::SmartType msg);
         *
         * @brief	����.
         *
         *
         * @return	��.
         */
        
        Any Copy(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Paste(IPCMessage::SmartType msg);
         *
         * @brief	ճ��.
         *
         *
         * @return	��.
         */
        
        Any Paste(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::Delete(IPCMessage::SmartType msg);
         *
         * @brief	ɾ��.
         *
         *
         * @return	��.
         */
        
        Any Delete(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::SelectAll(IPCMessage::SmartType msg);
         *
         * @brief	ȫѡ.
         *
         * @return	��.
         */
        
        Any SelectAll(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::ViewSource(IPCMessage::SmartType msg);
         *
         * @brief	�鿴��ҳԴ����.
         *
         * @return	��.
         */
        
        Any ViewSource(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetSource(IPCMessage::SmartType msg);
         *
         * @ignore
         *
         * @brief	��ȡ��ҳԴ����.
         *
         *
         * @return	#String.
         */
        
        Any GetSource(IPCMessage::SmartType msg);
        Any GetText(IPCMessage::SmartType msg);
        Any LoadRequest(IPCMessage::SmartType msg) ;
        
        /*!
         * @fn	Any FrameTransfer::LoadURL(IPCMessage::SmartType msg);
         *
         * @brief	����URL.
         *
         * @param	#String URL.
         *
         * @return	��.
         */
        
        Any LoadURL(IPCMessage::SmartType msg) ;
        Any LoadString(IPCMessage::SmartType msg) ;
        
        /*!
         * @fn	Any FrameTransfer::IsMain(IPCMessage::SmartType msg);
         *
         * @brief	��ǰҳ���Ƿ�Ϊ��ҳ��.
         *
         *
         * @return	#Boolean.
         */
        
        Any IsMain(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::IsFocused(IPCMessage::SmartType msg);
         *
         * @brief	��ǰҳ���Ƿ��ý���.
         *
         * @return	#Boolean.
         */
        
        Any IsFocused(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetName(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ��ǰҳ�������.
         *
         * @return	#String ҳ������.
         */
        
        Any GetName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetIdentifier(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ��ǰҳ���ID.
         *
         *
         * @return	#Int identifier.
         */
        
        Any GetIdentifier(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetParent(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ��ǰҳ��ĸ�ҳ��.
         *
         * @return	#Frame .
         */
        
        Any GetParent(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetURL(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ��ǰҳ���URL.
         *
         * @return	#String url.
         */
        
        Any GetURL(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::GetBrowser(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ��ǰҳ��������Browser����.
         *
         * @return	#Browser .
         */
        
        Any GetBrowser(IPCMessage::SmartType msg);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(FrameTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(current,
                                      TransferFuncConstProperty | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(injectSrcipt, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsValid, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Undo, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Redo, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Cut, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Copy, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Paste, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Delete, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(SelectAll, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(ViewSource, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetSource, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetText, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(LoadRequest, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(LoadURL, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(LoadString, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsMain, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsFocused, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetName, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetIdentifier, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetParent, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetURL, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetBrowser, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        CefRefPtr<CefFrame> m_pFrame;
    };
}

#endif // AMO_FRAMETRANSFER_H__
