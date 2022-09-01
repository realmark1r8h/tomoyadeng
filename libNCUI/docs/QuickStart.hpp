// Created by amoylel on 17/07/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBNCUI_QUICKSTART_51E7465A_7BD9_422B_BADB_9E3D479E949E_HPP__
#define LIBNCUI_QUICKSTART_51E7465A_7BD9_422B_BADB_9E3D479E949E_HPP__


namespace amo {

    /**
     * @class	快速开始
     * @desc 快速开始
     *
     * @chapter basic
     *
     * @brief	开始使用NCUI.
     */
    
    class QuickStart {
    
        /**
         * @section	配置文件
         *
         * @brief	编辑程序所在目录下的manifest.json文件可以自定义设置程序的启动方式。<br>
         * 			完整的manifest包含三个段，分别为 appSettings， browserWindowSettings， splashWindowSettings;<br>
         * 			对应可以设置{@link 启动参数}，{@link 启动浏览器窗口参数=浏览器窗口参数}，{@link 程序启动画面=启动画面}<br>
         * 			manifest不是必须的，如果不存在，那么程序将使用默认配置.
         *
         * @example
         *
         ```
        		 // 一个简单的配置文件,只包含启动窗口的参数配置段， 设置程序启时要打开的URL
        		 {
        			 "browserWindowSettings":{
        			 "titleBar": true,
        			 "url": "http://www.oschina.net"
        			 }
        		 }
         ```
         *
         * @example
         *
         ```
        		 // 一个包含所有段的的配置文件
        		{
        			"appSettings":{
        				"single_process": true
        			},
        			"browserWindowSettings":{
        				 "titleBar": true,
        				 "url": "http://www.oschina.net"
        			 },
        			 "splashWindowSettings":{
        				"images":"%webDir%images/splash.png"
        			 },
        		}
         ```
         */
        
        void foo() {
        
        }
        
        /*!
         * @section	创建浏览器窗口
         *
         * @brief	程序启动时会创建一个默认的浏览器窗口，该窗口的参数可以通过编辑manifest.json文件进行配置.<br>
         *			如果需要在页面上创建窗口，可以通过{@link BrowserWindow}提供的接口创建一个新的浏览器窗口。<br>
         *			除此之外，浏览器默认的窗口创建动作（如：**a标签**、**window.open**等）出来的窗口将使用默认的{@ling 浏览器窗口参数},
         *			这可能会影响你的正常使用（比如没有标题栏，不能拖动窗口），可以{@link 预设置浏览器窗口参数=BrowserWindow.addBrowserWindowSettings}来避免该问题
         *	@see BrowserWindow.addBrowserWindowSettings
         */
        
        void foo2() {
        
        }
        
        /*!
         * @section	导入模块
         *
         * @brief	如果要使用NCUI提供的模块，那么必须在使用之间前将需要的模块导入到页面中，你可以通过以下两个接口导入需要的模块。<br>
         * 			使用**include**导入单个模块，模块会被注入到页面的全局变量中.<br>
         * 			使用**includes**导入多个模块，所有模块都会被注入到页面的全局变量中.<br>
         * 			如果内置模块不存在，将会导入renderer_modules文件夹下模块，如果还是不存在会导入browser_modules文件夹下模块.
         * 			renderer_modules文件夹下的扩展在Renderer线程上运行，browser_modules文件夹下的扩展在UI线程上运行.<br>
         * 			使用**renderer_modules**导入renderer_modules文件夹下的模块，如果模块存在依赖那么，会使用includes加载依赖模块<br>
         * 			使用**browser_modules**可以跳过renderer_modules文件夹下的模块，直接导入browser_modules文件夹下的模块，如果模块存在依赖那么，会使用includes加载依赖模块<br>
         * 			说明：<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;**一个iframe中同一个模块只需要加载一次即可在任意地方使用**<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;**如无特殊需求，都应该使用include 或 inclcudes 加载模块**<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;**尽量不要编写与其他模块名相同的C++扩展模块**<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;**renderer_modules和browser_modules同样可以导入内置模块，但不建议用这两个函数来导入内置模块**<br>
         * @example 导入单个模块
         *
         ```
        		// 导入单个模块
        		include('BrowserWindow');
        		BrowserWindow.current.maximize();
         ```
         * @example 导入多个个模块
         *
         ```
        		// 导入多个个模块
        		include('BrowserWindow', 'app');
        		BrowserWindow.current.maximize();
        		BrowserWindow.current.restore();
        		// 尝试退出程序
        		app.quit();
         ```
         * @example renderer_modules
         *
         ```
        	 // 导入多个个模块
        	 renderer_modules('BrowserWindow', 'md5');
        
         ```
         * @example browser_modules
         *
         ```
        	 // 导入多个个模块
        	 browser_modules('BrowserWindow', 'Path');
        
         ```
         */
        
        
    };
}



#endif //LIBNCUI_QUICKSTART_51E7465A_7BD9_422B_BADB_9E3D479E949E_HPP__