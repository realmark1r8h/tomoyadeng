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
        //		·���ض���ϲ�����
        //////////////////////////////////////////////////////////////////////////
        
        /*!
         * @fn	path& path::remove_args()
         *
         * @brief	ȥ��·���Ĳ���.
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
         * @brief	ȥ��·�����ķ�б��"\".
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
         * @brief	��·�������Ϸ�б��"\"
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
         * @brief	ȥ��·��ǰ��Ŀո�.
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
         * @brief	���ļ�·�����������չ��.
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
         * @brief	ȥ���ļ�·����չ��.
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
         * @brief	�����ļ�·����չ��.
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
         * @brief	ȥ���ļ������õ�Ŀ¼.
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
         * @brief	ȥ��·���е���β�ո�.
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
         * @brief	�ж�·�����Ƿ��пո��еĻ��������á������Ű�����·����������.
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
         * @brief	��һ��·��׷�ӵ���һ��·������.
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
         * @brief	�ϲ�����·��.
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
         * @brief	ȥ��·���еĴ��̷���UNC����.
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
         * @brief	ȥ��·���е�Ŀ¼���֣��õ��ļ���.
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
         * @brief	ȥ��·�����ļ����֣��õ���Ŀ¼.
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
         * @brief	�����ַ����������ɷ��ϳ��ȵ�·��.
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
         * @brief	�����ַ����������ɷ��ϳ��ȵ�·��.
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
         * @brief	ȥ��·���е����Ρ������廹û�����ף�MSDN������ֻ��ȥ��������.
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
         * @brief	��·���в��������滻Ϊϵͳ����������ʽ.
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
        // ·�����ұȽϺ���
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
         * @brief	���Ҹ������ļ����Ƿ��и����ĺ�׺.
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
         * @brief		���Ҹ������ļ����Ƿ��и����ĺ�׺.
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
         * @brief	��ȡ·������.
         *
         * @return	The arguments.
         */
        amo::string get_args() {
            return amo::string(::PathGetArgsA(m_path), false);
        }
        /*!
         * @fn	path& path::get_char_type()
         *
         * @brief		��ȡ·���ַ�����.
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
         * @brief		�����߼��̷��������������.
         *
         * @return	The drive number.
         */
        int get_drive_number() {
            return ::PathGetDriveNumberA(m_path);
        }
        /*!
         * @fn	path path::relative_path_to(const path& to)
         *
         * @brief	����һ��·������һ��·�������·��.
         * 			��ǰ"c:\\a\\b\\path\\file"; Ŀ��to: "c:\\a\\b\\path";
         * 			���� ".\\file"
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
         * @brief	����һ��·������һ��·�������·��.
         * 			��ǰ"c:\\a\\b\\path\\file"; Ŀ��to: "c:\\a\\b\\path";
         * 			���� ".\\file"
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
        
        // ��·��
        path sub_path(const path& to) {
            return relative_path_to(to);
        }
        
        // ��·��
        path sub_path_c(const path& to) {
            return relative_path_to_c(to);
        }
        
        
        path& replace(const path& from, const path& to) {
            *this = to.append_c(sub_path_c(from));
        }
        
        path replace_c(const path& from, const path& to) {
            return to.append_c(sub_path_c(from));
        }
        
        // ȥ����·��
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
        
        // ȥ����·��
        path& trim_left(const path& left) {
            return relative_path_to(left);
        }
        
        path trim_right_c(const path& left) const  {
            return relative_path_to_c(left);
        }
        /*!
         * @fn	path& path::resolve()
         *
         * @brief		��һ�����·�������·��ת��Ϊһ���ϸ��·���������������Ƚ��ֿ�.
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
         * @brief		�淶��·��������ʽ�Ƚ��ҵ�·������ɹ淶��·����ʽ.
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
         * @brief	����·��תΪ8.3��ʽ�Ķ�·����ʽ.
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
         * @brief		����·����ʽתΪ��·��.
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
         * @brief		����·��תΪ��·����ʽ��8.3��ʽ��.
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
         * @brief	��·��ȫ��תΪСд�����ӿɶ���.
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
         * @brief	Cleanup specifier. ��Ϊ ' \' ����Ϊ����Ч���ַ�����ɾ��
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
         * @brief	��ȡ����·���Ĺ�ͬ·��.
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
         * @brief	��һ�����·��ת���ɾ���·��.
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
         * @brief	��һ�����·��ת���ɾ���·��.
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
         * @brief	��ȡ����Ŀ¼.
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
         * @brief		��֤·���Ƿ����.
         *
         * @return	true if it succeeds, false if it fails.
         */
        bool file_exists() const {
            return ::PathFileExistsA(m_path) != FALSE;
        }
        /*!
         * @fn	bool is_directory()
         *
         * @brief		�ж�·���Ƿ���һ����Ч��Ŀ¼.
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
         * @brief	��֤·���Ƿ�һ���ļ���.
         *
         * @return	true if file specifier, false if not.
         */
        bool is_file_spec() const {
            return ::PathIsFileSpecA(m_path) != FALSE;
        }
        /*!
         * @fn	bool is_exe()
         *
         * @brief	��֤·���Ƿ��ǿ�ִ���ļ���ע�⣺��������.exe������.bat��.com��.src��.
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
         * @brief		·���Ƿ�Ϊ��·��.
         *
         * @return	true if root, false if not.
         */
        bool is_root() const {
            return PathIsRootA(m_path) != FALSE;
        }
        /*!
         * @fn	bool is_relative()
         *
         * @brief		�ж�·���Ƿ������·��.
         *
         * @return	true if relative, false if not.
         */
        bool is_relative() const {
            return PathIsRelativeA(m_path) != FALSE;
        }
        /*!
         * @fn	bool is_prefix(const path& prefix)
         *
         * @brief		�ж�·���Ƿ���ָ��ǰ׺.
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
         * @brief		�ж�·���Ƿ�����ͬ��Ŀ¼.
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
         * @brief	�����ļ���.
         *
         * @param [in,out]	fn_cb	The cb. �ļ��ص�����
         * @param	recursion	 	(Optional) true to recursion. true�ݹ������ false ֻ������ǰ�ļ���.
         *
         * @return	true if it succeeds, false if it fails.
         */
        bool transfer(amo::function<void(path&)> fn_cb, bool recursion = false) {
            char* lpPath = m_path;
            CHAR szFind[MAX_PATH] = { ("\0") };
            WIN32_FIND_DATAA findFileData;
            
            strcpy_s(szFind, MAX_PATH, m_path);
            strcat_s(szFind, ("\\*.*"));     //����һ��Ҫָ��ͨ�������Ȼ�����ȡ�����ļ���Ŀ¼
            
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
                
                //if (findFileData.cFileName[0] != ('.')) //���ǵ�ǰ·�����߸�Ŀ¼�Ŀ�ݷ�ʽ
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
            // ֻ��Ϊ����·�������ļ���
            if (this->is_relative()) {
                return false;
            }
            
            // �����ǰ·�����ڣ��Ҳ�Ϊ�ļ��У�����ʧ��
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
         * @brief	Copies to described by to. ����ǰ·���ļ����Ƶ�����·��
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
         * @brief	�����Ѵ��ڵ��ļ����Զ�����һ��Ψһ���ļ�����
         * �Ƚ����ã�������ڡ��½��ļ������˺����ᴴ���ļ������½��ļ���2��
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
