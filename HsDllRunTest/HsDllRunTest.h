#pragma once

#ifndef _HSDLLRUNTEST_H_
#define _HSDLLRUNTEST_H_

#include "hv/HttpServer.h"

extern "C" _declspec(dllexport) int HsDllMain(const HttpContextPtr & ctx);

#endif // !_HSDLLRUNTEST_H_
