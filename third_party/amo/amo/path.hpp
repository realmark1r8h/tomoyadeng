#ifndef AMO_PATH_HPP__
#define AMO_PATH_HPP__

#include <amo/string.hpp>
#include <amo/config.hpp>
#include <amo/functional.hpp>
#include <amo/filesystem.hpp>

#include <memory.h>
#include <shlwapi.h>
#include <shlobj.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Shell32.lib")

namespace amo {
    class path {
    public:
        path() {
            memset(m_path, 0, 1000);
        }
        path(const path& rhs) {
            memset(m_path, 0, 1000);
            memcpy(m_path, rhs.c_str(), 1000);
        }
        
        path(const amo::string& str_path) {
            memset(m_path, 0, 1000);
            memcpy(m_path, str_path.c_str(), str_path.size());
        }
        
        path(const std::string& str_path) {
            memset(m_path, 0, 1000);
            memcpy(m_path, str_path.c_str(), str_path.size());
        }
        
        path(const char* str_path) {
            memset(m_path, 0, 1000);
            strcpy(m_path, str_path);
        }
        
        path(const amo::filesystem::path& p) {
            filesystem_path(p);
        }
        
        //////////////////////////////////////////////////////////////////////////
        //
        //		路径截断与合并函数
        //////////////////////////////////////////////////////////////////////////
        
        /*!
         * @fn	path& path::remove_args()
         *
         * @brief	去除路径的参数.
         *
         * @return	A reference to a path.
         */
        path& remove_args() {
            ::PathRemoveArgsA(m_path);
            return *this;
        }
        
        /*!
         * @fn	path& path::remove_backslash()
         *
         * @brief	去除路径最后的反斜杠"\".
         *
         * @return	A reference to a path.
         */
        path& remove_backslash() {
            ::PathRemoveBackslashA(m_path);
            return *this;
        }
        
        /*!
         * @fn	path& path::remove_front_backslash()
         *
         * @brief	移除路径前的斜杠.
         *
         * @return	A reference to a path.
         */
        
        path& remove_front_backslash() {
            std::string str = m_path;
            {
                int nIndex = str.find("./");
                
                if (nIndex == 0) {
                    str = str.substr(2);
                }
            }
            {
                int nIndex = str.find(".\\");
                
                if (nIndex == 0) {
                    str = str.substr(2);
                }
            }
            {
                int nIndex = str.find("/");
                
                if (nIndex == 0) {
                    str = str.substr(1);
                }
            }
            {
                int nIndex = str.find("\\");
                
                if (nIndex == 0) {
                    str = str.substr(1);
                }
            }
            memset(m_path, 0, 1000);
            strcpy(m_path, str.c_str());
            return *this;
        }
        
        path remove_front_backslash_c() const {
            std::string str = m_path;
            {
                int nIndex = str.find("./");
                
                if (nIndex = 0) {
                    str = str.substr(2);
                }
            }
            {
                int nIndex = str.find(".\\");
                
                if (nIndex = 0) {
                    str = str.substr(2);
                }
            }
            {
                int nIndex = str.find("/");
                
                if (nIndex = 0) {
                    str = str.substr(1);
                }
            }
            {
                int nIndex = str.find("\\");
                
                if (nIndex = 0) {
                    str = str.substr(1);
                }
            }
            return path(str);
        }
        
        /*!
         * @fn	path& path::add_backslash()
         *
         * @brief	在路径最后加上反斜杠"\"
         *
         * @return	A reference to a path.
         */
        path& add_backslash() {
            ::PathAddBackslashA(m_path);
            return *this;
        }
        /*!
         * @fn	path& path::remove_blanks()
         *
         * @brief	去除路径前后的空格.
         *
         * @return	A reference to a path.
         */
        path& remove_blanks() {
            ::PathRemoveBlanksA(m_path);
            return *this;
        }
        /*!
         * @fn	path& path::add_extension(const amo::string& ext)
         *
         * @brief	在文件路径后面加上扩展名.
         *
         * @param	ext	The extent.
         *
         * @return	A reference to a path.
         */
        path& add_extension(const amo::string& ext) {
            bool bOk = (::PathAddExtensionA(m_path,
                                            ext.c_str()) != FALSE);
                                            
            if (!bOk) {
                auto id = GetLastError();
                ++id;
                amo::string p(m_path);
                
                if (!p.end_with(ext)) {
                    p += ext;
                }
                
                memset(m_path, 0, 1000);
                strcpy(m_path, p.c_str());
            }
            
            return *this;
        }
        
        /*!
         * @fn	path& path::remove_file_spec()
         *
         * @brief	去除文件名，得到目录.
         *
         * @return	A reference to a path.
         */
        path& remove_file_spec() {
            canonicalize();
            ::PathRemoveFileSpecA(m_path);
            return *this;
        }
        
        path remove_file_spec_c() const {
            amo::path p = *this;
            p.remove_file_spec();
            return p;
        }
        
