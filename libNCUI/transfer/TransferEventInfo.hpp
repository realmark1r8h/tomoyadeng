// Created by amoylel on 11/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TRANSFEREVENTINFO_HPP__
#define AMO_TRANSFEREVENTINFO_HPP__

#include <amo/json.hpp>
#include <amo/string.hpp>
#include "ipc/Any.hpp"

namespace amo {
    class TransferEventInfo {
    public:
        TransferEventInfo() {
        
        }
        TransferEventInfo(const amo::string& name_,
                          bool suspend_ = false,
                          bool toAll_ = false,
                          int browser_ = -1,
                          int64_t frame_ = -1)
            : name(name_)
            , suspend(suspend_)
            , toAll(toAll_)
            , browser(browser_)
            , frame(frame_) {
            
        }
        
        // 这里进去的如果是一个字符串，或者JSON，必须是utf8编码的，（数据在传输过程中不会进行编码转换）
        void setData(const Any& val) {
            data = val;
        }
        
        // 暂时用不着
        amo::json toJson() const {
            amo::json json;
            json.put("name", name);
            json.put("suspend", suspend);
            json.put("toAll", toAll);
            json.put("browser", browser);
            json.put("frame", frame);
            //TODO: 这里要改
            json.put("data", data.value());
            return json;
        }
        
        amo::string toString() const {
            return toJson().to_string();
        }
        
        TransferEventInfo fromJson(const amo::json& json) {
            TransferEventInfo info;
            
            if (json.is_valid()) {
                return info;
            }
            
            info.name = json.getString("name");
            info.suspend = json.getBool("suspend");
            info.toAll = json.getBool("toAll");
            info.browser = json.getInt("browser", -1);
            info.frame = json.getInt64("frame", -1);
            //TODO: 这里要改
            info.data = json.getString("data");
            return info;
        }
        
    public:
        /** @brief	事件名称. */
        std::string name;
        /** @brief	暂停线程. */
        bool suspend;
        /** @brief	发送给所有JS对象. */
        bool toAll;
        /** @brief	数据. */
        Any data;
        /** @brief	目标浏览器ID. */
        int browser;
        /** @brief	目标FrameID. */
        int64_t frame;
    };
}

#endif // AMO_TRANSFEREVENTINFO_HPP__