// Created by amoylel on 07/07/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_APPTRANSFER_H__
#define AMO_APPTRANSFER_H__


#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"


namespace amo {

    /*!
     * @class	app
     *
     * @extend  Object
     *
     * @brief	���Ƴ��������������ڣ����ṩһЩ�������صĹ���.<br>
     * 			�����̣߳�**UI�߳�**.
     */
    
    class AppTransfer
        : public ClassTransfer
        , public amo::singleton<AppTransfer> {
        
    public:
        AppTransfer();
        
        /*!
         * @ignore
         *
         * @fn	void AppTransfer::initUrlMapping(amo::json& json);
         *
         * @brief	�������ļ��е�������ӵ�MAP��.
         *
         * @param [in,out]	json	The JSON.
         */
        
        void initUrlMapping(amo::json& json);
        
        /*!
         * @fn	static Any AppTransfer::getConfig(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	��ȡӦ�ó�����������ò���,�ɻ�ȡ�����ݼ�{@link ��������=��������}.
         *
         * @return	#JsonObject �������ò���.
         */
        
        
        /*!
        * @fn	static Any AppTransfer::getConfig(IPCMessage::SmartType msg);
        * @tag static sync
        * @brief	��ȡӦ�ó����ָ�����ò���.
        *
        * @param	#String ��Ҫ��ȡ���ֶ�����.
        *
        * @return	�����ֶ�������Ӧ�����ò������������������ò������Ͷ�����ΪJS��֧�ֵĻ�����������.
        *
        * @see setConfig=app.setConfig
        * @example
        			```
        				//��ȡӦ�ó�����������ò���
        				var config = app.getConfig();
        				console.log(config);
        
        				//��ȡӦ�ó����ָ�����ò���
        				var single_process = app.getConfig('single_process');
        				console.log('������ģʽ��' + single_process);
        			```
        */
        
        
        Any getConfig(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::setConfig(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	����Ӧ�ó������ò���.�ú�������Ҫ��һ��Ҫ������֧�ֵĲ�����
         * 			��Ҳ���������Զ������������getConfig�����ȡ�����õ�ֵ��{@link app.getConfig}���Ӧ.
         *
         * @param	#JsonObject ��Ҫ���õĲ�������ֵΪһ��JSON����.
         *
         * @return	��.
         *
         * @see getConfig=app.getConfig
         *
         * @example
        			```
        			app.setConfig({
        				debugMode: true,
        				custom: 'custom'
        			});
        
        			```
         */
        
        Any setConfig(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::toAbsolutePath(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	��һ��·��תΪ����·���磺%web%.
         *
         * @param	#String ��Ҫת����·��.
         *
         * @return	#String ת����ľ���·��.
         *
         * @example
         			```
        				// ��ȡweb��Դ�ļ�Ŀ¼
        				var webDir = app.toAbsolutePath('%webDir%');
        				console.log(webDir);
        				console.log(app.toAbsolutePath('%webDir%docs/index.html'));
        
        				// ��ȡͼƬ�ļ�����Ŀ¼
        				var picturesDir = app.toAbsolutePath('%picturesDir%');
        				console.log(picturesDir);
        
        			```
         */
        
        Any toAbsolutePath(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::quit(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�����˳����򣬿����û���ȡ������window.unload������.
         *
         *
         * @return	��.
         * @example
          		   ```
         		   app.quit();
          		   ```
         */
        
        Any quit(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::exit(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	ǿ���˳�����.
         *
         * @return	��.
         *
         * @example
        		   ```
        		   // ֱ���˳����򣬲������κ���ʾ
        		   app.exit();
        		   ```
         */
        
        Any exit(IPCMessage::SmartType msg);
        
        
        /*!
        * @fn	static Any AppTransfer::addUrlMapping(IPCMessage::SmartType msg);
        *
        * @tag static sync
        *
        * @brief   ���URLӳ��·��,����˵���ǽ�URL�滻Ϊ��ӳ���URL���ļ�·��.
        *
        * @param   #String ��Ҫ���ӳ���URL.
        *
        * @param   #String ��ӳ��ı����ļ�·������·��������һ����ͨ���ļ����ļ��У�
        * 					Ҳ������ZIPѹ������DLL��̬��.
        *
        * @return	#Boolean ��Ϊ����true, ʧ�ܷ���false.
        * @example ӳ�䵽��һ��URL
        			```
        				// ����ӳ��
        				app.addUrlMapping('http://www.baidu.com', 'http://www.qq.com');
        				window.open('http://www.baidu.com');
        
        				app.addUrlMapping('http://www.baidu.com/more', 'http://www.qq.com');
        				window.open('http://www.baidu.com/more');
        
        			```
        * @example ӳ�䵽�ļ�
        			```
        
        			// ��Ҳ����ָ��һ������·��
        			//	app.addUrlMapping('http://www.baidu.com/', 'E:/webDir/index.hmtl');
        			//	app.addUrlMapping('http://www.baidu.com/more', 'E:/webDir/more/more.html');
        
        			app.addUrlMapping('http://www.baidu.com', '%webDir%example/BrowserWindow.html');
        			window.open('http://www.baidu.com');
        
        			app.addUrlMapping('http://www.baidu.com/more', '%webDir%/example/FramelessWindow.html');
        			window.open('http://www.baidu.com/more');
        
        ```
        * @example ӳ�䵽ZIP�ļ�
        ```
        		// zip�ļ�ͬ��������һ������·��
        		// app.addUrlMapping('http://www.baidu.com', 'zip:///D:/web.zip');
        
        		app.addUrlMapping('http://127.0.0.1:8088', 'zip:///%webDir%web.zip');
        		window.open('http://127.0.0.1:8088/example/BrowserWindow.html');
        
        		app.addUrlMapping('http://127.0.0.1:8088/test',  'zip:///%webDir%web.zip/example/FramelessWindow.html');
        		window.open('http://127.0.0.1:8088/test');
        
        ```
        * @example ӳ�䵽DLL�ļ�
        ```
        
        		// demo�е�dll���ṩ�ĸ�Ŀ¼Ϊ��ǰ��������Ŀ¼�µ�webĿ¼
        		app.addUrlMapping('http://www.baidu.com', 'dll:///libResource.dll');
        		window.open('http://www.baidu.com/example/BrowserWindow.html');
        
        		app.addUrlMapping('http://www.baidu.com/more', 'dll:///libResource.dll/example');
        		window.open('http://www.baidu.com/more/BrowserWindow.html');
        ```
        * @example ӳ�䵽RES�ļ�
        ```
        
        	// RES��������ZIP��һ�£�ֻ�ǽ�ZIP�ļ���ǰд��EXE����Դ�ļ���.
        	// ����Բο�����������������ݣ���ZIP�ļ�д��EXE����ȥ
        	// ��ǰ�ĵ�����û��IDΪ131����Դ����������ķ���������ȷ�Ĵ�ҳ��
        	app.addUrlMapping('http://www.baidu.com', 'res:///131.res');
        	window.open('http://www.baidu.com/example/BrowserWindow.html');
        
        ```
        */
        
        Any addUrlMapping(IPCMessage::SmartType msg);	// UI
        
        /*!
        * @fn	static Any AppTransfer::removeUrlMapping(IPCMessage::SmartType msg);
        *
        * @tag static sync
        *
        * @brief	�Ƴ�URLӳ��·��.
        *
        * @param	#String ��Ҫ�Ƴ���URL.
        *
        * @return	��.
        * @example
        			```
        				// ɾ��ӳ��
        				app.removeUrlMapping('http://www.baidu.com');
        				window.open('http://www.baidu.com');
        			```
        */
        
        Any removeUrlMapping(IPCMessage::SmartType msg); //UI
        
        /*!
         * @fn	static Any AppTransfer::urlToNativePath(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	��һ��URLת��Ϊ����·����
         * 			�⼸���������ܻᱻIO�̺߳�UI�߳�ͬʱ���ã�����Ҫ����.
         *
         * @param	#String ��Ҫת����URL.
         * @param	#Boolean=false �Ƿ�Ҫ����ӳ����ļ����� .
         *
         * @return	#String ת�����·���������ǰ������URLû����֮ӳ��ı���·����
         * 			�����ظ�URL.
         * @example
         *
        	```
        		app.addUrlMapping('http://test/test.html', '%webDir%/test.html');
        		console.log(app.urlToNativePath('http://test/test.html', true));
        		console.assert(app.urlToNativePath('http://test/test.html', true) != '');
        		console.assert(app.urlToNativePath('http://test/test2.html', true) == '');
        		console.assert(app.urlToNativePath('http://test/test2.html', false)  == '');
        		console.assert(app.urlToNativePath('http://www.github.com', true)  == '');
        		console.assert(app.urlToNativePath('http://www.github.com', false)  == '');
        
        	```
         */
        
        Any urlToNativePath(IPCMessage::SmartType msg); //IO
        
        
        
        /*!
         * @ignore
         *
         * @fn	static Any AppTransfer::setDragClassName(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	���ÿ��϶����ڿؼ�Class��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setDragClassName(IPCMessage::SmartType msg);
        
        /*!
         * @ignore
         *
         * @fn	static Any AppTransfer::setNoDragClassName(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	���ò����ֶ����ڿؼ�Class��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setNoDragClassName(IPCMessage::SmartType msg);
        
        /*!
         * @ignore
         *
         * @fn	static Any AppTransfer::setGlobal(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	����ȫ������.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setGlobal(IPCMessage::SmartType msg);
        
        /*!
         * @ignore
         *
         * @fn	static Any AppTransfer::getGlobal(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	��ȡȫ������.
         *
         * @param	msg	The message.
         *
         * @return	The global.
         */
        
        Any getGlobal(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::getAutoRun(IPCMessage::SmartType msg);
         *
         * @tag static sync deprecated
         *
         * @brief	��ȡ�Ƿ񿪻�������ʹ��{@link isAutoRun=app.isAutoRun}����.
         *
         * @return	#Boolean .
         *
         * @see setAutoRun=app.setAutoRun
         */
        
        Any getAutoRun(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::isAutoRun(IPCMessage::SmartType msg);
           *
         * @tag static sync
         *
         * @brief	��ȡ�Ƿ񿪻�����.
         *
         * @return	#Boolean .
         *
         * @see setAutoRun=app.setAutoRun
         * @example
         *
         ```
        	include('app');
        	app.setAutoRun(false);
        	console.assert(app.isAutoRun() == false);
         ```
         */
        
        Any isAutoRun(IPCMessage::SmartType msg);
        
        
        /*!
         * @fn	static Any AppTransfer::setAutoRun(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	�����Ƿ񿪻�����.
         *
         * @param	#Boolean=false true����������faseȡ����������.
         *
         * @return	��.
         *
         * @see isAutoRun=app.isAutoRun
         *
         * @example
        			```
        			// ���ÿ�������
        			app.setAutoRun(true);
        			console.assert(app.isAutoRun() == true);
        
        			// ȡ����������
        			app.setAutoRun(false);
        			console.assert(app.isAutoRun() == false);
        			```
         */
        
        Any setAutoRun(IPCMessage::SmartType msg);
        
        /**
         * @fn	static Any AppTransfer::elapsed(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	��ǰ��������������ڵ�����ʱ��(����).
         *
         * @return	#Int.
         * @example
        			```
        			var elapsed = app.elapsed();
        			console.log('���������У�' + elapsed + ' ms');
        			```
         */
        
        Any elapsed(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::restart(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	������ǰ����.
         *
         * @param	#Int=0 ������ʱ(��)����ǰ����������رգ��µĳ��������ʱʱ�䵽�������.
         *
         * @return	#Boolean ���ɷ���true, ʧ�ܷ���false.
         *
         * @example
        			```
        			// 5����������е�ǰ����
        			app.restart(5);
        			```
         */
        
        Any restart(IPCMessage::SmartType msg);
        
        
        /**
         * @fn	static Any AppTransfer::destroy(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	���ٵ�ǰ����(�Ӵ�����ɾ����ǰ��ִ�г���).
         *
         *
         * @return	��.
         * @example
        		```
        			// ��Ҫ�ԣ�����
        			app.destroy();
        		```
         */
        
        Any destroy(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(AppTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getConfig, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setConfig, TransferFuncStatic)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setGlobal, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getGlobal, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setAutoRun, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getAutoRun, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isAutoRun, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(toAbsolutePath,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(urlToNativePath,
                                      TransferFuncStatic | TransferExecSync)
                                      
        AMO_CEF_MESSAGE_TRANSFER_FUNC(addUrlMapping, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeUrlMapping, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setDragClassName,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setNoDragClassName,
                                      TransferFuncStatic | TransferExecSync)
                                      
        AMO_CEF_MESSAGE_TRANSFER_FUNC(quit, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exit, TransferFuncStatic)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(restart, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(destroy, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(elapsed,
                                      TransferFuncStatic | TransferExecSync)
                                      
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        /*! @brief	URLת����·����. */
        std::recursive_mutex m_mutex;
        /*! @brief	URL������·��ӳ��. */
        std::list<std::pair<std::string, std::string > > m_oUrlToNativeMap;
        /*! @brief	ȫ������. */
        amo::json m_global;
    };
}



#endif // AMO_APPTRANSFER_H__