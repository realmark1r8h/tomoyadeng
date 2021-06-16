#ifndef AMO_JSON_HPP__
#define AMO_JSON_HPP__


#ifndef RAPIDJSON_HAS_STDSTRING
#define RAPIDJSON_HAS_STDSTRING 1
#endif

#include <vector>
#include <string>
#include <iosfwd>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/stringbuffer.h>

#include <amo/uuid.hpp>
#include <amo/stdint.hpp>
#include <amo/base64.hpp>
#include <amo/uuid.hpp>
#include <utility>

namespace amo {
    class json {
    public:
        typedef rapidjson::Value::MemberIterator  iterator;
        typedef rapidjson::Value::MemberIterator assoc_iterator;
        typedef const rapidjson::Value::ConstMemberIterator const_iterator;
        typedef rapidjson::Document::AllocatorType allocator_type;
        typedef rapidjson::Value::ValueIterator	value_iterator;
        
    public:
        static json from_file(const std::string& file) {
            std::fstream ifs(file);
            
            if (!ifs.is_open()) {
                return json();
            }
            
            std::stringstream strem;
            strem << ifs.rdbuf();
            return json(strem.str());
            
        }
        
        
    public:
    
        json() {
            m_valid = true;
            doc.SetObject();
        }
        
        
        json(const std::string& str_json) {
            m_valid = true;
            doc.Parse<0>(str_json.c_str());
            
            if (doc.HasParseError()) {
                //doc.Clear();
                m_valid = false;
                return;
            }
        }
        
        json(const json& rhs) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            rhs.doc.Accept(writer);
            std::string json_str = buffer.GetString();
            doc.Parse<0>(json_str.c_str());
            
            if (doc.HasParseError()) {
                doc.Clear();
                m_valid = false;
                return;
            }
            
            m_valid = true;
            bool lb = doc.IsObject();
        }
        
        json(const rapidjson::Document& document) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            std::string json_str = buffer.GetString();
            doc.Parse<0>(json_str.c_str());
            
            if (doc.HasParseError()) {
                doc.Clear();
                m_valid = false;
                return;
            }
            
