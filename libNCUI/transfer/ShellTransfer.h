// Created by amoylel on 07/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SHELLTRANSFER_H__
#define AMO_SHELLTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"


namespace amo {

    /**
     * @class	shell
     *
     * @brief	����һ���ⲿ���򣨻����Ǵ�һ����ע����ļ�����һ��Ŀ¼����ӡһ���ļ��ȵȣ�.
     *
     */
    
    class ShellTransfer
        : public ClassTransfer
        , public amo::singleton<ShellTransfer> {
    public:
        ShellTransfer();
        
        
        
        /**
         * @fn	Any ShellTransfer::exec(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	ִ��һ��shell����.
         *
         * @param	#String Ҫִ�е�shell���� open print ��.
         * @param	#String Ҫ���õĳ����򿪵��ļ�·��.
         * @param	#String ��������,Ĭ��Ϊ"".
         * @param	#String ����Ŀ¼,Ĭ��Ϊ��ǰ·��.
         * @param	#Int=1 ��ʾ����
         *
         *
         * @return	��.
         * @example
         *
        	 ```
        	 include('shell');
        	 shell.exec("open", "explorer", "/e, /select, skin\\close_p.png", "", shell.SW_SHOWNORMAL);
        	 ```
         */
        
        Any exec(IPCMessage::SmartType msg);
        
        
        
        /**
         * @fn	Any ShellTransfer::open(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	���ļ������.
         *
         * @param	#String	�ļ������·��.
         * @param	#String	��������,Ĭ��Ϊ"".
         * @param	#String	����Ŀ¼,Ĭ��Ϊ��ǰ·��.
         *
         * @return	��.
         * @example
         *
         ```
        		 include('shell');
        		 shell.open("www.baidu.com");
        
         ```
         */
        
        Any open(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ShellTransfer::print(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	 ��ӡ�ļ�.
         *
         * @param	#String �ļ�·��.
         *
         * @return	��.
         * @example
         *
        
        	 ```
        		include('shell');
        		shell.print("skin\\close_p.png");
        	 ```
         */
        
        Any print(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any ShellTransfer::showItemInFolder(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	���ļ�������ʾ�ļ�����λ�ļ�λ�ã�.
         *
         * @param	#String �ļ�·��.
         *
         * @return	��.
         * @example
         *
        		 ```
        			include('shell');
        			shell.showItemInFolder('skin\\close_p.png');
        		 ```
         */
        
        Any showItemInFolder(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(ShellTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exec, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(open, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(print, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(showItemInFolder, TransferFuncStatic)
        
        
        /*! @attr #Int=SW_HIDE SW_HIDE ��ʱ����ʾ����. {@tag const static property}*/
        /*! @attr #Int=SW_MINIMIZE SW_MINIMIZE ����С���ķ�ʽ��. {@tag const static property}*/
        /*! @attr #Int=SW_RESTORE SW_RESTORE �Ի�ԭ��ʾ�ķ�ʽ��. {@tag const static property}*/
        /*! @attr #Int=SW_SHOW SW_SHOW ��ʱ��ʾ����. {@tag const static property}*/
        /*! @attr #Int=SW_SHOWMAXIMIZED SW_SHOWMAXIMIZED ����ڲ��������. {@tag const static property}*/
        /*! @attr #Int=SW_SHOWMINIMIZED SW_SHOWMINIMIZED ����ڲ�������С��. {@tag const static property}*/
        /*! @attr #Int=SW_SHOWMINNOACTIVE SW_SHOWMINNOACTIVE ������С�����������Ȼά�ּ���״̬. {@tag const static property}*/
        /*! @attr #Int=SW_SHOWNA SW_SHOWNA �Դ���ԭ����״̬��ʾ���ڡ��������Ȼά�ּ���״̬. {@tag const static property}*/
        /*! @attr #Int=SW_SHOWNOACTIVATE SW_SHOWNOACTIVATE �Դ������һ�εĴ�С��״̬��ʾ���ڡ��������Ȼά�ּ���״̬. {@tag const static property}*/
        /*! @attr #Int=SW_SHOWNORMAL SW_SHOWNORMAL �����ʾһ�����ڡ�������ڱ���С������󻯣�ϵͳ����ָ���ԭ���ĳߴ�ʹ�С��. {@tag const static property}*/
        
        
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_HIDE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_MINIMIZE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_RESTORE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOW)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWMAXIMIZED)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWMINIMIZED)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWMINNOACTIVE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWNA)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWNOACTIVATE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWNORMAL)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        int StringToShowCmd(const amo::string& str);
    private:
    };
}


#endif // AMO_SHELLTRANSFER_H__
