#pragma once

#ifndef _PROCPARAM_H_
#define _PROCPARAM_H_

extern const char* ipv4;
extern const char* dir;
extern const char* config;
extern const int& port;
extern const bool& quiet;

// ����������
int ProcParam(int argc, char* argv[], int& id);

// ���������ַ����Ƿ���һ��IP��ַ
bool IsIPAddress(char* str);

//���������ַ��Ƿ���һ������
bool IsNumber(char ch);

#endif // !_PROCPARAM_H_
