// Created by amoylel on 08/07/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_BASICSETTINGS_H__
#define AMO_BASICSETTINGS_H__

#include <string>
#include <functional>
#include <amo/json.hpp>



#define DEFAULT_ARGS_SETTINGS(name, val) name = val; settings.put(#name, val);

#define BOOL_ARGS_SETTING(val) val = settings.getBool(#val, val);
#define INT_ARGS_SETTING(val) val = settings.getInt(#val, val);
#define INT64_ARGS_SETTING(val) val = settings.getInt64(#val, val);
#define UINT_ARGS_SETTING(val) val = settings.getUint(#val, val);
#define STRING_ARGS_SETTING(val) val = ToAbsolutePath(settings.getString(#val, val));
#define JSON_ARGS_SETTING(val) val = settings.getJson(#val, val);

namespace amo {
    class BasicSettings {
    public:
        BasicSettings();
        
        /*!
         * @fn	bool BasicSettings::UpdateArgsSettings(amo::json& config);
         *
         * @brief	Updates the arguments settings described by config.
         *
         * @param [in,out]	config	The configuration.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool UpdateArgsSettings(amo::json& config);
        
        /*!
         * @fn	bool BasicSettings::UpdateArgsSettings(const std::string& json_string);
         *
         * @brief	Updates the arguments settings described by json_string.
         *
         * @param	json_string	The JSON string.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool UpdateArgsSettings(const std::string& json_string);
        
        /*!
         * @fn	virtual void BasicSettings::AfterUpdateArgsSettings();
         *
         * @brief	After update arguments settings.
         */
        
        virtual void AfterUpdateArgsSettings();
        
        /*!
         * @fn	std::string BasicSettings::GetArgsSettings() const;
         *
         * @brief	Gets arguments settings.
         *
         * @return	The arguments settings.
         */
        
        std::string GetArgsSettings() const;
        
        /*!
         * @fn	std::string BasicSettings::ToAbsolutePath(const std::string& str);
         *
         * @brief	Converts a str to an absolute path.
         *
         * @param	str	The string.
         *
         * @return	str as a std::string.
         */
        
        std::string ToAbsolutePath(const std::string& str);
        
        /*!
         * @fn	std::function<void(BasicSettings*)> getUpdateArgsCallback() const;
         *
         * @brief	Callback, called when the get update arguments.
         *
         * @return	null if it fails, else the update arguments callback.
         */
        
        std::function<void(BasicSettings*)> getUpdateArgsCallback() const;
        
        /*!
         * @fn	void BasicSettings::setUpdateArgsCallback(std::function<void(BasicSettings*)> val);
         *
         * @brief	Callback, called when the set update arguments.
         *
         * @param [in,out]	val	If non-null, the value.
         */
        
        void setUpdateArgsCallback(std::function<void(BasicSettings*)> val);
    public:
        /*! @brief	Options for controlling the operation. */
        amo::json settings;
    private:
        /*! @brief	The update arguments callback. */
        std::function<void(BasicSettings*)> m_fnUpdateArgsCallback;
    };
}

#endif // AMO_BASICSETTINGS_H__
