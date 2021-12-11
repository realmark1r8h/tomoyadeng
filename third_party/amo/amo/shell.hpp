// Created by amoylel on 01/08/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_SHELL_HPP__
#define AMO_SHELL_HPP__

#include <string>
#include <WinSock2.h>
#include <windows.h>

namespace amo {
	class shell {
		
	public:
		shell(const std::string& strExe):
		fileName(strExe){
			nShowCmd = SW_SHOWNORMAL;
		}

		int exec( ) {
			return 0;
		}


		int open() { 
			return (int)::ShellExecuteA(NULL,
				"open",
				fileName.c_str(),
				params.c_str(),
				workDir.c_str(),
				nShowCmd);
		}
		int print() {
			return 0;
		}
		int showItemInFolder() {
			return 0;
		}

		void addArgs(const std::string args) {
			params += " ";
			params += args;
		}

		void show(bool bShow) {
			if (bShow) {
				nShowCmd = SW_SHOWNORMAL;
			}
			else {
				nShowCmd = SW_HIDE;
			}
		}
	private:
		int nShowCmd;
		std::string fileName;
		std::string params;
		std::string workDir;
	};
}

#endif // AMO_SHELL_HPP__