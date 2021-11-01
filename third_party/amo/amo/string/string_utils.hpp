// Created by 苏元海 on 01/29/2016.
// Copyright (c) 2016 amoylel. All rights reserved.

#ifndef IME_STRING_CONVERTOR_HPP__
#define IME_STRING_CONVERTOR_HPP__

#include <string>
#include <unordered_map>
#include <regex>
#include <amo/config.hpp>

#include <amo/string/iconv.hpp>


namespace amo {
    namespace string_utils {
    
#ifdef _WIN32
        static std::string UnicodeToAnsi(LPCWSTR pString) {
            char *pANSI = NULL;
            int nByte = 0;
            nByte = WideCharToMultiByte(CP_ACP, 0, pString, -1, NULL, 0, NULL, NULL);
            pANSI = (char*)malloc(nByte + 1);
            memset(pANSI, 0, nByte + 1);
            WideCharToMultiByte(CP_ACP, 0, pString, -1, pANSI, nByte, NULL, NULL);
            std::string str = pANSI;
            free(pANSI);
            return str;
        }
        
        static std::wstring AnsiToUnicode(LPCSTR pString) {
            wchar_t *pUnicode = NULL;
            int nWideCharLen = 0;
            nWideCharLen = MultiByteToWideChar(CP_ACP, 0, pString, -1, NULL, 0);
            pUnicode = (wchar_t*)malloc((nWideCharLen + 1) * sizeof(wchar_t));
            memset(pUnicode, 0, (nWideCharLen + 1) * sizeof(wchar_t));
            MultiByteToWideChar(CP_ACP, 0, pString, -1, pUnicode, nWideCharLen);
            std::wstring str = pUnicode;
            free(pUnicode);
            return str;
        }
        
        static std::string UTF8ToANSI(LPCSTR pString) {
            int nwLen = MultiByteToWideChar(CP_UTF8, 0, pString, -1, NULL, 0);
            wchar_t * pwBuf = new wchar_t[nwLen + 1];
            memset(pwBuf, 0, (nwLen + 1) * sizeof(wchar_t));
            MultiByteToWideChar(CP_UTF8, 0, pString, strlen(pString), pwBuf, nwLen);
            int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
            char * pBuf = new char[nLen + 1];
            memset(pBuf, 0, nLen + 1);
            WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
            std::string retStr = pBuf;
            delete[]pBuf;
            delete[]pwBuf;
            pBuf = NULL;
            pwBuf = NULL;
            
            return retStr;
        }
        
        static std::string ANSIToUTF8(LPCSTR lpszAnsi) {
            int wlen = MultiByteToWideChar(CP_ACP, 0, lpszAnsi, -1, NULL, 0);
            wchar_t* pwBuf = (wchar_t*)malloc(sizeof(wchar_t) * (wlen + 1));
            memset(pwBuf, 0, (wlen + 1) * sizeof(wchar_t));
            MultiByteToWideChar(CP_ACP, 0, lpszAnsi, strlen(lpszAnsi), pwBuf, wlen);
            int len = WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
            char* pBuf = (char*)malloc(len + 1);
            memset(pBuf, 0, len + 1);
            WideCharToMultiByte(CP_UTF8, 0, pwBuf, wlen, pBuf, len, NULL, NULL);
            std::string str = pBuf;
            free(pBuf);
            free(pwBuf);
            return str;
        }
        
        static std::wstring UTF8ToUnicode(LPCSTR pString) {
            int nwLen = MultiByteToWideChar(CP_UTF8, 0, pString, -1, NULL, 0);
            wchar_t * pwBuf = new wchar_t[nwLen + 1];
            memset(pwBuf, 0, (nwLen + 1) * sizeof(wchar_t));
            MultiByteToWideChar(CP_UTF8, 0, pString, strlen(pString), pwBuf, nwLen);
            std::wstring retStr = pwBuf;
            delete[]pwBuf;
            pwBuf = NULL;
            
            return retStr;
        }
#endif
        
#ifdef __linux__
        
        static std::wstring string_to_swtring(const char *pc) {
            std::wstring val = L"";
            
            if (NULL == pc) {
                return val;
            }
            
            //size_t size_of_ch = strlen(pc)*sizeof(char);
            //size_t size_of_wc = get_wchar_size(pc);
            size_t size_of_wc;
            size_t destlen = mbstowcs(0, pc, 0);
            
            if (destlen == (size_t)(-1)) {
                return val;
            }
            
            size_of_wc = destlen + 1;
            wchar_t * pw = new wchar_t[size_of_wc];
            mbstowcs(pw, pc, size_of_wc);
            val = pw;
            delete pw;
            return val;
        }
        /*
        wstring 转换为 string
        */
        static std::string wstring_to_string(const wchar_t * pw) {
            std::string val = "";
            
            if (!pw) {
                return val;
            }
            
            size_t size = wcslen(pw) * sizeof(wchar_t);
            char *pc = NULL;
            
            if (!(pc = (char*)malloc(size))) {
                return val;
            }
            
            size_t destlen = wcstombs(pc, pw, size);
            
            /*转换不为空时，返回值为-1。如果为空，返回值0*/
            if (destlen == (size_t)(0)) {
                return val;
            }
            
            val = pc;
            delete pc;
            return val;
        }
#endif
        
        static std::wstring utf8_to_wide(const std::string& utf8string) {
            $windows({
                return UTF8ToUnicode(utf8string.c_str());
            })
            $linux({
                amo::converter conv("UTF-8", "GBK");
                std::string out ;
                conv.convert(utf8string, out);
                return string_to_swtring(out.c_str());
            })
            return L"";
            
        }
        
