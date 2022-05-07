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
     * @class AppSettings
     *
     * @chapter settings
     *
     * @brief	An application settings.
     *
     * @sa	CefSettings
     * @sa	BasicSettings
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
    
        /*! @var	#String manifest	�Ƿ������ⲿ�����ļ�. manifest.json ���������Ansi���룬 ������Utf8, ����Ὣ����ת��ΪUTF8 */
        bool manifest;
        
        /*! @var	#String appID	����ΨһID. */
        std::string appID;
        
        /*! @var	#String singleInstance	����ģʽ. */
        bool singleInstance;
        
        /*! @var	#String showSplash	�Ƿ���ʾ��������. */
        bool showSplash;
        
        /*! @var	#String useNode	�Ƿ�ʹ��NODEJS. */
        bool useNode;
        /*! @var	#String useNodeProcess	�Ƿ��ڵ����Ľ�����ʹ��NODEJS. */
        bool useNodeProcess;
        
        /** @var	#String ipcTimeout	����ͨ�ŵĳ�ʱʱ�䣬����������ʱ��û�еõ����ؽ��������Ϣ��������������������������������⡣Ĭ��Ϊ0��������ʱ��. */
        uint64_t ipcTimeout;
        
        /*! @var	#String main	main.js �ļ�λ��. */
        std::string main;
        
        /*! @var	#String debugNode	�Ƿ��������NODEJS. */
        bool debugNode;
        
        /*! @var	#String appPath	��������·��. */
        std::string appPath;
        
        /*! @var	#String appDir	��������Ŀ¼. */
        std::string appDir;
        
        /*! @var	#String appName	��������. */
        std::string appName;
        
        /*! @var	#String skinDir	Duilib skin Ŀ¼. */
        std::string skinDir;
        
        /*! @var	#String workDir	����Ŀ¼,Ĭ�����������Ŀ¼��ͬ. */
        std::string workDir;
        
        /*! @var	#String webDir	html Դ����Ŀ¼. */
        std::string webDir;
        
        
        /*! @var	#String homeDir	������Ӧ�ó��������ļ����ļ��У�Ĭ���� appDataDir �ļ��и���Ӧ�õ�����. */
        std::string homeDir;
        
        /*! @var	#String downloadsDir �û�����Ŀ¼��·��. */
        std::string downloadsDir;
        
        /*! @var	#String musicsDir	�û�����Ŀ¼��·��. */
        std::string musicsDir;
        
        /*! @var	#String picturesDir	�û�ͼƬĿ¼��·��. */
        std::string picturesDir;
        
        /*! @var	#String videosDir	�û���ƵĿ¼��·��. */
        std::string videosDir;
        
        /*! @var	#String dragClassName	��ק�ƶ����ڵ�Ԫ������. */
        std::string dragClassName;
        
        /*! @var	#String noDragClassName	��ֹ����Ԫ������. */
        std::string noDragClassName;
        
        /*! @var	#String=%APPDATA% appDataDir ��ǰ�û���Ӧ�������ļ���. */
        std::string appDataDir;
        
        /*!@var #String temp	��ʱ�ļ���. */
        std::string temp;
        
        /*! @var #String module  ��Ŀ¼. */
        std::string module;
        
        /*! @var #String desktop ��ǰ�û��������ļ���. */
        std::string desktop;
        /*!
         * @var #String documents �û��ĵ�Ŀ¼��·��.  */
        std::string documents;
        
        /*!
         * @var #Int startTime  ����ʱ��.
         */
        int64_t startTime;
        
        
        /*!
         * @var #Boolean=false debugMode �Ƿ��Ե���ģʽ����,Ĭ��false.��ģʽ��F12���Դ򿪵��Դ��ڣ�F5����ˢ��ҳ��
         */
        bool debugMode;
        
        
    };
}

#endif // AMO_APPSETTINGS_H__
