// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_GEOLOCATIONHANDLER_H__
#define AMO_GEOLOCATIONHANDLER_H__

#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"
namespace amo {

    /*!
     * @class	GeolocationHandlerDelegate
     *
     * @brief	����λ���¼������࣬�����еķ�������IO�߳��б�����.
     */
    
    class GeolocationHandlerDelegate {
    public:
        GeolocationHandlerDelegate() {}
        
        virtual ~GeolocationHandlerDelegate() {}
        
        /*	virtual void OnRequestGeolocationPermission(CefRefPtr<CefBrowser> browser, const CefString& requesting_url, int request_id, CefRefPtr<CefGeolocationCallback> callback)
        	{
        
        	}
        
        	virtual void OnCancelGeolocationPermission(CefRefPtr<CefBrowser> browser, const CefString& requesting_url, int request_id)
        	{
        
        	}*/
#if CHROME_VERSION_BUILD >= 2272
        virtual bool OnRequestGeolocationPermission(
            CefRefPtr<CefBrowser> browser,
            const CefString& requesting_url,
            int request_id,
            CefRefPtr<CefGeolocationCallback> callback) {
            return false;
        }
#else
        virtual void OnRequestGeolocationPermission(CefRefPtr<CefBrowser> browser,
                const CefString& requesting_url,
                int request_id,
                CefRefPtr<CefGeolocationCallback> callback) {}
#endif
        
#if CHROME_VERSION_BUILD >= 2623
        virtual void OnCancelGeolocationPermission(CefRefPtr<CefBrowser> browser,
                int request_id) {}
#else
                
        virtual void OnCancelGeolocationPermission(CefRefPtr<CefBrowser> browser,
                const CefString& requesting_url,
                int request_id) {}
#endif
                
                
    };
    
    /*!
     * @class	GeolocationHandler
     *
     * @brief	����λ���¼������࣬�����еķ�������IO�߳��б�����.
     */
    
    class GeolocationHandler : public CefGeolocationHandler
        , public HandlerDelegate < GeolocationHandlerDelegate > {
    public:
        GeolocationHandler() {}
        
        virtual ~GeolocationHandler() {}
        
        
#if CHROME_VERSION_BUILD >= 2272
        
        /*!
         * @fn	virtual bool GeolocationHandler::OnRequestGeolocationPermission(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefString& requesting_url,
         * 		int request_id,
         * 		CefRefPtr<CefGeolocationCallback> callback);
         *
         * @brief	ҳ������λʱ����
         * 			B IO.
         *
         * @param	browser		  	The browser.
         * @param	requesting_url	URL of the requesting.
         * @param	request_id	  	Identifier for the request.
         * @param	callback	  	The callback.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnRequestGeolocationPermission(
            CefRefPtr<CefBrowser> browser,
            const CefString& requesting_url,
            int request_id,
            CefRefPtr<CefGeolocationCallback> callback) override;
#else
        virtual void OnRequestGeolocationPermission(CefRefPtr<CefBrowser> browser,
                const CefString& requesting_url,
                int request_id,
                CefRefPtr<CefGeolocationCallback> callback) override;
#endif
            
            
            
#if CHROME_VERSION_BUILD >= 2623
            
        /*!
         * @fn	virtual void GeolocationHandler::OnCancelGeolocationPermission(
         * 		CefRefPtr<CefBrowser> browser,
         * 		int request_id);
         *
         * @brief	ҳ��ȡ����λʱ����
         * 			B IO.
         *
         * @param	browser   	The browser.
         * @param	request_id	Identifier for the request.
         */
        
        virtual void OnCancelGeolocationPermission(CefRefPtr<CefBrowser> browser,
                int request_id) override;
#else
                
        virtual void OnCancelGeolocationPermission(CefRefPtr<CefBrowser> browser,
                const CefString& requesting_url,
                int request_id) override;
#endif
                
        IMPLEMENT_REFCOUNTING(GeolocationHandler);
        
        
    };
}
#endif // AMO_GEOLOCATIONHANDLER_H__