        /*!
         * @fn	path& path::unquote_spaces()
         *
         * @brief	去除路径中的首尾空格.
         *
         * @return	A reference to a path.
         */
        path& unquote_spaces() {
            ::PathUnquoteSpacesA(m_path);
            return *this;
        }
        /*!
         * @fn	path& path::quote_spaces()
         *
         * @brief	判断路径中是否有空格，有的话，就是用“”引号把整个路径包含起来.
         *
         * @return	A reference to a path.
         */
        path& quote_spaces() {
            ::PathQuoteSpacesA(m_path);
            return *this;
        }
        
        
        /*!
         * @fn	path& path::append(const path& other)
         *
         * @brief	将一个路径追加到另一个路径后面.
         *
         * @param	other	The other to append.
         *
         * @return	A reference to a path.
         */
        path& append(const path& other) {
            path p = other.remove_front_backslash_c();
            ::PathAppendA(m_path, p.c_str());
            return *this;
        }
        
        
        
        /*!
         * @fn	path path::append_c(const path& other)
         *
         * @brief	Appends a c.
         *
         * @param	other	The other.
         *
         * @return	A path.
         */
        path append_c(const path& other) const {
            path p = other.remove_front_backslash_c();
            char a[1000] = { 0 };
            strcpy(a, m_path);
            ::PathAppendA(a, p.c_str());
            return path(a);
        }
        
        path trim_left() const {
            amo::string str(m_path);
            int index = str.find_first_of("\\");
            
            if (index == -1) {
                return *this;
            }
            
            amo::string ss = str.substr(0,
                                        index);													//!< The ss
            ss.replace(".", "");
            
            if (ss.empty()) {
                return path(str.substr(index + 1));
            }
        }
        /*!
         * @fn	path& path::combine(const path& other)
         *
         * @brief	合并两个路径.
         *
         * @param	other	The other.
         *
         * @return	A reference to a path.
         */
        path& combine(const path& other) {
            ::PathCombineA(m_path, m_path, other.c_str());
            return *this;
        }
        /*!
         * @fn	path& path::skip_root()
         *
         * @brief	去掉路径中的磁盘符或UNC部分.
         *
         * @return	A reference to a path.
         */
        path& skip_root() {
            strcpy(m_path, ::PathSkipRootA(m_path));
            return *this;
        }
        /*!
         * @fn	path& path::strip_path()
         *
         * @brief	去掉路径中的目录部分，得到文件名.
         *
         * @return	A reference to a path.
         */
        path& strip_path() {
            ::PathStripPathA(m_path);
            return *this;
        }
        
        path strip_path_c() const {
            char a[1000] = { 0 };
            strcpy(a, m_path);
            ::PathStripPathA(a);
            return amo::path(a);
        }
        /*!
         * @fn	path& path::strip_to_root()
         *
         * @brief	去掉路径的文件部分，得到根目录.
         *
         * @return	A reference to a path.
         */
        path& strip_to_root() {
            ::PathStripToRootA(m_path);
            return *this;
        }
        /*!
         * @fn	path& path::compact_path(int dx = 120)
         *
         * @brief	根据字符个数来生成符合长度的路径.
         *
         * @param	dx	(Optional) the dx.
         *
         * @return	A reference to a path.
         */
        path& compact_path(int dx = 120) {
            ::PathCompactPathExA(m_path, m_path, dx, 0);
            return *this;
        }
        /*!
         * @fn	path& path::compact_path_ex(int dx = 120)
         *
         * @brief	根据字符个数来生成符合长度的路径.
         *
         * @param	dx	(Optional) the dx.
         *
         * @return	A reference to a path.
         */
        path& compact_path_ex(int dx = 120) {
            ::PathCompactPathExA(m_path, m_path, dx, 0);
            return *this;
        }
        /*!
         * @fn	path& path::undecorate()
         *
         * @brief	去除路径中的修饰——具体还没看明白，MSDN的例子只是去掉了括号.
         *
         * @return	A reference to a path.
         */
        path& undecorate() {
            ::PathUndecorateA(m_path);
            return *this;
        }
        /*!
         * @fn	path& path::unexpand_env_strings()
         *
         * @brief	将路径中部分数据替换为系统环境变量格式.
         *
         * @return	A reference to a path.
         */
        path& unexpand_env_strings() {
            char a[1000] = { 0 };
            ::PathUnExpandEnvStringsA(m_path, a, 1000);
            memcpy(m_path, a, 1000);
            return *this;
        }
        
        path parent() const {
            amo::string str(m_path);
            int index = str.find_last_of('\\');
            
            if (index == -1) {
                index = str.find_last_of('/');
            }
            
            if (index == -1) {
                return path();
            }
            
            str = str.substr(0, index);
            return path(str);
        }
        //////////////////////////////////////////////////////////////////////////
        // 路径查找比较函数
        //////////////////////////////////////////////////////////////////////////
        
