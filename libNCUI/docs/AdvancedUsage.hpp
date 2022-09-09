// Created by amoylel on 07/21/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_ADVANCEDUSAGE_E1DEC618_F70E_496C_A726_0D629A243048_HPP__
#define AMO_ADVANCEDUSAGE_E1DEC618_F70E_496C_A726_0D629A243048_HPP__

namespace amo {

    /*!
     * @class	�߼��÷�
     * @desc	�߼��÷�
     * @chapter basic
     * @brief	NCUI���׽̳�.
     */
    
    class AdvancedUsage {
    public:
    
        /*!
         * @section	ʹ��Node.js
         *
         * @brief	NCUI֧��ʹ��Node.js���Ƴ��򣬵�Ŀǰֻ���4.7.3���й����������߻���͵İ汾���ܲ���֧��.
         * 			�������Node.js��ʹ���ĵ�api�������ṩ�ľ��󲿷ֽӿڣ��������͵Ľӿڲ���֧��.<br>
         * 			����Ա༭manifest.json�ļ�(useNode=true)����ȡNode.js֧��.Ĭ�������Node.js��ע�뵽NCUI�У����ڵ������߳�������.<br>
         * 			����Ա༭manifest.json�ļ�(useNodeProcess=true)ʹNode.js�ڵ����Ľ�����ִ��,��ģʽ��Node.js���Ե���ģʽ�����������ʹ��node-inspector���������Թ�������Node.js����.
         *
         * @example
         *
        ```
        		// ֱ����NCUI��ʹ��Node.js
        		{
        			"appSettings":{
        				useNode: true,
        				useNodeProcess: false
        			}
        		}
        
        		// �ڵ����Ľ�����ʹ��Node.js
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
         * @section	����Ӧ��
         *
         * @brief	����ʹ��{@link ��Դ�༭ģ��=rcedit}�����Լ���Ӧ��.
         */
        
        void foo1() {
        
        }
        
        /*!
         * @section	localЭ��
         *
         * @brief	NCUIע�����Զ���Э��local://file��֧�ֱ����ļ��ķ���.����Ϊ"local://file/�ļ�·��",�ļ�·�����Ϊ���·���Ļ�������%webDir%����Ŀ¼���в���.
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
        * @section	@fileЭ��
        *
        * @brief	NCUI֧���Զ���Э��@file:///��֧�ֱ����ļ��ķ���.����Ϊ"@file:///�ļ�·��",�ļ�·�����Ϊ���·���Ļ�������%webDir%����Ŀ¼���в���.<br>
        * 			@fileЭ�����ǿ��,�����������url��ע��@fileЭ�齫urlָ�򱾵��ļ����Ҳ����ڿ��������.
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
         * @section ��ַӳ��
         *
         * @brief	�ù��ܿ��Խ�һ��URLӳ�䵽�����ļ�.Ŀǰ֧�ֵ�ӳ�䷽ʽ���ļ���Ŀ¼��ZIP��ʽѹ���ļ���DLL��̬�⡢RES��Դ�ļ�<br>
         * 			���Ա༭manifest.jsonָ��ӳ��·����Ҳ�����ڳ������к�{@link �ֶ�ָ��=app.addUrlMapping}ӳ��·��.<br>
         * 			���ĵ�������ǲ���URL���ļ��еķ�ʽ����ҳ���.<br>
         *
         *
         * @see app.addUrlMapping
         * @example �޸�manifest.json
         *
         ```
        	//ͨ���޸�manifest.jsonӳ���ļ�
        	{
        		"appSettings": {
        			"urlMappings":[
        				{
        					"url":"http://127.0.0.1:8020",
        					"path": "%webDir%"
        				},
        				{
        					"url":"http://127.0.0.1:8020",
        					"path": "zip:///%webDir%web.zip"
        				},
        				{
        					"url":"http://127.0.0.1:8020",
        					"path": "dll:///libResource.dll"
        				},
        				{
        					"url":"http://127.0.0.1:8020",
        					"path": "res:///131.res"
        				}
        			]
        		}
        	}
         ```
         *
         */
        
        void foo4() {
        
        }
        
        /*!
         * @section	Դ�������
         *
         * @brief	NCUI֧�ֶ�ȡ�����ļ���ZIP��ʽѹ���ļ���DLL��̬���е�HTMLԴ���룬�����ͨ����Щ��ʽΪNCUI�ṩԴ����.<br>
         * 			1. **�ӱ���Ŀ¼�ж�ȡHTML:** ֱ��ָ���ļ�·�����ļ���·������D:/web<br>
         * 			2. **��ZIP�ļ��ж�ȡHTML:** ��zip:///��ͷ<br>
         * 			3. **��DLL�ж�ȡHTML:** ��dll:///��ͷ<br>
         * 			4. **�ӳ������Դ�ļ��ж�ȡHTML:**��res:///��ͷ<br>
         * 			NCUI��ֱ���ṩԴ������ܹ��ܣ���֧�ֶ�ȡ���ܵ�ZIP�ļ������ص�SQLITE���ݿ⣬�����ͨ���޸�Դ����ķ�ʽ�ṩ��Ӧ�ļ����ļ����빩����ʹ��.
         *
         */
        
        void foo5() {
        
        }
        
        /*!
         * @section	C++��չ
         *
         * @brief	NCUI�ṩ���Ӽ򵥵���չ��д��ʽ��ֻ��Ҫ����չ��Ŀ���ɵĶ�̬���ļ��ŵ�renderer_modules����browser_modulesĿ¼������ҳ���е���.<br>
         * 			�������C++����Ա����ο�libDemo��Ŀ��Դ����.
         */
        
        void foo6() {
        
        }
        
        
        /*!
        * @section	�ⲿ��Ⱦ��
        *
        * @brief	������ģʽ��֧��ʹ���ⲿ������Ⱦ����.
        *
        * @see BrowserWindow.addOverlap
        *
        */
        
        void foo7() {
        
        }
        
        /*!
        * @section	DLL����
        *
        * @brief	NCUIֱ�ӵ���C������DLL�ӿ�,�����ƱȽ϶࣬������ֱ��дC++��չ�죬��δ����.
        *
        */
        
        void foo8() {
        
        }
    };
}

#endif // AMO_ADVANCEDUSAGE_E1DEC618_F70E_496C_A726_0D629A243048_HPP__

