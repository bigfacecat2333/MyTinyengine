#pragma once
#include <stdio.h>
#ifdef MTE_PLATFORM_WINDOWS

extern MTE::Application* MTE::CreateApplication();

// 创建一个dll对应的Main函数，进行Engine对应的操作，同时，封装一个接口函数，用于创建对应的Application，
// 具体创建Application对象的任务交给了对象，对象需要new出自己的应用对象，继承于Engine里的Application基类，
// 然后把这个指针传过来，之后的内存释放就交给引擎来处理了，因为实际上执行的只有Sandbox.cpp文件

int main(int argc, char** argv)
{
	printf("start!");
	auto app = MTE::CreateApplication();
	app->Run();
	delete app;
}

#endif