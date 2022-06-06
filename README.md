[中文](https://github.com/Coder33485/HTTP-Server/blob/master/README-CN.md) | English<br>

# HTTP-Server

By default, the software only supports static HTTP pages and does not support dynamic HTTP pages, but can be solved by adding external modules.<br>

## Addition of external modules

For the prepared modules (DLL files and configuration files), we put them into the directory where the software is located, and add such a line to the configuration file (server.hsconfig).<br>

`DLL_file_name(including extension) <space> file_name_of_configuration_file`<br>

For example, I have a DLL file called "module.dll". The configuration file is called: "module.hsconfig".<br>

Then, I will add this line to the configuration file:<br>

`module.dll module.hsconfig`<br>

In this way, the configuration file will be read when the software starts, and then the module will be loaded.<br>

## How to make external modules

### DLL

For DLL files, the stored functions are as follows:<br>

`int xxx(HttpRequest* req, HttpResponse* resp);`<br>
`void xxx(const HttpRequestPtr& req, const HttpResponseWriterPtr& writer);`<br>
`int xxx(const HttpContextPtr& ctx);`<br>

Where xxx is the function name, and the three functions correspond to three different loading modes. Therefore, the type of the corresponding function should also be indicated in the configuration file.<br>

A DLL can store multiple functions with different names, as long as they are added to the configuration file.<br>

However, it should be noted that our software uses the third-party library libhv, and the DLL module must also rely on it.<br>

That is, you need to reference in the header file:<br>

`#include "hv/HttpServer.h"`<br>

In addition, to ensure that the module can run on the software as expected, we need to ensure that the libhv versions used by the software and the module are consistent.<br>

And your module must use dynamic libraries and implicitly load libhv (that is, use *.lib and *.Dll files).<br>

However, when you distribute your module, you do not need to distribute the libhv DLL file of the corresponding version at the same time, because the software already has.<br>

### hsconfig

The module configuration file should be written as follows:<br>

For each function that needs to be exposed, we use at least one line to describe it.<br>

`Function_Type Function_Name Request_Mode Regular_Expression`<br>

However, only simple regular expressions are supported.<br>

For example, I have a function:<br>

`int txt_proc(HttpRequest* req, HttpResponse* resp);`< br>

To process GET requests for txt files, write this line in the configuration file:<br>

`ONCE txt_proc GET *. txt`<br>

Where once is the function type and txt_proc is the function name, GET is the request mode, *.txt means that the function receives all requests with file names ending in ".txt".<br>

In addition, it should be noted that not one function can only handle one request, which depends on how you design the function. If a function can handle multiple requests, you can write the configuration file as follows:<br>

`ONCE txt_proc GET *.txt`<br>
`ONCE txt_proc GET *.log`<br>
`ONCE txt_proc POST *.cgi`<br>

This means that the function can handle not only requests with file names ending in ".txt", but also requests with file names ending in ".log", and even post requests.<br>

In fact, we have almost no restrictions on the last two fields in a row. Theoretically, you can match them at will, depending on what work you need the function to handle.<br>

However, the last field cannot be set to * or \*.\* And other similar values.<br>

For the server configuration file, we should write it as follows:<br>

`DLL_file_name(including extension) <space> file_name_of_configuration_file`<br>

All hsconfig files support comments. English semicolons are used for comments. Characters after semicolons in each line will be ignored.<br>

In addition, the length of each line cannot exceed 4096 bytes, otherwise an error will occur.<br>

#### Function type

`ONCE - int xxx(HttpRequest* req, HttpResponse* resp);`<br>
`WAIT - void xxx(const HttpRequestPtr& req, const HttpResponseWriterPtr& writer);`<br>
`CTX  - int xxx(const HttpContextPtr& ctx);`<br>

### Request mode

`HEAD`<br>
`GET`<br>
`POST`<br>
`PUT`<br>
`DELETE`<br>
`PATCH`<br>
`ANY`<br>

## Example

We provide a sample module and its code.<br>

## Third party resources and copyrights used

[libhv](https://github.com/Coder33485/HTTP-Server/blob/master/public/libhv.md)<br>
