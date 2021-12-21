// Created by amoylel on 12/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_ADB_HPP__
#define AMO_ADB_HPP__



#include <memory>
#include <string>
#include <amo/process.hpp>
#include <amo/file.hpp>
#include <amo/string.hpp>
#include <vector>
#include <amo/timer.hpp>

namespace amo {
    class adb
        : public log_object
        , public std::enable_shared_from_this<adb> {
    public:
        static std::shared_ptr<adb> create(const std::string& deviceID = "") {
            std::shared_ptr<adb> pCommand(new adb(deviceID));
            return pCommand;
        }
        
    public:
        adb(const std::string& deviceID = "")
            : m_strDeviceID(deviceID) {
            setAdbPath("adb/adb.exe");
            
        }
        
        /**
         * @fn	void adb::setAdbPath(const std::string& adbPath)
         *
         * @brief	设置ADB程序路径.
         *
         * @param	adbPath	Full pathname of the adb file.
         */
        
        void setAdbPath(const std::string& adbPath) {
            m_strAdbPath = adbPath;
        }
        
        /**
         * @fn	std::shared_ptr<process::result> adb::execute(const std::string& args, int nDelayMS = 0)
         *
         * @brief	执行adb命令.
         *
         * @param	args		The arguments.
         * @param	nDelayMS	(Optional) the delay in milliseconds.
         *
         * @return	A std::shared_ptr&lt;process::result&gt;
         */
        
        std::shared_ptr<process::result> execute(const std::string& args, int nTimeoutMS = 0) {
            auto pProcess = createProcess(args);
            pProcess->start();
            return pProcess->getResult(nTimeoutMS);
        }
        
        /**
         * @fn	bool AdbCommand::restartService();
         *
         * @brief	重启ADB server.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool restartService() {
            {
                auto pProcess = createProcess();
                pProcess->clearArgs();
                pProcess->start("kill-server");
                
                auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            }
            
            {
                auto pProcess = createProcess();
                pProcess->clearArgs();
                pProcess->start("start-server");
                
                auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            }
            
            return true;
        }
        
        /**
         * @fn	std::vector<amo::string> AdbCommand::getDevicelist();
         *
         * @brief	获取所有手机设备.
         *
         * @return	The devicelist.
         */
        
        std::vector<amo::string> getDevicelist() {
            std::vector<amo::string> ret;
            auto pProcess = createProcess();
            pProcess->clearArgs();
            pProcess->start("devices");
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return ret;
            }
            
            const std::vector<amo::string>& message = result->removeBlankMessage()->getResultMessage();
            
            for (auto& p : message) {
                if (p.find("\tdevice") != -1) {
                    std::vector<amo::string> vec = p.split("\t");
                    ret.push_back(vec[0]);
                }
            }
            
            return ret;
        }
        
        /**
         * @fn	std::vector<std::pair<amo::string, amo::string> > AdbCommand::getAppList(const std::string& keys = "");
         *
         * @brief	获取手机上的应用列表.
         *
         * @param	keys	(Optional) the keys.
         *
         * @return	The application list.
         */
        
        std::vector<std::pair<amo::string, amo::string> > getAppList(const std::string& keys = "") {
            std::vector<std::pair<amo::string, amo::string> > ret;
            auto pProcess = createProcess();
            
            pProcess->addArgs("shell pm list packages -3 -f ");
            pProcess->addArgs(keys);
            pProcess->start();
            
            std::vector<amo::string> message = pProcess->getResult(DEFAULT_ADB_TIMEOUT)->removeBlankMessage()->getResultMessage();
            
            for (auto& p : message) {
                amo::string str = p;
                str.replace("package:", "");
                std::vector<amo::string> ss = str.split("=");
                
                if (ss.size() != 2) {
                    //
                    std::cout << "数据错误。" << std::endl;
                    continue;
                }
                
                ret.push_back({ ss[1], ss[0] });
                
            }
            
            return ret;
        }
        
