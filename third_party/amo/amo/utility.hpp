
#ifndef AMO_UTILITY_HPP__
#define AMO_UTILITY_HPP__

#include <algorithm>
#include <cctype>

namespace amo {
    inline int isnan(double x) {
        return x != x;
    }
    inline int isinf(double x) {
        return !isnan(x) && isnan(x - x);
    }
    
    
    
    template<typename T>
    static T* vec_data(std::vector<T>& vec) {
        return (vec.size() > 0) ? &vec[0] : 0;
    }
    
    template<typename T>
    const T* vec_data(const std::vector<T>& vec) {
        return (vec.size() > 0) ? &vec[0] : 0;
    }
    
    static std::string bytes_to_hex_string(const unsigned char* bytes, int buffer_size, bool to_upper = false) {
        std::string ret;
        
        for (int i = 0; i < buffer_size; ++i) {
            unsigned char p = bytes[i];
            int val = p;
            
            char high = (p & 0xf0) >> 4;
            
            if (high < 10) {
                high += 0x30;
            } else {
                high += 0x61 - 10;
            }
            
            char low = p & 0xf;
            
            if (low < 10) {
                low += 0x30;
            } else {
                low += 0x61 - 10;
            }
            
            
            
            
            /*  std::cout << high << std::endl;
              std::cout << low << std::endl;*/
            ret += high;
            ret += low;
        }
        
        if (to_upper) {
            std::transform(ret.begin(), ret.end(), ret.begin(), [](unsigned char c) {
                return std::toupper(c);
            });
        } else {
            std::transform(ret.begin(), ret.end(), ret.begin(), [](unsigned char c) {
                return std::tolower(c);
            });
        }
        
        return ret;
    }
    
    template <typename IntegerType>
    static IntegerType bytes_to_int(const unsigned char* bytes, bool littleEndian = true) {
        IntegerType result = 0;
        
        if (littleEndian)
            for (int n = sizeof(result) - 1; n >= 0; n--) {
                result = (result << 8) + bytes[n];
            } else
            for (unsigned n = 0; n < sizeof(result); n++) {
                result = (result << 8) + bytes[n];
            }
            
        return result;
    }
    
    static double bytes_to_double(const unsigned char* bytes, bool littleEndian = true) {
        double result;
        int numBytes = sizeof(double);
        
        if (littleEndian) {
            memcpy(&result, bytes, numBytes);
        } else {
            std::vector<unsigned char> bytesReverse(numBytes);
            std::reverse_copy(bytes, bytes + numBytes, bytesReverse.begin());
            memcpy(&result, vec_data(bytesReverse), numBytes);
        }
        
        return result;
    }
    
    static std::vector<unsigned char> double_to_bytes(double val, bool littleEndian = true) {
        std::vector<unsigned char> result(sizeof(double));
        memcpy(vec_data(result), &val, sizeof(double));
        
        if (!littleEndian) {
            std::reverse(result.begin(), result.end());
        }
        
        return result;
    }
    
    template<typename IntegerType>
    static std::vector<unsigned char> int_to_bytes(IntegerType val, bool littleEndian = true) {
        unsigned int numBytes = sizeof(val);
        std::vector<unsigned char> bytes(numBytes);
        
        for (unsigned n = 0; n < numBytes; ++n)
            if (littleEndian) {
                bytes[n] = (val >> 8 * n) & 0xff;
            } else {
                bytes[numBytes - 1 - n] = (val >> 8 * n) & 0xff;
            }
            
        return bytes;
    }
    
    static std::vector<unsigned char> get_range(const unsigned char* origBytes, int64_t index, int64_t size) {
        std::vector<unsigned char> result((std::vector<unsigned char>::size_type)size);
        std::copy(origBytes + index, origBytes + index + size, result.begin());
        return result;
    }
    
    static std::vector<char> get_range(const char* origBytes, int64_t index, int64_t size) {
        std::vector<char> result((std::vector<char>::size_type)size);
        std::copy(origBytes + index, origBytes + index + size, result.begin());
        return result;
    }
    
    static std::vector<unsigned char> get_range(const std::vector<unsigned char>& origBytes, int64_t index, int64_t size) {
        if ((index + size) > (int64_t)origBytes.size()) {
            return std::vector<unsigned char>();
        }
        
        return get_range(vec_data(origBytes), index, size);
    }
    
}



#endif // AMO_UTILITY_HPP__