// Created by amoylel on 17/07/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBNCUI_QUICKSTART_51E7465A_7BD9_422B_BADB_9E3D479E949E_HPP__
#define LIBNCUI_QUICKSTART_51E7465A_7BD9_422B_BADB_9E3D479E949E_HPP__


namespace amo {

    /**
     * @class	���ٿ�ʼ
     * @desc ���ٿ�ʼ
     *
     * @chapter basic
     *
     * @brief	��ʼʹ��NCUI.
     */
    
    class QuickStart {
    
        /**
         * @section	�����ļ�
         *
         * @brief	�༭��������Ŀ¼�µ�manifest.json�ļ������Զ������ó����������ʽ��<br>
         * 			������manifest���������Σ��ֱ�Ϊ appSettings�� browserWindowSettings�� splashWindowSettings;<br>
         * 			��Ӧ��������{@link ��������}��{@link ������������ڲ���=��������ڲ���}��{@link ������������=��������}<br>
         * 			manifest���Ǳ���ģ���������ڣ���ô����ʹ��Ĭ������.
         *
         * @example
         *
         ```
        		 // һ���򵥵������ļ�,ֻ�����������ڵĲ������öΣ� ���ó�����ʱҪ�򿪵�URL
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
        		 // һ���������жεĵ������ļ�
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
         * @section	�������������
         *
         * @brief	��������ʱ�ᴴ��һ��Ĭ�ϵ���������ڣ��ô��ڵĲ�������ͨ���༭manifest.json�ļ���������.<br>
         *			�����Ҫ��ҳ���ϴ������ڣ�����ͨ��{@link BrowserWindow}�ṩ�Ľӿڴ���һ���µ���������ڡ�<br>
         *			����֮�⣬�����Ĭ�ϵĴ��ڴ����������磺**a��ǩ**��**window.open**�ȣ������Ĵ��ڽ�ʹ��Ĭ�ϵ�{@ling ��������ڲ���},
         *			����ܻ�Ӱ���������ʹ�ã�����û�б������������϶����ڣ�������{@link Ԥ������������ڲ���=BrowserWindow.addBrowserWindowSettings}�����������
         *	@see BrowserWindow.addBrowserWindowSettings
         */
        
        void foo2() {
        
        }
        
        /*!
         * @section	����ģ��
         *
         * @brief	���Ҫʹ��NCUI�ṩ��ģ�飬��ô������ʹ��֮��ǰ����Ҫ��ģ�鵼�뵽ҳ���У������ͨ�����������ӿڵ�����Ҫ��ģ�顣<br>
         * 			ʹ��**include**���뵥��ģ�飬ģ��ᱻע�뵽ҳ���ȫ�ֱ�����.<br>
         * 			ʹ��**includes**������ģ�飬����ģ�鶼�ᱻע�뵽ҳ���ȫ�ֱ�����.<br>
         * 			�������ģ�鲻���ڣ����ᵼ��renderer_modules�ļ�����ģ�飬������ǲ����ڻᵼ��browser_modules�ļ�����ģ��.
         * 			renderer_modules�ļ����µ���չ��Renderer�߳������У�browser_modules�ļ����µ���չ��UI�߳�������.<br>
         * 			ʹ��**renderer_modules**����renderer_modules�ļ����µ�ģ�飬���ģ�����������ô����ʹ��includes��������ģ��<br>
         * 			ʹ��**browser_modules**��������renderer_modules�ļ����µ�ģ�飬ֱ�ӵ���browser_modules�ļ����µ�ģ�飬���ģ�����������ô����ʹ��includes��������ģ��<br>
         * 			˵����<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;**һ��iframe��ͬһ��ģ��ֻ��Ҫ����һ�μ���������ط�ʹ��**<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;**�����������󣬶�Ӧ��ʹ��include �� inclcudes ����ģ��**<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;**������Ҫ��д������ģ������ͬ��C++��չģ��**<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;**renderer_modules��browser_modulesͬ�����Ե�������ģ�飬������������������������������ģ��**<br>
         * @example ���뵥��ģ��
         *
         ```
        		// ���뵥��ģ��
        		include('BrowserWindow');
        		BrowserWindow.current.maximize();
         ```
         * @example ��������ģ��
         *
         ```
        		// ��������ģ��
        		include('BrowserWindow', 'app');
        		BrowserWindow.current.maximize();
        		BrowserWindow.current.restore();
        		// �����˳�����
        		app.quit();
         ```
         * @example renderer_modules
         *
         ```
        	 // ��������ģ��
        	 renderer_modules('BrowserWindow', 'md5');
        
         ```
         * @example browser_modules
         *
         ```
        	 // ��������ģ��
        	 browser_modules('BrowserWindow', 'Path');
        
         ```
         */
        
        
    };
}



#endif //LIBNCUI_QUICKSTART_51E7465A_7BD9_422B_BADB_9E3D479E949E_HPP__