// Created by amoylel on 11/08/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBNCUI_DISPATCHEVENT_3C949AC8_6F42_4A67_A7C6_EF033BFA40BD_HPP__
#define LIBNCUI_DISPATCHEVENT_3C949AC8_6F42_4A67_A7C6_EF033BFA40BD_HPP__


namespace amo {

    /**
     * @class	�¼��������
     * @chapter basic
     * @brief	�����ʹ���¼�������̷�ֹNCUI��Ⱦ���ҳ��.
     */
    
    class DispatchEvent {
    public:
    
        /**
         * @section �����¼�
         *
         * @brief	ʹ��document.addEventListener����һ���Զ����¼�.
         * 			NCUI�Ὣipc.dispatchEvent���͵���Ϣ�ض���document��
         * @example
         *
         ```
        	document.addEventListener('NCUI.TEST', function(event){
        		console.log(arguments);
        	});
        	// ����Ĵ������д��Node.js����ȥ������ֻ����ʾ
        	include('ipc');
        	ipc.dispatchEvent('NCUI.TEST', {name:3, value:'2323'});
        
         ```
         */
        
        void foo1() {
        
        }
        
        /**
         * @section �����¼�
         *
         * @brief	NCUI������ͨ��document.dispatchEvent��Node.js������ҳ�淢���Զ���Ϣ.<br>
         * 			1. "ipc.exec", ͨ��{@ling ipc.exec}��Node.js������ҳ�淢����Ϣ��ʹ��ipc.on��ipc.unique���Լ�������Ϣ<br>
         * 			2. "ipc.dispatchEvent", ͨ��{@ling ipc.dispatchEvent}��ҳ���document��������Ϣ��ʹ��document.addEventListener���Լ�������Ϣ��Node.js�����޷����ո���Ϣ<br>
         * 			˵����**������CustomEvent��detail����������eventName�ֶα�����Ҫ�������¼�����**
         * @example
         *
         ```
        	// ����Խ�ipc.uniqueд��Node.js������,��༭manifest.json������Node.js֧�֣����Ե���ģ������NCUI-DEV.exe�鿴Ч��
        	include('ipc');
        	ipc.unique('NCUI.TEST2', function(){
        		console.log('NCUI.TEST2');
        		console.log(arguments);
        	});
        
        	document.addEventListener('NCUI.TEST3', function(event){
        		console.log('NCUI.TEST3');
        		console.log(arguments);
        	});
        
        	document.dispatchEvent(new CustomEvent('ipc.exec', {
        			detail: {
        				eventName: 'NCUI.TEST2',
        				value: 3232
        			}
        		}));
        
        	document.dispatchEvent(new CustomEvent('ipc.dispatchEvent', {
        			detail: {
        				eventName: 'NCUI.TEST3',
        				value: 3232,
        				path: 'D:/'
        			}
        		}));
        
         ```
         */
        
        void foo2() {
        
        }
    };
}



#endif //LIBNCUI_DISPATCHEVENT_3C949AC8_6F42_4A67_A7C6_EF033BFA40BD_HPP__