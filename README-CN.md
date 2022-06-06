中文 | [EngLish](https://github.com/Coder33485/HTTP-Server/blob/master/README.md)<br>

# HTTP-Server

默认状态下，软件仅支持静态HTTP页面，不支持动态HTTP页面，但可以通过添加外部模块的方式解决<br>

## 外部模块的添加

对于编写好的模块(dll文件以及配置文件)，我们将其放入软件所在的目录中，并向配置文件(server.hsconfig)中添加这样一行<br>

`dll文件名(包括扩展名) 配置文件的文件名`<br>

比如我有一个dll文件叫：module.dll，配置文件叫：module.hsconfig<br>

那么，我就向配置文件加入这样一行：<br>

`module.dll module.hsconfig`<br>

这样，在软件启动时就会去读取配置文件，然后加载你的模块<br>

## 外部模块如何制作

### dll

对于dll文件，其中存储的函数是这样的：<br>

`int xxx(HttpRequest* req, HttpResponse* resp);`<br>
`void xxx(const HttpRequestPtr& req, const HttpResponseWriterPtr& writer);`<br>
`int xxx(const HttpContextPtr& ctx);`<br>

其中 xxx 是函数名，3种函数对应3种不同的加载模式，所以对应相应的函数它的类型也要在配置文件中表示出来<br>

一个dll可以存储多个这样的不同名的函数，只要最后都添加到配置文件中即可<br>

但是需要注意的是，我们的软件使用了第三方库libhv，而dll模块必须也依赖它<br>

也就是说，您需要在头文件中引用：<br>

`#include "hv/HttpServer.h"`<br>

而且为了保证模块能够按照预期的想法在软件上运行，我们需要保证软件和模块使用的libhv版本一致<br>

并且您的模块必须使用动态库并隐式加载libhv(也就是使用 .lib 和 .dll 文件)<br>

但是当您分发您的模块的时候，您不需要同时分发对应版本的libhv dll文件，因为软件中已经有了<br>

### hsconfig

对于模块配置文件，我们应该这样编写：<br>

对于每一个需要暴露的函数，我们使用至少一行来描述它<br>

`函数类型 函数名 请求模式 正则表达式`<br>

但是只支持简单的正则表达式<br>

比如我有一个函数：<br>

`int txt_proc(HttpRequest* req, HttpResponse* resp);`<br>

用来处理关于txt文件的GET请求，那么在配置文件中应该写这样一行：<br>

`ONCE txt_proc GET *.txt`<br>

其中，ONCE是函数类型，txt_proc是函数名，GET是请求模式，*.txt表示函数接收所有文件名以“.txt”结尾的请求<br>

另外需要注意的是，并非一个函数只能处理一种请求，这取决于您如何设计函数，对于一个函数如果可以处理多种请求的话，您可以这样写配置文件：<br>

`ONCE txt_proc GET *.txt`<br>
`ONCE txt_proc GET *.log`<br>
`ONCE txt_proc POST *.cgi`<br>

这代表函数不仅可以处理文件名以“.txt”结尾的请求，还可以处理文件名以“.log”结尾的请求，甚至还可以处理POST请求<br>

事实上，我们对一行中的最后2个字段是几乎不做限制的，理论上您可以任意搭配它们，这取决于你需要让函数处理什么样的工作<br>

但是，最后一个字段不能设为 * 或 \*.\* 以及其他的类似值<br>

对于服务器配置文件，我们应该这样编写：<br>

`dll文件名(包括扩展名) 配置文件的文件名`<br>

所有hsconfig文件均支持注释，使用英文分号注释，每一行分号之后的字符都会被忽略<br>

另外，每行的长度不能超过4096字节，否则会出现错误<br>

#### 函数类型

`ONCE - int xxx(HttpRequest* req, HttpResponse* resp);`<br>
`WAIT - void xxx(const HttpRequestPtr& req, const HttpResponseWriterPtr& writer);`<br>
`CTX  - int xxx(const HttpContextPtr& ctx);`<br>

###  请求模式

`HEAD`<br>
`GET`<br>
`POST`<br>
`PUT`<br>
`DELETE`<br>
`PATCH`<br>
`ANY`<br>

## 示例

我们提供了一个模块示例及其代码<br>

## 使用的第三方资源及著作权

[libhv](https://github.com/Coder33485/HTTP-Server/blob/master/public/libhv.md)<br>

