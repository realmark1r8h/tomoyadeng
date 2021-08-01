// Created by amoylel on 03/12/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_JSV8HANDLER_H__
#define AMO_JSV8HANDLER_H__

#include <functional>
#include <unordered_map>

#include "handler/CefHeader.hpp"

#include "transfer/FunctionWrapper.hpp"


#ifndef AMO_CEF_IMPL_NO_REFCOUNTING
#define AMO_CEF_IMPL_NO_REFCOUNTING(_TYPE) \
    void    AddRef() const { } \
    bool   Release() const { return false; } \
    bool HasOneRef() const { return true; }

#endif

// CefV8Value object��������
// ����JS���� �൱��var a = {};
#define AMO_CEF_BEGIN_OBJECT_FACTORY(ClassName)\
	public:\
		IMPLEMENT_REFCOUNTING(ClassName);\
    public: \
    virtual CefRefPtr<CefV8Value> getV8Object(CefRefPtr<CefV8Value> object = NULL) \
	{ \
		typedef ClassName ClassType;\
		CefRefPtr<CefV8Value> _object = object;\
		if(_object == NULL) _object = CefV8Value::CreateObject(NULL);
// �����������ɣ��������onGetV8Object�����ɵ�Object���������ط�����
#define AMO_CEF_END_OBJECT_FACTORY() \
		onGetV8Object(_object);\
        return _object; \
	}
