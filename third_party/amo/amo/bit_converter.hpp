// Created by amoylel on 11/18/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_BIT_CONVERTER_HPP__
#define AMO_BIT_CONVERTER_HPP__

#include <vector>
#include <string>

namespace amo {

    /**
     * @class	BitConverter
     *
     * @brief	ժҪ:
     * 			    �����������������ֽ������໥ת����.
     */
    
    class bit_converter {
    
    public:
        /**
         * @fn	static bool BitConverter::IsLittleEndian()
         *
         * @brief	 ָʾ�����ڴ˼�����ṹ�д洢ʱ���ֽ�˳�򣨡�Endian�����ʣ���.
         *
         * @return	true if little endian, false if not.
         */
        
        static  bool IsLittleEndian() {
            int i = 0x11223344;
            char *p;
            
            p = (char *)&i;
            
            if (*p == 0x44) {
                //printf("Little endian\n");
                return true;
            } else {
                //printf("Big endian\n");
                return false;
            }
            
            return  false;
        }
        
        template<typename T>
        static T bytesToNumber(std::vector<int8_t> b, size_t len = 0) {
            T mask = (T)0xff;
            T val = 0;
            
            if (len == 0) {
                len = b.size();
            }
            
            if (len > b.size()) {
                len = b.size();
            }
            
            for (size_t i = 0; i < len; ++i) {
                val += ((b[len - i] & mask) << (i * 8));
            }
            
            return val;
        }
        
        template<typename T>
        static T toNumber(std::vector<int8_t>& value, size_t startIndex = 0, size_t len = 0) {
            std::vector<int8_t> vec;
            std::copy(value.begin() + startIndex, value.end(), std::back_inserter(vec));
            
            if (IsLittleEndian()) {
                std::reverse(vec.begin(), vec.end());
            }
            
            return bytesToNumber<T>(vec, len);
        }
        
        template<typename T>
        static std::vector<int8_t> numberToBytes(T val) {
            T mask = (T)0xff;
            
            int len = sizeof(T);
            std::vector<int8_t> vec(len, 0);
            
            for (int i = 0; i < len; i++) {
                vec[i] = (int8_t)(val >> (len * 8 - i * 8));
            }
            
            return vec;
        }
        
        
        //
        // ժҪ:
        //     ��ָ����˫���ȸ�����ת��Ϊ 64 λ�з���������
        //
        // ����:
        //   value:
        //     Ҫת�������֡�
        //
        // ���ؽ��:
        //     64 λ�з�����������ֵ���� value��
        
        static long DoubleToInt64Bits(double value) {
            return ((int64_t)value);
        }
        //
        // ժҪ:
        //     ���ֽ��������ʽ����ָ���Ĳ���ֵ��
        //
        // ����:
        //   value:
        //     һ������ֵ��
        //
        // ���ؽ��:
        //     ����Ϊ 1 ���ֽ����顣
        static std::vector<int8_t> GetBytes(bool value) {
            return numberToBytes((int8_t)value);
        }
        //
        // ժҪ:
        //     ���ֽ��������ʽ����ָ���� Unicode �ַ�ֵ��
        //
        // ����:
        //   value:
        //     Ҫת�����ַ���
        //
        // ���ؽ��:
        //     ����Ϊ 2 ���ֽ����顣
        static std::vector<int8_t> GetBytes(char value) {
            return numberToBytes(value);
        }
        //
        // ժҪ:
        //     ���ֽ��������ʽ����ָ���� 16 λ�з�������ֵ��
        //
        // ����:
        //   value:
        //     Ҫת�������֡�
        //
        // ���ؽ��:
        //     ����Ϊ 2 ���ֽ����顣
        
        static std::vector<int8_t> GetBytes(short value) {
            return numberToBytes(value);
        }
        //
        // ժҪ:
        //     ���ֽ��������ʽ����ָ���� 32 λ�з�������ֵ��
        //
        // ����:
        //   value:
        //     Ҫת�������֡�
        //
        // ���ؽ��:
        //     ����Ϊ 4 ���ֽ����顣
        
        static std::vector<int8_t> GetBytes(int value) {
            return numberToBytes(value);
        }
        //
        // ժҪ:
        //     ���ֽ��������ʽ����ָ���� 64 λ�з�������ֵ��
        //
        // ����:
        //   value:
        //     Ҫת�������֡�
        //
        // ���ؽ��:
        //     ����Ϊ 8 ���ֽ����顣
        
        static std::vector<int8_t> GetBytes(long value) {
            return numberToBytes(value);
        }
        //
        // ժҪ:
        //     ���ֽ��������ʽ����ָ���� 16 λ�޷�������ֵ��
        //
        // ����:
        //   value:
        //     Ҫת�������֡�
        //
        // ���ؽ��:
        //     ����Ϊ 2 ���ֽ����顣
        