        /*!
         * @fn	path& path::find_on_path(const path& other)
         *
         * @brief	Searches for the first path.
         *
         * @param	other	The other.
         *
         * @return	The found path.
         */
        bool find_on_path(const path& other) {
            BOOL bOk = ::PathFindOnPathA(m_path,
                                         (PZPCSTR)other.c_str());
            return bOk != FALSE;
        }
        /*!
         * @fn	amo::string path::find_extension()
         *
         * @brief	Searches for the first extension.
         *
         * @return	The found extension.
         */
        amo::string find_extension() {
            std::string ext = ::PathFindExtensionA(m_path);
            return amo::string(ext, false);
        }
        /*!
         * @fn	path& path::find_file_name()
         *
         * @brief	Searches for the first file name.
         *
         * @return	The found file name.
         */
        amo::string find_file_name() {
            return amo::string(::PathFindFileNameA(m_path),
                               false);
        }
        /*!
         * @fn	amo::string path::find_next_component()
         *
         * @brief	Searches for the next component.
         *
         * @return	The found component.
         */
        amo::string find_next_component() {
            return amo::string(::PathFindNextComponentA(
                                   m_path), false);
        }
        /*!
         * @fn	bool path::find_suffix_array(std::vector<amo::string> suffix)
         *
         * @brief	查找给定的文件名是否有给定的后缀.
         *
         * @param	suffix	The suffix.
         *
         * @return	true if it succeeds, false if it fails.
         */
        bool find_suffix_array(std::vector<amo::string>
                               suffix) {
            char **a = new char*[suffix.size()];
            
            for (std::size_t i = 0; i < suffix.size(); ++i) {
                a[i] = new char[suffix[i].size() + 1];
                strcpy(a[i], suffix[i].c_str());
            }
            
            /*	char a[100][100] = {0};
            	for (size_t i = 0; i < suffix.size(); ++i)
            	{
            	strcpy(a[i], suffix[i].c_str());
            	}*/
            bool bOk = find_suffix_array((const char**)a,
                                         suffix.size());
                                         
            for (std::size_t i = 0; i < suffix.size(); ++i) {
                delete[] a[i];
            }
            
            delete [] a;
            return bOk;
        }
        /*!
         * @fn	bool path::find_suffix_array(const char** suffix, int size)
         *
         * @brief		查找给定的文件名是否有给定的后缀.
         *
         * @param	suffix	The suffix.
         * @param	size  	The size.
         *
         * @return	true if it succeeds, false if it fails.
         */
        bool find_suffix_array(const char** suffix,
                               int size) {
            return ::PathFindSuffixArrayA(m_path, suffix,
                                          size) != NULL;
        }
        /*!
         * @fn	amo::string path::get_args()
         *
         * @brief	获取路径参数.
         *
         * @return	The arguments.
         */
        amo::string get_args() {
            return amo::string(::PathGetArgsA(m_path), false);
        }
        /*!
         * @fn	path& path::get_char_type()
         *
         * @brief		获取路径字符类型.
         *
         * @return	The character type.
         */
        path& get_char_type() {
            //::PathGetCharTypeA()
            return *this;
        }
        /*!
         * @fn	path& path::get_drive_number()
         *
         * @brief		根据逻辑盘符返回驱动器序号.
         *
         * @return	The drive number.
         */
        int get_drive_number() {
            return ::PathGetDriveNumberA(m_path);
        }
        /*!
         * @fn	path path::relative_path_to(const path& to)
         *
         * @brief	创建一个路径到另一个路径的相对路径.
         * 			当前"c:\\a\\b\\path\\file"; 目标to: "c:\\a\\b\\path";
         * 			返回 ".\\file"
         *
         * @param	to	to.
         *
         * @return	A reference to a path.
         */
        path& relative_path_to(const path& to) {
            char a[1000] = { 0 };
            BOOL bOk = ::PathRelativePathToA(a, to.c_str(),
                                             FILE_ATTRIBUTE_DIRECTORY, m_path,
                                             FILE_ATTRIBUTE_NORMAL);
            strcpy(m_path, a);
            return *this;
        }
        
        
        /*!
         * @fn	path path::relative_path_to_c(const path& to)
         *
         * @brief	创建一个路径到另一个路径的相对路径.
         * 			当前"c:\\a\\b\\path\\file"; 目标to: "c:\\a\\b\\path";
         * 			返回 ".\\file"
         *
         * @param	to	to.
         *
         * @return	A path.
         */
        path relative_path_to_c(const path& to) const {
            char a[1000] = { 0 };
            BOOL bOk = ::PathRelativePathToA(a, to.c_str(),
                                             FILE_ATTRIBUTE_DIRECTORY, m_path,
                                             FILE_ATTRIBUTE_NORMAL);
            return path(a);
        }
        
        // 子路径
        path sub_path(const path& to) {
            return relative_path_to(to);
        }
        
        // 子路径
        path sub_path_c(const path& to) {
            return relative_path_to_c(to);
        }
        
        
        path& replace(const path& from, const path& to) {
            *this = to.append_c(sub_path_c(from));
        }
        
        path replace_c(const path& from, const path& to) {
            return to.append_c(sub_path_c(from));
        }
        
        // 去除子路径
        path& trim_right(const path& right) {
            std::string strRight = right.c_str();
            
            while (true) {
                if (strRight.empty()) {
                    return *this;
                }
                
                if (strRight[0] == '\\' || strRight[0] == '/') {
                    strRight = strRight.substr(1);
                    
                } else {
                    break;
                }
            }
            
            if (strRight.empty()) {
                return *this;
            }
            
            std::string m_str = m_path;
            int nIndex = m_str.find(strRight);
            
            if (nIndex == -1) {
                return *this;
            }
            
            m_str = m_str.substr(0, nIndex);
            *this = path(m_str);
            return *this;
        }
        
