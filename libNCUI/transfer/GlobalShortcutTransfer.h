// Created by amoylel on 06/26/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_GLOBALSHORTCUTTRANSFER_H__
#define AMO_GLOBALSHORTCUTTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {

    /*!
     * @class	globalShortcut
     *
     * @brief	ȫ�ֿ�ݼ�.<br>
     * 			�����߳� **UI�߳�**
     */
    
    class GlobalShortcutTransfer
        : public ClassTransfer
        , public amo::singleton<GlobalShortcutTransfer> {
    public:
    
        GlobalShortcutTransfer();
        
        /*!
         * @fn	Any GlobalShortcutTransfer::registerShortcut(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	ͨ����ϼ�ע���ݼ�.
         *
         * @param	#String �ַ���.
         *
         * @return	#Int ��ݼ�ID �� ������ֵΪ0ʱ��ʾע��ʧ��.
         * @example
         *
        		```
        			include('globalShortcut');
        			var hotkey = globalShortcut.registerShortcut('MOD_CONTROL+MOD_ALT+D');
        			console.log(hotkey);
        			console.assert(hotkey != 0);
        
        		```
         */
        
        /*!
        * @fn	Any GlobalShortcutTransfer::registerShortcut(IPCMessage::SmartType msg);
        *
        * @tag static sync
        *
        * @brief	ע���ݼ�.
        *
        * @param	#JsonObject �ַ���.<br>
        * 						[**Boolean**] ctrl		�����ϵ�CTRL������Ĭ��Ϊfalse, ��Ӧ�ַ���MOD_CONTROL.<br>
        * 						[**Boolean**] win		�����ϵ�WIN������Ĭ��Ϊfalse, ��Ӧ�ַ���MOD_WIN.<br>
        * 						[**Boolean**] alt		�����ϵ�ALT������Ĭ��Ϊfalse, ��Ӧ�ַ���MOD_ALT.<br>
        * 						[**Boolean**] shift		�����ϵ�SHIFT������Ĭ��Ϊfalse, ��Ӧ�ַ���MOD_SHIFT.<br>
        * 						[**String**]  key		�����ϵ���ĸ�����ְ�����һ���ַ�.<br>
        * 						[**String**]  action	��ǰ��ݼ���������{@link Ԥ�����¼�=Ԥ���¼�}.<br>
        *
        *
        * @return	#Int ��ݼ�ID�� ������ֵΪ0ʱ��ʾע��ʧ��.
        *
        * @example
        *
        			```
        			include('globalShortcut');
        			var hotkey = globalShortcut.registerShortcut({ ctrl: true, alt: true, key: 'O', action: 'toggleVisible' });
        			console.log(hotkey);
        			// ����Ctrl+Atl+O������ʾ�����ص�ǰ����
        			console.assert(hotkey != 0);
        
        			```
        */
        
        Any registerShortcut(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any GlobalShortcutTransfer::isRegistered(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	ͨ��ID�жϿ�ݼ��Ƿ�ע��.
         *
         * @param	#Int ��ݼ�ID.
         *
         * @return	��.
         *
         * @example
         *
        			 ```
        				include('globalShortcut');
        				var hotkey = globalShortcut.registerShortcut('MOD_CONTROL+MOD_ALT+M');
        				console.assert(globalShortcut.isRegistered(hotkey) == true);
        
        			 ```
         */
        
        /*!
        * @fn	Any GlobalShortcutTransfer::isRegistered(IPCMessage::SmartType msg);
        * @tag static
        * @brief	ͨ����ϼ��жϿ�ݼ��Ƿ�ע��.
        *
        * @param	#String ��ϼ�.
        *
        * @return	��.
        * @example
        *
        			```
        				include('globalShortcut');
        				var hotkey = globalShortcut.registerShortcut('MOD_CONTROL+MOD_ALT+M');
        				console.assert(globalShortcut.isRegistered('MOD_CONTROL+MOD_ALT+M') == true);
        			```
        
        */
        
        Any isRegistered(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any GlobalShortcutTransfer::unregisterShortcut(IPCMessage::SmartType msg);
         * @tag static
         * @brief	ͨ��IDע����ݼ�.
         *
         * @param	#Int ��ݼ�ID.
         *
         * @return	��.
         */
        
        /*!
        * @fn	Any GlobalShortcutTransfer::unregisterShortcut(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	ͨ����ϼ�ע����ݼ�.
        *
        * @param	#String ��ϼ�����ɵ��ַ���.
        *
        * @return	��.
        * @example
        *
        		```
        			include('globalShortcut');
        			var hotkey = globalShortcut.registerShortcut('MOD_CONTROL+MOD_ALT+N');
        			console.assert(globalShortcut.isRegistered('MOD_CONTROL+MOD_ALT+N') == true);
        
        			globalShortcut.unregisterShortcut('MOD_CONTROL+MOD_ALT+N');
        			console.assert(globalShortcut.isRegistered('MOD_CONTROL+MOD_ALT+N') == false);
        
        		```
        */
        
        Any unregisterShortcut(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any GlobalShortcutTransfer::unregisterAll(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	ע�����п�ݼ�.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        			 include('globalShortcut');
        			 globalShortcut.unregisterAll();
        		 ```
         */
        
        Any unregisterAll(IPCMessage::SmartType msg);
        
        
        /*!
        * @event	Any GlobalShortcutTransfer::hotkeydown(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	��ݼ��¼�������������ע��Ŀ�ݼ�ʱ�����¼��ᱻ����.
        * 			�������ע���ݼ�ʱָ����action���Ҹ�action�ܱ���������ô�ÿ�ݼ����¼����ᱻ����.
        *
        * @param	#Int ��ݼ�ID
        *
        * @param	#JsonObject ��ݼ������Ϣ
        * 				[**Boolean**] ctrl		�����ϵ�CTRL������ ��Ӧ�ַ���MOD_CONTROL.<br>
        * 				[**Boolean**] win		�����ϵ�WIN������ ��Ӧ�ַ���MOD_WIN.<br>
        * 				[**Boolean**] alt		�����ϵ�ALT������ ��Ӧ�ַ���MOD_ALT.<br>
        * 				[**Boolean**] shift		�����ϵ�SHIFT����, ��Ӧ�ַ���MOD_SHIFT.<br>
        * 				[**String**]  key		�����ϵ���ĸ�����ְ�����һ���ַ�.<br>
        * 				[**String**]  action	��ǰ��ݼ���������{@link Ԥ�����¼�=Ԥ���¼�}.<br>
        *
        * @example
        *
        	```
        	include('globalShortcut');
        	globalShortcut.on('hotkeydown', function(hotkey){
        		console.log(hotkey);
        	});
        	```
        */
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(GlobalShortcutTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(registerShortcut, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isRegistered, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(unregisterShortcut, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(unregisterAll, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
    };
}


#endif // AMO_GLOBALSHORTCUTTRANSFER_H__