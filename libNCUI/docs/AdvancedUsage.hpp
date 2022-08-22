// Created by amoylel on 07/21/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_ADVANCEDUSAGE_E1DEC618_F70E_496C_A726_0D629A243048_HPP__
#define AMO_ADVANCEDUSAGE_E1DEC618_F70E_496C_A726_0D629A243048_HPP__

namespace amo {

    /*!
     * @class	高级用法
     * @desc	高级用法
     * @chapter basic
     * @brief	NCUI进阶教程.
     */
    
    class AdvancedUsage {
    public:
    
        /*!
         * @section	使用Node.js
         *
         * @brief	NCUI支持使用Node.js控制程序，但目前只针对4.7.3进行过开发，更高或更低的版本可能并不支持.
         * 			你可以在Node.js中使用文档api部分所提供的绝大部分接口，其他类型的接口不被支持.<br>
         * 			你可以编辑manifest.json文件(useNode=true)来获取Node.js支持.默认情况下Node.js会注入到NCUI中，并在单独的线程中运行.<br>
         * 			你可以编辑manifest.json文件(useNodeProcess=true)使Node.js在单独的进程中执行,该模式下Node.js会以调试模式启动，你可以使用node-inspector或其他调试工作调试Node.js代码.
         *
         * @example
         *
        ```
        		// 直接在NCUI中使用Node.js
        		{
        			"appSettings":{
        				useNode: true,
        				useNodeProcess: false
        			}
        		}
        
        		// 在单独的进程中使用Node.js
        		{
        			"appSettings":{
        				useNode: true,
        				useNodeProcess: true
        			}
        		}
        ```
         *
         */
        
        void foo() {}
        
        /*!
         * @section	生成应用
         *
         * @brief	可以使用{@link 资源编辑模块=rcedit}生成自己的应用.
         */
        
        void foo1() {
        
        }
        
        /*!
         * @section	local协议
         *
         * @brief	NCUI注册了自定义协议local://file来支持本地文件的访问.具体为"local://file/文件路径",文件路径如果为相对路径的话，将以%webDir%所在目录进行查找.
         *
         * @example
         *
         ```
        	includes('BrowserWindow', 'app');
        
        	var win = new BrowserWindow({
        		titleBar: true,
        		url: 'local://file/example/localfile.html'
        	})
        
        	var url = app.toAbsolutePath("%webDir%example/FramelessWindow.html");
        	console.log(url);
        
        	new BrowserWindow({
        		titleBar: false,
        		url: url
        	})
         ```
         */
        
        void foo2() {
        
        }
        
        /*!
        * @section	@file协议
        *
        * @brief	NCUI支持自定义协议@file:///来支持本地文件的访问.具体为"@file:///文件路径",文件路径如果为相对路径的话，将以%webDir%所在目录进行查找.<br>
        * 			@file协议更加强大,你可以在任意url中注入@file协议将url指向本地文件，且不存在跨域等问题.
        *
        * @example
        *
        ```
        		includes('BrowserWindow', 'app');
        
        		var win = new BrowserWindow({
        			titleBar: true,
        			url: 'localhost/@file:///example/localfile.html'
        		})
        
        		var url = app.toAbsolutePath("%webDir%example/FramelessWindow.html");
        		console.log(url);
        
        		new BrowserWindow({
        			titleBar: false,
        			url: 'http://www.baidu.com/ananana/@file:///'+url
        		})
        ```
        */
        
        void foo3() {
        
        }
        
        /*!
         * @section 地址映射
         *
         * @brief	Foo 4.
         */
        
        void foo4() {
        
        }
        
        /*!
         * @section	源代码管理
         *
         * @brief	Foo 5.
         */
        
        void foo5() {
        
        }
        
        /*!
         * @section	C++扩展
         *
         * @brief	Foo 6.
         */
        
        void foo6() {
        
        }
        
        /*!
        * @section	外部渲染层
        *
        * @brief	仅离屏模式下支持使用外部数据渲染界面.
        */
        
        void foo7() {
        
        }
    };
}

#endif // AMO_ADVANCEDUSAGE_E1DEC618_F70E_496C_A726_0D629A243048_HPP__

