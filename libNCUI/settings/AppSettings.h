// Created by amoylel on 06/09/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_APPSETTINGS_H__
#define AMO_APPSETTINGS_H__

#include <amo/json.hpp>
#include <amo/singleton.hpp>
#include <amo/string.hpp>
#include "handler/CefHeader.hpp"
#include "BasicSettings.h"

namespace amo {

    /*!
     * @class ��������
     *
     * @id settingsAppSettings
     *
     * @desc ��������
     *
     *
     * @chapter settings
     *
     * @brief	Ӧ�ó���������������Щ�����󲿷ֲ��ɸ��ģ���ֻ�ڳ�������ǰ���ò�����Ч.<br>
     * 			���ʹ��NodeJS������JS�����������{@link app.setConfig}������������.<br>
     * 			���δʹ��NodeJS����ͨ������Ŀ¼�µ�manifest.json�ļ��ﵽͬ����Ч��.<br>
     * 			˵����**���ò��������ڳ������й������޸ģ�ֻ�г����ڲ����������޸���Щֵ��**
     *
     */
    
    class AppSettings : public CefSettings, public BasicSettings, public amo::singleton<AppSettings> {
    public:
        AppSettings();
        
        
        bool updateCefAppSettings();
        
        virtual void afterUpdateArgsSettings();
        
        virtual amo::json toJson()   override;
    private:
        void initDefaultCefSettings();
        
        void initDefaultAppSettings();
        
        amo::string getCachePath();
        
        /*!
         * @fn	amo::string AppSettings::getUserHomeDir();
         * @ignore
         * @brief	�û����ݸ�Ŀ¼.
         *
         * @return	The user home dir.
         */
        amo::string getUserHomeDir();
        
        /*!
         * @fn	std::string AppSettings::getSpecialFolder(int nType);
         * @ignore
         * @brief	��ȡWindows�ϵ�����Ŀ¼.
         *
         * @param	nType	The type.
         *
         * @return	The special folder.
         */
        std::string getSpecialFolder(int nType);
    public:
    
    
        /*! @var	#String=%appDir%locales locales  �����ļ�����Ŀ¼  {@tag const}*/
        /*! @var	#Boolean=true single_process  �Ƿ�ʹ�õ�����ģʽ���������Ƚϸ��ӣ�Ӧ�þ���ʹ�ö����ģʽ{@tag const}*/
        /*! @var	#String=%appDir% resources_dir_path  ��Դ�ļ�����Ŀ¼{@tag const}*/
        /*! @var	#String=%APPDATA%appName/cache cache_path  CEF�����ļ�����Ŀ¼{@tag const}*/
        /*! @var	#String=zh-CN locale  CEF���Ի���{@tag const}*/
        
        
        
        /*! @var	#Boolean=true manifest	�Ƿ������ⲿ�����ļ�manifest.json�����Ҫʹ�ã����ļ�������Ӧ�ó�������Ŀ¼��ͬ��ֻ��ʹ��ANSI���룬 ������UTF8, ����Ὣ����ת��ΪUTF8{@tag const} */
        bool manifest;
        
        /*! @var	#String=783a02fd-b493-45ad-aa7f-ddbefeec1122 appID	����ΨһID��Ĭ��ΪNCUI�ĳ���ID. ��������Ӧ���޸ĸ�ֵ�������Ӱ�쵥��ģʽ��ʹ�ã�appID��ͬ�ĳ���ᱻ�ж�Ϊͬһ���������{@tag const}. */
        std::string appID;
        
        /*! @var	#Boolean=false singleInstance	����ģʽ,��ģʽ��ֻ����һ��ʵ�����У������������������򽫲���ɹ� */
        bool singleInstance;
        
        /*! @var	#Boolean=false showSplash	�Ƿ���ʾ��������.�����Ҫ�������棬��Ҫ�޸����ò���{@link ��������} */
        bool showSplash;
        
        /*! @var	#Boolean=false useNode	�Ƿ�ʹ��NodeJs.{@tag const} */
        bool useNode;
        