// ��Object����Ӻ���
#define AMO_CEF_MAP_OBJECT_FUNCTION(Func)\
	 this->addFunction(#Func, std::bind(&ClassType::Func,\
										this,\
										std::placeholders::_1,\
										std::placeholders::_2,\
										std::placeholders::_3,\
										std::placeholders::_4));\
	_object->SetValue(#Func, \
					  CefV8Value::CreateFunction(#Func, this), \
					  V8_PROPERTY_ATTRIBUTE_NONE);

// ��Object���String
#define AMO_CEF_MAP_OBJECT_STRING(Func)\
	_object->SetValue(#Func,\
					 CefV8Value::CreateString(Func()), \
					 V8_PROPERTY_ATTRIBUTE_NONE);

#define AMO_CEF_MAP_OBJECT_PROPERTY(Func)\
	_object->SetValue(#Func,\
					 V8_ACCESS_CONTROL_DEFAULT, \
					 V8_PROPERTY_ATTRIBUTE_NONE);

namespace amo {



    /*!
     * @class	JsV8Handler
     *
     * @brief	JS ����C++ ����.
     * 			��Transfer ת��Ϊ V8 Object
     */
    class JsV8Handler : public CefV8Handler {
    public:
    
        /*!
         * @typedef	std::function < void(CefRefPtr<CefV8Value>, const CefV8ValueList&, CefRefPtr<CefV8Value>&, CefString&) > FuncType
         *
         * @brief	JS�������ö�ӦC++�ĺ�������.
         */
        
        typedef std::function < void(CefRefPtr<CefV8Value>,
                                     const CefV8ValueList&,
                                     CefRefPtr<CefV8Value>&,
                                     CefString&) > FuncType;
                                     
        /*!
         * @typedef	std::function<void(CefRefPtr<CefListValue>&, const CefV8ValueList&, int)> OnCopyParamsType
         *
         * @brief	�Զ��崦��������ƻص�����.
         */
        
        typedef std::function<void(CefRefPtr<CefListValue>&,
                                   const CefV8ValueList&,
                                   int)> OnCopyParamsType;
                                   
                                   
    public:
    
        JsV8Handler();
        
        virtual ~JsV8Handler();
        
        /*!
         * @fn	virtual CefRefPtr<JsV8Handler> JsV8Handler::createV8Handler()
         *
         * @brief	��������̳д����µ�Handler.
         *
         * @return	The new v 8 handler.
         */
        virtual CefRefPtr<JsV8Handler> createV8Handler();
        
        /*!
         * @fn	void JsV8Handler::setHandlerName(const std::string& strName)
         *
         * @brief	����Handler����.
         *
         * @param	strName	The name.
         */
        void setHandlerName(const std::string& strName);
        
        /*!
         * @fn	const std::string& JsV8Handler::getHandlerName() const
         *
         * @brief	��ȡHandler����.
         *
         * @return	The handler name.
         */
        const std::string& getHandlerName() const;
        
        ///*!
        // * @fn	virtual void JsV8Handler::setFunctions(
        // * 		const std::vector<FunctionWrapper>& vec)
        // *
        // * @brief	����JS�������Ƽ��ϣ�ͨ��Ϊ�������е�C++����.
        // *
        // * @param	vec	The vector.
        // */
        //virtual void setFunctions(const std::vector<FunctionWrapper>& vec);
        //
        ///*!
        // * @fn	virtual std::vector<amo::FunctionWrapper>& JsV8Handler::getFunctions()
        // *
        // * @brief	��ȡ���еĺ���.
        // *
        // * @return	The functions.
        // */
        //virtual std::vector<amo::FunctionWrapper>& getFunctions();
        
        //// ���õ�ǰHandler���õ�����ģ�鼯�ϣ��õ���Щģ��
        //
        //virtual void setModules(const std::vector<std::string>& vec);
        //
        ///*!
        // * @fn	virtual std::vector<std::string>& JsV8Handler::getModules()
        // *
        // * @brief	��ȡ��ǰHandler������������ģ��.
        // *
        // * @return	The modules.
        // */
        //virtual std::vector<std::string>& getModules();
        
        /*!
         * @fn	virtual CefRefPtr<CefV8Value> JsV8Handler::getV8Object(
         * 		 CefRefPtr<CefV8Value> object = NULL)
         *
         * @brief	ģ��JS���� ��ȡ��ǰHandler��Js���� ͨ���ú����ɣ�
         * 			���object== NULL �������µĶ��󣬷���ʹ�����еĶ���.
         *
         * @param	object	(Optional) the object.
         *
         * @return	The v 8 object.
         */
        virtual CefRefPtr<CefV8Value> getV8Object(
            CefRefPtr<CefV8Value> object = NULL);
            
        /*!
         * @fn	virtual void JsV8Handler::onGetV8Object(CefRefPtr<CefV8Value> object)
         *
         * @brief	ͨ�����ظú�������չobject.
         *
         * @param	object	The object.
         */
        virtual void onGetV8Object(CefRefPtr<CefV8Value> object);
        
        /*!
         * @fn	virtual bool JsV8Handler::Execute(const CefString& name,
         * 		CefRefPtr<CefV8Value> object,
         * 		const CefV8ValueList& arguments,
         * 		CefRefPtr<CefV8Value>& retval,
         * 		 CefString& exception) OVERRIDE
         *
         * @brief	JS����C++ʱ��ִ�еĺ���.
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
                             CefString& exception) OVERRIDE;
                             
        /*!
         * @fn	void JsV8Handler::addFunction(const std::string& key, FuncType fn)
         *
         * @brief	ע��JS����.
         *
         * @param	key	The key.
         * @param	fn 	The function.
         */
        void addFunction(const std::string& key, FuncType fn);
        
        /*!
         * @fn	std::vector<std::string> JsV8Handler::getAllKeys()
         *
         * @brief	��ȡ���е�JS��������.
         *
         * @return	all keys.
         */
        std::vector<std::string> getAllKeys();
        
        /*!
         * @fn	const int64_t& JsV8Handler::getID() const
         *
         * @brief	Gets the identifier.
         *
         * @return	The identifier.
         */
        const int64_t& getID() const;
        
        /*!
         * @fn	void JsV8Handler::setID(const int64_t& val)
         *
         * @brief	Sets an identifier.
         *
         * @param	val	The value.
         */
        void setID(const int64_t& val);
        
        
        FunctionWrapperMgr& getFuncMgr() ;
        
        void setFuncMgr(FunctionWrapperMgr& val);
        
    protected:
    
        /*! @brief ��ӦC++�е�Transfer objectID. */
        int64_t m_nID;
        /*! @brief	��Ҫִ�еĺ���, ��UI�̴߳��ݹ����ĺ�����. */
        std::vector<amo::FunctionWrapper> m_vecFunctions;
        /*! @brief	��Ҫ�õ���ģ��. */
        std::vector<std::string> m_vecModules;
        /*! @brief	ģ����. */
        std::string m_strHandlerName;
        
        FunctionWrapperMgr m_oFuncMgr;
        
        /*! @brief	ģ������ע��ĺ���. */
        std::unordered_map < std::string, FuncType> m_oFuncMap;
        
    };
    
    
    
}



#endif // AMO_JSV8HANDLER_H__
