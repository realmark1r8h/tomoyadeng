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
         * @section	�༭�����ļ�
         *
         * @brief	�༭��������Ŀ¼�µ�manifest.json�ļ������Զ������ó����������ʽ��<br>
         * 			������manifest���������Σ��ֱ�Ϊ appSettings�� browserWindowSettings�� splashWindowSettings;<br>
         * 			��Ӧ��������{@link ��������}��{@link ������������ڲ���=��������ڲ���}��{@link ������������=��������}<br>
         * 			manifest���Ǳ���ģ���������ڣ���ô����ʹ��Ĭ������.<br>
         * 			NCUI���������ط����������������������ȼ���1��3���ֱ�Ϊ��<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;1. manifest.json������ͨ���༭���ļ��޸���������<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;2. exe�����е���Դ�ļ�������ͨ���༭exe�����޸���������,�ο�{@link ��Դ�༭=rcedit}��{@link Ӧ������}<br>
         * 			&nbsp;&nbsp;&nbsp;&nbsp;3. Դ�����е�Ĭ������������ֻ��ͨ���޸�Դ������������������<br>
         * 			ע�⣺**manifest.jsonֻ֧��ANSI���룬�������͵ı�����ܲ��ᱻ��ȷʶ��**
         *
         * @example
         *
         ```
        		 // һ���򵥵������ļ�,ֻ�����������ڵĲ������öΣ� ���ó�����ʱҪ�򿪵�URL
        		 {
        			 "browserWindowSettings":{
        			 "titleBar": true,
        			 "url": "http://127.0.0.1:8020/doc/example/ManifestWindow.html"
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
        				"single_process": true,
        				"useNode":false
        			},
        			"browserWindowSettings":{
        				 "titleBar": true,
        				 "url": "http://127.0.0.1:8020/doc/example/ManifestWindow.html"
        			 },
        			 "splashWindowSettings":{
        				"images":"%webDir%images/splash.png"
        			 }
        		}
         ```
         * @example �޸�manifest.json
         *
         ```
        	 includes('Path','FileStream', 'app');
        	 var path = new Path('manifest.json');
        	 path.copyTo('manifest2.json');// ����manifest.json��������ٲ鿴Ч�����ֶ��ָ����ļ�
        	 var filestream = new FileStream('manifest.json', 2 + 32); // 2 ��д�뷽ʽ�򿪣�32 �Զ����Ʒ�ʽ��
        	 filestream.write(`
        		 {
        			 "appSettings":{
        				 "single_process": true,
        				 "useNode":false,
        				 "urlMappings":[
        					{
        						"url":"http://127.0.0.1:8020/doc",
        						"path":"%webDir%"
        					}
        				 ]
        			 },
        			 "browserWindowSettings":{
        				 "titleBar": true,
        				 "url": "http://127.0.0.1:8020/doc/example/ManifestWindow.html"
        			 },
        			 "splashWindowSettings":{
        				"images":"%webDir%images/splash.png"
        			 }
        		}`,3);
        	 filestream.close();
        	 app.restart();
         ```
         * @example �޸�manifest.json
         *
         ```
        			include('Path');
        			var path = new Path('manifest.json');
        			path.copyTo('manifest2.json');// ����manifest.json��������ٲ鿴Ч�����ֶ��ָ����ļ�
        			include('shell');
        			shell.exec('open', 'notepad', 'manifest.json');
        			sleep(1000);
        			include('keyboard');
        			keyboard.keyPress(keyboard.VK_CONTROL, 'A');
        			keyboard.sayString(`{
        								"appSettings":{
        									"single_process": true,
        									"useNode":false,
        									"urlMappings":[
        										{
        											"url":"http://127.0.0.1:8020/doc",
        											"path":"%webDir%"
        										}
        									]
        								},
        								"browserWindowSettings":{
        									 "titleBar": true,
        									 "url": "http://127.0.0.1:8020/doc/example/ManifestWindow.html"
        								 },
        								 "splashWindowSettings":{
        									"images":"%webDir%images/splash.png"
        								 }
        							}`,3);
        			sleep(1000);
        			keyboard.keyPress(keyboard.VK_CONTROL, 'S');
        			keyboard.keyPress(keyboard.VK_MENU, keyboard.VK_F4);
        			include('app');
        			app.restart();
         ```
         */
        
        void foo() {
        
        }
        
        /*!
         * @section	�������������
         *
         * @brief	��������ʱ�ᴴ��һ��Ĭ�ϵ���������ڣ��ô��ڵĲ�������ͨ���༭manifest.json�ļ���������.<br>
         *			�����Ҫ��ҳ���ϴ������ڣ�����ͨ��{@link BrowserWindow}��{@link ���캯��=BrowserWindow.BrowserWindow}����һ���µ���������ڡ�<br>
         *			����֮�⣬�����Ĭ�ϵĴ��ڴ����������磺**a��ǩ**��**window.open**�ȣ������Ĵ��ڽ�ʹ��Ĭ�ϵ�{@link ��������ڲ���},
         *			����ܻ�Ӱ���������ʹ�ã�����û�б������������϶����ڣ�������{@link Ԥ������������ڲ���=BrowserWindow.addBrowserWindowSettings}�����������
         *	@see BrowserWindow.addBrowserWindowSettings
         *	@example �������������
         *
         ```
        	include('BrowserWindow');
        	var win = new BrowserWindow({
        					titleBar: true,
        					url: 'http://127.0.0.1:8020/doc/example/BrowserWindow.html'
        				});
         ```
         */
        
        void foo2() {
        
        }
        
        /*!
         * @section	����ģ��
         *
         * @brief	���Ҫʹ��NCUI�ṩ��ģ�飬��ô������ʹ��֮��ǰ����Ҫ��ģ�鵼�뵽ҳ���У������ͨ�����·�ʽ������Ҫ��ģ�顣**���б������ģ�鶼�ᱻע�뵽ҳ���ȫ�ֱ����У����ܻ���ҳ���еı�����ͻ**<br>
         * 			ʹ��**include**���뵥��ģ��.<br>
         * 			ʹ��**includes**������ģ��.<br>
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
        		includes('BrowserWindow', 'app');
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