// Created by amoylel on 08/09/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_USENODEJS_A7E11AE8_5D40_48BA_BDBD_BD276B84F3E0_HPP__
#define AMO_USENODEJS_A7E11AE8_5D40_48BA_BDBD_BD276B84F3E0_HPP__

namespace amo {

    /*!
     * @class	ʹ��Node
     *
     * @chapter	basic
     *
     * @brief	NCUI֧��ʹ��Node.js���Ƴ��򣬵�Ŀǰֻ���4.7.1���й����������߻���͵İ汾���ܲ���֧��.
     * 			�������Node.js��ʹ���ĵ�api�������ṩ�ľ��󲿷ֽӿڣ��������͵Ľӿڲ���֧��.
     */
    
    class UserNodeJs {
    public:
    
        /*!
         * @section �༭�����ļ�
         *
         * @brief	ͨ���༭manifest.json����ʹ������Node.js����.<br>
         * 			����Ա༭manifest.json�ļ�(useNode=true)����ȡNode.js֧��.Ĭ�������Node.js��ע�뵽NCUI�У����ڵ������߳�������.<br>
         * 			����Ա༭manifest.json�ļ�(useNodeProcess=true)ʹNode.js�ڵ����Ľ�����ִ��.<br>
         *
         * @example
         *
        	```
        			// ֱ����NCUI��ʹ��Node.js
        			{
        				"appSettings":{
        					useNode: true,
        					useNodeProcess: false,
        					"main": "main.js"
        				}
        			}
        
        			// �ڵ����Ľ�����ʹ��Node.js
        			{
        				"appSettings":{
        					"useNode": true,
        					"useNodeProcess": true,
        					"main": "main.js"
        				}
        			}
        	```
         */
        
        void foo1() {
        
        }
        
        /*!
         * @section	��дNode.js����
         *
         * @brief	��дmanifest.json��"appSettings"��"main"�ֶ���ָ�����ļ���ΪNode.js�ṩ���.<br>
         * 			NCUIͨ��Node ��չ�ķ�ʽ�ṩ�ĵ��е����е����ýӿڣ�ֻ��Ҫrequire(process.cwd() + '/ncui')����ʹ�ã�����Ҫʹ��include֮��ĺ�������ģ��.
         * 			ͬNode.js���벻��ʹ��renderer_modules����browser_modules���ļ���������ⲿ��չ.<br>
         * 			ע�⣺**ͼ�ν�����NCUI��Ҫ�ض���Node.js�Ŀ���̨����������޷�����ncui.node���**
         *
         * @example main.js
         *
         ```
        	'use strict';
        	var console = {};
        	console.log = function() {}
        	console.info = function() {}
        	console.warn = function() {}
        	console.error = function() {}
        	console.dir = function() {}
        	console.time = function() {}
        	console.timeEnd = function() {}
        	console.trace = function() {}
        	console.assert = function() {}
        	require(process.cwd() + '/ncui');
        	app.addUrlMapping('http://127.0.0.1:8020/', 'web/');
        	tray.show(true);
        	const win = new BrowserWindow({
        		show: true,
        		hasShadow: true,
        		titleBar: false,
        		offscreen: false,
        		transparent: false,
        		width: 1280,
        		height: 720,
        		roundcorner: 5,
        		sizebox: "4,4,6,6",
        		url: "http://127.0.0.1:8020/index.html",
        		titleBar: false
        	});
         ```
         */
        
        void foo2() {
        
        }
        
        /*!
         * @section ����Node.js
         *
         * @brief	��ʽ��NCUI����֧�ֵ���Node.js���������ͨ�����·�ʽ������Node.js����<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;1.�༭manifest.json��ʹNode.js�ڵ����Ľ��������У�{"useNode": true, "useNodeProcess": true}<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;2.���Node.js������ļ�������C++��չ require(process.cwd() + '/ncui-dev').<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;3.����node-insepector����.<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;3.����NCUI-DEV.exe������������е���Node.js����.<br>
         * 			˵����**NCUI-DEV.exeΪ����̨���򣬲���Ҫ�ض���Node.js�Ŀ���̨���.**
         * 			˵����**NCUI-DEV.exe����ʱ������ͼ�겻����ȷ��ʾ.**
         * @example
         *
         ```
        	'use strict';
        	require(process.cwd() + '/ncui-dev');
        	app.addUrlMapping('http://127.0.0.1:8020/', 'web/');
        	tray.show(true);
        	const win = new BrowserWindow({
        		show: true,
        		hasShadow: true,
        		titleBar: false,
        		offscreen: false,
        		transparent: false,
        		width: 1280,
        		height: 720,
        		roundcorner: 5,
        		sizebox: "4,4,6,6",
        		url: "http://127.0.0.1:8020/index.html",
        		titleBar: false
        	});
         ```
         *
         */
        
        void foo3() {
        
        }
        
        /*!
         * @section	���Ա�־
         *
         * @brief	����ģʽ�µ�Node.js����������в�����--ncui-debug���������ͨ���ò����ж�Node.js�Ƿ��ڵ���״̬����������ȷ��c++��չ.
         * @example
         *
         ```
        	    'use strict';
        
        		var debugMode = false;
        		process.argv.forEach((val, index) => {
        			if(val == '--ncui-debug') {
        				debugMode = true;
        			}
        		});
        
        		var console = {};
        		if(!debugMode) {
        			console.log = function() {}
        			console.info = function() {}
        			console.warn = function() {}
        			console.error = function() {}
        			console.dir = function() {}
        			console.time = function() {}
        			console.timeEnd = function() {}
        			console.trace = function() {}
        			console.assert = function() {}
        			require(process.cwd() + '/ncui');
        		} else {
        			console = global.console;
        			require(process.cwd() + '/ncui-dev');
        		}
        
        		app.addUrlMapping('http://127.0.0.1:8020/', 'web/');
        		tray.show(true);
        		const win = new BrowserWindow({
        			show: true,
        			hasShadow: true,
        			titleBar: false,
        			offscreen: false,
        			transparent: false,
        			width: 1280,
        			height: 720,
        			roundcorner: 5,
        			sizebox: "4,4,6,6",
        			url: "http://127.0.0.1:8020/index.html",
        			titleBar: false
        		});
         ```
         */
        
        void foo4() {
        
        }
    };
}

#endif // AMO_USENODEJS_A7E11AE8_5D40_48BA_BDBD_BD276B84F3E0_HPP__

