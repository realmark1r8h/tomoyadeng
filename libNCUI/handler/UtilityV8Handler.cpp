#include "stdafx.h"
#include "handler/UtilityV8Handler.h"

namespace amo {

    bool UtilityV8Handler::Execute(const CefString& name,
                                   CefRefPtr<CefV8Value> object,
                                   const CefV8ValueList& arguments,
                                   CefRefPtr<CefV8Value>& retval,
                                   CefString& exception) {
        do {
            if (name == "sleep") {
            
                if (arguments.size() < 1) {
                    break;
                }
                
                CefRefPtr<CefV8Value> pValue = arguments.at(0);
                
                if (!pValue->IsInt()) {
                    break;
                }
                
                int val = pValue->GetIntValue();
                
                if (val <= 0) {
                    break;
                }
                
                std::this_thread::sleep_for(std::chrono::milliseconds(val));
                return true;
                
            } else if (name == "usleep") {
                if (arguments.size() < 1) {
                    break;
                }
                
                CefRefPtr<CefV8Value> pValue = arguments.at(0);
                
                if (!pValue->IsInt()) {
                    break;
                }
                
                int val = pValue->GetIntValue();
                
                if (val <= 0) {
                    break;
                }
                
                std::this_thread::sleep_for(std::chrono::microseconds(val));
                return true;
            }
        } while (false);
        
        
        exception == L"函数调用失败";
        return false;
    }
    
}

