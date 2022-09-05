// Created by amoylel on 08/20/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_KEYBOARDTRANSFER_H__
#define AMO_KEYBOARDTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {

    /*!
     * @class	keyboard
     *
     * @script	keyboard.js
     *
     * @extend Object
     *
     * @brief	���̲�����.<br>
     * 			�����̣߳�**UI�߳�**.
     */
    
    class KeyboardTransfer
        : public ClassTransfer
        , public amo::singleton < KeyboardTransfer > {
    public:
    
        KeyboardTransfer();
        
        /*!
         * @fn	Any KeyboardTransfer::sayString(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	����һ���ı�.
         *
         * @param	#String Ҫ���͵��ַ���.
         * @param	#Int=5 ÿ����һ���ַ������ͣʱ��.Ĭ��Ϊ5ms������̫���п��ܵ����ַ�����.
         *
         * @return	��.
         *
         * @example
         *
        			 ```
        				include('keyboard');
        				$('#div_sayString').find('.example').focus();
        				keyboard.sayString('NCUI�����ַ���');
        			 ```
         */
        
        Any sayString(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any KeyboardTransfer::keyPress(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	��������.
         *
         * @param	#Args... ����, �������������������������������һ���ַ�����Ҳ������һ�����ⰴ��..
         *
         * @return	��.
         *
         * @example
         *
        			 ```
        				include('keyboard');
        				$('#div_keyPress').find('.example').focus();
        				keyboard.keyPress('1','2','3', '5');
        				// �رյ�ǰ����
        				keyboard.keyPress(keyboard.VK_MENU, keyboard.VK_F4);
        			 ```
         */
        
        Any keyPress(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any KeyboardTransfer::keyDown(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	���°���.
         *
         * @param	#Args... ����, �������������������������������һ���ַ�����Ҳ������һ�����ⰴ��.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        			include('keyboard');
        			$('#div_keyDown').find('.example').focus();
        			keyboard.keyDown('1');
        			keyboard.keyUp('1');
        		 ```
         */
        
        Any keyDown(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any KeyboardTransfer::keyUp(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	���𰴼�.
         *
         * @param	#Args... ����, �������������������������������һ���ַ�����Ҳ������һ�����ⰴ��.
         *
         * @return	��.
         * @example
         *
        			 ```
        				include('keyboard');
        				$('#div_keyUp').find('.example').focus();
        				keyboard.keyDown('2');
        				keyboard.keyUp('2');
        			 ```
         */
        
        Any keyUp(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any KeyboardTransfer::waitKey(IPCMessage::SmartType msg);
         *
         * @tag sync static
         *
         * @brief	�ȴ��������.
         *
         * @return	��.
         */
        
        Any waitKey(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any KeyboardTransfer::getLastKey(IPCMessage::SmartType msg);
         *
         * @tag sync static
         *
         * @brief	����ϴΰ���.
         *
         * @return	#String.
         */
        
        Any getLastKey(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(KeyboardTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(sayString, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(keyPress, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(keyDown, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(keyUp, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(waitKey, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getLastKey, TransferFuncStatic | TransferExecSync)
        
        /*! @attr #Int=CONTROL VK_CONTROL ���̰���CONTROL. {@tag const static property}*/
        /*! @attr #Int=SHIFT VK_SHIFT ���̰���SHIFT.{@tag const static property} */
        /*! @attr #Int=ALT VK_MENU ���̰���ALT.{@tag const static property} */
        
        /*! @attr #Int=F1 VK_F1 ���̰���F1. {@tag const static property}*/
        /*! @attr #Int=F2 VK_F2 ���̰���F2. {@tag const static property}*/
        /*! @attr #Int=F3 VK_F3 ���̰���F3. {@tag const static property}*/
        /*! @attr #Int=F4 VK_F4 ���̰���F4. {@tag const static property}*/
        /*! @attr #Int=F5 VK_F5 ���̰���F5. {@tag const static property}*/
        /*! @attr #Int=F6 VK_F6 ���̰���F6. {@tag const static property}*/
        /*! @attr #Int=F7 VK_F7 ���̰���F7. {@tag const static property}*/
        /*! @attr #Int=F8 VK_F8 ���̰���F8. {@tag const static property}*/
        /*! @attr #Int=F9 VK_F9 ���̰���F9. {@tag const static property}*/
        /*! @attr #Int=F10 VK_F10 ���̰���F10. {@tag const static property}*/
        /*! @attr #Int=F11 VK_F11 ���̰���F11. {@tag const static property}*/
        /*! @attr #Int=F12 VK_F12 ���̰���F12. {@tag const static property}*/
        
        /*! @attr #Int=UP VK_UP ���̰���UP. {@tag const static property}*/
        /*! @attr #Int=DOWN VK_DOWN ���̰���DOWN. {@tag const static property}*/
        /*! @attr #Int=LEFT VK_LEFT ���̰���LEFT. {@tag const static property}*/
        /*! @attr #Int=RIGHT VK_RIGHT ���̰���RIGHT. {@tag const static property}*/
        /*! @attr #Int=RETURN VK_RETURN ���̰���RETURN. {@tag const static property}*/
        /*! @attr #Int=ESCAPE VK_ESCAPE ���̰���ESCAPE. {@tag const static property}*/
        /*! @attr #Int=BACK VK_BACK ���̰���BACK. {@tag const static property}*/
        /*! @attr #Int=HOME VK_HOME ���̰���HOME. {@tag const static property}*/
        /*! @attr #Int=DELETE VK_DELETE ���̰���DELETE. {@tag const static property}*/
        /*! @attr #Int=INSERT VK_INSERT ���̰���INSERT. {@tag const static property}*/
        
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_CONTROL)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_SHIFT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_MENU)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F1)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F2)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F3)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F4)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F5)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F6)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F7)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F8)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F9)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F10)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F11)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F12)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_UP)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_DOWN)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_LEFT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_RIGHT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_RETURN)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_ESCAPE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_BACK)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_HOME)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_DELETE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_INSERT)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
    private:
        void SendKeyDown(char data);
        void SendKeyUp(char data);
        void SendUnicode(wchar_t data);
        void SendKeys(const amo::string& msg, int interval = 5);
        
        std::vector<char> getKeys(IPCMessage::SmartType msg);
    private:
    };
}

#endif // AMO_KEYBOARDTRANSFER_H__

