

// Created by amoylel on 05/20/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TYPECONVERTOR_H__
#define AMO_TYPECONVERTOR_H__

#include <vector>
#include <amo/unordered_map.hpp>
#include "handler/CefHeader.hpp"
#include <sstream>
#include "ipc/Any.hpp"


namespace amo {
    class Any;
    class json;
    
    
    template <class T1, class T2>
    struct pair_hash2 {
    
        std::size_t operator()(const std::pair<T1, T2>& p) const {
            std::stringstream stream;
            stream << p.first << "," << p.second;
            std::string str = stream.str();
            return std::hash<std::string>()(str);
            /*auto h1 = std::hash < T1 > {}(p.first);
            auto h2 = std::hash < T2 > {}(p.second);
            return h1 ^ h2;*/
        }
    };
    
    /*!
     * @class	TypeConvertor
     *
     * @brief	A type convertor.
     */
    
    class TypeConvertor {
    public:
        typedef std::vector< std::pair<int64_t, CefRefPtr<CefV8Value> > >
        ObjectContainer;
        
    public:
        TypeConvertor(CefRefPtr<CefFrame> frame = NULL);
        
        ~TypeConvertor();
        
        /*!
         * @fn	bool TypeConvertor::getRendererObject() const;
         *
         * @brief	Gets renderer object.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool getRendererObject() const;
        
        /*!
         * @fn	void TypeConvertor::setRendererObject(bool val);
         *
         * @brief	Sets renderer object.
         *
         * @param	val	true to value.
         */
        
        void setRendererObject(bool val);
        
        /*!
         * @fn	CefRefPtr<CefV8Value> TypeConvertor::ParseJsonToObject(amo::json& json);
         *
         * @brief	Parse JSON to object.
         *
         * @param [in,out]	json	The JSON.
         *
         * @return	A CefRefPtr&lt;CefV8Value&gt;
         */
        
        CefRefPtr<CefV8Value> ParseJsonToObject(amo::json& json);
        
        /*!
         * @fn	CefRefPtr<CefV8Value> TypeConvertor::ParseSingleJsonToObject(amo::json& json);
         *
         * @brief	Parse single JSON to object.
         *
         * @param [in,out]	json	The JSON.
         *
         * @return	A CefRefPtr&lt;CefV8Value&gt;
         */
        
        CefRefPtr<CefV8Value> ParseSingleJsonToObject(amo::json& json);
        
        /*!
         * @fn	Any TypeConvertor::ParseObjectToJson(CefRefPtr<CefV8Value> pObject);
         *
         * @brief	Parse object to JSON.
         *
         * @param	pObject	The object.
         *
         * @return	Any.
         */
        
        Any ParseObjectToJson(CefRefPtr<CefV8Value> pObject);
        
        /*!
         * @fn	Any TypeConvertor::ParseSingleObjectToAny(CefRefPtr<CefV8Value> pValue);
         *
         * @brief	Parse single object to any.
         *
         * @param	pValue	The value.
         *
         * @return	Any.
         */
        
        Any ParseSingleObjectToAny(CefRefPtr<CefV8Value> pValue);
        
        /*!
         * @fn	void TypeConvertor::AddAnyToJson(amo::json& json, const std::string& key, Any& val);
         *
         * @brief	Adds any to JSON.
         *
         * @param [in,out]	json	The JSON.
         * @param	key				The key.
         * @param [in,out]	val 	The value.
         */
        
        void AddAnyToJson(amo::json& json, const std::string& key, Any& val);
        
        /*!
         * @fn	void TypeConvertor::AddAnyToJsonArray(amo::json& json, Any& val);
         *
         * @brief	Adds any to JSON array to 'val'.
         *
         * @param [in,out]	json	The JSON.
         * @param [in,out]	val 	The value.
         */
        
        void AddAnyToJsonArray(amo::json& json, Any& val);
        
        /*!
         * @fn	std::string TypeConvertor::transferObject(CefRefPtr<CefV8Value> pValue);
         *
         * @brief	Transfer object.
         *
         * @param	pValue	The value.
         *
         * @return	A std::string.
         */
        
        std::string transferObject(CefRefPtr<CefV8Value> pValue);
        
        /*!
         * @fn	std::string TypeConvertor::V8ValueType(CefRefPtr<CefV8Value> object);
         *
         * @brief	获取V8类型.
         *
         * @param	object	The object.
         *
         * @return	A std::string.
         */
        static std::string V8ValueType(CefRefPtr<CefV8Value> object);
        
        /*!
         * @fn	amo::json TypeConvertor::ObjectToJson(CefRefPtr<CefV8Value> pV8Value);
         *
         * @brief	将JS Object 转换为 JSON.
         *
         * @param	pV8Value	The v 8 value.
         *
         * @return	An amo::json.
         */
        amo::json ObjectToJson(CefRefPtr<CefV8Value> pV8Value);
        
