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
         * @brief	����ADB����·��.
         *
         * @param	adbPath	Full pathname of the adb file.
         */
        
        void setAdbPath(const std::string& adbPath) {
            m_strAdbPath = adbPath;
        }
        
        /**
         * @fn	std::shared_ptr<process::result> adb::execute(const std::string& args, int nDelayMS = 0)
         *
         * @brief	ִ��adb����.
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
         * @brief	����ADB server.
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
         * @brief	��ȡ�����ֻ��豸.
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
         * @brief	��ȡ�ֻ��ϵ�Ӧ���б�.
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
                    std::cout << "���ݴ���" << std::endl;
                    continue;
                }
                
                ret.push_back({ ss[1], ss[0] });
                
            }
            
            return ret;
        }
        
        /**
         * @fn	amo::string AdbCommand::getPhoneInfoForBrand();
         *
         * @brief	��ȡ�ֻ�Ʒ��.
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
         * @brief	��ȡ�ֻ�IMEI����һ���ܳɹ�(�� Android 4.4 �����°汾��ͨ��).
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
            
            // һ���ֻ������ж��IMEI,ֻ��ֻ������һ��
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
         * @brief	��ȡ�ֻ��ͺ�.
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
         * @brief	ͨ��������ѯapp�Ƿ�װ.
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
         * @brief	���ֻ�����ȡ����.
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
                    $err("�ļ������ڣ�{0}", dstPath);
                    return false;
                }
                int nSize = file.size();
                $devel("����PULL�ļ�����ǰ��С[{0}],�ķ�ʱ��[{1}ms]", nSize, nTime);
                
                if (nSize < nTime) {
                
                    $err("PULL�ļ�д���ٶȲ�����,��ǰ�ļ���С[{0}],��ǰ�ķ�ʱ��[{1}]", nSize, nTime);
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
            
            // ������ص���ϢΪ�գ�����Ϣ��������1������Ϊʧ��
            if (message.empty() || message.size() > 1) {
                return false;
            }
            
            // ������ص���Ϣ�������not��������ʾʧ��
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
         * @brief	��װ�����ϵ�app���ֻ�.
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
                // ��װAPP5���ӳ�ʱ
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
         * @brief	ж��APP, Ĭ�ϱ�������.
         *
         * @param	strPackage	The package.
         * @param	bReserved 	(Optional) true if reserved.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool unistall(const std::string& strPackage, bool bReserved = true) {
            //TODO: �����Ͻ̳̿�����������
            // adb uninstall -k com.tencent.mm
            // adb shell pm uninstall �Ck com.tencent.mm
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
            
            // ���û����Ϣ����Ϊж�سɹ�
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
         * @brief	����App.
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
         * @brief	ǿ��ֹͣӦ��.
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
         * @brief	�ж��豸�Ƿ�root.
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
            
            // restarting adbd as root # ˵����rootȨ�� ��
            // ����adbd cannot run as root in production builds ��˵��û��rootȨ��
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
         * @brief	��ȡ���Ȩ��.
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
         * @brief	�ж�app�Ƿ��ܱ��� .
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
            
            // �����ݵĸ�ʽ
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
         * @brief	����Ӧ��.
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
                    $err("�����ļ������ڣ�{0}", localName);
                    return false;
                }
                int nSize = file.size();
                $devel("���ڱ����ļ�����ǰ��С[{0}],�ķ�ʱ��[{1}ms]������[{2}]", nSize, nTime, strPackage);
                
                if (nSize < nTime) {
                
                    $err("�����ļ�д���ٶȲ�����,��ǰ�ļ���С[{0}],��ǰ�ķ�ʱ��[{1}]", nSize, nTime);
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
            
            // ͨ���ļ��Ƿ���ں��ļ���С���ж��Ƿ񱸷ݳɹ���һ�������ı����ļ�����С��1M
            // ���ڰ�����һ�����Ա��ݵ�APP�ļ������ݳ����ĺ�С
            if (!file.is_exists() || file.size() < unsigned int(10000)) {
                return false;
            }
            
            return true;
        }
        
        /**
         * @fn	bool AdbCommand::sendKeyEvent(const std::string& strMsg);
         *
         * @brief	ģ�ⰴ��/����.
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
         * @brief	ģ�ⰴ��/����.
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
         * @brief	�����ı�.
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
         * @brief	����USB����ʱ�ֻ�������.
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
         * @brief	������Ļ.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool lightScreen() {
            return keyevent(224);
        }
        
        /**
         * @fn	bool adb::incBrightness()
         *
         * @brief	������Ļ����.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool incBrightness() {
            // ������Ļ����
            return keyevent(221);
        }
        
        /**
         * @fn	bool adb::decBrightness()
         *
         * @brief	������Ļ����.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool decBrightness() {
            // ������Ļ����
            return keyevent(220);
        }
        
        /**
         * @fn	bool AdbCommand::unlockPhone();
         *
         * @brief	������Ļ.
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
         * @brief	���ô�����Ϣ.
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
         * @brief	��ȡ������Ϣ.
         *
         * @return	The last error.
         */
        
        const std::string& getLastError() const {
            return m_strLastError;
        }
        
        /**
         * @fn	bool AdbCommand::waitForDevice()
         *
         * @brief	�ȴ�ֱ����Android�豸����.
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
         * @brief	��ͼ������.
         *
         * @param	strSavePath	Full pathname of the save file.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool screencap(const std::string& strSavePath) {
            //TODO: ��ͼδʵ��
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
         * @brief	��ȡϵͳ�汾.
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
            
            // ϵͳ�汾��
            return message[0];
        }
        
        /**
         * @fn	amo::string AdbCommand::sdkVersion();
         *
         * @brief	��ȡϵͳapi�汾.
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
            
            // SDK�汾��
            return message[0];
        }
        
        /**
         * @fn	amo::string AdbCommand::appVersion(const amo::string& packageName);
         *
         * @brief	��ȡAPP�İ汾��.
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
            
            // versionName �ĸ�ʽ    versionName=1.0.0
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
            // ��������ĳ�ʱʱ��Ϊ10��
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
                $err("�����ֻ�ʱadb����ʱ��ֹ");
                return false;
            }
            
            // versionName �ĸ�ʽ    versionName=1.0.0
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
                        $devel("�ֻ��������");
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
         * @brief	����ADB����.
         *
         * @param	args	(Optional) the arguments.
         *
         * @return	The new process.
         */
        
        std::shared_ptr<process> createProcess(const std::string& args = "") {
            std::shared_ptr<amo::process> pProcess(new process(m_strAdbPath));
            pProcess->setLogger(getLogger());
            // ������adb.exe �°汾��adb���ʹ��utf8����
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
        /** @brief	��׿�ֻ��豸ID. */
        std::string m_strDeviceID;
        /** @brief	������Ϣ. */
        std::string m_strLastError;
        std::shared_ptr<process> m_process;
        /** @brief	adb·��. */
        std::string m_strAdbPath;
        /** @brief	Ĭ��adb���ʱʱ��Ϊ30��. */
        const static int DEFAULT_ADB_TIMEOUT = 30000;
    };
}

#endif // AMO_ADB_HPP__


