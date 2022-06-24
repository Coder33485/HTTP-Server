/*
* This project has stopped updating,
  what you see may not be the latest version
* 这个项目已经停止更新，您看到的可能不是最新版本
*/
#pragma once

#ifndef _STD_H_
#define _STD_H_

#undef UNICODE

#include "hv/HttpServer.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

typedef int (*CTX)(const HttpContextPtr& ctx);

extern "C"
{
	_declspec(dllexport) int HsDllRun(const HttpContextPtr& ctx);
}

#endif // !_STD_H_