            m_valid = true;
        };
        
        json(const rapidjson::Value& val) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            val.Accept(writer);
            std::string json_str = buffer.GetString();
            doc.Parse<0>(json_str.c_str());
            
            if (doc.HasParseError()) {
                doc.Clear();
                m_valid = false;
                return;
            }
            
            m_valid = true;
        }
        
        amo::json& operator =(const amo::json & rhs) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            rhs.doc.Accept(writer);
            std::string json_str = buffer.GetString();
            doc.Parse<0>(json_str.c_str());
            
            if (doc.HasParseError()) {
                doc.Clear();
                m_valid = false;
                return *this;
            }
            
            m_valid = true;
            return *this;
        }
        
        amo::json& join(amo::json& other) {
            for (iterator iter = other.begin(); iter != other.end(); ++iter) {
                std::string name = iter->name.GetString();
                iterator it = find_member(name);
                
                if (it != this->end()) {
                    it->value.CopyFrom(iter->value, get_allocator());
                } else {
                    doc.AddMember(iter->name, iter->value, get_allocator());
                }
            }
            
            return *this;
        }
        
        void put_child(const std::string& key,  const json& val) {
            iterator iter = find_member(key);
            
            if (iter != end()) {
                iter->value.CopyFrom(val.doc, get_allocator());
            } else {
                rapidjson::Value name;
                name.SetString(key.c_str(), get_allocator());
                doc.AddMember(name, rapidjson::Value().CopyFrom(val.doc, get_allocator()), get_allocator());
            }
            
        }
        
        json get_child(const std::string& key) {
            iterator iter = find_member(key);
            
            if (iter == end()) {
                return json();
            }
            
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            iter->value.Accept(writer);
            std::string json_str = buffer.GetString();
            return json(json_str);
        }
        
        allocator_type& get_allocator() {
            return doc.GetAllocator();
        }
        
        rapidjson::Document& get_document() {
            return doc;
        }
        
        iterator find_member(const std::string& key) {
            return doc.FindMember(key.c_str());
        }
        
        
        const_iterator find_member(const std::string& key) const {
            return doc.FindMember(key.c_str());
        }
        
        
        bool contains_key(const std::string& key) const {
            return doc.HasMember(key.c_str());
        }
        
        std::vector<std::string> keys() {
            std::vector<std::string> vec;
            
            for (auto iter = begin(); iter != end(); ++iter) {
                vec.push_back(iter->name.GetString());
            }
            
            return vec;
        }
        
        std::vector<std::pair<std::string, amo::json> > values() {
            std::vector<std::pair<std::string, amo::json> > vec;
            
            for (auto iter = begin(); iter != end(); ++iter) {
                vec.push_back(std::pair<std::string, amo::json>(
                                  iter->name.GetString(), amo::json(iter->value)));
                                  
            }
            
            return vec;
        }
        
        template<typename T>
        void put(const T& val) {
            put_impl(val);
        }
        
        void put_impl(const bool& val) {
            doc.SetBool(val);
            
        }
        
        void put_impl(const int& val) {
            doc.SetInt(val);
        }
        
        void put_impl(const uint32_t& val) {
            doc.SetUint(val);
        }
        
        void put_impl(const uint64_t& val) {
            doc.SetUint64(val);
        }
        
        void put_impl(const int64_t& val) {
            doc.SetInt64(val);
        }
        
        void put_impl(const double& val) {
            doc.SetDouble(val);
        }
        
        void put_impl(const float& val) {
            doc.SetDouble(val);
        }
        
        void put_impl(const std::string& val) {
            doc.SetString(val.c_str(), val.size(), get_allocator());
        }
        
        void put_impl(const char* val) {
            doc.SetString(val, strlen(val), get_allocator());
        }
        
        template<typename T>
        void put(const std::string& key, const T& val) {
            rapidjson::Value node;
            node = val;
            rapidjson::Value name;
            name.SetString(key.c_str(), get_allocator());
            
            iterator iter = find_member(key);
            
            if (iter != end()) {
                iter->value.CopyFrom(node, get_allocator());
            } else {
                doc.AddMember(name, node, get_allocator());
            }
            
        }
        
        void put(const std::string& key, const json& val) {
            iterator iter = find_member(key);
            
            if (iter != end()) {
                iter->value.CopyFrom(val.doc, get_allocator());
            } else {
                rapidjson::Value name;
                name.SetString(key.c_str(), get_allocator());
                doc.AddMember(name, rapidjson::Value().CopyFrom(val.doc, get_allocator()), get_allocator());
            }
            
        }
        
        void put(const std::string key, const std::string& val) {
        
            rapidjson::Value node;
            node.SetString(val.c_str(), get_allocator());
            rapidjson::Value name;
            name.SetString(key.c_str(), get_allocator());
            
            iterator iter = find_member(key);
            
            if (iter != end()) {
                iter->value.CopyFrom(node, get_allocator());
            } else {
                doc.AddMember(name, node, get_allocator());
            }
            
            
        }
        
        
        void put(const std::string& key, const amo::uuid& val) {
            put(key, val.to_string());
        }
        
        void put(rapidjson::Value key,  rapidjson::Value val) {
            iterator iter = find_member(key.GetString());
            
            if (iter != end()) {
                iter->value.CopyFrom(val, get_allocator());
            } else {
                doc.AddMember(key, val, get_allocator());
            }
            
        }
        
        template<typename T>
        T get() {
            if (!is_value()) {
                return T();
            }
            
            return get_impl(T());
        }
        
        bool get_impl(bool) {
            if (doc.IsBool()) {
                return doc.GetBool();
            }
            
            return false;
        }
        
        int get_impl(int) {
            if (doc.IsNumber()) {
                return (int)doc.GetInt();
            }
            
            return int();
        }
        
        uint32_t get_impl(uint32_t) {
            if (doc.IsNumber()) {
                return (uint32_t)doc.GetUint();
            }
            
            return int();
        }
        
        uint64_t get_impl(uint64_t) {
            if (doc.IsNumber()) {
                return (uint64_t)doc.GetUint64();
            }
            
            return uint64_t();
        }
        
        int64_t get_impl(int64_t) {
            if (doc.IsNumber()) {
                return (int64_t)doc.GetInt64();
            }
            
            return int();
        }
        
        double get_impl(double) {
            if (doc.IsNumber()) {
                return doc.GetDouble();
            }
            
            return double();
        }
        
        float get_impl(float) {
            if (doc.IsNumber()) {
                return (float)doc.GetDouble();
            }
            
            return float();
        }
        
        std::string get_impl(std::string) {
            if (doc.IsString()) {
                return doc.GetString();
            }
            
            return std::string();
        }
        
        
        
        bool is_null()   const {
            return doc.IsNull();
        }
        bool is_false()  const {
            return doc.IsFalse();
        }
        bool is_true()   const {
            return doc.IsTrue();
        }
        bool is_bool()   const {
            return doc.IsBool();
        }
        bool is_object() const {
            return doc.IsObject();
        }
        bool is_array()  const {
            return doc.IsArray();
        }
        bool is_number() const {
            return doc.IsNumber();
        }
        bool is_int()    const {
            return doc.IsInt();
        }
        bool is_uint()   const {
            return doc.IsUint();
        }
        bool is_int64()  const {
            return doc.IsInt64();
        }
        bool is_uint64() const {
            return doc.IsUint64();
        }
        bool is_double() const {
            return doc.IsDouble();
        }
        bool is_string() const {
            return doc.IsString();
        }
        
        
        bool is_null(const std::string& key)   const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsNull()) {
                return false;
            }
            
            return true;
        }
        bool is_false(const std::string& key)  const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsFalse()) {
                return false;
            }
            
            return true;
        }
        bool is_true(const std::string& key)   const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsTrue()) {
                return false;
            }
            
            return true;
        }
        bool is_bool(const std::string& key)   const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsBool()) {
                return false;
            }
            
            return true;
        }
        bool is_object(const std::string& key) const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsObject()) {
                return false;
            }
            
            return true;
        }
        bool is_array(const std::string& key)  const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsArray()) {
                return false;
            }
            
            return true;
        }
        bool is_number(const std::string& key) const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsNumber()) {
                return false;
            }
            
            return true;
        }
        bool is_int(const std::string& key)    const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsInt()) {
                return false;
            }
            
            return true;
        }
        bool is_uint(const std::string& key)   const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsUint()) {
                return false;
            }
            
            return true;
        }
        bool is_int64(const std::string& key)  const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsInt64()) {
                return false;
            }
            
            return true;
        }
        bool is_uint64(const std::string& key) const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsUint64()) {
                return false;
            }
            
            return true;
        }
        bool is_double(const std::string& key) const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsDouble()) {
                return false;
            }
            
            return true;
        }
        bool is_string(const std::string& key) const {
            const_iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsString()) {
                return false;
            }
            
            return true;
        }
        
        bool is_value() const {
            return !is_array() && !is_object() && !is_null();
            
        }
        
        template<typename T>
        T get(const std::string& key, T default_val = T()) {
            return get(key, default_val);
        }
        
        char getChar(const std::string& key, char default_val = '\0') {
            return get<char>(key, default_val);
        }
        
        bool getBool(const std::string& key, bool default_val = false) {
            return get<bool>(key, default_val);
        }
        
        std::string getString(const std::string& key, const std::string& default_val = "") {
            return get<std::string>(key, default_val);
        }
        
        amo::json getJson(const std::string& key, const amo::json& default_val = amo::json()) {
            return get<amo::json>(key, default_val);
        }
        
        
        char getChar(const std::string& key, const char& default_val = '0') {
            return get<char>(key, default_val);
        }
        
        int getInt(const std::string& key, int default_val = 0) {
            return get<int32_t>(key, default_val);
        }
        uint32_t getUint(const std::string& key, uint32_t default_val = 0) {
            return get<uint32_t>(key, default_val);
        }
        
        
        int64_t getInt64(const std::string& key, int64_t default_val = 0) {
            return get<int64_t>(key, default_val);
        }
        
        char get(const std::string& key, char default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsInt()) {
                return default_val;
            }
            
            return (char)iter->value.GetInt();
        }
        
        bool get(const std::string& key, bool default_val) {
            iterator iter = find_member(key);
            
            if (iter == end()) {
                return default_val;
            }
            
            if (iter->value.IsString()) {
                std::string val = iter->value.GetString();
                
                if (val == "true" || val == "TRUE" || val == "1") {
                    return true;
                }
                
                return false;
            } else if (iter->value.IsBool()) {
                return iter->value.GetBool();
                
            } else if (iter->value.IsInt()) {
                return (iter->value.GetInt() != 0);
            }
            
            return default_val;
        }
        
        std::string get(const std::string& key, const char* default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsString()) {
                return default_val;
            }
            
            return iter->value.GetString();
        }
        
        std::string get(const std::string& key, std::string default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsString()) {
                return default_val;
            }
            
            return iter->value.GetString();
        }
        
        
        int8_t get(const std::string& key, int8_t default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsInt()) {
                return default_val;
            }
            
            return (int8_t)iter->value.GetInt();
        }
        
        uint8_t get(const std::string& key, uint8_t default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsUint()) {
                return default_val;
            }
            
            return (uint8_t)iter->value.GetUint();
        }
        
        int16_t get(const std::string& key, int16_t default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsInt()) {
                return default_val;
            }
            
            return (int16_t)iter->value.GetInt();
        }
        
        uint16_t get(const std::string& key, uint16_t default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsUint()) {
                return default_val;
            }
            
            return (uint16_t)iter->value.GetUint();
        }
        
        int32_t get(const std::string& key, int32_t default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsInt()) {
                return default_val;
            }
            
            return iter->value.GetInt();
        }
        
        
        uint32_t get(const std::string& key, uint32_t default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsUint()) {
                return default_val;
            }
            
            return iter->value.GetUint();
        }
        
        
        int64_t get(const std::string& key, int64_t default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsInt64()) {
                return default_val;
            }
            
            return iter->value.GetInt64();
        }
        
        uint64_t get(const std::string& key, uint64_t default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsUint64()) {
                return default_val;
            }
            
            return iter->value.GetInt64();
        }
        
        
        float get(const std::string& key, float default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsNumber()) {
                return default_val;
            }
            
            return (float)iter->value.GetDouble();
        }
        
        
        double get(const std::string& key, double default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsDouble()) {
                return default_val;
            }
            
            return iter->value.GetDouble();
        }
        
        amo::uuid get(const std::string& key, amo::uuid default_val) {
            iterator iter = find_member(key);
            
            if (iter == end() || !iter->value.IsString()) {
                return default_val;
            }
            
            return amo::uuid::from_string(iter->value.GetString());
        }
        
        json get(const std::string& key, json default_val) {
            iterator iter = find_member(key);
            
            if (iter == end()) {
                return default_val;
            }
            
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            iter->value.Accept(writer);
            std::string json_str = buffer.GetString();
            return json(json_str);
        }
        
        iterator begin() {
            return doc.MemberBegin();
        }
        
        const_iterator begin() const {
            return doc.MemberBegin();
        }
        
        iterator end() {
            return doc.MemberEnd();
        }
        
        const_iterator end() const {
            return doc.MemberEnd();
        }
        
        std::vector<amo::json> to_array() {
            std::vector<amo::json> vec;
            
            if (!is_array()) {
                return vec;
            }
            
            value_iterator iter = doc.Begin();
            
            for (value_iterator iter = doc.Begin(); iter != doc.End(); ++iter) {
                vec.push_back(amo::json(*iter));
            }
            
            return vec;
        }
        
        assoc_iterator not_found() {
            return doc.MemberEnd();
        }
        
        assoc_iterator find(std::string key) {
            return find_member(key);
        }
        
        std::string to_string() const {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            doc.Accept(writer);
            std::string json_str = buffer.GetString();
            return json_str;
        }
        
        void set_array() {
            doc.SetArray();
        }
        
        
        template<typename T>
        void push_back(const T& val) {
            rapidjson::Value v = (val);
            doc.PushBack(v, get_allocator());
        }
        
        
        void push_back(const bool& val) {
            rapidjson::Value v;
            v.SetBool(val);
            doc.PushBack(v, get_allocator());
        }
        
        void push_back(const int& val) {
            rapidjson::Value v;
            v.SetInt(val);
            doc.PushBack(v, get_allocator());
        }
        
        void push_back(const int64_t& val) {
            rapidjson::Value v;
            v.SetInt64(val);
            doc.PushBack(v, get_allocator());
        }
        
        void push_back(const uint32_t& val) {
            rapidjson::Value v;
            v.SetUint(val);
            doc.PushBack(v, get_allocator());
        }
        
        void push_back(const uint64_t& val) {
            rapidjson::Value v;
            v.SetUint64(val);
            doc.PushBack(v, get_allocator());
        }
        
        
        void push_back(const float& val) {
            rapidjson::Value v;
            v.SetFloat(val);
            doc.PushBack(v, get_allocator());
        }
        
        void push_back(const double& val) {
            rapidjson::Value v;
            v.SetDouble(val);
            doc.PushBack(v, get_allocator());
        }
        
        void push_back(const std::string& val) {
            rapidjson::Value v;
            v.SetString(val.c_str(), get_allocator());
            doc.PushBack(v, get_allocator());
        }
        
        
        void push_back(const json& val) {
            json js(val.to_string());
            rapidjson::Value v;
            v.CopyFrom(js.get_document(), get_allocator());
            doc.PushBack(v, get_allocator());
        }
        
        template<typename T>
        void push_back(const std::string& key, const std::vector<T>& val) {
            rapidjson::Value arr(rapidjson::kArrayType);
            
            for (int i = 0; i < val.size(); ++i) {
                rapidjson::Value v(val[i]);
                arr.PushBack(v, get_allocator());
            }
            
            rapidjson::Value name;
            name.SetString(key.c_str(), get_allocator());
            doc.AddMember(name, arr, get_allocator());
        }
        
        
        void push_back(const std::string& key, const std::vector<json>& val) {
        
            rapidjson::Value arr(rapidjson::kArrayType);
            
            for (size_t i = 0; i < val.size(); ++i) {
                json js(val[i].to_string());
                
                rapidjson::Value v;
                v.CopyFrom(js.get_document(), get_allocator());
                arr.PushBack(v, get_allocator());
                
            }
            
            rapidjson::Value name;
            name.SetString(key.c_str(), get_allocator());
            doc.AddMember(name, arr, get_allocator());
        }
        
        
        void push_back(const std::string& key, const std::vector<std::string>& val) {
        
            rapidjson::Value arr(rapidjson::kArrayType);
            
            for (size_t i = 0; i < val.size(); ++i) {
                rapidjson::Value v;
                v.SetString(val[i].c_str(), get_allocator());
                arr.PushBack(v, get_allocator());
                
            }
            
            rapidjson::Value name;
            name.SetString(key.c_str(), get_allocator());
            doc.AddMember(name, arr, get_allocator());
        }
        
        bool is_valid() const {
            return m_valid;
        }
        void set_valid(bool valid = true) {
            m_valid = valid;
        }
        void clear() {
            if (doc.IsArray()) {
                doc.Clear();
            } else if (doc.IsObject()) {
                doc.RemoveAllMembers();
            }
        }
        
        bool empty() {
            if (doc.IsArray()) {
                return doc.Empty();
            } else if (doc.IsObject()) {
                return doc.ObjectEmpty();
            } else {
                return true;
            }
        }
        
        size_t size()const  {
            if (doc.IsArray()) {
                return doc.Size();
            } else if (doc.IsObject()) {
                return doc.MemberCount();
            }
            
            return 0;
            
        }
        
        
        void erase(const std::string& key) {
            const_iterator iter = find_member(key);
            
            if (iter == end()) {
                return;
            }
            
            doc.RemoveMember(key.c_str());
        }
        
        void add_child(const std::string& key, json& val) {
            return put_child(key, val);
        }
        
    private:
        bool m_valid;
        rapidjson::Document doc;
    };
    
}


#endif // AMO_JSON_HPP__