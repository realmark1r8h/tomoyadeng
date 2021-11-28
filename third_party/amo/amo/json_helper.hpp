// Created by amoylel on 11/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_ENTITYHELPER_HPP__
#define AMO_ENTITYHELPER_HPP__

#include <string>
#include <vector>
#include <memory>
#include <amo/json.hpp>
#include <amo/string.hpp>


template<typename T>
static T typeFromJson(const amo::json& json, const std::string& key) {
    return json.get<T>(key);
}

template<typename T>
static void jsonFromType(const T& val, amo::json& json, const std::string& key)  {
    json.put(key, val);
    return;
}


// ×¢²áºê ¿ªÊ¼
#define ENTITY_ARGS_SET_BEGIN(ClassName)\
	void join( amo::json& other)  {\
		typedef ClassName ClassType;\
		amo::json json = this->toJson();\
		json.join(other);\
		*this = *ClassType::fromJson(json);\
		return;\
	}\
	virtual amo::json toJson() const{\
		amo::json json;\

#ifndef ENTITY_ARGS_SET
#define  ENTITY_ARGS_SET(val) (jsonFromType<decltype(this->##val)>(this->##val, json, #val));
#endif

#ifndef ENTITY_ARGS_SMART_SET
#define  ENTITY_ARGS_SMART_SET(val) (jsonFromSmartType<decltype(this->##val)>(this->##val, json, #val));
#endif

// ×¢²áºê ½áÊø
#define ENTITY_ARGS_SET_END()\
		this->onToJson(json); \
		return json;\
	}\
	std::string toString() const {\
		return toJson().to_string();\
	}

#define ENTITY_ARGS_GET_BEGIN(ClassName)\
	static std::shared_ptr<ClassName> fromJson(amo::json& json) {\
		typedef ClassName ClassType;\
		std::shared_ptr<ClassType> ptr(new ClassType());

#ifndef ENTITY_ARGS_GET
#define  ENTITY_ARGS_GET(key) (ptr->##key = typeFromJson<decltype(ptr->##key)>(json, #key));
#endif

#ifndef ENTITY_ARGS_SMART_GET
#define  ENTITY_ARGS_SMART_GET(key) (ptr->##key = smartTypeFromJson<decltype(ptr->##key)>(json, #key));
#endif


#define ENTITY_ARGS_GET_END()\
		ptr->onFromJson(json);\
		return ptr;\
	}

#endif // AMO_ENTITYHELPER_HPP__