// Created by amoylel on 04/11/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_JSCLASSV8HANDLER_H__
#define AMO_JSCLASSV8HANDLER_H__

#include "module/JSV8Handler.h"

namespace amo {

    /*!
     * @class	JsClassObjectV8Accessor
     *
     * @brief	��������������������⣬��ʱû����.
     */
    
    class JsClassObjectV8Accessor : public CefV8Accessor {
    public:
    
        /*!
         * @fn	virtual bool JsClassObjectV8Accessor::Get(
         * 		const CefString& name,
         * 		const CefRefPtr<CefV8Value> object,
         * 		CefRefPtr<CefV8Value>& retval,
         * 		CefString& exception) override
         *
         * @brief	Gets.
         *
         * @param	name			 	The name.
         * @param	object			 	The object.
         * @param [in,out]	retval   	The retval.
         * @param [in,out]	exception	The exception.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool Get(const CefString& name,
                         const CefRefPtr<CefV8Value> object,
                         CefRefPtr<CefV8Value>& retval,
                         CefString& exception) override {
            if (m_fnGet) {
                CefV8ValueList list;
                return m_fnGet(name, object, list, retval, exception);
            } else {
                return false;
            }
        }
        
        /*!
         * @fn	bool JsClassObjectV8Accessor::Set(
         * 		const CefString& name,
         * 		const CefRefPtr<CefV8Value> object,
         * 		const CefRefPtr<CefV8Value> value,
         * 		CefString& exception)
         *
         * @brief	Sets.
         *
         * @param	name			 	The name.
         * @param	object			 	The object.
         * @param	value			 	The value.
         * @param [in,out]	exception	The exception.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool Set(const CefString& name,
                 const CefRefPtr<CefV8Value> object,
                 const CefRefPtr<CefV8Value> value,
                 CefString& exception) {
            if (m_fnGet) {
                CefV8ValueList list;
                list.push_back(value);
                CefRefPtr<CefV8Value> retval = CefV8Value::CreateUndefined();
                return m_fnGet(name, object, list, retval, exception);
            } else {
                return false;
            }
            
        }
        
        /*!
         * @fn	void JsClassObjectV8Accessor::SetGetSetCallback(
         * 		std::function < bool(const CefString&,
         * 		 CefRefPtr<CefV8Value>,
         * 		 const CefV8ValueList&,
         * 		 CefRefPtr<CefV8Value>&,
         * 		 CefString&) > fn)
         *
         * @brief	Callback, called when the set get set.
         *
         * @param	fn	The function.
         */
        
        void SetGetSetCallback(
            std::function < bool(const CefString&,
                                 CefRefPtr<CefV8Value>,
                                 const CefV8ValueList&,
                                 CefRefPtr<CefV8Value>&,
                                 CefString&) > fn) {
            m_fnGet = fn;
        }
        
        IMPLEMENT_REFCOUNTING(JsClassObjectV8Accessor);
        
    protected:
        std::function < bool(const CefString&,
                             CefRefPtr<CefV8Value>,
                             const CefV8ValueList&,
                             CefRefPtr<CefV8Value>&,
                             CefString&) > m_fnGet;
    };
    
    // class ����UI�߳��е�Transfer
    class JsClassV8Handler : public JsV8Handler {
    public:
    
        JsClassV8Handler();
        
        virtual ~JsClassV8Handler();
        
        
        /*!
         * @fn	virtual CefRefPtr<CefV8Value> JsClassV8Handler::getV8Object(
         * 		CefRefPtr<CefV8Value> object = NULL);
         *
         * @brief	��ȡ���JS����.
         * 			����ʹ�ú괴������������Ҫ��������һ�����������캯����
         * 			����ʹ��new Object();
         *
         * @param	object	(Optional) the object.
         * 					���object�����ڣ���ô����һ���µĶ���
         * 					���object���ڣ���ôֱ��������������������
         *
         * @return	The v8 object.
         */
        virtual CefRefPtr<CefV8Value> getV8Object(
            CefRefPtr<CefV8Value> object = NULL) override;
            
        /*!
         * @fn	virtual void JsClassV8Handler::onGetV8Object(
         * 		CefRefPtr<CefV8Value> object) override;
         *
         * @brief	����������Ĵ�������������Խ�һЩ��̬����֮��Ķ������ӵ�����.
         *
         * @param	object	The object.
         */
        virtual void onGetV8Object(CefRefPtr<CefV8Value> object) override;
        
        /*!
         * @fn	virtual bool JsClassV8Handler::Execute(const CefString& name,
         * 		 CefRefPtr<CefV8Value> object,
         * 		 const CefV8ValueList& arguments,
         * 		  CefRefPtr<CefV8Value>& retval,
         * 		  CefString& exception) override;
         *
         * @brief	����Execute����.
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
         * @fn	bool JsClassV8Handler::isRendererClass() const;
         *
         * @brief	�жϵ�ǰ���õ�C++�����Ƿ�������Ⱦ������ִ��.
         *
         * @return	true if renderer class, false if not.
         */
        bool isRendererClass() const;
        
        /*!
         * @fn	void JsClassV8Handler::setRendererClass(bool val);
         *
         * @brief	���õ�ǰ���C++��������Ⱦ������ִ��.
         *
         * @param	val	true to value.
         */
        void setRendererClass(bool val);
        /*!
         * @fn	void JsClassV8Handler::nativeObject(CefRefPtr<CefV8Value> object,
         * 		 const CefV8ValueList& arguments,
         * 		  CefRefPtr<CefV8Value>& retval,
         * 		   CefString& exception);
         *
         * @brief	js���� ʱ�����ж�����һ������Transfer����.
         *
         * @param	name	The name.
         *
         * @param	object			 	The object.
         * @param	arguments		 	The arguments.
         * @param 	retval   	The retval.
         * @param 	exception	The exception.
         */
        void nativeObject(CefRefPtr<CefV8Value> object,
                          const CefV8ValueList& arguments,
                          CefRefPtr<CefV8Value>& retval,
                          CefString& exception);
        /*!
         * @fn	void JsClassV8Handler::nativeToJson(CefRefPtr<CefV8Value> object,
         * 		 const CefV8ValueList& arguments,
         * 		  CefRefPtr<CefV8Value>& retval,
         * 		   CefString& exception);
         *
         * @brief	�����ض���ת��Ϊ JSON�ַ���.
         *
         * @param	name	The name.
         *
         * @param	object			 	The object.
         * @param	arguments		 	The arguments.
         * @param 	retval   	The retval.
         * @param 	exception	The exception.
         */
        void nativeToJson(CefRefPtr<CefV8Value> object,
                          const CefV8ValueList& arguments,
                          CefRefPtr<CefV8Value>& retval,
                          CefString& exception);
                          
        IMPLEMENT_REFCOUNTING(JsClassV8Handler);
    protected:
    
        bool m_bRendererClass;
        CefRefPtr<JsClassObjectV8Accessor> m_pAccessor;
    };
}

#endif // AMO_JSCLASSV8HANDLER_H__
