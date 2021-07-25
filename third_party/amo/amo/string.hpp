// Created by amoylel on 06/11/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_STRING_HPP__
#define AMO_STRING_HPP__
  
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <vector>

#include <amo/config.hpp>
#include <amo/lexical_cast.hpp>
#include <amo/string/string_convertor.hpp>


#ifdef	__linux__
#include <cstdarg>
#endif
#ifdef __GNUC__
#define vsprintf_s vsnprintf
#endif
#include <regex> 
#include <amo/json.hpp>

 

#ifndef _WIN32
#define DEFAULT_STRING_UTF8 true
#else
#define DEFAULT_STRING_UTF8 false
#endif

// 以下只对中文件系统有效
// 编码
// 1. ANSI 编码
// 一个文本文件ANSI格式的，就表示他的语言编码与操作系统的一致。
// 在简体中文操作系统中就是 GBK 的
// 在繁体中文操作系统中就是 Big5 的

// 2. WIDE
// std::wstring 在linux和windows(gcc msvc) 编译出来都是一样的

// 字面常量
// 1.msvc 不管源代码文件是什么格式保存都会将常量字符串转换为GB2312， 只测了windows平台，
// 如果以utf-8 编码保存还是会编码为GB3212
// 2.gcc 会将常量字符串转换为对应格式，只测了linux平台
// 如果以utf-8 编码保存会编码为utf8
// 宽字符不受影响 都是GBK编码（ANSI）

// linux 使用该类需要设置本地化信息  setlocale(LC_ALL, "zh_CN");

// 参考
// http://blog.csdn.net/gong_xucheng/article/details/25950607
// http://bbs.csdn.net/topics/370102948
// http://bbs.csdn.net/topics/110110206
// http://blog.chinaunix.net/uid-731376-id-7966.html
// http://bjoern.hoehrmann.de/utf-8/decoder/dfa/
// http://stackoverflow.com/questions/1031645/how-to-detect-utf-8-in-plain-c


namespace amo
{
	//字符串转换类，用于各类字符集之间的转换，目前功能不完整
	class string
	{
	public:
		typedef std::string::iterator iterator;
		typedef std::string::const_iterator const_iterator;
		typedef std::string::size_type size_type;
		typedef std::string::pointer pointer;
		typedef std::string::const_pointer const_pointer;
		typedef std::string::reference reference;
		typedef std::string::const_reference const_reference;
		typedef std::string::reverse_iterator reverse_iterator;
		typedef std::string::const_reverse_iterator const_reverse_iterator;
		typedef char _Elem;
		typedef std::string _Myt;
		 
	public:
		string()
		{

		}

		string(const string& str)
		{
			m_str = str.m_str;
		}

	 

		string(const std::string& str, bool is_utf8 = DEFAULT_STRING_UTF8)
		{
			if (is_utf8)
			{
				m_str = amo::string_convertor::utf8_to_ansi(str);
			}
			else
			{
				m_str = str;
			}

		}

		string(const std::wstring& str/*, bool is_utf8 = DEFAULT_STRING_UTF8*/)
		{
			m_str = amo::string_convertor::wide_to_ansi(str);
		}

		string(const char* str, bool is_utf8 = DEFAULT_STRING_UTF8)
		{
			if (strlen(str) == 0) return;

			if (is_utf8)
			{
				m_str = amo::string_convertor::utf8_to_ansi(str);
			}
			else
			{
				m_str = str;
			}
		}

		string(const wchar_t* str)
		{
			m_str = amo::string_convertor::wide_to_ansi(str);
		}

		static bool is_utf8_constant()
		{
			static int b_is_utf8 = -1;
			if (b_is_utf8 == -1)
			{
				std::string str = "简单字面常量编码测试";
				bool b_utf8 = amo::string_convertor::is_utf8(str);
				b_is_utf8 = b_utf8 ? 1 : 0;
			}
			return b_is_utf8 == 1;
		}
		static string from_constant(const std::string& str)
		{
			return string(str, is_utf8_constant());
		}

		static string from_constant(const char* str)
		{
			return string(str, is_utf8_constant());
		}
		static string from_utf8(const std::string& str)
		{
			return string(str, true);
		}

		static string from_utf8(const char* str)
		{
			return string(str, true);
		}

