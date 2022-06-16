// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_DOWNLOADHANDLER_H__
#define AMO_DOWNLOADHANDLER_H__

#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"
namespace amo {

    /*!
     * @class	DownloadHandlerDelegate
     *
     * @brief	��������¼������࣬�����еķ�������UI�߳��б�����.
     */
    
    class DownloadHandlerDelegate {
    public:
        DownloadHandlerDelegate() {}
        
        virtual ~DownloadHandlerDelegate() {}
        
        
        virtual void OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefDownloadItem> download_item,
                                      const CefString& suggested_name,
                                      CefRefPtr<CefBeforeDownloadCallback> callback) {
                                      
        }
        
        virtual void OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
                                       CefRefPtr<CefDownloadItem> download_item,
                                       CefRefPtr<CefDownloadItemCallback> callback) {
                                       
        }
    };
    
    /*!
     * @class	DownloadHandler
     *
     * @brief	��������¼������࣬�����еķ�������UI�߳��б�����.
     */
    
    class DownloadHandler : public CefDownloadHandler
        , public HandlerDelegate < DownloadHandlerDelegate > {
    public:
        DownloadHandler() {}
        
        virtual ~DownloadHandler() {}
        
        IMPLEMENT_REFCOUNTING(DownloadHandler);
        
        /*!
         * @fn	virtual void DownloadHandler::OnBeforeDownload(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefDownloadItem> download_item,
         * 		const CefString& suggested_name,
         * 		CefRefPtr<CefBeforeDownloadCallback> callback);
         *
         * @brief	�ļ�����ǰ������Ĭ�ϻ�ȡ������
         * 			ִ��callbackʹ������Ч�� ���ܱ��� download_item ������
         * 			B UI.
         *
         * @param	browser		  	The browser.
         * @param	download_item 	The download item.
         * @param	suggested_name	Name of the suggested.
         * @param	callback	  	The callback.
         */
        
        virtual void OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefDownloadItem> download_item,
                                      const CefString& suggested_name,
                                      CefRefPtr<CefBeforeDownloadCallback> callback);
                                      
        /*!
         * @fn	virtual void DownloadHandler::OnDownloadUpdated(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefDownloadItem> download_item,
         * 		CefRefPtr<CefDownloadItemCallback> callback);
         *
         * @brief	�ļ�����״̬�ص�
         * 			���ܱ��� download_item ������
         * 			B UI.
         *
         * @param	browser		 	The browser.
         * @param	download_item	The download item.
         * @param	callback	 	The callback.
         */
        
        virtual void OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
                                       CefRefPtr<CefDownloadItem> download_item,
                                       CefRefPtr<CefDownloadItemCallback> callback);
    public:
    
        static void setBeforeDownloadCallback(std::function<bool(
                CefRefPtr<CefBrowser>,
                CefRefPtr<CefDownloadItem>,
                const CefString &,
                CefRefPtr<CefBeforeDownloadCallback>&)> val);
                
        static void setDownloadUpdateCallback(std::function<bool(
                CefRefPtr<CefBrowser>,
                CefRefPtr<CefDownloadItem>,
                CefRefPtr<CefDownloadItemCallback>&)> val);
                
        static bool hasBeforeDownloadCallback();
        
        static bool hasDownloadUpdateCallback();
        
        static std::function<bool(CefRefPtr<CefBrowser>,
                                  CefRefPtr<CefDownloadItem>,
                                  const CefString&,
                                  CefRefPtr<CefBeforeDownloadCallback>&)> m_fnBeforeDownload;
                                  
        static std::function < bool(CefRefPtr<CefBrowser>,
                                    CefRefPtr<CefDownloadItem>,
                                    CefRefPtr<CefDownloadItemCallback>&)> m_fnDownloadUpdate;
                                    
                                    
    };
    
}
#endif // AMO_DOWNLOADHANDLER_H__
