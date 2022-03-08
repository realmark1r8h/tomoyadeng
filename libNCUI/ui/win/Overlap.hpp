// Created by amoylel on 13/04/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBNCUI_OVERLAP_C7F8CD76_678A_4084_BA01_C6800CD33984_HPP__
#define LIBNCUI_OVERLAP_C7F8CD76_678A_4084_BA01_C6800CD33984_HPP__
#include <WinSock2.h>
#include <windows.h>

#include <vector>
#include <string>
#include <memory>
#include <amo/utility.hpp>
#include <gdiplus.h>

#include <amo/json.hpp>
#include <amo/rect.hpp>

using namespace Gdiplus;
namespace amo {
    class OverlapData {
    public:
        virtual void fill(const char* buffer, int size) = 0;
        virtual int size() = 0;
        virtual std::shared_ptr<Bitmap> toBitmap() = 0;
        
    };
    class DefalutOverlapData : public OverlapData {
    public:
        DefalutOverlapData() {
            imageWidth = imageHeight = imageWidth = imageSize = 0;
            imageDataOrigin = NULL;
        }
        
        virtual void fill(const char* buffer, int size) override {
            m_buffer.resize(size);
            memcpy(m_buffer.data(), buffer, size);
            unsigned char* bytes = (unsigned char*)m_buffer.data();
            /*  totalSize = (amo::bytes_to_int<int>(bytes));
              bytes += 4;*/
            imageWidth = (amo::bytes_to_int<int>(bytes));
            bytes += 4;
            imageHeight = (amo::bytes_to_int<int>(bytes));
            bytes += 4;
            widthStep = (amo::bytes_to_int<int>(bytes));
            bytes += 4;
            imageSize = (amo::bytes_to_int<int>(bytes));
            bytes += 4;
            imageDataOrigin = (char*)bytes;
        }
        virtual int size() override {
            return m_buffer.size();
        }
        
        std::shared_ptr<Bitmap>  toBitmap() override {
            std::shared_ptr<Bitmap>  pBitmap;
            
            if (m_buffer.empty()) {
                return pBitmap;
            }
            
            pBitmap.reset(new Bitmap(imageWidth, imageHeight,
                                     PixelFormat24bppRGB));
                                     
            if (!pBitmap) {
                return pBitmap;
            }
            
            BitmapData bmpData;
            Gdiplus::Rect rect(0, 0, imageWidth, imageHeight);
            pBitmap->LockBits(&rect, ImageLockModeWrite, PixelFormat24bppRGB, &bmpData);
            BYTE *pByte = (BYTE*)bmpData.Scan0;
            
            if (widthStep == bmpData.Stride) { //likely
                memcpy(bmpData.Scan0, imageDataOrigin, imageSize);
            }
            
            pBitmap->UnlockBits(&bmpData);
            return pBitmap;
        }
        
    public:
        //int totalSize;  //整个数据包的长度
        int imageWidth;
        int imageHeight;
        int widthStep;
        int imageSize;
        char* imageDataOrigin;
        std::vector<int8_t> m_buffer;
    };
    
    class Overlap {
    public:
        enum OverlapType {
            OverlapDefault,
        };
    public:
        Overlap(amo::json& json) {
            amo::json dst = json.getJson("dstRect");
            amo::json src = json.getJson("srcRect");
            
            if (dst.is_array()) {
                std::vector<amo::json> vec = dst.to_array();
                
                if (vec.size() == 4) {
                    dstRect = amo::rect(vec[0].get<int>(),
                                        vec[1].get<int>(),
                                        vec[2].get<int>(),
                                        vec[3].get<int>());
                }
            }
            
            if (src.is_array()) {
                std::vector<amo::json> vec = src.to_array();
                
                if (vec.size() == 4) {
                    srcRect = amo::rect(vec[0].get<int>(),
                                        vec[1].get<int>(),
                                        vec[2].get<int>(),
                                        vec[3].get<int>());
                }
            }
        }
        
        int size() const {
            if (getOverlapData()) {
                return getOverlapData()->size();
            }
            
            return 0;
            
        }
        std::shared_ptr<OverlapData> getOverlapData() const {
            return m_data;
        }
        void setOverlapData(std::shared_ptr<OverlapData> val) {
            m_data = val;
        }
        
        std::shared_ptr<OverlapData> fill(const char* buffer, int size) {
            switch (overlapType) {
            case Overlap::OverlapDefault:
            
                m_data.reset(new DefalutOverlapData());
                m_data->fill(buffer, size);
                break;
                
            default:
                break;
            }
            
            return m_data;
        }
    public:
        OverlapType overlapType;
        amo::rect dstRect;
        amo::rect srcRect;
        
        
        std::shared_ptr <OverlapData> m_data;
    };
    
}



#endif //LIBNCUI_OVERLAP_C7F8CD76_678A_4084_BA01_C6800CD33984_HPP__