// Created by amoylel on 06/29/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_MENUWINDOWTRANSFER_H__
#define AMO_MENUWINDOWTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"


namespace amo {
    class LayeredWindow;
    
    /*!
     * @class	Menu
     *
     * @extend Object
     *
     * @brief	�����˵�.<br>
     * 			�����̣߳�**UI�߳�**.
     */
    
    class MenuTransfer
        : public ClassTransfer
        , public amo::singleton<MenuTransfer> {
    public:
    
        /*!
         * @fn	MenuTransfer::Menu();
         *
         * @tag constructor
         *
         * @brief	����һ���˵�.�˵�������λ��Ĭ��Ϊ�������λ�ã��˵�ʧȥ������Զ��ر�.
         *
         * @param	#JsonObject �����˵����õ��Ĳ���<br>
         * 						[**Int**]		lineHeight �˵����иߣ�Ĭ��Ϊ32<br>
         * 						[**String**]	separatorColor �ָ�����ɫ��Ĭ��"0xffe8e8e8"<br>
         * 						[**JsonObject**] menu ���в˵���,�������ݲο���<br>
         * 							&nbsp;&nbsp;&nbsp;&nbsp;[**String**]	id ��ǰ�˵���ID,һ���˵�����Ĳ˵���IDӦ����Ψһ��<br>
         * 							&nbsp;&nbsp;&nbsp;&nbsp;[**String**]	text ��ǰ�˵�������ʾ���ı�<br>
         * 							&nbsp;&nbsp;&nbsp;&nbsp;[**String**]	String ��ǰ�˵����Ԥ���嶯���������Ч��ִ�Ҳ�����ҳ�淵�ز˵�ѡ���¼�<br>
         * 							&nbsp;&nbsp;&nbsp;&nbsp;[**Boolean**]	separator �Ƿ���ʾ�ָ�����Ĭ��false<br>
         * 							&nbsp;&nbsp;&nbsp;&nbsp;[**Boolean**]	visible ��ǰ�˵����Ƿ�ɼ���Ĭ��true<br>
         * 							&nbsp;&nbsp;&nbsp;&nbsp;[**Boolean**]	enabled ��ǰ�˵����Ƿ���ã�Ĭ��true<br>
         * 							&nbsp;&nbsp;&nbsp;&nbsp;[**String**]	shortcut ��ǰ�˵����ݼ���Ĭ���޿�ݼ�<br>
         * 							&nbsp;&nbsp;&nbsp;&nbsp;[**String**]	icon ��ǰ�˵���ͼ�꣬��ʾ������ǰ�棬Ĭ���ޣ�����ΪskinĿ¼�µ��ļ�<br>
         * 							&nbsp;&nbsp;&nbsp;&nbsp;[**String**]	selected ��ǰ�˵���ѡ��״̬��֧��"checkbox"��"radio",**���ֶ��������icon�ֶγ�ͻ���������ȼ�����icon�ֶ�**��Ĭ����<br>
         * 							&nbsp;&nbsp;&nbsp;&nbsp;[**JsonObject**] menu �Ӳ˵��������������һ�������Բ���
         *
         *
         *
         *
         *
         * @return	#MenuObject Menu����
         * @html <div id="example" class="example code" contenteditable="true"> �Ҽ�����</div>
         * @example
         *
        		 ```
        			// ����һ����ͨ�˵�
        			include('Menu');
        			var menu = new Menu({
        				lineHeight: 32,
        				backgroundColor: 0xFFFFFFFF,
        				roundcorner: 3,
        				menu: [
        					{ id: '1', text: '����', 'separator': true },
        					{ id: '2', text: 'Ӣ��' },
        					{ id: '3', text: '����' },
        					{ id: '4', text: '����' }
        				]
        			});
        		 ```
         * @example
         *
        		 ```
        			// ����ʹ�ÿ�ݼ��Ĳ˵�
        			include('Menu');
        			var menu = new Menu({
        				lineHeight: 32,
        				backgroundColor: 0xFFFFFFFF,
        				roundcorner: 3,
        				menu: [
        					{ id: '1', text: '����', 'separator': true, icon: 'huiyuan.png' },
        					{ id: '2', text: 'Ӣ��', 'shortcut': 'D', selected: 'checkbox' },
        					{ id: '3', text: '����', 'shortcut': 'E', selected: true  },
        					{ id: '4', text: '����', 'shortcut': 'F', selected: 'radio' },
        					{ id: '5', text: '����', 'shortcut': 'G', icon: 'pick.png' }
        				]
        			});
        		 ```
        * @example
        *
        		 ```
        			// ��action�Ĳ˵�
        			include('Menu');
        			var menu = new Menu({
        				lineHeight: 32,
        				backgroundColor: 0xFFFFFFFF,
        				roundcorner: 3,
        				menu: [
        					{ id: '1', text: '����', 'separator': true },
        					{ id: '2', text: '�رմ���', 'shortcut': 'D', action:'close' },
        					{ id: '3', text: '����', 'shortcut': 'E'  },
        					{ id: '4', text: '����', 'shortcut': 'F'  }
        				]
        			});
        			menu.on('select', function(item) {
        				alert('�����˵���' + item.text);
        			})
        		 ```
        * @example
        *
        		 ```
        		 // ��㼶�˵�
        		 include('Menu');
        		 var menu = new Menu({
        			transparent: false,
        			separatorColor: '0xffff0000',
        			menu: [{
        					id: '1',
        					text: '111',
        					'separator': true,
        					menu: [
        						{ id: '1', text: '�о������׸�', 'separator': true },
        						{ id: '2', text: '222' },
        						{ id: '3', text: '333', shortcut: 'd' },
        						{
        							id: '4',
        							text: '444',
        							menu: [
        								{ id: '1', text: '111', 'separator': true },
        								{ id: '2', text: '222' },
        								{ id: '3', text: '333' }
        							]
        						}
        					]
        				},
        				{
        					id: '2',
        					text: '222',
        					menu: [
        						{ id: '1', text: '111' },
        						{ id: '2', text: '222' },
        						{ id: '3', text: '333' },
        						{ id: '4', text: '444' }
        					]
        				},
        				{ id: '3', text: '333' },
        				{ id: '4', text: '444' }
        			]
        		});
        		menu.on('select', function(item) {
        			console.log(item);
        		})
        		 ```
        
         * @example
         *
         ```
        	// �Ҽ��˵�
        	include('Menu');
        	document.oncontextmenu = function() {
        		var menu = new Menu({
        			menu: [
        				{ id: '1', text: '111' },
        				{ id: '2', text: '222' },
        				{ id: '3', text: '333' },
        				{
        					id: '4',
        					text: '444',
        					menu: [
        						{ id: '1', text: '111' },
        						{ id: '2', text: '222' },
        						{ id: '3', text: '333' },
        						{ id: '4', text: '444' }
        					]
        				}
        			]
        		});
        		menu.on('select', function(item) {
        			alert('�����˵���' + item.text);
        		})
        		return false;
        	};
         ```
         * @example
         *
         ```
        		 // �Ҽ��˵�
        		 include('Menu');
        		 var example = document.getElementById('example');
        		 example.oncontextmenu = function() {
        			 var menu = new Menu({
        				 menu: [
        					{ id: '1', text: '����', action: 'undo', shortcut: 'U' },
        					{ id: '2', text: '����', action: 'redo', shortcut: 'R', separator: true },
        					{ id: '3', text: '����', action: 'cut', shortcut: 'T', enabled: false },
        					{ id: '4', text: '����', action: 'copy', shortcut: 'C', visible: false },
        					{ id: '5', text: 'ճ��', action: 'paste', shortcut: 'P', visible: false },
        					{ id: '6', text: 'ɾ��', action: 'delete', shortcut: 'D', separator: true },
        					{ id: '7', text: 'ȫѡ', action: 'selectAll', shortcut: 'A', separator: true },
        					{ id: '8', text: '�Ŵ�', action: 'zoomOut', shortcut: 'Z' },
        					{ id: '9', text: '��С', action: 'zoomIn', shortcut: 'X' },
        					{ id: '10', text: '����', action: 'resetZoom', separator: true },
        					{ id: '11', text: '��ӡ', action: 'print' },
        				 ]
        			 });
        			 menu.on('select', function(item) {
        				alert('�����˵���' + item.text);
        			 })
        			 return false;
        		 };
         ```
         */
        
        MenuTransfer();
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        
        /*!
         * @fn	virtual Any MenuTransfer::close(IPCMessage::SmartType msg);
         *
         * @brief	�رղ˵�.
         *
         * @return	��.
         * @example
         *
         ```
        	include('Menu');
        	var menu = new Menu({
        		menu: [
        				{ id: '1', text: '111' },
        				{ id: '2', text: '222' },
        				{ id: '3', text: '333' },
        				{
        					id: '4',
        					text: '444',
        					menu: [
        						{ id: '1', text: '111' },
        						{ id: '2', text: '222' },
        						{ id: '3', text: '333' },
        						{ id: '4', text: '444' }
        					]
        				}
        			]
        	});
        	// ���û�в�����5���˵����Զ��ر�
        	setTimeout(function(){
        	console.log(123);
        		menu.close();
        	}, 5000);
         ```
         */
        
        virtual Any close(IPCMessage::SmartType msg);
        
        
        /*!
        * @event	virtual Any MenuTransfer::select(IPCMessage::SmartType msg);
        *
        * @brief	�˵��ѡ��ʱ����.
        *
        * @param	#JsonObject ��ѡ�еĲ˵���.
        *
        *
        * @return	��.
        *
        * @example
        *
        ```
        	include('Menu');
        	var menu = new Menu({
        		id: '2',
        		text: '222',
        		menu: [
        		{ id: '1', text: '111' },
        		{ id: '2', text: '222' },
        		{ id: '3', text: '333' },
        		{ id: '4', text: '444' }
        		]
        	});
        	menu.on('select', function(){
        		console.log(arguments);
        	});
        ```
        */
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(MenuTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(close, TransferFuncNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
        void onMenuClosed(LayeredWindow* window);
    };
    
}



#endif // AMO_MENUWINDOWTRANSFER_H__