// Created by amoylel on 08/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_CLIPBOARD_H__
#define AMO_CLIPBOARD_H__

#include <string>
#include <amo/stdint.hpp>

namespace amo {
    inline bool BOOL2bool(BOOL bVal) {
        return bVal != FALSE;
    }
    
    class Clipboard {
    public:
        Clipboard(HWND hWnd = NULL);
        ~Clipboard();
        
        
        
        
        std::string getClipboardData();
        
        std::string getClipboardHTML(uint32_t HTMLformat);
        
        std::string getClipboardFiles();
        
        std::string getClipboardText();
        
        
        
        
        
        bool writeText(const std::string& text);
        
        void on() {
            // copy
            // paste
            // cut
            // clear
        }
        
        void read() {
        
        }
        void readText() {
        
        }
        void write() {
        
        }
        void writeText() {
        
        }
        
        
        //inline Clipboard::Clipboard(HWND hwndOwner /* = NULL */)  {
        //    if (!::OpenClipboard(hwndOwner)) {
        //
        //    }
        //}
        //
        //inline Clipboard::~Clipboard()   {
        //    ::CloseClipboard();
        //}
        //
        
        
        //        inline void Clipboard::clear()   {
        //            if (!::EmptyClipboard()) {
        //                // // STLSOFT_THROW_X(Clipboard_exception("Cannot empty clipboard", ::GetLastError()));
        //            }
        //        }
        //
        //        inline HWND Clipboard::owner() const {
        //            HWND hwnd = ::GetClipboardOwner();
        //
        //            if (NULL == hwnd &&
        //                    ERROR_SUCCESS != ::GetLastError()) {
        //                // // STLSOFT_THROW_X(Clipboard_exception("Cannot get clipboard owner", ::GetLastError()));
        //            }
        //
        //            return hwnd;
        //        }
        //
        //        inline bool Clipboard::is_fmt_available(UINT fmt) const {
        //            return BOOL2bool(::IsClipboardFormatAvailable(fmt));
        //        }
        //
        //        inline void Clipboard::set_data(UINT fmt, HANDLE hData)   {
        //            if (NULL == ::SetClipboardData(fmt, hData)) {
        //                // // STLSOFT_THROW_X(Clipboard_exception("Cannot set clipboard data", ::GetLastError()));
        //            }
        //        }
        //
        //        inline void Clipboard::set_data(char const* str) {
        //#ifdef STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT
        //            allocator_type::rebind<char>::other     ator(*this);
        //#else /* ? STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
        //            global_allocator<char>                  ator;
        //#endif /* STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
        //            size_t                                  n;
        //            char*                                   memory = stlsoft_ns_qual(string_dup)(str, ator, &n);
        //
        //            set_data_or_deallocate_and_throw_(CF_TEXT, memory, n, ator);
        //        }
        //
        //        inline void Clipboard::set_data(char const* str, ws_size_t n)  {
        //#ifdef STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT
        //            allocator_type::rebind<char>::other     ator(*this);
        //#else /* ? STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
        //            global_allocator<char>                  ator;
        //#endif /* STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
        //            char*                                   memory = stlsoft_ns_qual(string_dup)(str, n, ator);
        //
        //            set_data_or_deallocate_and_throw_(CF_TEXT, memory, n, ator);
        //        }
        //
        //        inline void Clipboard::set_data(wchar_t const* str)  {
        //#ifdef STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT
        //            allocator_type::rebind<wchar_t>::other  ator(*this);
        //#else /* ? STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
        //            global_allocator<wchar_t>               ator;
        //#endif /* STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
        //            size_t                                  n;
        //            wchar_t*                                memory = stlsoft_ns_qual(string_dup)(str, ator, &n);
        //
        //            set_data_or_deallocate_and_throw_(CF_UNICODETEXT, memory, n, ator);
        //        }
        //
        //        inline void Clipboard::set_data(wchar_t const* str, ws_size_t n)  {
        //#ifdef STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT
        //            allocator_type::rebind<wchar_t>::other  ator(*this);
        //#else /* ? STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
        //            global_allocator<wchar_t>               ator;
        //#endif /* STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
        //            wchar_t*                                memory = stlsoft_ns_qual(string_dup)(str, n, ator);
        //
        //            set_data_or_deallocate_and_throw_(CF_UNICODETEXT, memory, n, ator);
        //        }
        //
        //        inline void Clipboard::set_data(HBITMAP hBmp) {
        //            set_data(CF_BITMAP, hBmp);
        //        }
        //
        //        inline void Clipboard::set_data(HDROP hDrop) {
        //            set_data(CF_HDROP, hDrop);
        //        }
        //
        //        inline void Clipboard::set_data(HENHMETAFILE hEmf)  {
        //            set_data(CF_ENHMETAFILE, hEmf);
        //        }
        //
        //        inline void Clipboard::set_data(HPALETTE hPal)  {
        //            set_data(CF_PALETTE, hPal);
        //        }
        //
        //        inline HANDLE Clipboard::get_data(UINT fmt) const  {
        //            HANDLE hData = ::GetClipboardData(fmt);
        //
        //            if (NULL == hData &&
        //                    ERROR_SUCCESS != ::GetLastError()) {
        //                // STLSOFT_THROW_X(Clipboard_exception("Cannot get clipboard data", ::GetLastError()));
        //            }
        //
        //            return hData;
        //        }
        //
        //        inline void Clipboard::get_data(char const*& str) const  {
        //            str = static_cast<char const*>(get_data(CF_TEXT));
        //        }
        //
        //        inline void Clipboard::get_data(wchar_t const*& str) const  {
        //            str = static_cast<wchar_t const*>(get_data(CF_UNICODETEXT));
        //        }
        //
        //        inline void Clipboard::get_data(HBITMAP& hBmp) const  {
        //            hBmp = static_cast<HBITMAP>(get_data(CF_BITMAP));
        //        }
        //
        //        inline void Clipboard::get_data(HDROP& hDrop) const  {
        //            hDrop = static_cast<HDROP>(get_data(CF_HDROP));
        //        }
        //
        //        inline void Clipboard::get_data(HENHMETAFILE& hEmf) const  {
        //            hEmf = static_cast<HENHMETAFILE>(get_data(CF_ENHMETAFILE));
        //        }
        //
        //        inline void Clipboard::get_data(HPALETTE& hPal) const  {
        //            hPal = static_cast<HPALETTE>(get_data(CF_PALETTE));
        //        }
        //
        //
    private:
        HWND m_hWnd;
    };
}

#endif // AMO_CLIPBOARD_H__