        path trim_right_c(const path& right) {
            amo::path p(*this);
            return p.trim_right(right);
        }
        
        // 去除父路径
        path& trim_left(const path& left) {
            return relative_path_to(left);
        }
        
        path trim_left_c(const path& left)  {
            return relative_path_to_c(left);
        }
        /*!
         * @fn	path& path::resolve()
         *
         * @brief		将一个相对路径或绝对路径转换为一个合格的路径，这个理解起来比较拗口.
         *
         * @return	A reference to a path.
         */
        path& resolve() {
            //::PathResolve()
            return *this;
        }
        /*!
         * @fn	path& path::canonicalize()
         *
         * @brief		规范化路径。将格式比较乱的路径整理成规范的路径格式.
         *
         * @return	A reference to a path.
         */
        path& canonicalize() {
            char a[1000] = { 0 };
            std::string str = m_path;
            amo::string_utils::replace(str, "/", "\\");
            memset(m_path, 0, 1000);
            strcpy(m_path, str.c_str());
            ::PathCanonicalizeA(a, m_path);
            strcpy(m_path, a);
            return *this;
        }
        
        
        /*!
         * @fn	path& path::get_short_path_name()
         *
         * @brief	将长路径转为8.3格式的短路径格式.
         *
         * @return	The short path name.
         */
        path& get_short_path_name() {
            char a[1000] = { 0 };
            ::GetShortPathNameA(m_path, a, 1000);
            strcpy(m_path, a);
            return*this;
        }
        /*!
         * @fn	path& path::get_long_path_name()
         *
         * @brief		将短路径格式转为长路径.
         *
         * @return	The long path name.
         */
        path& get_long_path_name() {
            char a[1000] = { 0 };
            BOOL bRet =  ::GetLongPathNameA(m_path, a, 1000);
            
            if (bRet != FALSE) {
                strcpy(m_path, a);
            }
            
            return*this;
        }
        /*!
         * @fn	path& path::get_short_path()
         *
         * @brief		将长路径转为短路径格式（8.3格式）.
         *
         * @return	The short path.
         */
        path& get_short_path() {
            char a[1000] = { 0 };
            BOOL bRet = ::GetShortPathNameA(m_path, a, 1000);
            
            if (bRet != FALSE) {
                memcpy(m_path, a, 1000);
            }
            
            return *this;
        }
        /*!
         * @fn	path& path::make_pretty()
         *
         * @brief	把路径全部转为小写，增加可读性.
         *
         * @return	A reference to a path.
         */
        path& make_pretty() {
            ::PathMakePrettyA(m_path);
            return *this;
        }
        
        /*path& PathProcessCommand()
        {
        	::PathProcessCommand
        }*/
        /*!
         * @fn	path& cleanup_spec()
         *
         * @brief	Cleanup specifier. 因为 ' \' 被认为是无效的字符，将删除
         *
         * @return	A reference to a path.
         */
        path& cleanup_spec() {
            amo::string s(m_path, false);
            std::wstring ws = s.to_wide();
            wchar_t a[1000] = { 0 };
            memcpy(a, ws.c_str(), ws.size());
            ::PathCleanupSpec(NULL, a);
            s = ws;
            strcpy(m_path, s.c_str());
            return *this;
        }
        /*!
         * @fn	path common_prefix(const path& other)
         *
         * @brief	获取两个路径的共同路径.
         *
         * @param	other	The other.
         *
         * @return	A path.
         */
        path common_prefix(const path& other) {
            path p;
            ::PathCommonPrefixA(m_path, other.c_str(),
                                p.c_str());
            return p;
        }
        
        
        /**
         * @fn	static path work_path()
         *
         * @brief	获取工作目录.
         *
         * @return	A path.
         */
        
        static path work_path() {
            char tszModule[MAX_PATH + 1] = { 0 };
            ::GetCurrentDirectoryA(MAX_PATH, tszModule);
            return path(tszModule);
        }
        
