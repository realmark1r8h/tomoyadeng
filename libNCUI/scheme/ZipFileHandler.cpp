#include "stdafx.h"
#include "scheme/ZipFileHandler.h"
#include "utility/libzippp.h"
#include "scheme/ZipFileMnager.h"



namespace amo {


    ZipFileHandler::ZipFileHandler(const std::string& url,
                                   const std::string& u8ZipPath,
                                   const std::string& u8File)
        : m_strUrl(url)
        , m_strFile(u8File)
        , m_strZip(u8ZipPath) {
        
        
        m_strUrl = amo::util().getUrlFromUtf8(m_strUrl);
        m_strFile = amo::util().getUrlFromUtf8(m_strFile);
        m_strZip = amo::util().getUrlFromUtf8(m_strZip);
    }
    
    bool ZipFileHandler::ProcessRequest(CefRefPtr<CefRequest> request,
                                        CefRefPtr<CefCallback> callback) {
        //AMO_TIMER_ELAPSED();
        amo::string url = amo::util().getUrlFromUtf8(request->GetURL());
        
        if (url != m_strUrl) {
            return false;
        }
        
        amo::string zipPath = m_strZip;
        zipPath.replace("\\", "/");
        //zipPath = "web/web.zip";
        
        std::shared_ptr<libzippp::ZipArchive> zf = ZipFileManager::getInstance()->get(
                    zipPath);
                    
        if (!zf) {
            return false;
        }
        
        amo::path p(m_strFile);
        p.remove_front_backslash();
        amo::string strFile(p.c_str(), false);
        strFile.replace("\\", "/");
        //amo::path dirPath = p.remove_file_spec_c().remove_front_backslash();
        /*std::vector<libzippp::ZipEntry>  vec = zf->getEntries();
        
        for (auto& p : vec) {
            amo::cdevel << p.getName() << amo::endl;
        }*/
        //AMO_TIMER_ELAPSED();
        auto entry =  zf->getEntry(strFile.to_utf8(), false, false);
        /*  entry = zf->getEntry("ReactJs/images/列表01.png", false, false);
          entry = zf->getEntry(amo::string("ReactJs/images/列表01.png").to_utf8());*/
        
        if (entry.isNull()) {
            amo::cerr << "未能找到资源文件：" << strFile.to_ansi() << amo::endl;
            return false;
        }
        
        
        m_strData = entry.readAsText();
        
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