		static string from_unicode(const std::wstring& str)
		{
			return string(str);
		}

		static string from_unicode(const wchar_t* str)
		{
			return string(str);
		}

		static string from_ansi(const std::string& str)
		{
			return string(str, false);
		}

		static string from_ansi(const char* str)
		{
			return string(str, false);
		}

		std::string to_ansi()
		{
			return this->operator std::string();
		}

		std::string to_ansi() const
		{
			return this->operator std::string();
		}

		std::wstring to_wide()
		{
			return this->operator std::wstring();
		}

		std::wstring to_wide() const
		{
			return this->operator std::wstring();
		}

#ifdef UNICODE
		std::wstring to_unicode()
		{
			return this->operator std::wstring();
		}

		std::wstring to_unicode() const
		{
			return this->operator std::wstring();
		}
#else
		std::string to_unicode()
		{
			return this->operator std::string();
		}

		std::string to_unicode() const
		{
			return this->operator std::string();
		}
#endif


		std::string to_utf8()
		{
			return  amo::string_convertor::ansi_to_utf8(m_str);
		}

		std::string to_utf8() const
		{
			return amo::string_convertor::ansi_to_utf8(m_str);
		}


		operator std::string()
		{
			return  m_str;
		}

		operator std::string() const
		{
			return m_str;
		}

		operator std::wstring()
		{
			return amo::string_convertor::ansi_to_wide(m_str);
		}

		operator std::wstring() const
		{
			return amo::string_convertor::ansi_to_wide(m_str);
		}

		 

		std::string& str()
		{
			return m_str;
		}

		const std::string& str() const
		{
			return m_str;
		}

		string& operator+=(const std::string& str)
		{
			m_str += str;
			return *this;
		}

		string& operator+=(const char* str)
		{
			m_str += str;
			return *this;
		}

		string& operator+=(const string& str)
		{
			m_str += str.m_str;
			return *this;
		}


		string& operator+=(const std::wstring& str)
		{
			m_str += amo::string_convertor::wide_to_ansi(str);
			return *this;
		}

		string& operator+=(const wchar_t* str)
		{
			m_str += amo::string_convertor::wide_to_ansi(str);
			return *this;
		}

	 

		string operator+(const std::string& str)
		{
			return m_str + str;
		}

		string operator+(const char* str)
		{
			return m_str + str;
		}

		string operator+(const string& str)
		{
			return amo::string(m_str + str.m_str, false);
		}


		string operator+(const std::wstring& str)
		{
			return amo::string(m_str + amo::string_convertor::wide_to_ansi(str), false);
		}

		string operator+(const wchar_t* str)
		{
			return amo::string(m_str + amo::string_convertor::wide_to_ansi(str), false);
		}

	 
		bool operator!=(const std::string& str)
		{
			return m_str != str;
		}

		bool operator!=(const char* str)
		{
			return m_str != str;
		}

		bool operator!=(const string& str)
		{
			return m_str != str.m_str;
		}


		bool operator!=(const std::wstring& str)
		{
			std::string tmp = amo::string_convertor::wide_to_ansi(str);
			return m_str != tmp;
		}

		bool operator!=(const wchar_t* str)
		{
			std::string tmp = amo::string_convertor::wide_to_ansi(str);
			return m_str != tmp;
		}

	 


		bool operator==(const std::string& str)
		{
			return m_str == str;
		}

		bool operator==(const char* str)
		{
			return m_str == str;
		}

		bool operator==(const string& str)
		{
			return m_str == str.m_str;
		}


		bool operator==(const std::wstring& str)
		{
			std::string tmp = amo::string_convertor::wide_to_ansi(str);
			return m_str == tmp;
		}

		bool operator==(const wchar_t* str)
		{
			std::string tmp = amo::string_convertor::wide_to_ansi(str);
			return m_str == tmp;
		}

	 

		bool operator==(const std::string& str) const
		{
			return m_str == str;
		}

		bool operator==(const char* str) const
		{
			return m_str == str;
		}

		bool operator==(const string& str) const
		{
			return m_str == str.m_str;
		}


		bool operator==(const std::wstring& str) const
		{
			std::string tmp = amo::string_convertor::wide_to_ansi(str);
			return m_str == tmp;
		}

