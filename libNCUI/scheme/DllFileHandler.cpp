#include "stdafx.h"
#include "scheme/DllFileHandler.h"
#include "scheme/DllFileManager.h"




namespace amo {


    DllFileHandler::DllFileHandler(const std::string& url,
                                   const std::string& u8ZipPath,
                                   const std::string& u8File)
        : m_strUrl(url)
        , m_strFile(u8File)
        , m_strZip(u8ZipPath) {
        
        
        m_strUrl = amo::util().getUrlFromUtf8(m_strUrl);
        m_strFile = amo::util().getUrlFromUtf8(m_strFile);
        m_strZip = amo::util().getUrlFromUtf8(m_strZip);
    }
    
    bool DllFileHandler::ProcessRequest(CefRefPtr<CefRequest> request,
                                        CefRefPtr<CefCallback> callback) {
        //AMO_TIMER_ELAPSED();
        amo::string url = amo::util().getUrlFromUtf8(request->GetURL());
        
        if (url != m_strUrl) {
            return false;
        }
        
        amo::string dllPath = m_strZip;
        dllPath.replace("\\", "/");
        //zipPath = "web/web.zip";
        
        std::shared_ptr<amo::loader> zf = DllFileManager::getInstance()->get(
                                              dllPath);
                                              
        if (!zf) {
            return false;
        }
        
        amo::path p(m_strFile);
        p.remove_front_backslash();
        amo::string strFile(p.c_str(), false);
        strFile.replace("\\", "/");
        
        std::string filePath = strFile;
        char* val = NULL;
        amo::optional<int> retval  = zf->exec<int, const char*, char**>("readAsText",
                                     filePath.c_str(), &val);
                                     
        if (!retval || *retval == 0 || val == NULL) {
            amo::cerr << "δ���ҵ���Դ�ļ���" << strFile.to_ansi() << amo::endl;
            return false;
        }
        
        std::string ssss(val, *retval);
        m_strData = ssss;
        
        bool bHandled = readMimeType(p.find_extension());
        //AMO_TIMER_ELAPSED();
        /*    OutputDebugStringA(strFile.c_str());
          OutputDebugStringA("\n");*/
        
        if (bHandled) {
            callback->Continue();
            return true;
        }
        
        return false;
        
    }
    
}