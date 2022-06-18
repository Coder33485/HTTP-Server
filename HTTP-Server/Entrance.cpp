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

	HINSTANCE dll_handle[1024] = { nullptr };
	int dll_handles = 0;
	fstream file1, file2;
	struct stat fs;
	if (!quiet)
	{
		cout << "加载" << config << endl;
	}
	file1.open(config, ios::in | ios::binary);
	//  Open the configuration file.
	char* line = new char[4096];
	char* ptr = nullptr, * ptr2 = nullptr, * func_ptr = nullptr, * func_mode_ptr = nullptr;
	int func_mode = 0;
	ONCE func1 = nullptr;
	WAIT func2 = nullptr;
	CTX func3 = nullptr;
	bool loadFunction = false;
	memset(line, 0, 4096);
	// Read the configuration file.
	while (file1.getline(line, 4095)) // Read a line.
	{
		// Process comments.
		for (int i = 0; i < 4096; i++)
		{
			if (line[i] == ';')
			{
				line[i] = 0;
				break;
			}
		}

		ptr = strtok(line, " "); // Get Dll File Name.

		// Error Proc.
		if (ptr == nullptr)
		{
			memset(line, 0, 4096);
			continue;
		}
		// Error Proc.
		if (stat(ptr, &fs) != 0)
		{
			memset(line, 0, 4096);
			cerr << "加载" << ptr << "失败，是否有这个模块？" << endl;
			continue;
		}
		// Error Proc.
		if (!S_ISREG(fs.st_mode))
		{
			memset(line, 0, 4096);
			cerr << "加载" << ptr << "失败，似乎不是一个文件？" << endl;
			continue;
		}
		if (!quiet)
		{
			cout << "加载" << ptr << endl;
		}
		dll_handle[dll_handles] = LoadLibrary(ptr); // Load the DLL (module).
		ptr = strtok(nullptr, "\r\n "); // Get Module Configuration File Name.

		// Error Proc.
		if (ptr == nullptr)
		{
			memset(line, 0, 4096);
			continue;
		}
		// Error Proc.
		if (stat(ptr, &fs) != 0)
		{
			memset(line, 0, 4096);
			cerr << "加载" << ptr << "失败，缺少配置文件。" << endl;
			FreeLibrary(dll_handle[dll_handles]);
			dll_handle[dll_handles] = nullptr;
			continue;
		}
		// Error Proc.
		if (!S_ISREG(fs.st_mode))
		{
			memset(line, 0, 4096);
			cerr << "加载" << ptr << "失败，似乎不是一个文件？" << endl;
			FreeLibrary(dll_handle[dll_handles]);
			dll_handle[dll_handles] = nullptr;
			continue;
		}
		if (!quiet)
		{
			cout << "加载" << ptr << endl;
		}
		file2.open(ptr, ios::in | ios::binary); // Open module configuration file.
		memset(line, 0, 4096);
		while (file2.getline(line, 4095)) // Read a line.
		{
			func_mode = 0;
			// Process comments.
			for (int i = 0; i < 4096; i++)
			{
				if (line[i] == ';')
				{
					line[i] = 0;
					break;
				}
			}

			func_mode_ptr = strtok(line, " "); // Get Function Type.

			// Error Proc.
			if (func_mode_ptr == nullptr)
			{
				memset(line, 0, 4096);
				continue;
			}

			// Test FuncType.
			if (strcmp(func_mode_ptr, "ONCE") == 0)
			{
				func_mode = 1;
			}
			// Test FuncType.
			else if (strcmp(func_mode_ptr, "WAIT") == 0)
			{
				func_mode = 2;
			}
			// Test FuncType.
			else if (strcmp(func_mode_ptr, "CTX") == 0)
			{
				func_mode = 3;
			}

			func_ptr = strtok(nullptr, " "); // Get Function Name.

			// Error Proc.
			if (func_ptr == nullptr)
			{
				memset(line, 0, 4096);
				continue;
			}

			ptr = strtok(nullptr, " "); // Get Request Mode.

			// Error Proc.
			if (ptr == nullptr)
			{
				memset(line, 0, 4096);
				continue;
			}

			ptr2 = strtok(nullptr, "\r\n "); // Get Regular Expression.

			// Error Proc.
			if (ptr == nullptr)
			{
				memset(line, 0, 4096);
				continue;
			}
			// Test Request Mode.
			if (strcmp(ptr, "HEAD") == 0)
			{
				switch (func_mode)
				{
				case 1: // FuncType: ONCE
					func1 = (ONCE)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func1) // If you get a function pointer.
					{
						service.HEAD(ptr2, func1); // Set Rule.
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 2: // FuncType: WAIT
					func2 = (WAIT)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func2)
					{
						service.HEAD(ptr2, func2);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 3: // FuncType: CTX
					func3 = (CTX)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func3)
					{
						service.HEAD(ptr2, func3);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				}
			}
			else if (strcmp(ptr, "GET") == 0)
			{
				switch (func_mode)
				{
				case 1:
					func1 = (ONCE)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func1)
					{
						service.GET(ptr2, func1);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 2:
					func2 = (WAIT)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func2)
					{
						service.GET(ptr2, func2);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 3:
					func3 = (CTX)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func3)
					{
						service.GET(ptr2, func3);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				}
			}
			else if (strcmp(ptr, "POST") == 0)
			{
				switch (func_mode)
				{
				case 1:
					func1 = (ONCE)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func1)
					{
						service.POST(ptr2, func1);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 2:
					func2 = (WAIT)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func2)
					{
						service.POST(ptr2, func2);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 3:
					func3 = (CTX)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func3)
					{
						service.POST(ptr2, func3);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				}
			}
			else if (strcmp(ptr, "PUT") == 0)
			{
				switch (func_mode)
				{
				case 1:
					func1 = (ONCE)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func1)
					{
						service.PUT(ptr2, func1);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 2:
					func2 = (WAIT)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func2)
					{
						service.PUT(ptr2, func2);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 3:
					func3 = (CTX)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func3)
					{
						service.PUT(ptr2, func3);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				}
			}
			else if (strcmp(ptr, "DELETE") == 0)
			{
				switch (func_mode)
				{
				case 1:
					func1 = (ONCE)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func1)
					{
						service.Delete(ptr2, func1);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 2:
					func2 = (WAIT)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func2)
					{
						service.Delete(ptr2, func2);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 3:
					func3 = (CTX)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func3)
					{
						service.Delete(ptr2, func3);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				}
			}
			else if (strcmp(ptr, "PATCH") == 0)
			{
				switch (func_mode)
				{
				case 1:
					func1 = (ONCE)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func1)
					{
						service.PATCH(ptr2, func1);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 2:
					func2 = (WAIT)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func2)
					{
						service.PATCH(ptr2, func2);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 3:
					func3 = (CTX)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func3)
					{
						service.PATCH(ptr2, func3);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				}
			}
			else if (strcmp(ptr, "ANY") == 0)
			{
				switch (func_mode)
				{
				case 1:
					func1 = (ONCE)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func1)
					{
						service.Any(ptr2, func1);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 2:
					func2 = (WAIT)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func2)
					{
						service.Any(ptr2, func2);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				case 3:
					func3 = (CTX)GetProcAddress(dll_handle[dll_handles], func_ptr);
					if (func3)
					{
						service.Any(ptr2, func3);
						loadFunction = true;
					}
					else
					{
						loadFunction = false;
					}
					break;
				}
			}
			if (!quiet)
			{
				if (loadFunction)
				{
					cout << "成功加载" << func_mode_ptr << "函数：" << func_ptr << " 目标：" << ptr << " -> " << ptr2 << endl;
				}
				else
				{
					cout << "加载函数：" << func_ptr << "失败" << endl;
				}
			}
			func1 = nullptr;
			func2 = nullptr;
			func3 = nullptr;
			// Reset Function Pointers.
			memset(line, 0, 4096);
		}
		// End of read.
		file2.close(); // Close configuration file.
		dll_handles++;
		memset(line, 0, 4096);
	}
	file1.close(); // Close configuration file.
	if (!quiet)
	{
		cout << "成功加载了" << dll_handles << "个模块。" << endl;
	}

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
			dll_handles--;
			for (true; dll_handles >= 0; dll_handles--)
			{
				FreeLibrary(dll_handle[dll_handles]);
				dll_handle[dll_handles] = nullptr;
			}
			server.stop();
			delete[] line;
			break;
		}
	}
	// Exit.
	return 0;
}