[中文](https://github.com/Coder33485/HTTP-Server/blob/master/README-CN.md) | English<br>

# HTTP-Server

** Sorry this project has stopped updating. **<br>

In fact we also think it's a great idea, but it has to be said that in the process of using it we found some fatal problems.<br>

If we only start one server then obviously it's enough, but if we want to start multiple servers at the same time things get cumbersome,which we don't want to see. Even a toy has to make it perfect isn't it?<br>

In fact, the problem lies in the configuration file, at first we designed the configuration file format in order to make the configuration file as concise and easier to remember as possible and adopted a format close to the command line, this format does make the configuration file concise but also brings some problems: it can not handle some complex transactions, such as starting multiple servers at the same time, and it is difficult for the program to understand how to do some detailed processing.<br>

So I decided to stop the update of this project to prevent the wrong research direction from being expanded, another project based on the same concept is being developed, and the first version is 80% complete and will soon be launched.<br>

## Third party resources and copyrights used

[libhv](https://github.com/Coder33485/HTTP-Server/blob/master/public/libhv.md)<br>
