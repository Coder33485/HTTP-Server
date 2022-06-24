/*
* This project has stopped updating,
  what you see may not be the latest version
* 这个项目已经停止更新，您看到的可能不是最新版本
*/
#include "Std.h"

int HsDllRun(const HttpContextPtr& ctx)
{
	string path = ".";
	path += ctx->request->Path(); // Get DLL Path.
	struct stat fs;
	if (stat(path.c_str(), &fs) == 0) // Test Path.
	{
		if (S_ISREG(fs.st_mode)) // If exist and it is file.
		{
			HINSTANCE dllHandle = LoadLibrary(path.c_str()); // Load Library.
			if (dllHandle) // If OK.
			{
				CTX func = (CTX)GetProcAddress(dllHandle, "HsDllMain"); // Load Funcction.
				if (func) // If OK.
				{
					func(ctx); //Run Function.
					return ctx->send();
				}
				else // If Fail.
				{
					ctx->writer->Begin();
					ctx->writer->WriteStatus(HTTP_STATUS_NOT_FOUND);
					ctx->writer->WriteHeader("Content-Type", "text/html");
					ctx->writer->WriteBody("<!DOCTYPE html>\n<html>\n<head>\n\t<title>Function HsDllMain Not Found</title>\n</head>\n<body>\n\t<center><h1>Function HsDllMain Not Found</h1></center>\n\t<hr/>\n</body>\n</html>");
					ctx->writer->End();
					return ctx->send();
				}
				FreeLibrary(dllHandle);
			}
			else // If Fail.
			{
				ctx->writer->Begin();
				ctx->writer->WriteStatus(HTTP_STATUS_INTERNAL_SERVER_ERROR);
				ctx->writer->WriteHeader("Content-Type", "text/html");
				ctx->writer->WriteBody("<!DOCTYPE html>\n<html>\n<head>\n\t<title>Load Dll File Fail.</title>\n</head>\n<body>\n\t<center><h1>Load Dll File Fail.</h1></center>\n\t<hr/>\n</body>\n</html>");
				ctx->writer->End();
				return ctx->send();
			}
		}
		else // If it is not file
		{
			ctx->writer->Begin();
			ctx->writer->WriteStatus(HTTP_STATUS_NOT_FOUND);
			ctx->writer->WriteHeader("Content-Type", "text/html");
			ctx->writer->WriteBody("<!DOCTYPE html>\n<html>\n<head>\n\t<title>404 Not Found</title>\n</head>\n<body>\n\t<center><h1>404 Not Found</h1></center>\n\t<hr/>\n</body>\n</html>");
			ctx->writer->End();
			return ctx->send();
		}
	}
	else // If it is not exist.
	{
		ctx->writer->Begin();
		ctx->writer->WriteStatus(HTTP_STATUS_NOT_FOUND);
		ctx->writer->WriteHeader("Content-Type", "text/html");
		ctx->writer->WriteBody("<!DOCTYPE html>\n<html>\n<head>\n\t<title>404 Not Found</title>\n</head>\n<body>\n\t<center><h1>404 Not Found</h1></center>\n\t<hr/>\n</body>\n</html>");
		ctx->writer->End();
		return ctx->send();
	}
	return ctx->send();
}
