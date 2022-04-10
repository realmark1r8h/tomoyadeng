// Created by amoylel on 06/09/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_APPSETTINGS_H__
#define AMO_APPSETTINGS_H__

#include <amo/json.hpp>
#include <amo/string.hpp>
#include "handler/CefHeader.hpp"
#include "BasicSettings.h"

namespace amo {
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
    
        /*! @brief	�Ƿ������ⲿ�����ļ�. manifest.json ���������Ansi���룬 ������Utf8, ����Ὣ����ת��ΪUTF8 */
        bool manifest;
        
        /*! @brief	����ΨһID. */
        std::string appID;
        
        /*! @brief	����ģʽ. */
        bool singleInstance;
        
        /*! @brief	�Ƿ���ʾ��������. */
        bool showSplash;
        
        /*! @brief	�Ƿ�ʹ��NODEJS. */
        bool useNode;
        /*! @brief	�Ƿ��ڵ����Ľ�����ʹ��NODEJS. */
        bool useNodeProcess;
        
        /** @brief	����ͨ�ŵĳ�ʱʱ�䣬����������ʱ��û�еõ����ؽ��������Ϣ��������������������������������⡣Ĭ��Ϊ0��������ʱ��. */
        uint64_t ipcTimeout;
        
        /*! @brief	main.js �ļ�λ��. */
        std::string main;
        
        /*! @brief	�Ƿ��������NODEJS. */
        bool debugNode;
        
        /*! @brief	��������·��. */
        std::string appPath;
        
        /*! @brief	��������Ŀ¼. */
        std::string appDir;
        
        /*! @brief	��������. */
        std::string appName;
        
        /*! @brief	Duilib skin Ŀ¼. */
        std::string skinDir;
        
        /*! @brief	����Ŀ¼,Ĭ�����������Ŀ¼��ͬ. */
        std::string workDir;
        
        /*! @brief	html Դ����Ŀ¼. */
        std::string webDir;
        
        
        /*! @brief	������Ӧ�ó��������ļ����ļ��У�Ĭ���� appDataDir �ļ��и���Ӧ�õ�����. */
        std::string homeDir;
        
        /*! @brief	�û�����Ŀ¼��·��. */
        std::string downloadsDir;
        
        /*! @brief	�û�����Ŀ¼��·��. */
        std::string musicsDir;
        
        /*! @brief	�û�ͼƬĿ¼��·��. */
        std::string picturesDir;
        
        /*! @brief	�û���ƵĿ¼��·��. */
        std::string videosDir;
        
        /*! @brief	��ק�ƶ����ڵ�Ԫ������. */
        std::string dragClassName;
        
        /*! @brief	��ֹ����Ԫ������. */
        std::string noDragClassName;
        
        
        /*! @brief	��ǰ�û���Ӧ�������ļ��У�Ĭ�϶�Ӧ��.
        % APPDATA % Windows ��
        $XDG_CONFIG_HOME or ~ / .config Linux ��
        ~ / Library / Application Support macOS �� */
        std::string appDataDir;
        
        /*! @brief	��ʱ�ļ���. */
        std::string temp;
        
        /*! @brief	rcef ��Ŀ¼. */
        std::string module;
        /*! @brief	��ǰ�û��������ļ���. */
        std::string desktop;
        /*! @brief	�û��ĵ�Ŀ¼��·��. */
        std::string documents;
        
        /** @brief	����ʱ��. */
        int64_t startTime;
        
        /** @brief	�Ƿ��Ե���ģʽ����,Ĭ��false.��ģʽ��F12���Դ򿪵��Դ��ڣ�F5����ˢ��ҳ�� */
        bool debugMode;
        
        
    };
}

#endif // AMO_APPSETTINGS_H__