		bool operator==(const wchar_t* str) const
		{
			std::string tmp = amo::string_convertor::wide_to_ansi(str);
			return m_str == tmp;
		}

	 
		string& operator+=(char _Ch)
		{
			m_str.append((size_type)1, _Ch);
			return *this;
		}


		string& operator+=(wchar_t _Ch)
		{
			std::wstring ws = L"";
			ws += _Ch;
			this->operator+=(ws);
			return *this;
		}

		string& append(const _Myt& _Right)
		{
			m_str.append(_Right);
			return (*this);
		}

		string& append(const _Myt& _Right, size_type _Roff, size_type _Count)
		{
			m_str.append(_Right, _Roff, _Count);
			return (*this);
		}

		string& append(const _Elem *_Ptr, size_type _Count)
		{
			m_str.append(_Ptr, _Count);
			return (*this);
		}

		string& append(const _Elem *_Ptr)
		{
			m_str.append(_Ptr);
			return (*this);
		}

		string& append(size_type _Count, _Elem _Ch)
		{
			m_str.append(_Count, _Ch);
			return (*this);
		}



		string& append(const_pointer _First, const_pointer _Last)
		{
			m_str.append(_First, _Last);
			return (*this);
		}

		string& append(const_iterator _First, const_iterator _Last)
		{
			m_str.append(_First, _Last);
			return (*this);
		}

		string& assign(const _Myt& _Right)
		{
			m_str.assign(_Right);
			return (*this);
		}

		string& assign(const _Myt& _Right, size_type _Roff, size_type _Count)
		{
			m_str.assign(_Right, _Roff, _Count);
			return (*this);
		}

		string& assign(const _Elem *_Ptr, size_type _Count)
		{
			m_str.assign(_Ptr, _Count);
			return (*this);
		}

		string& assign(const _Elem *_Ptr)
		{
			m_str.assign(_Ptr);
			return (*this);
		}

		string& assign(size_type _Count, _Elem _Ch)
		{
			m_str.assign(_Count, _Ch);
			return (*this);
		}



		string& assign(const_pointer _First, const_pointer _Last)
		{
			m_str.assign(_First, _Last);
			return (*this);
		}

		string& assign(const_iterator _First, const_iterator _Last)
		{
			m_str.assign(_First, _Last);
			return (*this);
		}

		string& insert(size_type _Off, const _Myt& _Right)
		{
			m_str.insert(_Off, _Right);
			return (*this);
		}

		string& insert(size_type _Off, const _Myt& _Right, size_type _Roff, size_type _Count)
		{
			m_str.insert(_Off, _Right, _Roff, _Count);
			return (*this);
		}

		string& insert(size_type _Off, const _Elem *_Ptr, size_type _Count)
		{
			m_str.insert(_Off, _Ptr, _Count);
			return (*this);
		}

		string& insert(size_type _Off, const _Elem *_Ptr)
		{
			m_str.insert(_Off, _Ptr);
			return (*this);
		}

		string& insert(size_type _Off, size_type _Count, _Elem _Ch)
		{
			m_str.insert(_Off, _Count, _Ch);
			return (*this);
		}

		
		iterator insert(iterator _Where, char _Ch)
		{
			return m_str.insert(_Where, _Ch);
		}

#ifdef _WIN32
		iterator insert(iterator _Where)
		{
			return m_str.insert(_Where);
		}


		iterator insert(iterator _Where, size_type _Count, _Elem _Ch)
		{
			return m_str.insert(_Where, _Count, _Ch);
		}

		iterator insert(iterator _Where, const_pointer _First, const_pointer _Last)
		{
			return m_str.insert(_Where, _First, _Last);
		}

		iterator insert(iterator _Where, iterator _First, iterator _Last)
		{
			return m_str.insert(_Where, _First, _Last);
		}
#endif
		

		string& erase(size_type _Off = 0)
		{
			m_str.erase(_Off);
			return (*this);
		}

		string& erase(size_type _Off, size_type _Count)
		{
			m_str.erase(_Off, _Count);
			return *this;
		}

		iterator erase(iterator _Where)
		{
			return m_str.erase(_Where);
		}

