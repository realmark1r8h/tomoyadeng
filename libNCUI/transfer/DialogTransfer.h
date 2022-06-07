// Created by amoylel on 08/14/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DIALOGTRANSFER_H__
#define AMO_DIALOGTRANSFER_H__


#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"


namespace amo {

    /**
     * @class	dialog
     *
     * @brief	�������ļ�ѡ���.
     *
     */
    
    class DialogTransfer
        : public ClassTransfer
        , public amo::singleton < DialogTransfer > {
        
    public:
        DialogTransfer();
        
        /*!
         * @fn	Any DialogTransfer::runFileDialog(IPCMessage::SmartType msg);
         *
         * @tag async static
         *
         * @brief	���ļ�ѡ��Ի���.
         *
         * @param	#JsonObject �ļ��򿪲���.<br>
         * 						[**String**]  title ����.<br>
         * 						[**String**]	model �Ի������ͣ����õ�{@link �Ի���ģʽ=dialog.�����б�}<br>
         * 						[**String**]	defaultFilePath Ĭ�Ͽ�ʼĿ¼<br>
         * 						[**Array**]	acceptFilters, �ɽ��ܵ��ļ�����<br>
         * 						[**String**]	selectedAcceptFilter ������
         *
         * @param	#Function  ѡ����ɺ�Ļص�����, ���ڴ����û���ѡ���������Ϊһ��Array.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        		 include('dialog');
        		 // ���ļ�ѡ��
        		 dialog.runFileDialog({
        			 title: 'NCUI�ļ�ѡ��Ի���',
        			 model: dialog.FILE_DIALOG_OPEN,
        			 defaultFilePath: '',
        			 acceptFilters: ['image/*'],
        			 selectedAcceptFilter: 0
        		 }, function(arr) {
        			 console.log(arr);
        		 });
        		 ```
         * @example
         *
        		 ```
        		 include('dialog');
        		 // ���ļ�ѡ��
        		 dialog.runFileDialog({
        			 title: 'NCUI�ļ�ѡ��Ի���',
        			 model: dialog.FILE_DIALOG_OPEN_MULTIPLE,
        			 defaultFilePath: '',
        			 acceptFilters: ['image/*'],
        			 selectedAcceptFilter: 0
        		 }, function(arr) {
        			console.log(arr);
        		 });
        		 ```
        * @example
        *
        		 ```
        		 include('dialog');
        		 // ���ļ�ѡ��
        		 dialog.runFileDialog({
        		 title: 'NCUI�ļ�ѡ��Ի���',
        		 model: dialog.FILE_DIALOG_OPEN_MULTIPLE,
        		 defaultFilePath: '',
        		 acceptFilters: ['image/*'],
        		 selectedAcceptFilter: 0
        		 }, function(arr) {
        		 console.log(arr);
        		 });
         */
        
        Any runFileDialog(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any DialogTransfer::alert(IPCMessage::SmartType msg);
         *
         * @tag sync static
         *
         * @brief	������ʾ�������js��alert����.
         *
         * @param	#String ��Ҫ��ʾ���ı�.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        		 include('dialog');
        		 dialog.alert('����һ��������');
        		 ```
         */
        
        Any alert(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any DialogTransfer::confirm(IPCMessage::SmartType msg);
         *
         * @tag sync static
         *
         * @brief	ѡ��Ի����൱��js��confirm����.
         *
         * @param	#String ��Ҫ��ʾ���ı�.
         *
         * @return	#Boolean.
         *
         * @example
         *
        			 ```
        				include('dialog');
        				var retval = dialog.confirm('�Ƿ���Ҫ�˳�����');
        				console.log(retval);
        			 ```
         */
        
        Any confirm(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any DialogTransfer::prompt(IPCMessage::SmartType msg);
         * @tag sync static
         * @brief	��ȡ�û�����ֵ���൱��js��prompt����.
         *
         * @param	#String ��ʾ�ı�.
         * @param	#String Ĭ�������ı�����ѡ.
         *
         * @return	#JsonObject.
         * 			|#Boolean code �û���ѡ����,true /false.
         * 			|#String text �û��������ı�.
         * @example
         *
        			 ```
        			 include('dialog');
        			 var retval = dialog.prompt('�������������', '����');
        			 console.log(retval);
        			 ```
         */
        
        Any prompt(IPCMessage::SmartType msg);
        
        /*! @attr #Int=FILE_DIALOG_OPEN FILE_DIALOG_OPEN ����ѡ��һ�����ڵ��ļ�. {@tag const static property}*/
        /*! @attr #Int=FILE_DIALOG_OPEN_MULTIPLE FILE_DIALOG_OPEN_MULTIPLE ����ѡ�������ڵ��ļ�. {@tag const static property}*/
        /*! @attr #Int=FILE_DIALOG_OPEN_FOLDER FILE_DIALOG_OPEN_FOLDER ѡ���ļ���. {@tag const static property}*/
        /*! @attr #Int=FILE_DIALOG_SAVE FILE_DIALOG_SAVE ����ѡ��һ�������ڵ��ļ��������ѡ����ļ����ڣ���ô����ʾ�Ƿ񸲸Ǹ��ļ���һ���������ļ�����ѡ��. {@tag const static property}*/
        /*! @attr #Int=FILE_DIALOG_TYPE_MASK FILE_DIALOG_TYPE_MASK General mask defining the bits used for the type values. {@tag const static property}*/
        /*! @attr #Int=FILE_DIALOG_OVERWRITEPROMPT_FLAG FILE_DIALOG_OVERWRITEPROMPT_FLAG Prompt to overwrite if the user selects an existing file with the Save dialog. {@tag const static property}*/
        /*! @attr #Int=FILE_DIALOG_HIDEREADONLY_FLAG FILE_DIALOG_HIDEREADONLY_FLAG ����ʾֻ���ļ�. {@tag const static property}*/
        
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DialogTransfer, ClassTransfer)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(runFileDialog,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(alert, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(confirm, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(prompt, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_OPEN, (int)FILE_DIALOG_OPEN)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_OPEN_MULTIPLE,
                                       (int)FILE_DIALOG_OPEN_MULTIPLE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_OPEN_FOLDER,
                                       (int)FILE_DIALOG_OPEN_FOLDER)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_SAVE, (int)FILE_DIALOG_SAVE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_TYPE_MASK,
                                       (int)FILE_DIALOG_TYPE_MASK)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_OVERWRITEPROMPT_FLAG,
                                       (int)FILE_DIALOG_OVERWRITEPROMPT_FLAG)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_HIDEREADONLY_FLAG,
                                       (int)FILE_DIALOG_HIDEREADONLY_FLAG)
                                       
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
    };
}
#endif // AMO_DIALOGTRANSFER_H__