        static std::vector<int8_t> GetBytes(uint16_t value) {
            return numberToBytes(value);
        }
        //
        // ժҪ:
        //     ���ֽ��������ʽ����ָ���� 32 λ�޷�������ֵ��
        //
        // ����:
        //   value:
        //     Ҫת�������֡�
        //
        // ���ؽ��:
        //     ����Ϊ 4 ���ֽ����顣
        
        static std::vector<int8_t> GetBytes(uint32_t value) {
            return numberToBytes(value);
        }
        //
        // ժҪ:
        //     ���ֽ��������ʽ����ָ���� 64 λ�޷�������ֵ��
        //
        // ����:
        //   value:
        //     Ҫת�������֡�
        //
        // ���ؽ��:
        //     ����Ϊ 8 ���ֽ����顣
        
        static std::vector<int8_t> GetBytes(uint64_t value) {
            return numberToBytes(value);
        }
        //
        // ժҪ:
        //     ���ֽ��������ʽ����ָ���ĵ����ȸ���ֵ��
        //
        // ����:
        //   value:
        //     Ҫת�������֡�
        //
        // ���ؽ��:
        //     ����Ϊ 4 ���ֽ����顣
        
        static std::vector<int8_t> GetBytes(float value) {
            return numberToBytes((int32_t)value);
        }
        //
        // ժҪ:
        //     ���ֽ��������ʽ����ָ����˫���ȸ���ֵ��
        //
        // ����:
        //   value:
        //     Ҫת�������֡�
        //
        // ���ؽ��:
        //     ����Ϊ 8 ���ֽ����顣
        
        static std::vector<int8_t> GetBytes(double value) {
            return numberToBytes((int64_t)value);
        }
        //
        // ժҪ:
        //     ��ָ���� 64 λ�з�������ת����˫���ȸ�������
        //
        // ����:
        //   value:
        //     Ҫת�������֡�
        //
        // ���ؽ��:
        //     ˫���ȸ���������ֵ���� value��
        
        static double Int64BitsToDouble(long value) {
            return value;
        }
        //
        // ժҪ:
        //     �������ֽ�������ָ��λ�õ�һ���ֽ�ת�����Ĳ���ֵ��
        //
        // ����:
        //   value:
        //     �ֽ����顣
        //
        //   startIndex:
        //     value �ڵ���ʼλ�á�
        //
        // ���ؽ��:
        //     ��� value �е� startIndex �����ֽڷ��㣬��Ϊ true������Ϊ false��
        //
        // �쳣:
        //   T:System.ArgumentNullException:
        //     value Ϊ null��
        //
        //   T:System.ArgumentOutOfRangeException:
        //     startIndex С�������� value �� 1 �ĳ��ȡ�
        static bool ToBoolean(std::vector<int8_t> value, int startIndex = 0) {
            return (toNumber<int8_t>(value, startIndex) != 0);
        }
        //
        // ժҪ:
        //     �������ֽ�������ָ��λ�õ������ֽ�ת������ Unicode �ַ���
        //
        // ����:
        //   value:
        //     һ�����顣
        //
        //   startIndex:
        //     value �ڵ���ʼλ�á�
        //
        // ���ؽ��:
        //     �������ֽڹ��ɡ��� startIndex ��ʼ���ַ���
        //
        // �쳣:
        //   T:System.ArgumentException:
        //     startIndex ���� value �� 1 �ĳ��ȡ�
        //
        //   T:System.ArgumentNullException:
        //     value Ϊ null��
        //
        //   T:System.ArgumentOutOfRangeException:
        //     startIndex С�������� value �� 1 �ĳ��ȡ�
        static char ToChar(std::vector<int8_t> value, int startIndex = 0) {
            return toNumber<char>(value, startIndex);
        }
        //
        // ժҪ:
        //     �������ֽ�������ָ��λ�õİ˸��ֽ�ת������˫���ȸ�������
        //
        // ����:
        //   value:
        //     �ֽ����顣
        //
        //   startIndex:
        //     value �ڵ���ʼλ�á�
        //
        // ���ؽ��:
        //     �ɰ˸��ֽڹ��ɡ��� startIndex ��ʼ��˫���ȸ�������
        //
        // �쳣:
        //   T:System.ArgumentException:
        //     startIndex ���ڵ��� value �� 7 �ĳ��ȣ���С�ڵ��� value �� 1 �ĳ��ȡ�
        //
        //   T:System.ArgumentNullException:
        //     value Ϊ null��
        //
        //   T:System.ArgumentOutOfRangeException:
        //     startIndex С�������� value �� 1 �ĳ��ȡ�
        
