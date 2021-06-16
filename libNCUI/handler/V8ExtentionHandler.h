// Created by amoylel on 06/13/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_V8EXTENTIONHANDLER_H__
#define AMO_V8EXTENTIONHANDLER_H__





#include <memory>

#include "handler/CefHeader.hpp"

namespace amo {

    class JsV8Handler;
    class ClassTransfer;
    
    template <class T1, class T2>
    struct pair_hash {
    
        std::size_t operator()(const std::pair<T1, T2>& p) {
            auto h1 = std::hash < T1 > {}(p.first);
            auto h2 = std::hash < T2 > {}(p.second);
            return h1 ^ h2;
        }
    };
    
    /*!
     * @class	V8ExtentionHandler
     *
     * @brief	��չ������.
     */
    
    class V8ExtentionHandler : public CefV8Handler {
    public:
        V8ExtentionHandler();
        ~V8ExtentionHandler();
        // �����
        //void addClass(const std::string& strClass, FunctionWrapperMgr& mgr);
        
        /*!
         * @fn	void V8ExtentionHandler::registerExternalTransfer(
         * 		int nBrowserID,
         * 		std::shared_ptr<ClassTransfer> pTransfer);
         *
         * @brief	Registers the external transfer.
         *
         * @param	nBrowserID	Identifier for the browser.
         * @param	pTransfer 	The transfer.
         */
        
        void registerExternalTransfer(int nBrowserID,
                                      std::shared_ptr<ClassTransfer> pTransfer);
                                      
        /*!
         * @fn	bool V8ExtentionHandler::loadExternalTransfer(
         * 		const std::string& strClass,
         * 		CefRefPtr<CefBrowser> browser);
         *
         * @brief	Loads external transfer.
         *
         * @param	strClass	The class.
         * @param	browser 	The browser.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool loadExternalTransfer(const std::string& strClass,
                                  CefRefPtr<CefBrowser> browser);
                                  
        /*!
         * @fn	CefRefPtr<JsV8Handler> V8ExtentionHandler::fromClass(
         * 		const std::string& strClass,
         * 		CefRefPtr<CefBrowser> browser);
         *
         * @brief	�����д���Handler.
         *
         * @param	strClass	The class.
         * @param	browser 	The browser.
         *
         * @return	A CefRefPtr&lt;JsV8Handler&gt;
         */
        
        CefRefPtr<JsV8Handler> fromClass(const std::string& strClass, CefRefPtr<CefBrowser> browser);
        
        /*!
         * @fn	CefRefPtr<CefV8Value> V8ExtentionHandler::includeFromRendererThread(
         * 		const std::string& module);
         *
         * @brief	Include from renderer thread.
         *
         * @param	module	The module.
         *
         * @return	A CefRefPtr&lt;CefV8Value&gt;
         */
        
        CefRefPtr<CefV8Value> includeFromRendererThread(const std::string& module);
        
        /*!
         * @fn	CefRefPtr<CefV8Value> V8ExtentionHandler::includeFromBrowserThread(
         * 		const std::string& module);
         *
         * @brief	Include from browser thread.
         *
         * @param	module	The module.
         *
         * @return	A CefRefPtr&lt;CefV8Value&gt;
         */
        
        CefRefPtr<CefV8Value> includeFromBrowserThread(const std::string& module);
        
        /*!
         * @fn	virtual bool V8ExtentionHandler::Execute(
         * 		const CefString& name,
         * 		CefRefPtr<CefV8Value> object,
         * 		const CefV8ValueList& arguments,
         * 		CefRefPtr<CefV8Value>& retval,
         * 		CefString& exception) override;
         *
         * @brief	Executes.
         *
         * @param	name			 	The name.
         * @param	object			 	The object.
         * @param	arguments		 	The arguments.
         * @param 	retval   	The retval.
         * @param 	exception	The exception.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool Execute(const CefString& name,
                             CefRefPtr<CefV8Value> object,
                             const CefV8ValueList& arguments,
                             CefRefPtr<CefV8Value>& retval,
                             CefString& exception) override;
                             
        /*!
         * @fn	bool V8ExtentionHandler::includeDepends(const std::vector<std::string>& vec);
         *
         * @brief	Include depends.
         *
         * @param	vec	The vector.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool includeDepends(const std::vector<std::string>& vec);
        
        /*!
         * @fn	void V8ExtentionHandler::OnContextReleased(int64 nFrameID);
         *
         * @brief	Executes the context released action.
         *
         * @param	nFrameID	Identifier for the frame.
         */
        
        void OnContextReleased(int64 nFrameID);
        
        /*!
         * @fn	void V8ExtentionHandler::OnBrowserDestory(int nBrowserID);
         *
         * @brief	Executes the browser destory action.
         *
         * @param	nBrowserID	Identifier for the browser.
         */
        
        void OnBrowserDestory(int nBrowserID);
        IMPLEMENT_REFCOUNTING(V8ExtentionHandler);
        
        
    private:
        //std::unordered_map<std::pair<std::string, int>,
        //    CefRefPtr<JsV8Handler>, pair_hash<std::string, int> > m_oClassHandler;
        //std::unordered_map<std::string, FunctionWrapperMgr > m_oClassSet;							//!< ��������������г�Ա����
        std::unordered_map<std::string, std::shared_ptr<ClassTransfer> > m_oClassTransferMap;
        
        /*! @brief	Set the module belongs to. */
        std::set<std::pair<std::string, int64_t> > m_oModuleSet;
    };
    
}
#endif // AMO_V8EXTENTIONHANDLER_H__