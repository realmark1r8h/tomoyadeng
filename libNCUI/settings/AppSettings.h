// Created by amoylel on 06/09/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_APPSETTINGS_H__
#define AMO_APPSETTINGS_H__

#include <amo/json.hpp>
#include <amo/string.hpp>
#include "handler/CefHeader.hpp"
#include "BasicSettings.h"

namespace amo {

    /*!
     * @class ��������
     *
     * @id AppSettings
     *
     * @desc ��������
     *
     * @chapter settings
     *
     * @brief	Ӧ�ó���������������Щ�����󲿷ֲ��ɸ��ģ���ֻ�ڳ�������ǰ���ò�����Ч.<br>
     * 			���ʹ��NodeJS������JS�����������{@link app.setConfig}������������;<br>
     * 			���δʹ��NodeJS����ͨ������Ŀ¼�µ�manifest.json�ļ��ﵽͬ����Ч��.
     *
     */
    
    class AppSettings : public CefSettings, public BasicSettings {
    public:
        AppSettings();
        
        
        bool updateCefAppSettings();
        
        virtual void afterUpdateArgsSettings();
        
    private:
        void initDefaultCefSettings();
        
        void initDefaultAppSettings();
        
        amo::string getCachePath();
        
        /*!
         * @fn	amo::string AppSettings::getUserHomeDir();
         *
         * @brief	�û����ݸ�Ŀ¼.
         *
         * @return	The user home dir.
         */
        amo::string getUserHomeDir();
        
        /*!
         * @fn	std::string AppSettings::getSpecialFolder(int nType);
         *
         * @brief	��ȡWindows�ϵ�����Ŀ¼.
         *
         * @param	nType	The type.
         *
         * @return	The special folder.
         */
        std::string getSpecialFolder(int nType);
    public:
    
    
        /*! @var	#String=%appDir%locales locales  �����ļ�����Ŀ¼*/
        /*! @var	#Boolean=true single_process  �Ƿ�ʹ�õ�����ģʽ���������Ƚϸ��ӣ�Ӧ�þ���ʹ�ö����ģʽ*/
        /*! @var	#String=%appDir% resources_dir_path  ��Դ�ļ�����Ŀ¼*/
        /*! @var	#String cache_path  CEF�����ļ�����Ŀ¼*/
        /*! @var	#String=zh-CN locale  CEF���Ի���*/
        
        
        
        /*! @var	#Boolean=true manifest	�Ƿ������ⲿ�����ļ�manifest.json�����Ҫʹ�ã����ļ�������Ӧ�ó�������Ŀ¼��ͬ��ֻ��ʹ��Ansi���룬 ������Utf8, ����Ὣ����ת��ΪUTF8 */
        bool manifest;
        
        /*! @var	#String=783a02fd-b493-45ad-aa7f-ddbefeec1122 appID	����ΨһID��Ĭ��ΪNCUI�ĳ���ID. ��������Ӧ���޸ĸ�ֵ�������Ӱ�쵥��ģʽ��ʹ�ã�appID��ͬ�ĳ���ᱻ�ж�Ϊͬһ���������. */
        std::string appID;
        
        /*! @var	#Boolean=false singleInstance	����ģʽ,��ģʽ��ֻ����һ��ʵ�����У������������������򽫲���ɹ� */
        bool singleInstance;
        
        /*! @var	#Boolean=false showSplash	�Ƿ���ʾ��������.�����Ҫ�������棬��Ҫ�޸����ò���{@link ��������} */
        bool showSplash;
        
        /*! @var	#Boolean=false useNode	�Ƿ�ʹ��NodeJs. */
        bool useNode;
        
        /*! @var	#Boolean=false useNodeProcess �Ƿ��ڵ����Ľ�����ʹ��NodeJs.��useNode=trueʱ���ֶ���Ч������ڵ����Ľ�����ʹ��NodeJs,��ôNCUI��Node�����ڲ�ͬ�ؽ������У���ͨ��ͨ��������Ϣͬ�� */
        bool useNodeProcess;
        
        /** @var	#Int=0 ipcTimeout	����ͨ�ŵĳ�ʱʱ�䣬����������ʱ��û�еõ����ؽ��������Ϣ��������������������������������⡣Ĭ��Ϊ0��������ʱ��. */
        int64_t ipcTimeout;
        
        /*! @var	#String=main.js main	NodeJs��Ҫ���õ�JS�ļ�����λ��. useNodeΪtrue ʱ����ֵ��Ч */
        std::string main;
        
        /*! @var	#Boolean=false debugNode �Ƿ��������NodeJs.���δ�ڵ�����������NodeʱҪ����NodeJs ��Ҫʹ��NCUI-DEV.exe,��������������ģʽ������NCUI(�������������ͼ�ν�����һ�������д���) */
        bool debugNode;
        
        /*! @var	#String appPath �����ڴ����ϵ�����·��. */
        std::string appPath;
        
        /*! @var	#String appDir	��������Ŀ¼. */
        std::string appDir;
        
        /*! @var	#String appName	�������ƣ�������Ŀ¼����������չ��. */
        std::string appName;
        
        /*! @var	#String=%appDir%skin skinDir	Duilib skin Ŀ¼. */
        std::string skinDir;
        
        /*! @var	#String=%appDir% workDir	����Ŀ¼,Ĭ�����������Ŀ¼��ͬ. */
        std::string workDir;
        
        /*! @var	#String=%appDir%web webDir	html Դ����Ŀ¼. */
        std::string webDir;
        
        /*! @var	#String homeDir	����Ӧ�ó��������ļ����ļ��У�Ĭ���� appDataDir �ļ��и���Ӧ�õ�����. */
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
        
        /*!@var #String=%TEMP% temp	��ʱ�ļ���. */
        std::string temp;
        
        /*! @var #String desktop ��ǰ�û��������ļ���. */
        std::string desktop;
        /*!
         * @var #String documents �û��ĵ�Ŀ¼��·��.  */
        std::string documents;
        
        /*!
         * @var #Int startTime  ����ʱ�䣨����ʱ���ms��.
         */
        int64_t startTime;
        
        /*!
         * @var #Boolean=false debugMode �Ƿ��Ե���ģʽ����,Ĭ��false.��ģʽ��F12���Դ򿪵��Դ��ڣ�F5����ˢ��ҳ��
         */
        bool debugMode;
        
        /*! @var #Boolean=false clearCache �Ƿ���Ӧ�ó�������ʱ�����������棨�����ã�. */
        bool clearCache;
        
    };
}

#endif // AMO_APPSETTINGS_H__
