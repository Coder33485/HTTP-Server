/*
* This project has stopped updating,
  what you see may not be the latest version
* 这个项目已经停止更新，您看到的可能不是最新版本
*/
#include "General.h"

void HelpMessage(void)
{
	cout << "\
HTTP-Server 帮助信息\n\
Options:\n\
	-dir	设置工作目录\n\
	-ip 	设置监听IP\n\
	-port	设置监听端口\n\
	-conf	设置加载的模块列表配置文件(默认是server.hsconfig)\n\
	-quiet	安静启动(只有错误提示)\n\
	-help	显示帮助信息" << endl;
	exit(0);
}