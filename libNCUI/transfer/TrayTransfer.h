// Created by amoylel on 06/26/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TRAYTRANSFER_H__
#define AMO_TRAYTRANSFER_H__


#include <amo/singleton.hpp>
#include "transfer/ClassTransfer.hpp"


namespace amo {
    class Tray;
    class TrayTransfer
        : public ClassTransfer
        , public amo::singleton<TrayTransfer> {
    public:
    
        TrayTransfer();
        
        void onTrayEvent(const std::string& event);
        /*!
         * @fn	Any TrayTransfer::show(IPCMessage::SmartType msg);
         *
         * @brief	œ‘ æÕ–≈Ã.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any show(IPCMessage::SmartType msg);
        /*!
         * @fn	Any TrayTransfer::hide(IPCMessage::SmartType msg);
         *
         * @brief	“˛≤ÿÕ–≈Ã.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any hide(IPCMessage::SmartType msg);
        /*!
         * @fn	Any TrayTransfer::setIcon(IPCMessage::SmartType msg);
         *
         * @brief	…Ë÷√Õ–≈ÃÕº±Í.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setIcon(IPCMessage::SmartType msg);
        /*!
         * @fn	Any TrayTransfer::setTooltip(IPCMessage::SmartType msg);
         *
         * @brief	…Ë÷√Õ–≈ÃÃ· æŒƒ±æ.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setTooltip(IPCMessage::SmartType msg);
        /*!
         * @fn	Any TrayTransfer::blink(IPCMessage::SmartType msg);
         *
         * @brief	…¡À∏Õ–≈Ã.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any blink(IPCMessage::SmartType msg);
        /*!
         * @fn	Any TrayTransfer::isBlink(IPCMessage::SmartType msg);
         *
         * @brief	≈–∂œÕ–≈Ã «∑Ò…¡À∏.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isBlink(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(TrayTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(show, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(hide, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setIcon, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setTooltip, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(blink, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isBlink, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
        std::shared_ptr<Tray> m_pTray;
        
    };
}


#endif // AMO_TRAYTRANSFER_H__