        static bool set_work_path_to_app_path() {
            BOOL bOk = ::SetCurrentDirectoryA(
                           fullAppDir().c_str());
            return bOk != FALSE;
        }
        
        
        /*!
         * @fn	bool is_file_spec()
         *
         * @brief	验证路径是否一个文件名.
         *
         * @return	true if file specifier, false if not.
         */
        bool is_file_spec() const {
            return ::PathIsFileSpecA(m_path) != FALSE;
        }
        /*!
         * @fn	bool is_exe()
         *
         * @brief	验证路径是否是可执行文件。注意：不仅仅是.exe，还有.bat，.com，.src等.
         *
         * @return	true if executable, false if not.
         */
        bool is_exe() const {
            //return PathIsExe()
            return false;
        }
        /*!
         * @fn	bool is_root()
         *
         * @brief		路径是否为根路径.
         *
         * @return	true if root, false if not.
         */
        bool is_root() const {
            return PathIsRootA(m_path) != FALSE;
        }
        ///*!
        // * @fn	bool is_relative()
        // *
        // * @brief		判断路径是否是相对路径.
        // *
        // * @return	true if relative, false if not.
        // */
        //bool is_relative() const {
        //    return PathIsRelativeA(m_path) != FALSE;
        //}
        /*!
         * @fn	bool is_prefix(const path& prefix)
         *
         * @brief		判断路径是否含有指定前缀.
         *
         * @param	prefix	The prefix.
         *
         * @return	true if prefix, false if not.
         */
        bool is_prefix(const path& prefix) const {
            return ::PathIsPrefixA(prefix.c_str(),
                                   m_path) == NULL;
        }
        /*!
         * @fn	bool is_same_root(const path& other)
         *
         * @brief		判断路径是否有相同根目录.
         *
         * @param	other	The other.
         *
         * @return	true if same root, false if not.
         */
        bool is_same_root(const path& other) {
            return ::PathIsSameRootA(m_path,
                                     other.c_str()) != FALSE;
        }
        /*!
         * @fn	bool transfer(amo::function<void(path&)> fn_cb, bool recursion = false)
         *
         * @brief	遍历文件夹.
         *
         * @param [in,out]	fn_cb	The cb. 文件回调函数
         * @param	recursion	 	(Optional) true to recursion. true递归遍历， false 只遍历当前文件夹.
         *
         * @return	true if it succeeds, false if it fails.
         */
        bool transfer(amo::function<void(path&)> fn_cb,
                      bool recursion = false) {
            char* lpPath = m_path;
            CHAR szFind[MAX_PATH] = { ("\0") };
            WIN32_FIND_DATAA findFileData;
            strcpy_s(szFind, MAX_PATH, m_path);
            strcat_s(szFind,
                     ("\\*.*"));     //这里一定要指明通配符，不然不会读取所有文件和目录
            HANDLE hFind = ::FindFirstFileA(szFind,
                                            &findFileData);
                                            
            if (INVALID_HANDLE_VALUE == hFind) {
                return false;
            }
            
            do {
                //path p(amo::string(this->c_str()) + amo::string(findFileData.cFileName));
                amo::string pStr(findFileData.cFileName);
                
                if (pStr != "." && pStr != "..") {
                    path p = *this;
                    p.append(path(findFileData.cFileName));
                    
                    if (fn_cb) {
                        fn_cb(p);
                    }
                    
                    //printf("%s\\%s\n", lpPath, findFileData.cFileName);
                    
                    if (p.is_directory()/* && !p.transfer(fn_cb, recursion)*/) {
                        p.transfer(fn_cb, recursion);
                        //return false;
                    }
                }
                
                //if (findFileData.cFileName[0] != ('.')) //不是当前路径或者父目录的快捷方式
                //{
                //	path p = *this;
                //	p.append(path(findFileData.cFileName));
                //	if (fn_cb) fn_cb(p);
                //	//printf("%s\\%s\n", lpPath, findFileData.cFileName);
                //
                //	if (p.is_directory()/* && !p.transfer(fn_cb, recursion)*/)
                //	{
                //		p.transfer(fn_cb, recursion);
                //		//return false;
                //	}
                //}
            } while (::FindNextFileA(hFind, &findFileData));
            
            ::FindClose(hFind);
            return true;
        }
        
        /*!
        * @fn	bool file_exists()
        *
        * @brief		验证路径是否存在.
        *
        * @return	true if it succeeds, false if it fails.
        */
        bool file_exists() const {
            return	amo::filesystem::exists(filesystem_path());
            //return ::PathFileExistsA(m_path) != FALSE;
        }
        
        /**
         * @fn	bool is_valid() const
         *
         * @brief	判断路径是否合法（现在只有非法字符）.
         *
         * @return	true if valid, false if not.
         */
        
        bool is_valid() const {
            amo::string p(m_path);
            /*  if (p.find('\\') != -1) {
                  return false;
              }
            
              if (p.find('/') != -1) {
                  return false;
              }
              */
            /*  if (p.find(':') != -1) {
                  return false;
              }
            
              if (p.find('?') != -1) {
                  return false;
              }
            
              if (p.find('\"') != -1) {
                  return false;
              }
            
              if (p.find('<') != -1) {
                  return false;
              }
            
              if (p.find('>') != -1) {
                  return false;
              }
            
              if (p.find('|') != -1) {
                  return false;
              }*/
            return true;
        }
        
        
        static path fullAppDir() {
            return path(getExeDir());
        }
        
        
        static amo::string getExeDir() {
            char executionDir[MAX_PATH];
            
            if (::GetModuleFileNameA(NULL, executionDir,
                                     sizeof executionDir) == NULL) {
                executionDir[0] = 0;
            }
            
            char* pos = strrchr(executionDir, '\\');
            *pos = '\0';
            return executionDir;
        }
        
        static path appName() {
            return path(getExeName());
        }
        
        
        static amo::string getExeName() {
            char executionDir[MAX_PATH];
            
            if (::GetModuleFileNameA(NULL, executionDir,
                                     sizeof executionDir) == NULL) {
                executionDir[0] = 0;
            }
            
            amo::string ss(executionDir, false);
            int nIndex = ss.find_last_of('\\');
            ss = ss.substr(nIndex + 1);
            return ss;
        }
        
