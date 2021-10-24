#ifndef AMO_PATH_HPP__
#define AMO_PATH_HPP__

#include <amo/string.hpp>
#include <amo/config.hpp>
#include <amo/functional.hpp>

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
            bool bOk = (::PathAddExtensionA(m_path, ext.c_str()) != FALSE);
            
            if (!bOk) {
                auto id = GetLastError();
                ++id;
            }
            
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
            ::PathRemoveExtensionA(m_path);
            return *this;
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
        path& rename_extension(const amo::string& ext) {
            ::PathRenameExtensionA(m_path, ext.c_str());
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
            ::PathRemoveFileSpecA(m_path);
            return *this;
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
        
        operator std::string() {
        
            return c_str();
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
            ::PathAppendA(m_path, other.c_str());
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
        
            char a[1000] = { 0 };
            strcpy(a, m_path);
            ::PathAppendA(a, other.c_str());
            return path(a);
        }
        
        path trim_left() const {
            amo::string str(m_path);
            int index = str.find_first_of("\\");
            
            if (index == -1) {
                return *this;
            }
            
            amo::string ss = str.substr(0, index);													//!< The ss
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
            BOOL bOk = ::PathFindOnPathA(m_path, (PZPCSTR)other.c_str());
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
            return amo::string(::PathFindFileNameA(m_path), false);
        }
        /*!
         * @fn	amo::string path::find_next_component()
         *
         * @brief	Searches for the next component.
         *
         * @return	The found component.
         */
        amo::string find_next_component() {
            return amo::string(::PathFindNextComponentA(m_path), false);
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
        bool find_suffix_array(std::vector<amo::string> suffix) {
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
            bool bOk = find_suffix_array((const char**)a, suffix.size());
            
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
        bool find_suffix_array(const char** suffix, int size) {
            return ::PathFindSuffixArrayA(m_path, suffix, size) != NULL;
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
            BOOL bOk = ::PathRelativePathToA(a, to.c_str(), FILE_ATTRIBUTE_DIRECTORY, m_path, FILE_ATTRIBUTE_NORMAL);
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
            BOOL bOk = ::PathRelativePathToA(a, to.c_str(), FILE_ATTRIBUTE_DIRECTORY, m_path, FILE_ATTRIBUTE_NORMAL);
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
        
        path trim_right_c(const path& left) const  {
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
            ::GetLongPathNameA(m_path, a, 1000);
            strcpy(m_path, a);
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
            ::GetShortPathNameA(m_path, a, 1000);
            memcpy(m_path, a, 1000);
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
            ::PathCommonPrefixA(m_path, other.c_str(), p.c_str());
            return p;
        }
        
        /**
         * @fn	path& to_absolute()
         *
         * @brief	将一个相对路径转换成绝对路径.
         *
         * @return	This object as a path&amp;
         */
        
        path& to_absolute() {
            if (!is_relative()) {
                return *this;
            }
            
            path workPath = work_path();
            work_path().append(*this);
            *this = workPath;
            return *this;
        }
        
        /**
         * @fn	path to_absolute_c()
         *
         * @brief	将一个相对路径转换成绝对路径.
         *
         * @return	This object as a path.
         */
        
        path to_absolute_c() {
            if (!is_relative()) {
                return *this;
            }
            
            path workPath = work_path();
            work_path().append(*this);
            return workPath;
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
        
        /*!
         * @fn	bool file_exists()
         *
         * @brief		验证路径是否存在.
         *
         * @return	true if it succeeds, false if it fails.
         */
        bool file_exists() const {
            return ::PathFileExistsA(m_path) != FALSE;
        }
        /*!
         * @fn	bool is_directory()
         *
         * @brief		判断路径是否是一个有效的目录.
         *
         * @return	true if directory, false if not.
         */
        bool is_directory() const {
            /*   bool  bOk = ::PathIsDirectoryA(m_path);
               return bOk;*/
            BOOL BB = ::PathIsDirectoryA(m_path);
            return ::PathIsDirectoryA(m_path) != FALSE;
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
        /*!
         * @fn	bool is_relative()
         *
         * @brief		判断路径是否是相对路径.
         *
         * @return	true if relative, false if not.
         */
        bool is_relative() const {
            return PathIsRelativeA(m_path) != FALSE;
        }
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
            return ::PathIsPrefixA(prefix.c_str(), m_path) == NULL;
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
            return ::PathIsSameRootA(m_path, other.c_str()) != FALSE;
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
        bool transfer(amo::function<void(path&)> fn_cb, bool recursion = false) {
            char* lpPath = m_path;
            CHAR szFind[MAX_PATH] = { ("\0") };
            WIN32_FIND_DATAA findFileData;
            
            strcpy_s(szFind, MAX_PATH, m_path);
            strcat_s(szFind, ("\\*.*"));     //这里一定要指明通配符，不然不会读取所有文件和目录
            
            HANDLE hFind = ::FindFirstFileA(szFind, &findFileData);
            
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
        
        bool create_directory() const {
            // 只能为给对路径创建文件夹
            if (this->is_relative()) {
                return false;
            }
            
            // 如果当前路径存在，且不为文件夹，返回失败
            if (this->file_exists()) {
                if (this->is_directory()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                path p = parent();
                
                if (!p.create_directory()) {
                    return false;
                }
                
                return CreateDirectoryA(m_path, NULL) != FALSE;
            }
        }
        /*!
         * @fn	bool copy_to(const amo::path& to)
         *
         * @brief	Copies to described by to. 将当前路径文件复制到所给路径
         *
         * @param	to	to.
         *
         * @return	true if it succeeds, false if it fails.
         */
        bool copy_to(const amo::path& to) {
            if (this->is_directory()) {
                return to.create_directory();
            }
            
            return ::CopyFileA(m_path, to.c_str(), FALSE) != FALSE;
        }
        
        static path fullAppDir() {
            return path(getExeDir());
        }
        
        
        static amo::string getExeDir() {
            char executionDir[MAX_PATH];
            
            if (::GetModuleFileNameA(NULL, executionDir, sizeof executionDir) == NULL) {
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
            
            if (::GetModuleFileNameA(NULL, executionDir, sizeof executionDir) == NULL) {
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
            
            if (::GetModuleFileNameA(NULL, executionDir, sizeof executionDir) == NULL) {
                executionDir[0] = 0;
            }
            
            return amo::string(executionDir, false);
        }
        
        static path fullPathInAppDir(const path& filePath) {
            return getFullPathInExeDir(filePath.c_str());
        }
        
        /*  static path fullPathInAppDir(const amo::string& filePath) {
              return getFullPathInExeDir(filePath);
          }*/
        
        static amo::string getFullPathInExeDir(const amo::string& fileName, bool includingSlash = true) {
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
        
        char* c_str() {
            canonicalize();
            return m_path;
        }
        
        const char* c_str() const {
            return m_path;
        }
    private:
        //amo::string m_path;
        char m_path[1000];
    };
}


#endif // AMO_PATH_HPP__
