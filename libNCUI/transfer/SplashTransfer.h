// Created by amoylel on 10/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SPLASHTRANSFER_H__
#define AMO_SPLASHTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {
    class SplashWindow;
    class SplashWindowSettings;
    
    /*!
     * @class	splash
     *
     * @extend Object
     *
     * @brief	��������.<br>
     * 			�����̣߳�**UI�߳�**.
     */
    
    class SplashTransfer
        : public ClassTransfer
        , public amo::singleton<SplashTransfer> {
    public:
        SplashTransfer();
        ~SplashTransfer();
        
        void closeSplash(int nDelay = 0);
        
        void fadeout();
        /*!
         * @fn	Any SplashTransfer::show(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	��ʾSplash.
         *
         * @param	#JsonObject ��֧�ֵĲ�����{@link ��������=��������}.
         *
         * @return	��.
         *
         * @see hide=splash.hide
         * @example
         *
         ```
        	 include('splash');
        	 splash.show({
        		image: 'images/splash.jpg',
        		duration: 5000
        	 });
         ```
         */
        
        Any show(IPCMessage::SmartType msg);
        
        
        /*!
        * @fn	Any SplashTransfer::hide(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	n���������Splash��n��{@link show=splash.show}�����õ�fadeout����.
        *
        * @return	��.
        *
        * @example
        
        		```
        				include('splash');
        				splash.hide();
        		```
        */
        
        /*!
         * @fn	Any SplashTransfer::hide(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	n���������Splash.
         *
         * @param	#Int ָ����ʱʱ��n (����).
         *
         * @return	��.
         * @example
        
        		```
        				include('splash');
        				splash.hide(3000);
        		```
         */
        
        Any hide(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any SplashTransfer::isVisible(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	�ж�Splash�Ƿ�ɼ�.
         *
         * @return	#Boolean.
         * @example
        
        		```
        				include('splash');
        				console.assert(splash.isVisible() == false);
        		```
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
        
        /*! @brief	Splash�رն�ʱ��. */
        UINT_PTR m_splashTimer;
        
        /*! @brief	�رմ��ڵĶ���ʱ��. */
        int m_nDelay;
        
        /*! @brief	��ǰ��������ʣ�����. */
        int m_nfadeTimes;
    };
}

#endif // AMO_SPLASHTRANSFER_H__

