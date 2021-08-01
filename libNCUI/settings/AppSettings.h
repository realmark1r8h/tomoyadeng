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
         * @brief	用户数据根目录.
         *
         * @return	The user home dir.
         */
        amo::string getUserHomeDir();
        
        /*!
         * @fn	std::string AppSettings::getSpecialFolder(int nType);
         *
         * @brief	获取Windows上的特殊目录.
         *
         * @param	nType	The type.
         *
         * @return	The special folder.
         */
        std::string getSpecialFolder(int nType);
    public:
    
    
    
        /*! @brief	是否允许外部配置文件. manifest.json 里面的内容Ansi编码， 不能用Utf8 */
        bool manifest;
        
        /*! @brief	是否显示启动画面. */
        bool showSplash;
        
        /*! @brief	是否使用NODEJS. */
        bool useNode;
        /*! @brief	是否在单独的进程中使用NODEJS. */
        bool useNodeProcess;
        
        /*! @brief	main.js 文件位置. */
        std::string main;
        
        /*! @brief	是否允许调试NODEJS. */
        bool debugNode;
        
        /*! @brief	程序完整路径. */
        std::string appPath;
        /*! @brief	程序所在目录. */
        std::string appDir;
        
        /*! @brief	程序名称. */
        std::string appName;
        
        /*! @brief	Duilib skin 目录. */
        std::string skinDir;
        /*! @brief	工作目录,默认与程序所有目录相同. */
        std::string workDir;
        /*! @brief	html 源代码目录. */
        std::string webDir;
        
        
        /*! @brief	储存你应用程序设置文件的文件夹，默认是 appDataDir 文件夹附加应用的名称. */
        std::string homeDir;
        /*! @brief	用户下载目录的路径. */
        std::string downloadsDir;
        /*! @brief	用户音乐目录的路径. */
        std::string musicsDir;
        /*! @brief	用户图片目录的路径. */
        std::string picturesDir;
        /*! @brief	用户视频目录的路径. */
        std::string videosDir;
        
        /*! @brief	拖拽移动窗口的元素类名. */
        std::string dragClassName;
        /*! @brief	禁止窗口元素类名. */
        std::string noDragClassName;
        
        
        /*! @brief	当前用户的应用数据文件夹，默认对应：.
        % APPDATA % Windows 中
        $XDG_CONFIG_HOME or ~ / .config Linux 中
        ~ / Library / Application Support macOS 中 */
        std::string appDataDir;
        
        /*! @brief	临时文件夹. */
        std::string temp;
        
        /*! @brief	rcef 库目录. */
        std::string module;
        /*! @brief	当前用户的桌面文件夹. */
        std::string desktop;
        /*! @brief	用户文档目录的路径. */
        std::string documents;
        
        
        
        
        
        
        
    };
}

#endif // AMO_APPSETTINGS_H__
