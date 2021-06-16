// Created by amoylel on 06/19/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_RCEDIT_H__
#define AMO_RCEDIT_H__








#ifdef RCEDIT_EXPORTS
#define RCEDIT_API __declspec(dllexport)
#else
#define RCEDIT_API __declspec(dllimport)
#endif

 
#include "module/JSV8Handler.h"

class StringLoader{
public:
	StringLoader(HINSTANCE hInstance){ m_hInstance = hInstance; }
	std::string load(UINT id){
		char str[4096] = { 0 };
		::LoadStringA(m_hInstance, id, str, 4096);
		return str;
	}
private:
	HINSTANCE m_hInstance;
}; 
// 此类是从 rcedit.dll 导出的
class RCEDIT_API Crcedit {
public:
	Crcedit(void);
	// TODO:  在此添加您的方法。
};

extern RCEDIT_API int nrcedit;

RCEDIT_API int fnrcedit(void);


 


#endif // AMO_RCEDIT_H__