        static std::string wide_to_utf8(const std::wstring& widestring) {
            $windows({
                return ANSIToUTF8(UnicodeToAnsi(widestring.c_str()).c_str());
            })
            $linux({
                amo::converter conv("GBK", "UTF-8");
                std::string in = wstring_to_string(widestring.c_str());
                std::string out;
                conv.convert(in, out);
                return out;
            })
            return "";
        }
        
        static std::string wide_to_ansi(const std::wstring& widestring) {
            $windows({
                return UnicodeToAnsi(widestring.c_str());
            })
            $linux({
                return wstring_to_string(widestring.c_str());
            })
            return "";
        }
        
        static std::wstring ansi_to_wide(const std::string& ansistring) {
            $windows({
                return AnsiToUnicode(ansistring.c_str());
            })
            $linux({
                return string_to_swtring(ansistring.c_str());
            })
            return L"";
        }
        
        static std::string ansi_to_utf8(const std::string& ansistring) {
            $windows({
                return ANSIToUTF8(ansistring.c_str());
            })
            $linux({
                amo::converter conv("GBK", "UTF-8");
                std::string out;
                conv.convert(ansistring, out);
                return out;
            })
            return "";
        }
        
        static std::string utf8_to_ansi(const std::string& utf8string) {
            $windows({
                return UTF8ToANSI(utf8string.c_str());
            })
            $linux({
                amo::converter conv("UTF-8", "GBK");
                std::string out;
                conv.convert(utf8string, out);
                return out;
            })
            return "";
        }
        
        
        static bool is_utf8(const char * string) {
            if (!string) {
                return false;
            }
            
            const unsigned char * bytes = (const unsigned char *)string;
            
            while (*bytes) {
                if ((// ASCII
                            // use bytes[0] <= 0x7F to allow ASCII control characters
                            bytes[0] == 0x09 ||
                            bytes[0] == 0x0A ||
                            bytes[0] == 0x0D ||
                            (0x20 <= bytes[0] && bytes[0] <= 0x7E)
                        )
                   ) {
                    bytes += 1;
                    continue;
                }
                
                if ((// non-overlong 2-byte
                            (0xC2 <= bytes[0] && bytes[0] <= 0xDF) &&
                            (0x80 <= bytes[1] && bytes[1] <= 0xBF)
                        )
                   ) {
                    bytes += 2;
                    continue;
                }
                
                if ((// excluding overlongs
                            bytes[0] == 0xE0 &&
                            (0xA0 <= bytes[1] && bytes[1] <= 0xBF) &&
                            (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                        ) ||
                        (// straight 3-byte
                            ((0xE1 <= bytes[0] && bytes[0] <= 0xEC) ||
                             bytes[0] == 0xEE ||
                             bytes[0] == 0xEF) &&
                            (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
                            (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                        ) ||
                        (// excluding surrogates
                            bytes[0] == 0xED &&
                            (0x80 <= bytes[1] && bytes[1] <= 0x9F) &&
                            (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                        )
                   ) {
                    bytes += 3;
                    continue;
                }
                
                if ((// planes 1-3
                            bytes[0] == 0xF0 &&
                            (0x90 <= bytes[1] && bytes[1] <= 0xBF) &&
                            (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                            (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                        ) ||
                        (// planes 4-15
                            (0xF1 <= bytes[0] && bytes[0] <= 0xF3) &&
                            (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
                            (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                            (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                        ) ||
                        (// plane 16
                            bytes[0] == 0xF4 &&
                            (0x80 <= bytes[1] && bytes[1] <= 0x8F) &&
                            (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                            (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                        )
                   ) {
                    bytes += 4;
                    continue;
                }
                
                return false;
            }
            
            return true;
        }
        
        static bool is_utf8(const std::string& str) {
            return is_utf8(str.c_str());
        }
        
        
        static std::vector< std::string > split(const std::string& src, const std::string& sub)   {
            std::string s = src;
            std::string delim = sub;
            
            std::vector<std::string> ret;
            size_t start = 0;
            
            if (s.empty()) {
                return ret;
            }
            
            size_t index = s.find_first_of(delim, start);
            
            while (index != std::string::npos) {
                ret.push_back(std::string(s.substr(start, index - start)));
                start = index + sub.size();
                index = s.find_first_of(delim, start);
            }
            
            size_t size1 = src.size();
            
            if (start < src.size()) {
                ret.push_back(std::string(s.substr(start)));
            }
            
            return ret;
        }
        
        static void replace(std::string& m_str, const std::string &strsrc, const std::string &strdst) {
            if (strsrc.empty()) {
                return  ;
            }
            
            std::string::size_type pos = 0;
            std::string::size_type srclen = strsrc.size();
            std::string::size_type dstlen = strdst.size();
            
            while ((pos = m_str.find(strsrc, pos)) != std::string::npos) {
                m_str.replace(pos, srclen, strdst);
                pos += dstlen;
            }
            
            return  ;
        }
        
        static std::string mapValueToString(const std::unordered_map<std::string, std::string>& map, const std::string& key) {
            auto iter = map.find(key);
            
            if (iter == map.end()) {
                return "";
            }
            
            return iter->second;
        }
        
        static std::string format(const std::string& src, const std::unordered_map<std::string, std::string>& map)   {
            std::regex args("\\{\\w+\\}");
            std::smatch m;
            std::string str = src;
            
            while (std::regex_search(str, m, args)) {
                std::string key = m[0].str();
                replace(key, "{", "\\{");
                replace(key, "}", "\\}");
                
                std::regex e(key);
                replace(key, "\\{", "");
                replace(key, "\\}", "");
                str = std::regex_replace(str, e, mapValueToString(map, key));
            }
            
            return str;
        }
        
        
    }
}



#endif // IME_STRING_CONVERTOR_HPP__
