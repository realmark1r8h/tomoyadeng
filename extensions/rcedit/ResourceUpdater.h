// Created by amoylel on 06/19/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_RESOURCEUPDATER_H__
#define AMO_RESOURCEUPDATER_H__







#ifndef _UNICODE
#define _UNICODE
#endif

#ifndef UNICODE
#define UNICODE
#endif

#include <string>
#include <vector>
#include <map>

#include <windows.h>
#include <memory> // unique_ptr




#define RU_VS_COMMENTS          L"Comments"
#define RU_VS_COMPANY_NAME      L"CompanyName"
#define RU_VS_FILE_DESCRIPTION  L"FileDescription"
#define RU_VS_FILE_VERSION      L"FileVersion"
#define RU_VS_INTERNAL_NAME     L"InternalName"
#define RU_VS_LEGAL_COPYRIGHT   L"LegalCopyright"
#define RU_VS_LEGAL_TRADEMARKS  L"LegalTrademarks"
#define RU_VS_ORIGINAL_FILENAME L"OriginalFilename"
#define RU_VS_PRIVATE_BUILD     L"PrivateBuild"
#define RU_VS_PRODUCT_NAME      L"ProductName"
#define RU_VS_PRODUCT_VERSION   L"ProductVersion"
#define RU_VS_SPECIAL_BUILD     L"SpecialBuild"

namespace amo {

    class IconsValue {
    public:
        typedef struct _ICONENTRY {
            BYTE width;
            BYTE height;
            BYTE colorCount;
            BYTE reserved;
            WORD planes;
            WORD bitCount;
            DWORD bytesInRes;
            DWORD imageOffset;
        } ICONENTRY;
        
        typedef struct _ICONHEADER {
            WORD reserved;
            WORD type;
            WORD count;
            std::vector<ICONENTRY> entries;
        } ICONHEADER;
        
        ICONHEADER header;
        std::vector<std::vector<BYTE>> images;
        std::vector<BYTE> grpHeader;
    };
    
    struct Translate {
        LANGID wLanguage;
        WORD wCodePage;
    };
    
    typedef std::pair<std::wstring, std::wstring> VersionString;
    
    struct VersionStringTable {
        Translate Encoding;
        std::vector<VersionString> Strings;
    };
    
    struct VersionInfo {
        VersionInfo() {}
        
        VersionInfo(const HMODULE& hModule, const WORD& languageId);
        
        std::vector<BYTE> Serialize();
        
        bool HasFixedFileInfo() const;
        VS_FIXEDFILEINFO& GetFixedFileInfo();
        void SetFixedFileInfo(const VS_FIXEDFILEINFO& value);
        
        std::vector<VersionStringTable> StringTables;
        std::vector<Translate> SupportedTranslations;
        
    private:
        VS_FIXEDFILEINFO m_fixedFileInfo;
        void DeserializeVersionInfo(const BYTE* const pData, size_t size);
    };
    
    class ResourceUpdater  {
    public:
        typedef std::vector<std::wstring> StringValues;
        typedef std::map<UINT, StringValues> StringTable;
        typedef std::map<WORD, StringTable> StringTableMap;
        
        typedef std::map<LANGID, VersionInfo> VersionStampMap;
        
        typedef std::map<UINT, std::unique_ptr<IconsValue>> IconTable;
        
        struct IconResInfo {
            UINT MaxIconId = 0;
            IconTable IconBundles;
        };
        
        typedef std::map<LANGID, IconResInfo> IconTableMap;
        
        ResourceUpdater();
        ~ResourceUpdater();
        
        virtual bool Load(const WCHAR* filename);
        virtual bool SetVersionString(const WORD& languageId, const WCHAR* name, const WCHAR* value);
        virtual bool SetVersionString(const WCHAR* name, const WCHAR* value);
        virtual bool SetProductVersion(const WORD& languageId, const UINT& id, const unsigned short& v1, const unsigned short& v2, const unsigned short& v3, const unsigned short& v4);
        virtual bool SetProductVersion(const unsigned short& v1, const unsigned short& v2, const unsigned short& v3, const unsigned short& v4);
        virtual bool SetFileVersion(const WORD& languageId, const UINT& id, const unsigned short& v1, const unsigned short& v2, const unsigned short& v3, const unsigned short& v4);
        virtual bool SetFileVersion(const unsigned short& v1, const unsigned short& v2, const unsigned short& v3, const unsigned short& v4);
        virtual bool ChangeString(const WORD& languageId, const UINT& id, const WCHAR* value);
        virtual bool ChangeString(const UINT& id, const WCHAR* value);
        virtual bool SetIcon(const WCHAR* path, const LANGID& langId, const UINT& iconBundle);
        virtual bool SetIcon(const WCHAR* path, const LANGID& langId);
        virtual bool SetIcon(const WCHAR* path);
        virtual bool Commit();
        
        static bool UpdateRaw(const WCHAR* filename, const WORD& languageId, const WCHAR* type, const UINT& id, const void* data, const size_t& dataSize, const bool& deleteOld);
        static bool GetResourcePointer(const HMODULE& hModule, const WORD& languageId, const int& id, const WCHAR* type, BYTE*& data, size_t& dataSize);
        
    private:
        bool SerializeStringTable(const StringValues& values, const UINT& blockId, std::vector<char>& out);
        
        // not thread-safe
        static BOOL CALLBACK OnEnumResourceName(HMODULE hModule, LPCWSTR lpszType, LPWSTR lpszName, LONG_PTR lParam);
        
        // not thread-safe
        static BOOL CALLBACK OnEnumResourceLanguage(HANDLE hModule, LPCWSTR lpszType, LPCWSTR lpszName, WORD wIDLanguage, LONG_PTR lParam);
        
        HMODULE hModule;
        std::wstring filename;
        VersionStampMap versionStampMap;
        StringTableMap stringTableMap;
        IconTableMap iconBundleMap;
        
        unsigned short IconCount;
    };
    
    class ScopedResourceUpdater {
    public:
        ScopedResourceUpdater(const WCHAR* filename, const bool& deleteOld);
        ~ScopedResourceUpdater();
        
        HANDLE Get() const;
        bool Commit();
        
    private:
        bool EndUpdate(const bool& doesCommit);
        
        HANDLE handle;
        bool commited;
    };
    
}

#endif // AMO_RESOURCEUPDATER_H__