		iterator erase(iterator _First, iterator _Last)
		{
			return m_str.erase(_First, _Last);
		}

		void clear()
		{
			m_str.clear();
		}
		 
		 

		string& replace(size_type _Off, size_type _N0, const _Myt& _Right)
		{
			m_str.replace(_Off, _N0, _Right);
			return *this;
		}

		string& replace(size_type _Off, size_type _N0, const _Myt& _Right, size_type _Roff, size_type _Count)
		{
			m_str.replace(_Off, _N0, _Right, _Roff, _Count);
			return *this;
		}

		string& replace(size_type _Off,
			size_type _N0, const _Elem *_Ptr, size_type _Count)
		{
			m_str.replace(_Off, _N0, _Ptr, _Count);
			return *this;
		}

		string& replace(size_type _Off, size_type _N0, const _Elem *_Ptr)
		{
			m_str.replace(_Off, _N0, _Ptr);
			return *this;
		}

		string& replace(size_type _Off, size_type _N0, size_type _Count, _Elem _Ch)
		{
			m_str.replace(_Off, _N0, _Count, _Ch);
			return *this;
		}

		string& replace(iterator _First, iterator _Last, const _Myt& _Right)
		{
			m_str.replace(_First, _Last, _Right);
			return *this;
		}

		string& replace(iterator _First, iterator _Last, const _Elem *_Ptr, size_type _Count)
		{
			m_str.replace(_First, _Last, _Ptr, _Count);
			return *this;
		}

		string& replace(iterator _First, iterator _Last,
			const _Elem *_Ptr)
		{
			m_str.replace(_First, _Last, _Ptr);
			return *this;
		}

		string& replace(iterator _First, iterator _Last, size_type _Count, _Elem _Ch)
		{
			m_str.replace(_First, _Last, _Count, _Ch);
			return *this;
		}

		string& replace(iterator _First, iterator _Last, const_pointer _First2, const_pointer _Last2)
		{
			m_str.replace(_First, _Last, _First2, _Last2);
			return *this;
		}

		string& replace(iterator _First, iterator _Last, pointer _First2, pointer _Last2)
		{
			m_str.replace(_First, _Last, _First2, _Last2);
			return *this;
		}
		 
		string& replace(iterator _First, iterator _Last, iterator _First2, iterator _Last2)
		{
			m_str.replace(_First, _Last, _First2, _Last2);
			return *this;
		}
		 

		iterator begin()
		{
			return m_str.begin();
		}

		const_iterator begin() const
		{
			return m_str.begin();
		}

		iterator end()
		{
			return m_str.end();
		}

		const_iterator end() const
		{
			return m_str.end();
		}

		/*reverse_iterator rbegin()
		{
			return m_str.rbegin();
		}*/

		const_reverse_iterator rbegin() const
		{
			return m_str.rbegin();
		}

		reverse_iterator rend()
		{
			return m_str.rend();
		}

		const_reverse_iterator rend() const
		{
			return m_str.rend();
		}

		/*const_iterator cbegin() const
		{
		return m_str.cbegin();
		}*/

		/*const_iterator cend() const
		{
		return m_str.cend();
		}*/

		/*const_reverse_iterator crbegin() const
		{
			return m_str.crbegin();
		}*/

		/*const_reverse_iterator crend() const
		{
		return m_str.crend();
		}*/



		reference at(size_type _Off)
		{
			return m_str.at(_Off);
		}

		const_reference at(size_type _Off) const
		{
			return m_str.at(_Off);
		}

		reference operator[](size_type _Off)
		{
			return (m_str[_Off]);
		}

		const_reference operator[](size_type _Off) const
		{
			return (m_str[_Off]);
		}

		void push_back(_Elem _Ch)
		{
			m_str.push_back(_Ch);
		}

		void push_back(wchar_t _Ch)
		{
			this->operator+=(_Ch);
		}

		/*void pop_back()
		{
		m_str.pop_back();
		}
		*/
		/*reference front()
		{
			return m_str.front();
		}*/

		/*const_reference front() const
		{
			return m_str.front();
		}*/

		/*reference back()
		{
			return m_str.back();
		}*/

		/*const_reference back() const
		{
			return m_str.back();
		}*/

		const _Elem *c_str() const
		{
			return m_str.c_str();
		}

