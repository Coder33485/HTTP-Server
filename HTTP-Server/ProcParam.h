#pragma once

#ifndef _PROCPARAM_H_
#define _PROCPARAM_H_

extern const char* ipv4;
extern const char* dir;
extern const char* config;
extern const int& port;
extern const bool& quiet;

// 参数处理函数
int ProcParam(int argc, char* argv[], int& id);

// 检测输入的字符串是否是一个IP地址
bool IsIPAddress(char* str);

//检测输入的字符是否是一个数字
bool IsNumber(char ch);

#endif // !_PROCPARAM_H_
