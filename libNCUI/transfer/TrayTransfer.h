// Created by amoylel on 06/26/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TRAYTRANSFER_H__
#define AMO_TRAYTRANSFER_H__


#include <amo/singleton.hpp>
#include "transfer/ClassTransfer.hpp"


namespace amo {
    class Tray;
    
    /**
     * @class	tray
     *
     * @extend Object
     *
     * @brief	���̲�����.<br>
     * 			�����̣߳�**UI�߳�**.
     *
     */
    
    class TrayTransfer
        : public ClassTransfer
        , public amo::singleton<TrayTransfer> {
    public:
    
        TrayTransfer();
        std::shared_ptr<amo::Tray> getTray()  ;
        void setTray(std::shared_ptr<amo::Tray> val);
        
        void onTrayEvent(const std::string& event);
        /*!
         * @fn	Any TrayTransfer::show(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	��ʾ����.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        			include('tray');
        			tray.show();
        		 ```
         */
        Any show(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any TrayTransfer::hide(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	��������.
         *
         * @return	��.
         * @example
         *
        			 ```
        				include('tray');
        				tray.hide();
        			 ```
         */
        Any hide(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any TrayTransfer::setIcon(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	��������ͼ��.
         *
         * @param	#String ͼ�걾��·��.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        			include('tray');
        			tray.setIcon('skin/logo1.ico');
        		 ```
         */
        Any setIcon(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any TrayTransfer::setTooltip(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	����������ʾ�ı�.
         *
         * @param	#String ��Ҫ��ʾ����ʾ�ı�.
         *
         * @return	��.
         *
         * @example
         *
        	 ```
        		include('tray');
        		tray.setTooltip(new Date().toString());
        	 ```
         */
        Any setTooltip(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any TrayTransfer::blink(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	��˸����.
         *
         * @param	#Boolean=false true��˸/falseֹͣ��˸.
         *
         * @return	��.
         *
         * @see isBlink=tray.isBlink
         * @example
         *
        	 ```
        		include('tray');
        		tray.blink(true);
        	 ```
         */
        Any blink(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any TrayTransfer::isBlink(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�ж������Ƿ���˸.
         *
         * @return	#Boolean.
         *
         * @see blink=tray.blink
         *
         * @example
         *
        		 ```
        			include('tray');
        			tray.blink(true);
        			console.assert(tray.isBlink() == true);
        			tray.blink(false);
        			console.assert(tray.isBlink() == false);
        		 ```
         */
        Any isBlink(IPCMessage::SmartType msg);
        
        
        /*!
        * @event	Any TrayTransfer::buttondown(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	����������ʱ����.
        *
        * @example
        *
        	```
        	include('tray');
        	tray.on('buttondown', function(){
        		console.log('buttondown');
        	});
        	```
        */
        
        /*!
        * @event	Any TrayTransfer::buttonup(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	����������ʱ����.
        *
        * @example
        *
        	```
        		include('tray');
        		tray.on('buttonup', function(){
        			console.log('buttonup');
        		});
        	```
        */
        
        /*!
        * @event	Any TrayTransfer::rbuttondown(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	����Ҽ�����ʱ����.
        *
        * @example
        *
        	```
        	include('tray');
        	tray.on('rbuttondown', function(){
        		console.log('rbuttondown');
        	});
        	```
        */
        
        /*!
        * @event	Any TrayTransfer::rbuttonup(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	����Ҽ�����ʱ����.
        *
        * @example
        *
        		```
        		include('tray');
        		tray.on('rbuttonup', function(){
        			console.log('rbuttonup');
        		});
        		```
        */
        
        /*!
        * @event	Any TrayTransfer::click(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	����������ʱ����.
        *
        * @example
        *
        		```
        		include('tray');
        		tray.on('click', function(){
        			console.log('click');
        		});
        		```
        */
        
        /*!
        * @event	Any TrayTransfer::dbclick(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	������˫��ʱ����.
        *
        * @example
        *
        	```
        	include('tray');
        	tray.on('dbclick', function(){
        		console.log('dbclick');
        	});
        	```
        */
        
        /*!
        * @event	Any TrayTransfer::mousehover(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	�����ͣʱ����.
        *
        * @example
        *
        	```
        	include('tray');
        	tray.on('mousehover', function(){
        		console.log('mousehover');
        	});
        	```
        */
        
        /*!
        * @event	Any TrayTransfer::mouseleave(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	����뿪ʱ����.
        *
        * @example
        *
        			```
        			include('tray');
        			tray.on('mouseleave', function(){
        				console.log('mouseleave');
        			});
        			```
        */
        
        
        
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