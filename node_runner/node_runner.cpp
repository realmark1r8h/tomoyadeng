// node_runner.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "node_runner.h"

#include <node.h>



extern "C" NODE_RUNNER_API int Start(int argc, char** argv) {
    return node::Start(argc, argv);
}