        static path fullAppName() {
            return path(getFullExeName());
        }
        
        
        static amo::string getFullExeName() {
            char executionDir[MAX_PATH];
            
            if (::GetModuleFileNameA(NULL, executionDir,
                                     sizeof executionDir) == NULL) {
                executionDir[0] = 0;
            }
            
            return amo::string(executionDir, false);
        }
        
        static path fullPathInAppDir(const path&
                                     filePath) {
            return getFullPathInExeDir(filePath.c_str());
        }
        
        /*  static path fullPathInAppDir(const amo::string& filePath) {
              return getFullPathInExeDir(filePath);
          }*/
        
        static amo::string getFullPathInExeDir(
            const amo::string& fileName,
            bool includingSlash = true) {
            amo::string file_name = fileName;
            char buf[MAX_PATH];
            ZeroMemory(buf, MAX_PATH);
            
            if (::GetModuleFileNameA(NULL, buf, MAX_PATH)) {
                ::PathRemoveFileSpecA(buf);
                
                if (includingSlash) {
                    strcat_s(buf, _countof(buf), "\\");
                }
                
                if (!file_name.empty()) {
                    strcat_s(buf, _countof(buf), file_name.c_str());
                }
            }
            
            return amo::string(buf, false);
        }
        
        /*!
         * @fn	path PathYetAnotherMakeUniqueName()
         *
         * @brief	基于已存在的文件，自动创建一个唯一的文件名。
         * 比较有用，比如存在“新建文件”，此函数会创建文件名“新建文件（2）
         * Path yet another make unique name.
         *
         * @return	A path.
         */
        /*path PathYetAnotherMakeUniqueName()
        {
        	::PathYetAnotherMakeUniqueName()
        }*/
        
        
        
        
        // 新接口
        
        
        
        
        amo::filesystem::path filesystem_path() const {
            return  amo::filesystem::path(
                        amo::string(
                            m_path).to_string<amo::filesystem::path::string_type>());
        }
        
        void filesystem_path(const amo::filesystem::path&
                             p) {
            *this = p.generic_string();
            return;
        }
        
        operator amo::filesystem::path() const {
            return filesystem_path();
        }
        
        char* c_str() {
            canonicalize();
            return m_path;
        }
        
        const char* c_str() const {
            return m_path;
        }
        
        std::string to_string() const {
            return m_path;
        }
        
        operator std::string() {
            return c_str();
        }
        
        /**
         * @fn	std::string string() const
         *
         * @brief	返回用于初始化 path 的字符串的副本，其格式符合 path 语法规则。.
         *
         * @return	A std::string.
         */
        
        std::string string() const {
            return filesystem_path().string();
        }
        
        
        
        //  -----  decomposition  -----
        
        path  root_path() const {
            return filesystem_path().root_path();
        }
        
        /**
         * @fn	path root_name() const
         *
         * @brief	在给定从文件系统根目录开始的路径的情况下，
         * 			此例程将返回包含 PATHNAME 的第一个字符的字符串。.
         *
         * @return	A path.
         */
        
        path  root_name()
        const {       // returns 0 or 1 element path
            return filesystem_path().root_name();
        }
        
        /**
        * @fn	amo::path root_directory()
        *
        * @brief	在提供了路径的情况下，此 API 将返回根目录，否则将返回空字符串。
        * 			例如，如果路径包含 /tmp/var1，则此例程将返回 /，即 UNIX 文件系统的根。
        * 			不过，如果路径是相对路径，如 ../mywork/bin，此例程将返回空字符串。.
        *
        * @return	An amo::path.
        */
        
        amo::path root_directory() {
            return filesystem_path().root_directory();
        }
        
        path  relative_path() const {
            return filesystem_path().relative_path();
        }
        path  parent_path() const {
            return filesystem_path().parent_path();
        }
        
        path  filename() const {
            return filesystem_path().filename();
        }
        path  stem() const {
            return filesystem_path().stem();
        }
        path  extension() const {
            return filesystem_path().extension();
        }
        
        //  -----  query  -----
        
        bool empty() const  {
            return filesystem_path().empty();
        }
        bool filename_is_dot() const {
            return filesystem_path().filename_is_dot();
        }
        bool filename_is_dot_dot() const {
            return filesystem_path().filename_is_dot_dot();
        }
        bool has_root_path() const {
            return filesystem_path().has_root_path();
        }
        bool has_root_name() const {
            return filesystem_path().has_root_name();
        }
        bool has_root_directory() const {
            return filesystem_path().has_root_directory();
        }
        
        bool has_relative_path() const {
            return filesystem_path().has_relative_path();
        }
        
        bool has_parent_path() const {
            return filesystem_path().has_parent_path();
        }
        
        bool has_filename() const {
            return filesystem_path().has_filename();
        }
        
        bool has_stem() const {
            return filesystem_path().has_stem();
        }
        
        bool has_extension() const {
            return filesystem_path().has_extension();
        }
        