		_Elem *c_str()
		{
			return (char*)m_str.c_str();
		}

		const _Elem *data() const
		{
			return m_str.data();
		}

		_Elem *data()
		{
			return (char*)m_str.data();
		}
		size_type length() const
		{
			return m_str.length();
		}

		size_type size() const
		{
			return m_str.size();
		}

		size_type max_size() const
		{
			return m_str.max_size();
		}

		void resize(size_type _Newsize)
		{
			m_str.resize(_Newsize);
		}

		void resize(size_type _Newsize, _Elem _Ch)
		{
			m_str.resize(_Newsize, _Ch);
		}

		size_type capacity() const
		{
			return m_str.capacity();
		}

		void reserve(size_type _Newcap = 0)
		{
			m_str.reserve(_Newcap);
		}

		bool empty() const
		{
			return m_str.empty();
		}

		size_type copy(_Elem *_Ptr, size_type _Count, size_type _Off = 0) const
		{
			return m_str.copy(_Ptr, _Count, _Off);
		}

		void swap(_Myt& _Right)
		{
			m_str.swap(_Right);
		}

		size_type find(const _Myt& _Right, size_type _Off = 0) const
		{
			return m_str.find(_Right, _Off);
		}

		size_type find(const _Elem *_Ptr, size_type _Off, size_type _Count) const
		{
			return m_str.find(_Ptr, _Off, _Count);
		}

		size_type find(const _Elem *_Ptr, size_type _Off = 0) const
		{
			return m_str.find(_Ptr, _Off);
		}

		size_type find(_Elem _Ch, size_type _Off = 0) const
		{
			return m_str.find(_Ch, _Off);
		}

		size_type rfind(const _Myt& _Right, size_type _Off = std::string::npos) const
		{
			return m_str.rfind(_Right, _Off);
		}

		size_type rfind(const _Elem *_Ptr, size_type _Off, size_type _Count) const
		{
			return m_str.rfind(_Ptr, _Off, _Count);
		}

		size_type rfind(const _Elem *_Ptr, size_type _Off = std::string::npos) const
		{
			return m_str.rfind(_Ptr, _Off);
		}

		size_type rfind(_Elem _Ch, size_type _Off = std::string::npos) const
		{
			return m_str.rfind(_Ch, _Off);
		}

		size_type find_first_of(const _Myt& _Right, size_type _Off = 0) const
		{
			return m_str.find_first_of(_Right, _Off);
		}

		size_type find_first_of(const _Elem *_Ptr, size_type _Off, size_type _Count) const
		{
			return m_str.find_first_of(_Ptr, _Off, _Count);
		}

		size_type find_first_of(const _Elem *_Ptr, size_type _Off = 0) const
		{
			return m_str.find_first_of(_Ptr, _Off);
		}

		size_type find_first_of(_Elem _Ch, size_type _Off = 0) const
		{
			return m_str.find_first_of(_Ch, _Off);
		}

		size_type find_last_of(const _Myt& _Right, size_type _Off = std::string::npos) const 
		{
			return m_str.find_last_of(_Right, _Off);
		}

			size_type find_last_of(const _Elem *_Ptr, size_type _Off, size_type _Count) const
		{
			return m_str.find_last_of(_Ptr, _Off, _Count);
		}

		size_type find_last_of(const _Elem *_Ptr, size_type _Off = std::string::npos) const
		{
			return m_str.find_last_of(_Ptr, _Off);
		}

		size_type find_last_of(_Elem _Ch, size_type _Off = std::string::npos) const
		{
			return m_str.find_last_of(_Ch, _Off);
		}

		size_type find_first_not_of(const _Myt& _Right, size_type _Off = 0) const
		{
			return m_str.find_first_not_of(_Right, _Off);
		}

		size_type find_first_not_of(const _Elem *_Ptr, size_type _Off, size_type _Count) const
		{
			return m_str.find_first_not_of(_Ptr, _Off, _Count);
		}

		size_type find_first_not_of(const _Elem *_Ptr, size_type _Off = 0) const
		{
			return m_str.find_first_not_of(_Ptr, _Off);
		}

		size_type find_first_not_of(_Elem _Ch, size_type _Off = 0) const
		{
			return m_str.find_first_not_of(_Ch, _Off);
		}

