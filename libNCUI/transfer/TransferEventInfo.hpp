// Created by amoylel on 11/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TRANSFEREVENTINFO_HPP__
#define AMO_TRANSFEREVENTINFO_HPP__

#include <amo/json.hpp>
#include <amo/string.hpp>
#include "ipc/Any.hpp"
#include "utility/utility.hpp"

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
        
        // �����ȥ�������һ���ַ���������JSON��������utf8����ģ��������ڴ�������в�����б���ת����
        void setData(const Any& val) {
            data = val;
        }
        
        // ��ʱ�ò���
        amo::json toJson() const {
            amo::json json;
            json.put("name", name);
            json.put("suspend", suspend);
            json.put("toAll", toAll);
            json.put("browser", browser);
            json.put("frame", frame);
            util().addAnyToJson(json, "data", data);
            
            
            return json;
        }
        
        std::string toString() const {
            return toJson().to_string();
        }
        
        static TransferEventInfo fromJson(const amo::json& json) {
            TransferEventInfo info;
            
            if (json.is_valid()) {
                return info;
            }
            
            info.name = json.getString("name");
            info.suspend = json.getBool("suspend");
            info.toAll = json.getBool("toAll");
            info.browser = json.getInt("browser", -1);
            info.frame = json.getInt64("frame", -1);
            //TODO: ����Ҫ��
            info.data = json.getString("data");
            return info;
        }
        
    public:
        /** @brief	�¼�����. */
        std::string name;
        /** @brief	��ͣ�߳�. */
        bool suspend;
        /** @brief	���͸�����JS����. */
        bool toAll;
        /** @brief	����. */
        Any data;
        /** @brief	Ŀ�������ID. */
        int browser;
        /** @brief	Ŀ��FrameID. */
        int64_t frame;
        
    };
}

#endif // AMO_TRANSFEREVENTINFO_HPP__