        bool is_relative() const {
            return filesystem_path().is_relative();
        }
        
        bool is_absolute() const {
            return filesystem_path().is_absolute();
        }
        
        //  -----  lexical operations  -----
        
        path  lexically_normal() const {
            return filesystem_path().lexically_normal();
        }
        path  lexically_relative(const path& base) const {
            return filesystem_path().lexically_relative(
                       base.filesystem_path());
        }
        path  lexically_proximate(const path& base)
        const {
            return filesystem_path().lexically_proximate(
                       base.filesystem_path());
        }
        
        
        path&  normalize() {
            amo::filesystem::path p = filesystem_path();
            p.normalize();
            filesystem_path(p);
            return *this;
        }
        path&  remove_leaf() {
            amo::filesystem::path p = filesystem_path();
            p.remove_leaf();
            filesystem_path(p);
            return *this;
        }
        path   leaf() const {
            return filesystem_path().leaf();
        }
        path   branch_path() const {
            return filesystem_path().branch_path();
        }
        path   generic() const {
            return filesystem_path().generic();
        }
        
        bool   has_leaf() const {
            return filesystem_path().has_leaf();
        }
        
        bool   has_branch_path() const {
            return filesystem_path().has_branch_path();
        }
        
        bool   is_complete() const {
            return filesystem_path().is_complete();
        }
        
        /**
         * @fn	bool create_directory() const
         *
         * @brief	创建文件夹.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool create_directory() const {
            try {
                if (this->is_directory() && this->exists()) {
                    return true;
                }
                
                return amo::filesystem::create_directories(
                           filesystem_path());
                           
            } catch (const std::exception&) {
                return false;
            }
            
        }
        
        
        /**
        * @fn	bool exists() const
        *
        * @brief	此函数检查文件的扩展名.
        * 			文件可以为任何类型：常规文件、目录、符号链接等等.
        *
        * @return	true if it succeeds, false if it fails.
        */
        
        bool exists() const {
            return amo::filesystem::exists(filesystem_path());
        }
        
        /*!
        * @fn	bool is_directory()
        *
        * @brief 判断路径是否是一个有效的目录.
        *
        * @return	true if directory, false if not.
        */
        bool is_directory() const {
            return	amo::filesystem::is_directory(
                        filesystem_path());
        }
        
        /**
         * @fn	bool is_regular() const
         *
         * @brief	判断是否为普通文件
         * 			(即此文件不是目录、符号链接、套接字或设备文件).
         *
         * @return	true if regular, false if not.
         */
        
        bool is_regular() const {
            return	amo::filesystem::is_regular(
                        filesystem_path());
        }
        
        /**
         * @fn	bool is_file() const
         *
         * @brief	判断是否为普通文件.
         *
         * @return	true if file, false if not.
         */
        
        bool is_file() const {
            return	is_regular();
        }
        
        /**
         * @fn	bool is_other() const
         *
         * @brief	通常，此函数检查设备文件（如 /dev/tty0）或套接字文件.
         *
         * @return	true if other, false if not.
         */
        
        bool is_other() const {
            return	amo::filesystem::is_other(
                        filesystem_path());
        }
        
        /**
         * @fn	bool equal_to(const amo::path& other) const
         *
         * @brief	两个路径是否等效, 可以判断相对路径 和 绝对路径.
         *
         * @param	other	The other.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool equal_to(const amo::path& other) const {
            return amo::filesystem::equivalent(
                       filesystem_path(),
                       other.filesystem_path());
        }
        
        /**
         * @fn	bool is_empty() const
         *
         * @brief	如果路径与文件夹对应，此函数将检查文件夹是否为空，
         * 			并据此返回“True”或“False”。如果路径与文件对应，
         * 			此函数将检查文件的大小是否等于 0。
         * 			对于文件的硬链接或符号链接的情况，
         * 			此 API 将检查原始文件是否为空。.
         *
         * @return	true if empty, false if not.
         */
        
        bool is_empty() const {
            return	amo::filesystem::is_empty(
                        filesystem_path());
        }
        
        /**
         * @fn	amo::path to_absolute()
         *
         * @brief	此函数是与 bool equivalent(const path1&amp; p1, const path2&amp; p2) 同一系列的另一个 API。
         * 			给定当前工作目录中任意文件路径的情况下，此 API 将返回该文件的绝对路径。 例如，如果用户位于目录 /home/user1 并查询文件 ../user2/file2，
         * 			此函数将返回 /home/user2/file2，即文件 file2 的完整路径名.
         *
         * @param	p	The amo::path to process.
         *
         * @return	An amo::path.
         */
        
        amo::path& to_absolute() {
            amo::path p(amo::filesystem::system_complete(
                            filesystem_path()));
            *this = p;
            return *this;
        }
        
        amo::path to_absolute_c() const {
            amo::path p(amo::filesystem::system_complete(
                            filesystem_path()));
            return p;
        }
        
        amo::path& absolute() {
            return to_absolute();
        }
        
