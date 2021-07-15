// Created by amoylel on 10/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SPLASHTRANSFER_H__
#define AMO_SPLASHTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {
    class SplashWindow;
    class SplashWindowSettings;
    
    class SplashTransfer
        : public ClassTransfer
        , public amo::singleton<SplashTransfer> {
    public:
        SplashTransfer();
        ~SplashTransfer();
        
        void closeSplash();
        /*!
         * @fn	Any SplashTransfer::show(IPCMessage::SmartType msg);
         *
         * @brief	显示Splash.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any show(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any SplashTransfer::hide(IPCMessage::SmartType msg);
         *
         * @brief	隐藏Splash.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any hide(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any SplashTransfer::isVisible(IPCMessage::SmartType msg);
         *
         * @brief	判断Splash是否可见.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any isVisible(IPCMessage::SmartType msg);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(SplashTransfer, ClassTransfer)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(show, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(hide, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isVisible, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
        void create(std::shared_ptr<SplashWindowSettings> pSettings);
    protected:
        /*! @brief	The splash window. */
        SplashWindow* m_pSplashWindow;
        
        /*! @brief	Splash显示定时器. */
        UINT_PTR m_splashTimer;
    };
}

#endif // AMO_SPLASHTRANSFER_H__

