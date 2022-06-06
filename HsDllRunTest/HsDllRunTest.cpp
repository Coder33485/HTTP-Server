#include "HsDllRunTest.h"

int HsDllMain(const HttpContextPtr& ctx)
{
	ctx->writer->Begin();
	ctx->writer->WriteStatus(HTTP_STATUS_OK);
	ctx->writer->WriteHeader("Content-Type", "text/html");
	ctx->writer->WriteBody("<!DOCTYPE html>\n<html>\n<head>\n\t<meta charset=\"utf-8\"/>\n\t<title></title>\n</head>\n<body style=\"text-align: center;\">\n\t<h1>HsDllRunTest: Hello, World!</h1>\n\t<hr/>\n</body>\n</html>");
	ctx->writer->End();
	return ctx->send();
}