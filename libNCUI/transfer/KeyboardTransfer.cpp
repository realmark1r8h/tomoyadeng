#include "stdafx.h"
#include "transfer/KeyboardTransfer.h"
#include <atlconv.h>

namespace amo {



    KeyboardTransfer::KeyboardTransfer()
        : ClassTransfer("keyboard") {
        addDepends("system");
    }
    
    Any KeyboardTransfer::sayString(IPCMessage::SmartType msg) {
        amo::string str(msg->GetArgumentList()->GetString(0), true);
        SendKeys(str);
        return Undefined();
    }
    
    Any KeyboardTransfer::keyPress(IPCMessage::SmartType msg) {
    
        std::vector<char> vec = getKeys(msg);
        
        for (size_t i = 0; i < vec.size(); ++i) {
            SendKeyDown(vec[i]);
        }
        
        for (size_t i = 0; i < vec.size(); ++i) {
            SendKeyUp(vec[i]);
        }
        
        return Undefined();
    }
    
    Any KeyboardTransfer::keyDown(IPCMessage::SmartType msg) {
        std::vector<char> vec = getKeys(msg);
        
        for (size_t i = 0; i < vec.size(); ++i) {
            SendKeyDown(vec[i]);
        }
        
        return Undefined();
    }
    
    Any KeyboardTransfer::keyUp(IPCMessage::SmartType msg) {
        std::vector<char> vec = getKeys(msg);
        
        for (size_t i = 0; i < vec.size(); ++i) {
            SendKeyUp(vec[i]);
        }
        
        return Undefined();
    }
    
    Any KeyboardTransfer::waitKey(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any KeyboardTransfer::getLastKey(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    void KeyboardTransfer::SendKeyDown(char data) {
        INPUT input;
        memset(&input, 0, sizeof(INPUT));
        
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = data;
        input.ki.time = 0;
        SendInput(1, &input, sizeof(INPUT));
    }
    
    
    void KeyboardTransfer::SendKeyUp(char data) {
        INPUT input;
        memset(&input, 0, sizeof(INPUT));
        
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = data;
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        input.ki.time = 0;
        
        SendInput(1, &input, sizeof(INPUT));
    }
    
    
    void KeyboardTransfer::SendUnicode(wchar_t data) {
        INPUT input[2];
        memset(input, 0, 2 * sizeof(INPUT));
        
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = 0;
        input[0].ki.wScan = data;
        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
        input[0].ki.time = 0;
        
        input[1].type = INPUT_KEYBOARD;
        input[1].ki.wVk = 0;
        input[1].ki.wScan = data;
        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
        input[1].ki.time = 0;
        SendInput(2, input, sizeof(INPUT));
    }
    
    void KeyboardTransfer::SendKeys(const amo::string& msg) {
        short vk;
        BOOL shift;
        
        USES_CONVERSION;
        std::wstring data = msg.to_unicode();
        int len = data.size();
        
        for (int i = 0; i < len; i++) {
            SendUnicode(data[i]);
        }
    }
    
    std::vector<char> KeyboardTransfer::getKeys(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        amo::string str(msg->GetArgumentList()->GetString(0), true);
        std::vector<char> vec;
        
        for (int i = 0; i < args->getArgsSize(); ++i) {
            Any& val = args->GetValue(i);
            
            if (val.type() == AnyValueType<int>::value) {
                vec.push_back(val.As<int>() & 0xff);
            } else if (val.type() == AnyValueType<std::string>::value) {
                std::string str = val.As<std::string>();
                std::copy(str.begin(), str.end(), std::back_inserter(vec));
            } else {
                continue;
            }
        }
        
        return vec;
        
    }
    
}

