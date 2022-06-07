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
