#include "General.h"

char _ipv4[16] = "0.0.0.0";
char _dir[512] = "./";
char _config[512] = "./server.hsconfig";
int _port = 80;
bool _quiet = false;
const char* ipv4 = _ipv4;
const char* dir = _dir;
const char* config = _config;
const int& port = _port;
const bool& quiet = _quiet;

int ProcParam(int argc, char* argv[], int& id)
{
	if (id >= argc || id <= 0)
	{
		return -1;
	}
	if (strcmp(argv[id], "-dir") == 0)
	{
		id++;
		struct stat fs;
		if (stat(argv[id], &fs) != 0)
		{
			return ProcParam(argc, argv, id);
		}
		if (S_ISDIR(fs.st_mode))
		{
			strcpy(_dir, argv[id]);
		}
		else
		{
			return ProcParam(argc, argv, id);
		}
	}
	else if (strcmp(argv[id], "-ip") == 0)
	{
		id++;
		if (IsIPAddress(argv[id]))
		{
			strcpy(_ipv4, argv[id]);
		}
		else
		{
			return ProcParam(argc, argv, id);
		}
	}
	else if (strcmp(argv[id], "-port") == 0)
	{
		id++;
		int p = atoi(argv[id]);
		if (p >= 0 && p <= 65535)
		{
			_port = p;
		}
	}
	else if (strcmp(argv[id], "-conf") == 0)
	{
		id++;
		struct stat fs;
		if (stat(argv[id], &fs) != 0)
		{
			return ProcParam(argc, argv, id);
		}
		if (S_ISREG(fs.st_mode))
		{
			strcpy(_config, argv[id]);
		}
		else
		{
			return ProcParam(argc, argv, id);
		}
	}
	else if (strcmp(argv[id], "-quiet") == 0)
	{
		_quiet = true;
	}
	else if (strcmp(argv[id], "-help") == 0)
	{
		HelpMessage();
	}
	else 
	{
		return 1;
	}
	return 0;
}

bool IsIPAddress(char* str)
{
	if (strlen(str) > 15 || strlen(str) < 7)
	{
		return false;
	}
	char chk[16] = { 0 };
	int p[4] = { 0 };
	int& pt = p[0];
	strcpy(chk, str);
	for (int i = 0; i < strlen(chk); i++)
	{
		if (i == 0)
		{
			if (!IsNumber(chk[0]))
			{
				return false;
			}
		}
		if (!IsNumber(chk[i]) && chk[i] != '.')
		{
			return false;
		}
		if (chk[i] == '.')
		{
			pt++;
			if (pt > 3)
			{
				return false;
			}
			p[pt] = i;
		}
	}
	if (pt != 3)
	{
		return false;
	}
	if (!IsNumber(chk[p[1] + 1]) || !IsNumber(chk[p[2] + 1]) || !IsNumber(chk[p[3] + 1]))
	{
		return false;
	}
	chk[p[1]] = 0;
	chk[p[2]] = 0;
	chk[p[3]] = 0;
	if (atoi(&chk[0]) > 255 || atoi(&chk[p[1] + 1]) > 255 || atoi(&chk[p[2] + 1]) > 255 || atoi(&chk[p[3] + 1]) > 255)
	{
		return false;
	}
	return true;
}

bool IsNumber(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return true;
	}
	return false;
}