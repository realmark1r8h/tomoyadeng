// Created by amoylel on 08/19/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DOWNLOADERTRANSFER_H__
#define AMO_DOWNLOADERTRANSFER_H__


#include <memory>

#include <amo/singleton.hpp>

#include "handler/CefHeader.hpp"
#include "transfer/ClassTransfer.hpp"

namespace amo {

    class UIMessageEmitter;
    class DownloaderSettings;
    
    /*!
     * @class	Downloader
     *
     * @brief	�ļ������࣬ʹ������������ع��������ļ�.
     */
    
    class DownloaderTransfer
        : public ClassTransfer
        , public amo::singleton < DownloaderTransfer > {
    public:
    
        /*!
         * @enum	DLCommand
         *
         * @brief	Values that represent dl commands.
         */
        
        enum DLCommand {
            ///< An enum constant representing the dl normal option
            DL_NORMAL,
            DL_CANCEL,
            DL_RESUME,
            DL_PAUSE,
        };
    public:
    
        DownloaderTransfer();
        
        /*!
         * @fn	DownloaderTransfer::Downloader(std::shared_ptr<DownloaderSettings> pSettings);
         *
         * @tag constructor
         *
         * @brief	����һ�������࣬���������ļ�.
         *
         * @param	#JsonObject ���ز���.<br>
         * 						[**String**]	url �����ļ���url,���������URL��֮ǰ�����������ض���url��ͬ������֮ǰ�Ķ�������Ĳ�����������.<br>
         * 						[**String**]	file �ļ�����·��, Ĭ�ϻ����url�Զ�����.<br>
         * 						[**Boolean**]	autoDownload �Ƿ��Զ���ʼ����,Ĭ��Ϊtrue.<br>
         * 						[**Boolean**]	forceReplace �Ƿ�ǿ���滻�Ѿ����ڵ��ļ�,Ĭ��Ϊtrue.
         *
         * @return #Object ����һ��Downloaderʵ��.
         * @example
         *
        		 ```
        		 include('Downloader');
        		 window.downloader = new Downloader({
        			url: 'https://dldir1.qq.com/qqfile/qq/TIM1.2.0/21645/TIM1.2.0.exe'
        		 });
        		 // �������ؿ�ʼ�¼�
        		 window.downloader.on('start', function(item){
        
        			console.log('���ؿ�ʼ');
        			console.log(item);
        		 });
        
        		 window.downloader.on('resume', function(item){
        			 console.log('���ػָ�');
        		 });
        
        		 window.downloader.on('pause', function(item){
        			 console.log('������ͣ');
        		 });
        
        		 window.downloader.on('cancel', function(item){
        			console.log('����ȡ��');
        		 });
        
        		 window.downloader.on('canceled', function(item){
        			 console.log('����ȡ�����');
        		 });
        
        		 window.downloader.on('update', function(item){
        			console.log('���ؽ��ȣ�' + item.percentComplete);
        		 });
        
        		 window.downloader.on('complete', function(item){
        			 console.log('�������');
        		 });
        		 ```
         *
         */
        
        DownloaderTransfer(std::shared_ptr<DownloaderSettings> pSettings);
        
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        
        /*!
         * @fn	Any DownloaderTransfer::start(IPCMessage::SmartType msg);
         *
         * @brief	��ʼ����.
         *
         * @return	��.
         */
        
        Any start(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any DownloaderTransfer::resume(IPCMessage::SmartType msg);
         *
         * @brief	�ָ���ǰ����.
         *
         * @return	��.
         */
        
        Any resume(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any DownloaderTransfer::pause(IPCMessage::SmartType msg);
         *
         * @brief	��ͣ����.
         *
         *
         * @return	��.
         */
        
        Any pause(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any DownloaderTransfer::cancel(IPCMessage::SmartType msg);
         *
         * @brief	ȡ������.
         *
         * @return	��.
         */
        
        Any cancel(IPCMessage::SmartType msg);
        
        
        /*!
        * @event	Any DownloaderTransfer::start(IPCMessage::SmartType msg);
        *
        * @brief	��ʼ����ʱ����.
        * @param	#JsonObject <br>
        * 						[**Boolean**] isValid ��ǰ�����Ƿ���Ч.<br>
        * 						[**Boolean**] isInProgress ��ǰ�����Ƿ���Ч.<br>
        * 						[**Boolean**] isComplete ��ǰ�����Ƿ���Ч.<br>
        * 						[**Boolean**] isCanceled ��ǰ�����Ƿ���Ч.<br>
        * 						<br>
        * 						[**Int**] currentSpeed ��ǰ�����ٶ�.<br>
        * 						[**Int**] percentComplete ������ɰٷֱȣ��������-1����ʾδ��ȡ���������ļ��Ĵ�С.<br>
        * 						[**Int**] totalBytes ���ֽ���.<br>
        * 						[**Int**] receivedBytes �ѽ��յ��ֽ���.<br>
        * 						<br>
        * 						[**Double**] startTime ���ؿ�ʼ��ʱ��.<br>
        * 						[**Double**] endTime ���ؽ�����ʱ��.<br>
        *						<br>
        * 						[**String**] fullPath �����ļ������������·��.<br>
        * 						[**String**] id ��ǰ���ص�Ψһ��ʶ��.<br>
        * 						[**String**] url URL.<br>
        * 						[**String**] originalUrl �ض���֮ǰ��ԭʼURL��������ض���Ļ���.<br>
        * 						[**String**] suggestedFileName �����������ļ���.<br>
        * 						[**String**] contentDisposition  .<br>
        * 						[**String**] mimeType MIME����.<br>
        *
        *
        *
        * @return	��.
        */
        
        /*!
        * @event	Any DownloaderTransfer::resume(IPCMessage::SmartType msg);
        *
        * @brief	���ػָ�ʱ����.
        *
        * @param #JsonObject ��start�¼��еĲ�����ͬ.
        *
        *
        * @return	��.
        */
        
        /*!
        * @event	Any DownloaderTransfer::pause(IPCMessage::SmartType msg);
        *
        * @brief	��ͣ����ʱ����.
        *
        * @param #JsonObject ��start�¼��еĲ�����ͬ.
        *
        * @return	��.
        */
        
        /*!
        * @event	Any DownloaderTransfer::cancel(IPCMessage::SmartType msg);
        *
        * @brief	ȡ������ʱ����.
        *
        * @param #JsonObject ��start�¼��еĲ�����ͬ.
        *
        * @return	��.
        */
        
        /*!
        * @event	Any DownloaderTransfer::canceled(IPCMessage::SmartType msg);
        *
        * @brief	ȡ�����غ�ʱ����.
        *
        * @param #JsonObject ��start�¼��еĲ�����ͬ.
        *
        * @return	��.
        */
        
        /*!
        * @event	Any DownloaderTransfer::update(IPCMessage::SmartType msg);
        *
        * @brief	�������ݸ���ʱ����.
        *
        * @param #JsonObject ��start�¼��еĲ�����ͬ.
        *
        * @return	��.
        */
        
        
        /*!
        * @event	Any DownloaderTransfer::complete(IPCMessage::SmartType msg);
        *
        * @brief	�������ʱ����.
        *
        * @param #JsonObject ��start�¼��еĲ�����ͬ.
        *
        * @return	��.
        */
        
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DownloaderTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(start, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(resume, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(pause, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(cancel, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    public:
    
        /*!
         * @fn	void DownloaderTransfer::startDownload();
         * @ignore
         * @brief	Starts a download.
         */
        
        void startDownload();
        
        /*!
         * @fn	CefRefPtr<CefFrame> DownloaderTransfer::getFrame() const;
         *
         * @brief	Gets the frame.
         *
         * @return	The frame.
         */
        
        CefRefPtr<CefFrame> getFrame() const;
        
        /*!
         * @fn	void DownloaderTransfer::setFrame(CefRefPtr<CefFrame> val);
         * @ignore
         * @brief	Sets a frame.
         *
         * @param	val	The value.
         */
        
        void setFrame(CefRefPtr<CefFrame> val);
        
        /*!
         * @fn	CefRefPtr<CefBrowser> DownloaderTransfer::getBrowser() const;
         * @ignore
         * @brief	Gets the browser.
         *
         * @return	The browser.
         */
        
        CefRefPtr<CefBrowser> getBrowser() const;
        
        /*!
         * @fn	void DownloaderTransfer::setBrowser(CefRefPtr<CefBrowser> val);
         * @ignore
         * @brief	Sets a browser.
         *
         * @param	val	The value.
         */
        
        void setBrowser(CefRefPtr<CefBrowser> val);
        
        /*!
         * @fn	void DownloaderTransfer::removeDownloader(const std::string& url);
         * @ignore
         * @brief	Removes the downloader described by URL.
         *
         * @param	url	URL of the document.
         */
        
        void removeDownloader(const std::string& url);
        
        /*!
         * @fn	std::shared_ptr<UIMessageEmitter> DownloaderTransfer::getMessageEmitter();
         * @ignore
         * @brief	Gets message emitter.
         *
         * @return	The message emitter.
         */
        
        std::shared_ptr<UIMessageEmitter>  getMessageEmitter();
        
        /*!
         * @fn	bool DownloaderTransfer::OnBeforeDownload(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefDownloadItem> download_item,
         * 		const CefString& suggested_name,
         * 		CefRefPtr<CefBeforeDownloadCallback>& callback);
         * @ignore
         * @brief	Executes the before download action.
         *
         * @param	browser				The browser.
         * @param	download_item   	The download item.
         * @param	suggested_name  	Name of the suggested.
         * @param [in,out]	callback	The callback.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefDownloadItem> download_item,
                              const CefString& suggested_name,
                              CefRefPtr<CefBeforeDownloadCallback>& callback);
                              
        /*!
         * @fn	bool DownloaderTransfer::OnDownloadUpdated(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefDownloadItem> download_item,
         * 		CefRefPtr<CefDownloadItemCallback>& callback);
         * @ignore
         * @brief	Executes the download updated action.
         *
         * @param	browser				The browser.
         * @param	download_item   	The download item.
         * @param [in,out]	callback	The callback.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefDownloadItem> download_item,
                               CefRefPtr<CefDownloadItemCallback>& callback);
                               
        /*!
         * @fn	amo::json DownloaderTransfer::downloadItemToJson(CefRefPtr<CefDownloadItem>& item);
         * @ignore
         * @brief	Downloads the item to JSON described by item.
         *
         * @param [in,out]	item	The item.
         *
         * @return	An amo::json.
         */
        
        amo::json downloadItemToJson(CefRefPtr<CefDownloadItem>& item);
    private:
    
        /*! @brief	The frame. */
        CefRefPtr<CefFrame> m_pFrame;
        /*! @brief	The browser. */
        CefRefPtr<CefBrowser> m_pBrowser;
        /*! @brief	The download callback. */
        CefRefPtr<CefBeforeDownloadCallback> m_pDownloadCallback;
        /*! @brief	The download item callback. */
        CefRefPtr<CefDownloadItemCallback> m_pDownloadItemCallback;
        
        /*! @brief	The downloader settings. */
        std::shared_ptr<DownloaderSettings> m_pDownloaderSettings;
        
        /*! @brief	The downloader map. */
        std::unordered_map<std::string, std::shared_ptr<DownloaderTransfer> > m_oDownloaderMap;
        
        /*! @brief	The command. */
        DLCommand m_nCommand;
    };
}


#endif // AMO_DOWNLOADERTRANSFER_H__