        static double ToDouble(std::vector<int8_t> value, int startIndex = 0) {
            return (double)toNumber<int64_t>(value, startIndex);
        }
        //
        // ժҪ:
        //     �������ֽ�������ָ��λ�õ������ֽ�ת������ 16 λ�з���������
        //
        // ����:
        //   value:
        //     �ֽ����顣
        //
        //   startIndex:
        //     value �ڵ���ʼλ�á�
        //
        // ���ؽ��:
        //     �������ֽڹ��ɡ��� startIndex ��ʼ�� 16 λ�з���������
        //
        // �쳣:
        //   T:System.ArgumentException:
        //     startIndex ���� value �� 1 �ĳ��ȡ�
        //
        //   T:System.ArgumentNullException:
        //     value Ϊ null��
        //
        //   T:System.ArgumentOutOfRangeException:
        //     startIndex С�������� value �� 1 �ĳ��ȡ�
        
        static int16_t ToInt16(std::vector<int8_t> value, int startIndex = 0) {
            return toNumber<int16_t>(value, startIndex);
        }
        //
        // ժҪ:
        //     �������ֽ�������ָ��λ�õ��ĸ��ֽ�ת������ 32 λ�з���������
        //
        // ����:
        //   value:
        //     �ֽ����顣
        //
        //   startIndex:
        //     value �ڵ���ʼλ�á�
        //
        // ���ؽ��:
        //     ���ĸ��ֽڹ��ɡ��� startIndex ��ʼ�� 32 λ�з���������
        //
        // �쳣:
        //   T:System.ArgumentException:
        //     startIndex ���ڵ��� value �� 3 �ĳ��ȣ���С�ڵ��� value �� 1 �ĳ��ȡ�
        //
        //   T:System.ArgumentNullException:
        //     value Ϊ null��
        //
        //   T:System.ArgumentOutOfRangeException:
        //     startIndex С�������� value �� 1 �ĳ��ȡ�
        
        static int32_t ToInt32(std::vector<int8_t> value, int startIndex = 0) {
            return toNumber<int32_t>(value, startIndex);
        }
        //
        // ժҪ:
        //     �������ֽ�������ָ��λ�õİ˸��ֽ�ת������ 64 λ�з���������
        //
        // ����:
        //   value:
        //     �ֽ����顣
        //
        //   startIndex:
        //     value �ڵ���ʼλ�á�
        //
        // ���ؽ��:
        //     �ɰ˸��ֽڹ��ɡ��� startIndex ��ʼ�� 64 λ�з���������
        //
        // �쳣:
        //   T:System.ArgumentException:
        //     startIndex ���ڵ��� value �� 7 �ĳ��ȣ���С�ڵ��� value �� 1 �ĳ��ȡ�
        //
        //   T:System.ArgumentNullException:
        //     value Ϊ null��
        //
        //   T:System.ArgumentOutOfRangeException:
        //     startIndex С�������� value �� 1 �ĳ��ȡ�
        
        static int64_t ToInt64(std::vector<int8_t> value, int startIndex = 0) {
            return toNumber<int64_t>(value, startIndex);
        }
        //
        // ժҪ:
        //     �������ֽ�������ָ��λ�õ��ĸ��ֽ�ת�����ĵ����ȸ�������
        //
        // ����:
        //   value:
        //     �ֽ����顣
        //
        //   startIndex:
        //     value �ڵ���ʼλ�á�
        //
        // ���ؽ��:
        //     ���ĸ��ֽڹ��ɡ��� startIndex ��ʼ�ĵ����ȸ�������
        //
        // �쳣:
        //   T:System.ArgumentException:
        //     startIndex ���ڵ��� value �� 3 �ĳ��ȣ���С�ڵ��� value �� 1 �ĳ��ȡ�
        //
        //   T:System.ArgumentNullException:
        //     value Ϊ null��
        //
        //   T:System.ArgumentOutOfRangeException:
        //     startIndex С�������� value �� 1 �ĳ��ȡ�
        
        static float ToSingle(std::vector<int8_t> value, int startIndex = 0) {
            return (float)toNumber<int32_t>(value, startIndex);
        }
        
        static char intToChar(const int& val) {
            if (val > 10) {
                return 'A' + 10 - val;
            } else {
                return '0' + val;
            }
        }
        