        /*! @var	#Boolean=false useNodeProcess �Ƿ��ڵ����Ľ�����ʹ��NodeJs.��useNode=trueʱ���ֶ���Ч������ڵ����Ľ�����ʹ��NodeJs,��ôNCUI��Node�����ڲ�ͬ�ؽ������У���ͨ��ͨ��������Ϣͬ�� {@tag const}*/
        bool useNodeProcess;
        
        /** @var	#Int=0 ipcTimeout	����ͨ�ŵĳ�ʱʱ�䣬����������ʱ��û�еõ����ؽ��������Ϣ��������������������������������⡣Ĭ��Ϊ0��������ʱ��. */
        int64_t ipcTimeout;
        
        /*! @var	#String=main.js main	NodeJs��Ҫ���õ�JS�ļ�����λ��. useNodeΪtrue ʱ����ֵ��Ч{@tag const} */
        std::string main;
        
        /*! @var	#Boolean=false debugNode �Ƿ��������NodeJs.���δ�ڵ�����������NodeʱҪ����NodeJs ��Ҫʹ��NCUI-DEV.exe,��������������ģʽ������NCUI(�������������ͼ�ν�����һ�������д���){@tag const} */
        bool debugNode;
        
        /*! @var	#String appPath �����ڴ����ϵ�����·��.{@tag const} */
        std::string appPath;
        
        /*! @var	#String appDir	��������Ŀ¼.{@tag const} */
        std::string appDir;
        
        /*! @var	#String appName	�������ƣ�������Ŀ¼����������չ��.{@tag const} */
        std::string appName;
        
        /*! @var	#String=%appDir%skin skinDir	Duilib skin Ŀ¼.{@tag const} */
        std::string skinDir;
        
        /*! @var	#String=%appDir% workDir	����Ŀ¼,Ĭ�����������Ŀ¼��ͬ.{@tag const} */
        std::string workDir;
        
        /*! @var	#String=%appDir%web webDir	html Դ����Ŀ¼.{@tag const} */
        std::string webDir;
        
        /*! @var	#String homeDir	����Ӧ�ó��������ļ����ļ��У�Ĭ���� "�ҵ��ĵ�" �ļ��и���Ӧ�õ�����. */
        std::string homeDir;
        
        /*! @var	#String=%homeDir%downloads downloadsDir �û�����Ŀ¼��·��. */
        std::string downloadsDir;
        
        /*! @var	#String=%homeDir%musics musicsDir	�û�����Ŀ¼��·��. */
        std::string musicsDir;
        
        /*! @var	#String=%homeDir%pictures picturesDir	�û�ͼƬĿ¼��·��. */
        std::string picturesDir;
        
        /*! @var	#String=%homeDir%videos videosDir	�û���ƵĿ¼��·��. */
        std::string videosDir;
        
        /*! @var	#String=drag dragClassName	��ק�ƶ����ڵ�Ԫ������. */
        std::string dragClassName;
        
        /*! @var	#String=no-drag noDragClassName	��ֹ����Ԫ������. */
        std::string noDragClassName;
        
        /*! @var	#String=%APPDATA% appDataDir ��ǰ�û���Ӧ�������ļ���. */
        std::string appDataDir;
        
        /*!@var #String=%TEMP% temp	��ʱ�ļ���. {@tag const}*/
        std::string temp;
        
        /*! @var #String desktop ��ǰ�û��������ļ���. {@tag const}*/
        std::string desktop;
        /*!
         * @var #String documents �û��ĵ�Ŀ¼��·��. {@tag const} */
        std::string documents;
        
        /*!
         * @var #Int startTime  ����ʱ�䣨����ʱ���ms��.
         */
        int64_t startTime;
        
        /*!
         * @var #Boolean=true debugMode �Ƿ��Ե���ģʽ����,Ĭ��true.��ģʽ��F12���Դ򿪵��Դ��ڣ�F5����ˢ��ҳ��
         */
        bool debugMode;
        
        /*! @var #Boolean=false clearCache �Ƿ���Ӧ�ó�������ʱ�����������棨�����ã�. {@tag const}*/
        bool clearCache;
        
    };
}

#endif // AMO_APPSETTINGS_H__
