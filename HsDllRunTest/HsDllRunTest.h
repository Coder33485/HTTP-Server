/*
* This project has stopped updating,
  what you see may not be the latest version
* 这个项目已经停止更新，您看到的可能不是最新版本
*/
#pragma once

#ifndef _HSDLLRUNTEST_H_
#define _HSDLLRUNTEST_H_

#include "hv/HttpServer.h"

extern "C" _declspec(dllexport) int HsDllMain(const HttpContextPtr & ctx);

#endif // !_HSDLLRUNTEST_H_
