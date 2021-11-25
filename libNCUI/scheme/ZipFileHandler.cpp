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
        
    }
    
    bool ZipFileHandler::ProcessRequest(CefRefPtr<CefRequest> request,
                                        CefRefPtr<CefCallback> callback) {
        std::string url = request->GetURL();
        
        if (url != m_strUrl) {
            return false;
        }
        
        amo::string zipPath(m_strZip, true);
        zipPath.replace("\\", "/");
        //zipPath = "web/web.zip";
        
        std::shared_ptr<libzippp::ZipArchive> zf = ZipFileManager::getInstance()->get(zipPath);
        
        if (!zf) {
            return false;
        }
        
        amo::path p(amo::string(m_strFile, true));
        p.remove_front_backslash();
        amo::string strFile(p.c_str(), false);
        strFile.replace("\\", "/");
        //amo::path dirPath = p.remove_file_spec_c().remove_front_backslash();
        /*  std::vector<libzippp::ZipEntry>  vec = zf->getEntries();
        
          for (auto& p : vec) {
        	  amo::cdevel << p.getName() << amo::endl;
          }*/
        
        auto entry =  zf->getEntry(strFile.to_utf8(), false, false);
        
        if (entry.isNull()) {
        
            amo::cerr << "δ���ҵ���Դ�ļ���" << strFile.to_ansi() << amo::endl;
            return false;
        }
        
        m_strData = entry.readAsText();
        
        bool bHandled = readMimeType(p.find_extension());
        
        if (bHandled) {
            callback->Continue();
            return true;
        }
        
        return false;
        
    }
    
}