        /*!
         * @fn	CefRefPtr<CefV8Value> TypeConvertor::JsonToObject(const std::string& str);
         *
         * @brief	将普通的JSON对象转换为JS Object..
         *
         * @param	str	The string.
         *
         * @return	A CefRefPtr&lt;CefV8Value&gt;
         */
        
        CefRefPtr<CefV8Value> JsonToObject(const std::string& str);
        
        /*!
         * @fn	CefRefPtr<CefV8Value> TypeConvertor::JsonToObject(amo::json& json);
         *
         * @brief	将普通的JSON对象转换为JS Object.
         *
         * @param 	json	The JSON.
         *
         * @return	A CefRefPtr&lt;CefV8Value&gt;
         */
        CefRefPtr<CefV8Value> JsonToObject(amo::json& json);
        
        /*!
         * @fn	Any TypeConvertor::toAny(CefRefPtr<CefV8Value> pValue);
         *
         * @brief	将JS类型转换为IPCMessage可用的Any类型.
         *
         * @param	pValue	The value.
         *
         * @return	pValue as Any.
         */
        Any toAny(CefRefPtr<CefV8Value> pValue);
        
        /*!
         * @fn	CefRefPtr<CefV8Value> TypeConvertor::toV8Value(std::shared_ptr<AnyArgsList> args, int index);
         *
         * @brief	将Any类型转换为V8类型.
         *
         * @param	args 	The arguments.
         * @param	index	Zero-based index of the.
         *
         * @return	The given data converted to a CefRefPtr&lt;CefV8Value&gt;
         */
        CefRefPtr<CefV8Value> toV8Value(std::shared_ptr<AnyArgsList> args,
                                        int index);
        /*!
         * @fn	CefRefPtr<CefV8Value> TypeConvertor::toV8Value(Any& any);
         *
         * @brief	将Any类型转换为V8类型.
         *
         * @param 	any	any.
         *
         * @return	any as a CefRefPtr&lt;CefV8Value&gt;
         */
        CefRefPtr<CefV8Value> toV8Value(Any& any);
        
        /*!
         * @fn	static CefRefPtr<CefV8Value> TypeConvertor::getClassObject(int64_t nID, CefRefPtr<CefFrame> frame = NULL);
         *
         * @brief	保存Js对象.
         *
         * @param	nID  	The identifier.
         * @param	frame	(Optional) the frame.
         *
         * @return	The class object.
         */
        
        static CefRefPtr<CefV8Value>  getClassObject(int64_t nID,
                CefRefPtr<CefFrame> frame = NULL);
                
        /*!
         * @fn	static CefRefPtr<CefV8Value> TypeConvertor::getClassObject(int64_t nFrameID, int64_t nID);
         *
         * @brief	Gets class object.
         *
         * @param	nFrameID	Identifier for the frame.
         * @param	nID			The identifier.
         *
         * @return	The class object.
         */
        
        static CefRefPtr<CefV8Value>  getClassObject(int64_t nFrameID,
                int64_t nID);
                
        /*!
         * @fn	static ObjectContainer TypeConvertor::getClassObject(const std::vector<int64_t>& frames, int64_t nID);
         *
         * @brief	Gets class object.
         *
         * @param	frames	The frames.
         * @param	nID   	The identifier.
         *
         * @return	The class object.
         */
        
        static ObjectContainer getClassObject(const std::vector<int64_t>& frames,
                                              int64_t nID);
        /*!
         * @fn	static void TypeConvertor::addClassObject(int64_t nID, CefRefPtr<CefV8Value> pObject);
         *
         * @brief	添加Object对象到缓存中.
         *
         * @param	nID	   	The identifier.
         * @param	pObject	The object.
         */
        static void addClassObject(int64_t nID, CefRefPtr<CefV8Value> pObject);
        /*!
         * @fn	static void TypeConvertor::clearClassObject(int64_t nFrameID);
         *
         * @brief	删除所给Frame的缓存Object.
         * 			一般是在Frame被销毁时调用
         *
         * @param	nFrameID	Identifier for the frame.
         */
        static void clearClassObject(int64_t nFrameID);
        
        static void removeClassObject(int64_t nFrameID, int64_t nObjectID);
    protected:
        /*! @brief	The object map. */
        static std::unordered_map<std::pair<int64_t, int64_t>,
               CefRefPtr<CefV8Value>,
               pair_hash2<int64_t, int64_t> > m_oObjectMap;
               
        /*! @brief	The frame. */
        CefRefPtr<CefFrame> pFrame;
        /*! @brief	The context. */
        CefRefPtr<CefV8Context> pContext;
        /*! @brief	true to renderer object. */
        bool m_bRendererObject;
        
    };
}

#endif // AMO_TYPECONVERTOR_H__

