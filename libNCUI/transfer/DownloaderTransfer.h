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
    
        /*!
         * @fn	DownloaderTransfer::DownloaderTransfer();
         *
         * @brief	Default constructor.
         */
        
        DownloaderTransfer();
        
        /*!
         * @fn	DownloaderTransfer::DownloaderTransfer(std::shared_ptr<DownloaderSettings> pSettings);
         *
         * @brief	Constructor.
         *
         * @param	pSettings	Options for controlling the operation.
         */
        
        DownloaderTransfer(std::shared_ptr<DownloaderSettings> pSettings);
        
        /*!
         * @fn	virtual Any DownloaderTransfer::onCreateClass(IPCMessage::SmartType msg) override;
         *
         * @brief	Executes the create class action.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        
        /*!
         * @fn	Any DownloaderTransfer::start(IPCMessage::SmartType msg);
         *
         * @brief	Starts the given message.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any start(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any DownloaderTransfer::resume(IPCMessage::SmartType msg);
         *
         * @brief	Resumes the given message.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any resume(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any DownloaderTransfer::pause(IPCMessage::SmartType msg);
         *
         * @brief	Pauses the given message.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any pause(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any DownloaderTransfer::cancel(IPCMessage::SmartType msg);
         *
         * @brief	Cancels the given message.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any cancel(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DownloaderTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(start, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(resume, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(pause, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(cancel, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    public:
    
        /*!
         * @fn	void DownloaderTransfer::startDownload();
         *
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
         *
         * @brief	Sets a frame.
         *
         * @param	val	The value.
         */
        
        void setFrame(CefRefPtr<CefFrame> val);
        
        /*!
         * @fn	CefRefPtr<CefBrowser> DownloaderTransfer::getBrowser() const;
         *
         * @brief	Gets the browser.
         *
         * @return	The browser.
         */
        
        CefRefPtr<CefBrowser> getBrowser() const;
        
        /*!
         * @fn	void DownloaderTransfer::setBrowser(CefRefPtr<CefBrowser> val);
         *
         * @brief	Sets a browser.
         *
         * @param	val	The value.
         */
        
        void setBrowser(CefRefPtr<CefBrowser> val);
        
        /*!
         * @fn	void DownloaderTransfer::removeDownloader(const std::string& url);
         *
         * @brief	Removes the downloader described by URL.
         *
         * @param	url	URL of the document.
         */
        
        void removeDownloader(const std::string& url);
        
        /*!
         * @fn	std::shared_ptr<UIMessageEmitter> DownloaderTransfer::getMessageEmitter();
         *
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
         *
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
         *
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
         *
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

