#include "General.h"

void HelpMessage(void)
{
	cout << "\
HTTP-Server ������Ϣ\n\
Options:\n\
	-dir	���ù���Ŀ¼\n\
	-ip 	���ü���IP\n\
	-port	���ü����˿�\n\
	-conf	���ü��ص�ģ���б������ļ�(Ĭ����server.hsconfig)\n\
	-quiet	��������(ֻ�д�����ʾ)\n\
	-help	��ʾ������Ϣ" << endl;
	exit(0);
}