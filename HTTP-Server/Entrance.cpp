#undef UNICODE

#include "General.h"

typedef int (*ONCE)(HttpRequest* req, HttpResponse* resp);
typedef void (*WAIT)(const HttpRequestPtr& req, const HttpResponseWriterPtr& writer);
typedef int (*CTX)(const HttpContextPtr& ctx);

int main(int argc, char* argv[])
{
	// Process parameters.
	for (int i = 0; i < argc; i++)
	{
		ProcParam(argc, argv, i);
	}

	HttpService service;
	// Rule.

	// Add Rule.
	service.Any("*/", [](HttpRequest* req, HttpResponse* resp) {
		char* path = new char[2048];
		memset(path, 0, 2048);
		strcpy(path, ".");
		strcat(path, req->Path().c_str());
		strcat(path, "index.html");
		int ret = resp->File(path);
		delete[] path;
		return ret;
		});

	// Add Rule.
	service.Any("*", [](HttpRequest* req, HttpResponse* resp) {
		char* path = new char[2048];
		memset(path, 0, 2048);
		strcpy(path, ".");
		strcat(path, req->Path().c_str());
		struct stat fs;
		if (stat(path, &fs) == 0)
		{
			if (S_ISDIR(fs.st_mode))
			{
				strcat(path, "/index.html");
			}
		}
		int ret = resp->File(path);
		delete[] path;
		return ret;
		});

	chdir(dir); // Set working directory.

	HttpServer server;
	server.registerHttpService(&service); // Set Rule.
	server.setPort(port); //Set Port.
	server.setProcessNum(4);
	server.setThreadNum(4);
	thread t(http_server_run, &server, 1);
	t.detach(); // Run Server.

	char inputline[64] = { 0 };
	while (true) //get Input.
	{
		memset(inputline, 0, 64);
		cin.getline(inputline, 63);
		if (strcmp(inputline, "stop") == 0 || strcmp(inputline, "exit") == 0) // Exit the loop if you enter "stop" or "exit" 
		{
			break;
		}
	}
	// Exit.
	return 0;
}