        ///**
        // * @fn	std::string extension() const
        // *
        // * @brief	此函数以前面带句点 (.) 的形式返回给定文件名的扩展名。
        // * 			例如，对于文件名为 test.cpp 的文件，extension 将返回 .cpp。
        // * 			对于文件没有扩展名的情况，此函数将返回空字符串。
        // * 			对于隐藏文件（即 UNIX 系统中文件名以 . 开始的文件），
        // * 			此函数将相应地计算扩展名类型或返回空字符串
        // * 			（因此，对于 .test.profile，此例程将返回 .profile）。
        // *
        // * @return	A std::string.
        // */
        //
        //std::string extension() const {
        //    return amo::string(amo::filesystem::extension(
        //                           filesystem_path()).c_str()).str();
        //}
        
        /**
         * @fn	std::string basename() const
         *
         * @brief	这是与 extension 互补的例程。它将返回文件名中 . 之前的字符串。
         * 			请注意，即使提供了绝对文件名，此 API 仍然仅会返回属于文件名的直接部分.
         *
         * @return	A std::string.
         */
        
        std::string basename() const {
            return amo::filesystem::basename(
                       filesystem_path());
        }
        
        /**
         * @fn	std::string change_extension(const std::string& new_extension)
         *
         * @brief	此 API 将返回反映更改后的名称的新字符串。
         * 			请注意，与 oldpath 对应的文件保持不变。
         * 			这只是一个常规函数。另请注意，您必须显式地在扩展名中指定点。
         * 			例如，change_extension("test.c", "so") 会得到 testso，而不是 test.so。.
         *
         * @param	new_extension	The new extension.
         *
         * @return	A std::string.
         */
        
        amo::path& change_extension(const std::string&
                                    new_extension) {
            amo::filesystem::path oldpath(filesystem_path());
            amo::filesystem::path p = amo::path(
                                          new_extension).filesystem_path();
            this->filesystem_path(
                amo::filesystem::change_extension(oldpath, p));
            return *this;
        }
        
        /*!
        * @fn	path& path::remove_extension()
        *
        * @brief	去除文件路径扩展名.
        *
        * @return	A reference to a path.
        */
        path& remove_extension() {
            return change_extension("");
        }
        
        /*!
        * @fn	path& path::rename_extension(const amo::string& ext);
        *
        * @brief	更改文件路径扩展名.
        *
        * @param	ext	The extent.
        *
        * @return	A reference to a path.
        */
        path& rename_extension(const std::string& ext) {
            return change_extension(ext);
        }
        
        
        
        /*!
        * @fn	bool copy_to(const amo::path& to)
        *
        * @brief	复制文件或目录
        *
        * @param	to	to.
        *
        * @return	true if it succeeds, false if it fails.
        */
        bool copy_to(const amo::path& to) {
            //to.branch_path().create_directory();
            
            try {
            
                if (this->is_file()) {
                    amo::filesystem::copy_file(filesystem_path(),
                                               to.filesystem_path(),
                                               amo::filesystem::copy_option::overwrite_if_exists);
                    return true;
                } else {
                    copy_files(filesystem_path(), to);
                    return true;
                }
                
                
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                return false;
            }
        }
        
        /* bool move_to(const amo::path& to) {
             try {
                 amo::filesystem::rename(filesystem_path(), to.filesystem_path());
                 return true;
             } catch (const std::exception& e) {
                 e.what();
                 return false;
             }
         }*/
        
        bool move_to(const amo::path& to) {
        
            to.create_directory();
            return ::MoveFileA(m_path, to.c_str()) != FALSE;
        }
        
        
        bool rename(const amo::path& to) {
            return move_to(to);
        }
        
        /**
         * @fn	bool remove()
         *
         * @brief	移除一个文件或空目录.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool remove() {
            try {
                amo::filesystem::remove(filesystem_path());
                return true;
            } catch (const std::exception& e) {
                e.what();
                return false;
            }
        }
        
        /**
         * @fn	bool remove_all()
         *
         * @brief	移除一个文件或递归地移除一个目录及其所有内容.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool remove_all() {
            try {
                amo::filesystem::remove_all(filesystem_path());
                return true;
            } catch (const std::exception& e) {
                e.what();
                return false;
            }
        }
        
    private:
        void copy_files(const amo::filesystem::path &src,
                        const amo::filesystem::path &dst) {
                        
            if (!amo::filesystem::exists(dst)) {
                amo::filesystem::create_directories(dst);
            }
            
            for (amo::filesystem::directory_iterator it(src);
                    it != amo::filesystem::directory_iterator(); ++it) {
                const amo::filesystem::path newSrc = it->path();
                const amo::filesystem::path newDst = dst / it->path().filename().string();
                
                if (amo::filesystem::is_directory(newSrc)) {
                    copy_files(newSrc, newDst);
                } else if (amo::filesystem::is_regular_file(newSrc)) {
                    amo::filesystem::copy_file(newSrc, newDst,
                                               amo::filesystem::copy_option::overwrite_if_exists);
                } else {
                    std:: cerr << "Error: unrecognized file - " << newSrc.string() << std::endl;
                }
            }
        }
    private:
        //amo::string m_path;
        char m_path[1000];
        
    };
}


#endif // AMO_PATH_HPP__