		size_type find_last_not_of(const _Myt& _Right, size_type _Off = std::string::npos) const
		{
			return m_str.find_last_not_of(_Right, _Off);
		}

		size_type find_last_not_of(const _Elem *_Ptr, size_type _Off, size_type _Count) const
		{
			return m_str.find_last_not_of(_Ptr, _Off, _Count);
		}

		size_type find_last_not_of(const _Elem *_Ptr, size_type _Off = std::string::npos) const
		{
			return m_str.find_last_not_of(_Ptr, _Off);
		}

		size_type find_last_not_of(_Elem _Ch, size_type _Off = std::string::npos) const
		{
			return m_str.find_last_not_of(_Ch, _Off);
		}

		string substr(size_type _Off = 0, size_type _Count = std::string::npos) const
		{
			return m_str.substr(_Off, _Count);
		}

		int compare(const string& _Right) const
		{
			return m_str.compare(_Right);
		}

		int compare(size_type _Off, size_type _N0, const _Myt& _Right) const
		{
			return m_str.compare(_Off, _N0, _Right);
		}

		int compare(size_type _Off, size_type _N0, const _Myt& _Right, size_type _Roff, size_type _Count) const
		{
			return m_str.compare(_Off, _N0, _Right, _Roff, _Count);
		}

		int compare(const _Elem *_Ptr) const
		{
			return m_str.compare(_Ptr);
		}

		int compare(size_type _Off, size_type _N0, const _Elem *_Ptr) const
		{
			return m_str.compare(_Off, _N0, _Ptr);
		}

		int compare(size_type _Off, size_type _N0, const _Elem *_Ptr, size_type _Count) const
		{
			return m_str.compare(_Off, _N0, _Ptr, _Count);
		}

		bool operator < (const amo::string& rhs) const
		{
			return m_str < rhs.m_str;
		}

		//------------------------------------------------------------------------------
		// 方法:    ImeString::Split 
		// 功能:    分割字符串
		// 访问:    public   
		// 返回:    std::vector< ImeString > 
		// 参数:    ImeString sub
		//				
		// 说明:    
		//           
		//------------------------------------------------------------------------------
		std::vector< string > split(string sub)
		{
			std::string s = m_str;
			std::string delim = sub;

			std::vector<string> ret;
			size_t last = 0;
			if (s.empty()) return ret;
			size_t index = s.find_first_of(delim, last);
			while (index != std::string::npos)
			{
				ret.push_back(amo::string(s.substr(last, index - last), false));
				last = index + 1;
				index = s.find_first_of(delim, last);
			}
			if (index - last > 0)
			{
				ret.push_back(amo::string(s.substr(last, index - last), false));
			}
			return ret;
		}


		//------------------------------------------------------------------------------
		// 方法:    Replace
		// 功能:    替换字符串
		// 访问:    public 
		// 返回:    ImeString&
		// 参数:    const ImeString & strsrc
		// 参数:    const ImeString & strdst
		// 
		// 说明:    
		//         
		//------------------------------------------------------------------------------
		string& replace(const string &strsrc, const string &strdst)
		{
			std::string::size_type pos = 0;
			std::string::size_type srclen = strsrc.size();
			std::string::size_type dstlen = strdst.size();

			while ((pos = m_str.find(strsrc, pos)) != std::string::npos)
			{
				m_str.replace(pos, srclen, strdst);
				pos += dstlen;
			}
			return *this;
		}

		//------------------------------------------------------------------------------
		// 方法:    ToUpper
		// 功能:    所有字符转为大写，改变自身 
		// 访问:    public 
		// 返回:    ImeString&
		// 
		// 说明:    
		//         
		//------------------------------------------------------------------------------
		string& to_upper()
		{
			std::transform(m_str.begin(), m_str.end(), m_str.begin(), toupper);
			return *this;
		}


		//------------------------------------------------------------------------------
		// 方法:    ToUpper
		// 功能:    所有字符转为大写，不改变自身 
		// 访问:    public 
		// 返回:    ImeString
		// 
		// 说明:    
		//         
		//------------------------------------------------------------------------------
		string to_upper() const
		{
			string s(m_str);
			std::transform(m_str.begin(), m_str.end(), s.str().begin(), toupper);
			return s;
		}