        /**
         * @fn	amo::string AdbCommand::getPhoneInfoForBrand();
         *
         * @brief	获取手机品牌.
         *
         * @return	The phone information for brand.
         */
        
        amo::string getPhoneInfoForBrand() {
            auto pProcess = createProcess();
            pProcess->start("-d shell getprop ro.product.brand");
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return"";
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.size() != 1) {
                return "";
            }
            
            return message[0];
        }
        
        /**
         * @fn	amo::string AdbCommand::getPhoneInfoForIMEI();
         *
         * @brief	获取手机IMEI，不一定能成功(在 Android 4.4 及以下版本可通过).
         *
         * @return	The phone information for imei.
         */
        
        amo::string getPhoneInfoForIMEI() {
            auto pProcess = createProcess();
            pProcess->start("-d shell dumpsys iphonesubinfo");
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return"";
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            // 一个手机可能有多个IMEI,只里只处理了一个
            for (auto& p : message) {
                amo::string strVal = p;
                
                if (strVal.find("Device ID") != -1) {
                    strVal.replace("Device ID =", "").replace("\r\n", "");
                    return strVal;
                }
            }
            
            return "";
        }
        
        /**
         * @fn	amo::string AdbCommand::getPhoneInfoForModel();
         *
         * @brief	获取手机型号.
         *
         * @return	The phone information for model.
         */
        
        amo::string getPhoneInfoForModel() {
            auto pProcess = createProcess();
            pProcess->start("-d shell getprop ro.product.model");
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return"";
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return "";
            }
            
            amo::string strVal = *message.rbegin();
            strVal.replace("\r\n", "").trim_right(" ");
            return strVal;
        }
        
        /**
         * @fn	bool AdbCommand::isInstalled(const std::string& strApp);
         *
         * @brief	通过包名查询app是否安装.
         *
         * @param	strApp	The application.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool isInstalled(const std::string& strApp) {
            auto pProcess = createProcess("shell pm path ");
            pProcess->start(strApp);
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return false;
            }
            
            for (auto& p : message) {
                if (p.find("package") != -1) {
                    return true;
                }
            }
            
            return false;
        }
        
        /**
         * @fn	bool AdbCommand::pull(const std::string& srcPath, const std::string& dstPath);
         *
         * @brief	从手机中拉取数据.
         *
         * @param	srcPath	Full pathname of the source file.
         * @param	dstPath	Full pathname of the destination file.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool pull(const std::string& srcPath, const std::string& dstPath) {
            auto pProcess = createProcess("pull ");
            pProcess->addArgs(srcPath);
            pProcess->addArgs(dstPath);
            pProcess->start();
            
            int64_t nLastTimestamp = 0;
            auto result = pProcess->getResult(0, 0, [ & ](int64_t nTime)->bool {
            
                if (nLastTimestamp + DEFAULT_ADB_TIMEOUT > nTime) {
                    return true;
                }
                
                nLastTimestamp = nTime;
                
                amo::file file(dstPath);
                
                if (!file.is_exists()) {
                    $err("文件不存在：{0}", dstPath);
                    return false;
                }
                int nSize = file.size();
                $devel("正在PULL文件，当前大小[{0}],耗费时间[{1}ms]", nSize, nTime);
                
                if (nSize < nTime) {
                
                    $err("PULL文件写入速度不正常,当前文件大小[{0}],当前耗费时间[{1}]", nSize, nTime);
                    return false;
                }
                
                return true;
            });
            
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> vec = result->removeBlankMessage()->getResultMessage();
            std::vector<amo::string> message;
            
            for (auto& p : vec) {
                if (p.begin_with("[")) {
                    continue;
                }
                
                message.push_back(p);
            }
            
            // 如果返回的消息为空，都消息条数大于1，都视为失败
            if (message.empty() || message.size() > 1) {
                return false;
            }
            
            // 如果返回的消息里面包含not字样，表示失败
            for (auto iter = message.rbegin(); iter != message.rend(); ++iter) {
                amo::string retval = *iter;
                
                if (retval.to_upper().find("NOT") != -1) {
                    return false;
                }
            }
            
            return true;
        }
        
        /**
         * @fn	bool AdbCommand::install(const std::string& strAppFile, int nRetry = 5);
         *
         * @brief	安装电脑上的app到手机.
         *
         * @param	strAppFile	The application file.
         * @param	nRetry	  	(Optional) the retry.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool install(const std::string& strAppFile, int nRetry = 5) {
            if (nRetry < 1) {
                nRetry = 1;
            }
            
            if (nRetry > 30) {
                nRetry = 30;
            }
            
            /*
               amo::file fi(strAppFile);
               size_t nSize = fi.size();
               int nDelay = nSize  / (1000 * 10)*/;
            
            for (int i = 0; i < nRetry; ++i) {
                //auto pProcess = createProcess("install -r -d ");
                auto pProcess = createProcess("install ");
                pProcess->start(strAppFile);
                // 安装APP5分钟超时
                auto result = pProcess->getResult(20 * DEFAULT_ADB_TIMEOUT);
                
                
                if (!result->isSuccess()) {
                    continue;
                }
                
                std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
                
                if (message.empty()) {
                    continue;
                }
                
                bool bInstalled = true;
                
                for (auto iter = message.rbegin(); iter != message.rend(); ++iter) {
                    amo::string retval = *iter;
                    
                    if (retval.to_upper().find("FAILURE") != -1) {
                        bInstalled = false;
                        break;
                    }
                }
                
                if (bInstalled) {
                    return true;
                }
            }
            
            return false;
        }
        
        /**
         * @fn	bool AdbCommand::unistall(const std::string& strPackage, bool bReserved = true);
         *
         * @brief	卸载APP, 默认保留数据.
         *
         * @param	strPackage	The package.
         * @param	bReserved 	(Optional) true if reserved.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool unistall(const std::string& strPackage, bool bReserved = true) {
            //TODO: 看网上教程可能是有两步
            // adb uninstall -k com.tencent.mm
            // adb shell pm uninstall –k com.tencent.mm
            auto pProcess = createProcess("shell pm uninstall ");
            
            if (bReserved) {
                pProcess->addArgs("-k");
            }
            
            pProcess->start(strPackage);
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            // 如果没有消息，认为卸载成功
            if (message.empty()) {
                return true;
            }
            
            for (auto iter = message.rbegin(); iter != message.rend(); ++iter) {
                amo::string retval = *iter;
                
                if (retval.to_upper().find("SUCCESS") != -1) {
                    return true;
                }
            }
            
            
            return false;
        }
        
        /**
         * @fn	bool AdbCommand::start(const std::string& activity);
         *
         * @brief	运行App.
         *
         * @param	activity	The activity.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool start(const std::string& activity) {
            auto pProcess = createProcess("shell am start -n ");
            pProcess->start(activity);
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return false;
            }
            
            for (auto iter = message.rbegin(); iter != message.rend(); ++iter) {
                amo::string retval = *iter;
                
                if (retval.to_upper().find("ERROR") != -1) {
                    return false;
                }
            }
            
            
            
            
            return true;
        }
        
        /**
         * @fn	bool AdbCommand::stop(const std::string& strPackageName);
         *
         * @brief	强制停止应用.
         *
         * @param	strPackageName	Name of the package.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool stop(const std::string& strPackageName) {
            auto pProcess = createProcess("shell am force-stop ");
            pProcess->start(strPackageName);
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return true;
            }
            
            return false;
        }
        
        /**
         * @fn	bool AdbCommand::isRoot();
         *
         * @brief	判断设备是否root.
         *
         * @return	true if root, false if not.
         */
        
        bool isRoot() {
            auto pProcess = createProcess("root");
            pProcess->start();
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            // restarting adbd as root # 说明有root权限 ，
            // 若是adbd cannot run as root in production builds 则说明没有root权限
            for (auto& p : message) {
                if (p.find("cannot") != -1) {
                    return false;
                }
            }
            
            return true;
        }
        
        /**
         * @fn	bool AdbCommand::chmod777(const std::string& strPath);
         *
         * @brief	获取最高权限.
         *
         * @param	strPath	Full pathname of the file.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool chmod777(const std::string& strPath) {
            auto pProcess = createProcess("shell \"su -c chmod 777 '");
            pProcess->addArgs(strPath);
            pProcess->addArgs("'\"");
            pProcess->start();
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            
            for (auto& p : message) {
                // /system/bin/sh: su: not found
                if (p.find("not") != -1
                        || p.find("Permission denied") != -1) {
                    return false;
                }
            }
            
            return true;
        }
        
        /**
         * @fn	bool AdbCommand::allowBackup(const std::string strPackage);
         *
         * @brief	判断app是否能备份 .
         *
         * @param	strPackage	The package.
         *
         * @return	true if we allow backup, false if not.
         */
        
        bool allowBackup(const std::string& strPackage) {
            auto pProcess = createProcess("shell dumpsys package ");
            pProcess->start(strPackage);
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            // 允许备份的格式
            // flags = [DEBUGGABLE HAS_CODE ALLOW_CLEAR_USER_DATA ALLOW_BACKUP]
            for (auto& p : message) {
            
                amo::string str = p;
                str = str.to_upper();
                
                if (str.find("ALLOW_BACKUP") != -1) {
                    return true;
                }
            }
            
            return false;
        }
        
        /**
         * @fn	bool AdbCommand::backup(const std::string& strPackage, const std::string& localName);
         *
         * @brief	备份应用.
         *
         * @param	strPackage	The package.
         * @param	localName 	Name of the local.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool backup(const std::string& strPackage, const std::string& localName) {
            auto pProcess = createProcess("backup -f ");
            pProcess->addArgs(localName);
            pProcess->addArgs(strPackage);
            pProcess->start();
            
            int64_t nLastTimestamp = 0;
            auto result = pProcess->getResult(0, 0, [ & ](int64_t nTime)->bool {
            
                if (nLastTimestamp + DEFAULT_ADB_TIMEOUT > nTime) {
                    return true;
                }
                
                nLastTimestamp = nTime;
                
                amo::file file(localName);
                
                if (!file.is_exists()) {
                    $err("备份文件不存在：{0}", localName);
                    return false;
                }
                int nSize = file.size();
                $devel("正在备份文件，当前大小[{0}],耗费时间[{1}ms]，包名[{2}]", nSize, nTime, strPackage);
                
                if (nSize < nTime) {
                
                    $err("备份文件写入速度不正常,当前文件大小[{0}],当前耗费时间[{1}]", nSize, nTime);
                    return false;
                }
                return true;
            });
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.size() > 1) {
                return false;
            }
            
            
            amo::file file(localName);
            
            // 通过文件是否存在和文件大小来判断是否备份成功，一个正常的备份文件不会小于1M
            // 现在包含了一个测试备份的APP文件，备份出来的很小
            if (!file.is_exists() || file.size() < unsigned int(10000)) {
                return false;
            }
            
            return true;
        }
        
        /**
         * @fn	bool AdbCommand::sendKeyEvent(const std::string& strMsg);
         *
         * @brief	模拟按键/输入.
         *
         * @param	strMsg	The message.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool keyevent(const std::string& strMsg) {
        
            auto pProcess = createProcess("shell input keyevent ");
            pProcess->start(strMsg);
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return true;
            }
            
            return false;
        }
        
        bool sayString(const std::string& strMsg) {
            auto pProcess = createProcess("shell input text ");
            pProcess->start(strMsg);
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return true;
            }
            
            return false;
        }
        
        /**
         * @fn	bool AdbCommand::keyevent(const int nKey);
         *
         * @brief	模拟按键/输入.
         *
         * @param	nKey	The key.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool keyevent(const int nKey) {
            return keyevent(amo::string::from_number<int>(nKey));
        }
        
        /**
         * @fn	bool AdbCommand::swipe(const std::string& strMsg);
         *
         * @brief	发送文本.
         *
         * @param	strMsg	The message.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool swipe(const std::string& strMsg) {
            auto pProcess = createProcess("shell input swipe 300 1000 300 500  ");
            pProcess->start();
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return true;
            }
            
            return false;
        }
        
        /**
         * @fn	bool AdbCommand::powerStayonUSB();
         *
         * @brief	保持USB连接时手机不锁屏.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool powerStayonUSB() {
            auto pProcess = createProcess("shell svc power stayon usb");
            pProcess->start();
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return true;
            }
            
            return false;
        }
        
        /**
         * @fn	bool AdbCommand::lightScreen();
         *
         * @brief	点亮屏幕.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool lightScreen() {
            return keyevent(224);
        }
        
        /**
         * @fn	bool adb::incBrightness()
         *
         * @brief	增加屏幕亮度.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool incBrightness() {
            // 增加屏幕亮度
            return keyevent(221);
        }
        
        /**
         * @fn	bool adb::decBrightness()
         *
         * @brief	降低屏幕亮度.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool decBrightness() {
            // 降低屏幕亮度
            return keyevent(220);
        }
        
        /**
         * @fn	bool AdbCommand::unlockPhone();
         *
         * @brief	解锁屏幕.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool unlockPhone() {
            if (!lightScreen()) {
                return false;
            }
            
            auto pProcess = createProcess("shell input swipe 300 1000 300 500  ");
            pProcess->start();
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return true;
            }
            
            return false;
        }
        
        /**
         * @fn	bool AdbCommand::closeUSBModel();
         *
         * @brief	设置错误消息.
         *
         * @param	strMsg	The message.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool closeUSBModel() {
        
            auto pProcess = createProcess("shell settings put global adb_enabled 0");
            pProcess->start();
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return true;
            }
            
            return false;
        }
        
        void setLastError(const std::string& strMsg) {
            m_strLastError = strMsg;
        }
        
        /**
         * @fn	const std::string& AdbCommand::getLastError()const;
         *
         * @brief	获取错误消息.
         *
         * @return	The last error.
         */
        
        const std::string& getLastError() const {
            return m_strLastError;
        }
        
        /**
         * @fn	bool AdbCommand::waitForDevice()
         *
         * @brief	等待直到有Android设备连接.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool waitForDevice(int nMaxWaitTime = 0) {
            auto pProcess = createProcess("wait-for-device");
            pProcess->start();
            
            auto result = pProcess->getResult(nMaxWaitTime);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            return true;
        }
        
        /**
         * @fn	bool AdbCommand::screencap(const std::string& strSavePath);
         *
         * @brief	截图并保存.
         *
         * @param	strSavePath	Full pathname of the save file.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool screencap(const std::string& strSavePath) {
            //TODO: 截图未实现
            auto pProcess = createProcess("adb shell screencap -p  ");
            pProcess->start();
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            return true;
        }
        
        /**
         * @fn	amo::string AdbCommand::releaseVersion();
         *
         * @brief	获取系统版本.
         *
         * @return	An amo::string.
         */
        
        amo::string releaseVersion() {
            auto pProcess = createProcess(" shell getprop ro.build.version.release");
            pProcess->start();
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return "";
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.size() != 1) {
                return "";
            }
            
            for (auto& p : message) {
                auto str = p.to_upper();
                
                if (str.find("FAILED") != -1) {
                    return "";
                }
                
                if (str.find("ACK") != -1) {
                    return "";
                }
                
            }
            
            // 系统版本号
            return message[0];
        }
        
        /**
         * @fn	amo::string AdbCommand::sdkVersion();
         *
         * @brief	获取系统api版本.
         *
         * @return	An amo::string.
         */
        
        amo::string sdkVersion() {
            auto pProcess = createProcess(" shell getprop ro.build.version.sdk");
            pProcess->start();
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return "";
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.size() != 1) {
                return "";
            }
            
            for (auto& p : message) {
                auto str = p.to_upper();
                
                if (str.find("FAILED") != -1) {
                    return "";
                }
                
                if (str.find("ACK") != -1) {
                    return "";
                }
                
            }
            
            // SDK版本号
            return message[0];
        }
        
        /**
         * @fn	amo::string AdbCommand::appVersion(const amo::string& packageName);
         *
         * @brief	获取APP的版本号.
         *
         * @param	packageName	Name of the package.
         *
         * @return	An amo::string.
         */
        
        amo::string appVersion(const amo::string& packageName) {
            auto pProcess = createProcess("shell dumpsys package ");
            pProcess->start(packageName);
            
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return "";
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            // versionName 的格式    versionName=1.0.0
            for (auto& p : message) {
            
                amo::string str = p;
                str = str.to_upper();
                
                if (str.find("VERSIONNAME=") != -1) {
                    std::vector<amo::string> vec = str.split("=");
                    
                    if (vec.size() != 2) {
                        continue;
                    }
                    
                    return vec[1].trim();
                }
            }
            
            return "";
        }
        
        bool startServer() {
            auto pProcess = createProcess("start-server");
            pProcess->start();
            // 开启服务的超时时间为10秒
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return true;
            }
            
            for (auto& p : message) {
                auto str = p.to_upper();
                
                if (str.find("FAILED") != -1) {
                    return false;
                }
                
                if (str.find("ACK") != -1) {
                    return false;
                }
                
                
            }
            
            return true;
        }
        
        bool killServer() {
            auto pProcess = createProcess("kill-server");
            pProcess->start();
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return true;
            }
            
            
            for (auto& p : message) {
                auto str = p.to_upper();
                
                if (str.find("FAILED") != -1) {
                    return false;
                }
                
                if (str.find("ACK") != -1) {
                    return false;
                }
                
            }
            
            return true;
        }
        
        bool killProcess() {
            if (!m_process) {
                return true;
            }
            
            return m_process->kill();
        }
        
        bool reboot(int nWaitTime = 300000) {
            amo::timer t;
            auto pProcess = createProcess("reboot");
            pProcess->start();
            auto result = pProcess->getResult(DEFAULT_ADB_TIMEOUT);
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty() && t.elapsed() > DEFAULT_ADB_TIMEOUT) {
                $err("重启手机时adb被超时终止");
                return false;
            }
            
            // versionName 的格式    versionName=1.0.0
            for (auto& p : message) {
                if (p.find("error")  != -1) {
                    return false;
                }
            }
            
            t.restart();
            
            do {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                std::vector<amo::string> vec = getDevicelist();
                
                for (auto& p : vec) {
                    if (p == m_strDeviceID) {
                        $devel("手机重启完成");
                        return true;
                    }
                    
                }
            } while (t.elapsed() < nWaitTime);
            
            
            return false;
            
        }
    protected:
    
        /**
         * @fn	std::shared_ptr<process> AdbCommand::createProcess(const std::string& args = "");
         *
         * @brief	创建ADB进程.
         *
         * @param	args	(Optional) the arguments.
         *
         * @return	The new process.
         */
        
        std::shared_ptr<process> createProcess(const std::string& args = "") {
            std::shared_ptr<amo::process> pProcess(new process(m_strAdbPath));
            pProcess->setLogger(getLogger());
            // 升级了adb.exe 新版本的adb输出使用utf8编码
            pProcess->setUTF8(true);
            
            if (!m_strDeviceID.empty()) {
                std::string args = "-s ";
                args += m_strDeviceID;
                pProcess->addArgs(args);
            }
            
            if (!args.empty()) {
                pProcess->addArgs(args);
            }
            
            m_process = pProcess;
            
            return pProcess;
        }
        
    private:
        /** @brief	安卓手机设备ID. */
        std::string m_strDeviceID;
        /** @brief	错误消息. */
        std::string m_strLastError;
        std::shared_ptr<process> m_process;
        /** @brief	adb路径. */
        std::string m_strAdbPath;
        /** @brief	默认adb命令超时时间为30秒. */
        const static int DEFAULT_ADB_TIMEOUT = 30000;
    };
}

#endif // AMO_ADB_HPP__


