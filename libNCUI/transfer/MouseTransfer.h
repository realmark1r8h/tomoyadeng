// Created by amoylel on 08/20/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_MOUSETRANSFER_H__
#define AMO_MOUSETRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {

    /*!
     * @class	mouse
     *
     * @extend Object
     *
     * @brief	��������,���к�����Ϊ��̬����.<br>
     * 			�����̣߳�**UI�߳�**.
     */
    
    class MouseTransfer
        : public ClassTransfer
        , public amo::singleton < MouseTransfer > {
    public:
        MouseTransfer();
        
        /*!
        * @fn	Any MouseTransfer::click(IPCMessage::SmartType msg);
        *
        * @brief	����������.
        *
        * @param	#Int=0 x����
        * @param	#Int=0 y����
        *
        * @return	��.
        *
        * @see leftClick=mouse.leftClick
        *
        * @example
        *
        		```
        			includes('BrowserWindow','mouse');
        			var win = BrowserWindow.current;
        			// ��ȡ��󻯰�ť��λ��
        			var winRect = win.getWindowRect();
        			var x = winRect.r - 50;
        			var y = winRect.y + 10;
        			// �����󻯰�ť
        			mouse.click(x,y);
        		```
        */
        
        Any click(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::leftClick(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�������.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         *
         * @see click=mouse.click
         */
        
        Any leftClick(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::leftDown(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�������.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         * @example
         *
        			 ```
        			 includes('BrowserWindow','mouse');
        			 var win = BrowserWindow.current;
        
        
        			 var winRect = win.getWindowRect();
        			 var x = winRect.r - winRect.width / 2;
        			 var y = winRect.y + 20;
        
        			 // �ƶ��������
        			 mouse.moveTo(x, y);
        			 mouse.leftDown(x,y);
        			 ```
         */
        
        Any leftDown(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::leftUp(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�������.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         */
        
        Any leftUp(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::leftDoubleClick(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	˫�����.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        		 includes('BrowserWindow','mouse');
        		 var win = BrowserWindow.current;
        
        
        		 var winRect = win.getWindowRect();
        		 var x = winRect.r - winRect.width / 2;
        		 var y = winRect.y + 20;
        
        		 // ˫����������󻯴���
        		 mouse.moveTo(x, y)
        		 mouse.leftDoubleClick(x, y);
        		 ```
         */
        
        Any leftDoubleClick(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::rightClick(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�����Ҽ�.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         * @example
         *
        		 ```
        		 includes('BrowserWindow','mouse');
        		 var win = BrowserWindow.current;
        
        		 // ��ȡ��󻯰�ť��λ��
        		 var winRect = win.getWindowRect();
        		 var x = winRect.x + 150;
        		 var y = winRect.y + 20;
        
        		 // �Ҽ�
        		 mouse.rightClick(x,y);
        		 ```
         */
        
        Any rightClick(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::rightDown(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�����Ҽ�.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         */
        
        Any rightDown(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::rightUp(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�����Ҽ�.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         */
        
        Any rightUp(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::middleClick(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�����м�.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         * @example
         *
        		 ```
        		 includes('BrowserWindow','mouse');
        		 var win = BrowserWindow.current;
        
        
        		 var winRect = win.getWindowRect();
        		 var x = winRect.r - 500;
        		 var y = winRect.y + winRect.height / 2;
        
        		 //
        		 mouse.moveTo(x, y);
        		 mouse.middleClick(x, y);
        		 ```
         */
        
        Any middleClick(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::moveTo(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�ƶ���굽ָ��λ��.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         * @example
         *
        		 ```
        		 includes('BrowserWindow','mouse');
        		 var win = BrowserWindow.current;
        
        
        		 var winRect = win.getWindowRect();
        		 var x = winRect.r - 50;
        		 var y = winRect.y + 20;
        
        		 //
        		 mouse.moveTo(x, y);
        		 ```
         */
        
        Any moveTo(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::moveR(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�ƶ���굽��ǰλ�õ����λ��.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         *
         * @example
         *
        			 ```
        			 includes('BrowserWindow','mouse');
        			 var win = BrowserWindow.current;
        
        
        			 var winRect = win.getWindowRect();
        			 var x = 100;
        			 var y = 0;
        
        			 //
        			 mouse.moveR(x, y);
        			 ```
         */
        
        Any moveR(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::mouseWheel(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	������.
         *
         * @param	#Int=0 ƫ���� >0 ʱ���Ϲ�����<0ʱ���¹���.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        		 include('mouse');
        		 mouse.mouseWheel(100);
        		 ```
         */
        
        Any mouseWheel(IPCMessage::SmartType msg);
        
        /*!
        * @fn	Any MouseTransfer::saveMousePos(IPCMessage::SmartType msg);
        *
        * @tag static
        *
        * @brief	���浱ǰ���λ��.
        *
        * @return	��.
        * @example
        *
        			```
        			include('mouse');
        			mouse.saveMousePos();
        			```
        */
        
        /*!
         * @fn	Any MouseTransfer::saveMousePos(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	����ָ�����λ��.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	��.
         * @example
         *
        		 ```
        		 include('mouse');
        		 mouse.saveMousePos(100, 100);
        		 ```
         */
        
        Any saveMousePos(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::restoreMousePos(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�ƶ���굽�ϴα�������λ��.
         *
         * @return	��.
         * @example
         *
        			 ```
        			 include('mouse');
        			 mouse.restoreMousePos();
        			 ```
         */
        
        Any restoreMousePos(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::lockMouse(IPCMessage::SmartType msg);
         *
         * @brief	������꣬��ֹ������깦�ܣ�δʵ�֣�.
         *
         * @return	��.
         */
        
        Any lockMouse(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::unlockMouse(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	������꣨δʵ�֣�.
         * s
         * @return	��.
         */
        
        Any unlockMouse(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::waitClick(IPCMessage::SmartType msg);
         *
         * @brief	�ȴ�һ������¼���δʵ�֣�.
         *
         * @return	��.
         */
        
        Any waitClick(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::getLastClick(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ��һ�ΰ�������갴����δʵ�֣�.
         *
         *
         * @return	The last click.
         */
        
        Any getLastClick(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::getCursorPos(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ��ǰ�������Ļ�ϵ�λ��.
         *
         *
         * @return	#JsonObject.
         * 			|#Int x ���x������.
         * 			|#Int y ���y������.
         * @example
         *
        		 ```
        		 include('mouse');
        		 var pos = mouse.getCursorPos();
        		 console.log(pos);
        		 ```
         */
        
        Any getCursorPos(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::setCursorPos(IPCMessage::SmartType msg);
         *
         * @brief	�������λ��.
         *
         * @param	#Int=0 x x������.
         * @param	#Int=0 y y������
         *
         * @return	��.
         *
         * @see moveTo=mouse.moveTo
         *
         * @example
         *
        			 ```
        			 include('mouse');
        			 mouse.setCursorPos(100,100);
        			 ```
         */
        
        Any setCursorPos(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::screenToClient(IPCMessage::SmartType msg);
         *
         * @brief	��һ����Ļ����ת��Ϊ��ǰ��������.
         *
         * @param	#Int=0 x����.
         * @param	#Int=0 y����.
         *
         * @return	#JsonObject.
         * 			|#Int x ת�����x����
         * 			|#Int y ת�����y����
         * @example
         *
        			 ```
        			 include('mouse');
        			 var pos = mouse.screenToClient(100,100);
        			 console.log(pos);
        			 ```
        
         */
        
        /*!
        * @fn	Any MouseTransfer::screenToClient(IPCMessage::SmartType msg);
        *
        * @brief	��һ����Ļ����ת��Ϊָ����������.
        *
        * @param	#BrowserWindow ���ڶ���
        * @param	#Int=0 x����.
        * @param	#Int=0 y����.
        *
        * @return	#JsonObject.
        * 			|#Int x ת�����x����
        * 			|#Int y ת�����y����
        *
        * @example
        *
        			```
        			includes('BrowserWindow', 'mouse');
        			var win = BrowserWindow.current;
        			var pos = mouse.screenToClient(win, 100, 100);
        			console.log(pos);
        			```
        */
        
        
        Any screenToClient(IPCMessage::SmartType msg);
        
        
        /*!
        * @fn	Any MouseTransfer::clientToScreen(IPCMessage::SmartType msg);
        *
        * @brief	����ǰ��������ת��Ϊ��Ļ����.
        *
        * @param	#Int=0 x����.
        * @param	#Int=0 y����.
        *
        * @return	#JsonObject.
        * 			|#Int x ת�����x����
        * 			|#Int y ת�����y����
        * @example
        *
        			```
        			include('mouse');
        			var pos = mouse.clientToScreen(100,100);
        			console.log(pos);
        			```
        
        */
        
        /*!
        * @fn	Any MouseTransfer::clientToScreen(IPCMessage::SmartType msg);
        *
        * @brief	��һ��ָ����������ת��Ϊ��Ļ����.
        *
        * @param	#BrowserWindow ���ڶ���
        * @param	#Int=0 x����.
        * @param	#Int=0 y����.
        *
        * @return	#JsonObject.
        * 			|#Int x ת�����x����
        * 			|#Int y ת�����y����
        *
        * @example
        *
        		```
        		includes('BrowserWindow', 'mouse');
        		var win = BrowserWindow.current;
        		var pos = mouse.clientToScreen(win, 100, 100);
        		console.log(pos);
        		```
        */
        
        
        Any clientToScreen(IPCMessage::SmartType msg);
        
        
        
        /*!
         * @fn	Any MouseTransfer::hideCursor(IPCMessage::SmartType msg);
         *
         * @brief	������ֻ꣬�Ե�ǰ���򴰿���Ч.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        		 includes('mouse');
        		 mouse.hideCursor();
        		 setTimeout(function(){
        			mouse.showCursor();
        		 }, 5000);
        		 ```
         */
        
        Any hideCursor(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any MouseTransfer::showCursor(IPCMessage::SmartType msg);
         *
         * @brief	��ʾ���.
         *
         * @return	��.
         *
         * @example
         *
        			 ```
        			 includes('mouse');
        			 mouse.showCursor();
        			 ```
         */
        
        Any showCursor(IPCMessage::SmartType msg);
        
        
        /*!
        * @event	Any MouseTransfer::showCursor(IPCMessage::SmartType msg);
        *
        * @brief	��ʾ���.
        *
        *
        * @example
        *
        			```
        			includes('mouse');
        			mouse.showCursor();
        			```
        */
        
        /*!
        * @event	Any MouseTransfer::clientToScreen(IPCMessage::SmartType msg);
        *
        * @brief	��һ��ָ����������ת��Ϊ��Ļ����.
        *
        * @param	#BrowserWindow ���ڶ���
        * @param	#Int=0 x����.
        * @param	#Int=0 y����.
        *
        * @return	#JsonObject.
        * 			|#Int x ת�����x����
        * 			|#Int y ת�����y����
        *
        * @example
        *
        ```
        includes('BrowserWindow', 'mouse');
        var win = BrowserWindow.current;
        var pos = mouse.clientToScreen(win, 100, 100);
        console.log(pos);
        ```
        */
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(MouseTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(leftClick, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(leftDown, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(leftUp, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(leftDoubleClick, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(rightClick, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(rightDown, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(rightUp, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(middleClick, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(moveTo, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(moveR, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(mouseWheel, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(saveMousePos, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(restoreMousePos, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(lockMouse, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(unlockMouse, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(waitClick, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getLastClick, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getCursorPos, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setCursorPos, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(screenToClient, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(clientToScreen, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(click, TransferFuncStatic)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(hideCursor, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(showCursor, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        Any SendMouseEvent(IPCMessage::SmartType msg, uint32_t dwFlags, int mouseData = 0);
        
        POINT pt;
    };
}

#endif // AMO_MOUSETRANSFER_H__