		//------------------------------------------------------------------------------
		// 方法:    ToLower
		// 功能:    所有字符转为小写，改变自身 
		// 访问:    public 
		// 返回:    ImeString&
		// 
		// 说明:    
		//         
		//------------------------------------------------------------------------------
		string& to_lower()
		{
			std::transform(m_str.begin(), m_str.end(), m_str.begin(), tolower);
			return *this;
		}


		//------------------------------------------------------------------------------
		// 方法:    ToLower
		// 功能:    所有字符转为大写，不改变自身
		// 访问:    public 
		// 返回:    ImeString
		// 
		// 说明:    
		//         
		//------------------------------------------------------------------------------
		string to_lower() const
		{
			string s(m_str);
			std::transform(m_str.begin(), m_str.end(), s.str().begin(), tolower);
			return s;
		}

		//删除左边所有包含在target中的字符  
		string& trim(const string& target = " ")
		{
			return replace(target, "");
		}

		//删除左边所有包含在target中的字符  
		string& trim_left(const string& target)
		{
			while (!empty() && (target.find(*begin()) != std::string::npos))
				erase(begin());
			return *this;
		}

		//删除右边所有包含在target中的字符  
		string& trim_right(const string& target)
		{
			while (!empty() && target.find(*rbegin()) != std::string::npos)
				m_str.erase(--end());
			return *this;
		}

		//返回左边count个字符，count大于总长度则返回整个字符串  
		string left(size_type count) const
		{
			return substr(0, count);
		}

		//返回右边count个字符，count大于总长度则返回整个字符串  
		string right(size_type count) const
		{
			return substr(size() < count ? 0 : size() - count);
		}

		//忽略大小写判断两个字符串是否相等  
		int compare_no_case(const string& rhs) const
		{
			return to_lower().compare(rhs.to_lower());
		}

		//判断字符串是否以制定字符串开头  
		bool begin_with(const string& rhs) const
		{
			return find(rhs) == size_type(0);
		}

		//判断字符串是否以制定字符串结尾  
		bool end_with(const string& rhs) const
		{
			if (rhs.size() > size())
				return false;
			return compare(size() - rhs.size(), rhs.size(), rhs) == 0;
		}

		//------------------------------------------------------------------------------
		// 方法:    ToNumber
		// 功能:    转换成数字
		// 访问:    public 
		// 返回:    boost::T
		// 参数:    int base
		// 
		// 说明:    
		//         
		//------------------------------------------------------------------------------
		template<typename T>
		T to_number(int base = 10)
		{
			T t = T();
			std::stringstream ss(m_str);
			return convert_to_number<T>(ss, t, base);
		}

		template<typename T>
		T lexical_cast()
		{
			return amo::lexical_cast<T>(m_str);

		}

		//将整数转化为字符串  
		//base:进制数。可以为8,10,16，如果其它值则强制为10  
		template<typename T>
		static string from_number(T number, int base = 10) 
		{
			std::stringstream ss;
			ss.setf(BaseFlag(base), std::ios_base::basefield);
			ss << number;
			return ss.str();
		}

		//将float转化为字符串  
		//f:格式化参数。可以为'f','e','E','g','G'。'f'为定点数,'e'或'E'表示科学计数法  
		//  'g'或‘G’表示格式化为定点数或科学计数法，看哪一个表示方便。  
		//prec:小数点后的位数(定点数表示法)或总的有效位数(科学计数法)  
		static string from_number(float number, _Elem f = _Elem('g'), int prec = 6)
		{
			return from_number(static_cast<double>(number), f, prec);
		}

		//将double转化为字符串，参数解释同上  
		static string from_number(double number, _Elem f = _Elem('g'), int prec = 6)
		{
			std::stringstream ss;
			ss << std::setprecision(prec);
			if (f == 'f')
				ss << std::setiosflags(std::ios_base::fixed);
			else if ((f == 'e') || (f == 'E'))
				ss << std::setiosflags(std::ios_base::scientific);
			ss << number;
			return ss.str();
		} 
	 