        //
        // ժҪ:
        //     ��ָ�����ֽ��������ÿ��Ԫ�ص���ֵת��Ϊ���ĵ�Чʮ�������ַ�����ʾ��ʽ��
        //
        // ����:
        //   value:
        //     �ֽ����顣
        //
        //   startIndex:
        //     value �ڵ���ʼλ�á�
        //
        //   length:
        //     Ҫת���� value �е�����Ԫ������
        //
        // ���ؽ��:
        //     �������ַ��ָ���ʮ�����ƶԹ��ɵ� System.String������ÿһ�Ա�ʾ value ���������ж�Ӧ��Ԫ�أ����硰7F-2C-4A����
        //
        // �쳣:
        //   T:System.ArgumentNullException:
        //     value Ϊ null��
        //
        //   T:System.ArgumentOutOfRangeException:
        //     startIndex �� length С���㡣- �� -startIndex �������Ҵ��ڵ��� value �ĳ��ȡ�
        //
        //   T:System.ArgumentException:
        //     startIndex �� length ����ϲ�ָ�� value �е�λ�ã�Ҳ����˵��startIndex �������� value �ĳ��ȼ�ȥ length
        //     ������
        static std::string ToString(std::vector<int8_t> value, const std::string& placeholders = "", size_t startIndex = 0, size_t length = 0) {
            std::string str;
            
            if (length <= 0 || length > value.size()) {
                length = value.size();
            }
            
            for (size_t i = startIndex; i < length; ++i) {
                auto& p = value[i];
                int c1 = p & 0xf0;
                int c2 = p & 0xf;
                str += intToChar(c1);
                str += intToChar(c2);
                
                if (i < length - 1) {
                    str += placeholders;
                }
            }
            
            return str;
        }
        //
        // ժҪ:
        //     �������ֽ�������ָ��λ�õ������ֽ�ת������ 16 λ�޷���������
        //
        // ����:
        //   value:
        //     �ֽ����顣
        //
        //   startIndex:
        //     value �ڵ���ʼλ�á�
        //
        // ���ؽ��:
        //     �������ֽڹ��ɡ��� startIndex ��ʼ�� 16 λ�޷���������
        //
        // �쳣:
        //   T:System.ArgumentException:
        //     startIndex ���� value �� 1 �ĳ��ȡ�
        //
        //   T:System.ArgumentNullException:
        //     value Ϊ null��
        //
        //   T:System.ArgumentOutOfRangeException:
        //     startIndex С�������� value �� 1 �ĳ��ȡ�
        
        static uint16_t ToUInt16(std::vector<int8_t> value, int startIndex = 0) {
            return toNumber<uint16_t>(value, startIndex);
        }
        
        /**
         * @fn	static uint BitConverter::ToUInt32(std::vector<int8_t> value, int startIndex);
         *
         * @brief	ժҪ:
         * 			    �������ֽ�������ָ��λ�õ��ĸ��ֽ�ת������ 32 λ�޷���������
         *
         * 			����:
         * 			  value:
         * 			    �ֽ����顣
         *
         * 			  startIndex:
         * 			    value �ڵ���ʼλ�á�
         *
         * 			���ؽ��:
         * 			    ���ĸ��ֽڹ��ɡ��� startIndex ��ʼ�� 32 λ�޷���������
         *
         * 			�쳣:
         * 			  T:System.ArgumentException:
         * 			    startIndex ���ڵ��� value �� 3 �ĳ��ȣ���С�ڵ��� value �� 1 �ĳ��ȡ�
         *
         * 			  T:System.ArgumentNullException:
         * 			    value Ϊ null��
         *
         * 			  T:System.ArgumentOutOfRangeException:
         * 			    startIndex С�������� value �� 1 �ĳ��ȡ�.
         *
         * @param	value	  	The value.
         * @param	startIndex	The start index.
         *
         * @return	The given data converted to an uint.
         */
        
        
        static uint32_t ToUInt32(std::vector<int8_t> value, int startIndex = 0) {
            return toNumber<uint32_t>(value, startIndex);
        }
        //
        // ժҪ:
        //     �������ֽ�������ָ��λ�õİ˸��ֽ�ת������ 64 λ�޷���������
        //
        // ����:
        //   value:
        //     �ֽ����顣
        //
        //   startIndex:
        //     value �ڵ���ʼλ�á�
        //
        // ���ؽ��:
        //     �ɰ˸��ֽڹ��ɡ��� startIndex ��ʼ�� 64 λ�޷���������
        //
        // �쳣:
        //   T:System.ArgumentException:
        //     startIndex ���ڵ��� value �� 7 �ĳ��ȣ���С�ڵ��� value �� 1 �ĳ��ȡ�
        //
        //   T:System.ArgumentNullException:
        //     value Ϊ null��
        //
        //   T:System.ArgumentOutOfRangeException:
        //     startIndex С�������� value �� 1 �ĳ��ȡ�
        
        static uint64_t ToUInt64(std::vector<int8_t> value, int startIndex = 0) {
            return toNumber<uint32_t>(value, startIndex);
        }
    };
}

#endif // AMO_BIT_CONVERTER_HPP__