		amo::string format(amo::json json){
			std::regex args("\\{\\w+\\}");
			std::smatch m;
			std::string ss = m_str;

			while (std::regex_search(ss, m, args))
			{
				amo::string key = m[0].str();
				key = key.replace("{", "\\{");
				key = key.replace("}", "\\}");

				std::regex e(key.to_ansi());
				key = key.replace("\\{", "");
				key = key.replace("\\}", "");
				ss = std::regex_replace(ss, e, jsonvalueToString(json, key.to_ansi()));
			}
			return amo::string(ss);
		}

		//将szFormat格式化为字符串，参数解释同sprintf  
		string& format(const _Elem* szFormat, ...)
		{
			if (!szFormat) return *this;
			va_list argList;
			va_start(argList, szFormat);
			formatv(szFormat, argList);
			va_end(argList);
			return *this;
		}

		//将szFormat格式化为字符串，参数解释同sprintf  
		void formatv(const _Elem* szFormat, va_list argList)
		{
			if (!szFormat)
				return;
			int nLength = _vscprintf(szFormat, argList);
			if (nLength < 0)
				return;
			resize(nLength);
			vsprintf_s(c_str(), nLength + 1, szFormat, argList);
			va_end(argList);
		}
#ifdef __linux__
		int _vscprintf(const char * format, va_list pargs) {
			int retval;
			va_list argcopy;
			va_copy(argcopy, pargs);
			retval = vsnprintf(NULL, 0, format, argcopy);
			va_end(argcopy);
			return retval;
		}
#endif
		
	private:
		static std::ios_base::fmtflags BaseFlag(int base)
		{
			return (base == 16) ? (std::ios_base::hex) :
				((base == 8) ? (std::ios_base::oct) : (std::ios_base::dec));
		}

		template< typename Type>
		Type convert_to_number(std::stringstream& ss, Type t, int base)
		{
			std::string ss2 = typeid(t).name();
			ss.setf(BaseFlag(base), std::ios_base::basefield);
			ss >> t;
			return t;
		}

		unsigned short convert_to_number(std::stringstream& ss, unsigned short t, int/*ignore base*/)
		{
			int val = 0;
			ss >> val;
			return (unsigned short)val;
		}
	 
		float convert_to_number(std::stringstream& ss, float t, int/*ignore base*/)
		{
			ss >> t;
			return t;
		}

		 
		double convert_to_number(std::stringstream& ss, double t, int/*ignore base*/)
		{
			ss >> t;
			return t;
		} 


		std::string jsonvalueToString(amo::json& json, const std::string& key){
			if (!json.contains_key(key)) return "";

			if (json.is_null(key)) {
				return "null";
			}
			else if (json.is_false(key))  {
				return "false";
			}
			else if (json.is_true(key))  {
				return "true";
			}
			else if (json.is_bool(key)) {
				bool b = json.get<bool>(key);
				if (b) return "true";
				return "false";
			}
			else if (json.is_object(key))  {
				return "object";
			}
			else if (json.is_array(key))  {
				return "array";
			}
			/*	else if (m_json.is_number(key))  {
			}*/
			else if (json.is_int(key))  {
				return amo::string::from_number(json.get<int32_t>(key));
			}
			else 	if (json.is_uint(key))  {
				return amo::string::from_number(json.get<uint32_t>(key));
			}
			else if (json.is_int64(key))  {
				return amo::string::from_number(json.get<int64_t>(key));
			}
			else if (json.is_uint64(key))  {
				return amo::string::from_number(json.get<uint64_t>(key));
			}
			else if (json.is_double(key))  {
				return amo::string::from_number(json.get<double>(key));
			}
			else if (json.is_string(key))  {
				return json.get<std::string>(key);
			}

			return "";
		}

	public:
		std::string m_str; 
		 
	};
}


namespace std
{
	template <>
	struct hash<amo::string> : public unary_function < amo::string, size_t >
	{
	public:
		size_t operator()(const amo::string& value) const
		{
			std::hash<std::string> hs;
			return hs(value);
		}
	};


	template <>
	struct equal_to<amo::string> : public unary_function < amo::string, bool >
	{
	public:
		bool operator()(const amo::string& x, const amo::string& y) const
		{
			std::equal_to<std::string> eq;
			return eq(x, y);
		}
	};

} // namespace std

#endif // AMO_STRING_HPP__
