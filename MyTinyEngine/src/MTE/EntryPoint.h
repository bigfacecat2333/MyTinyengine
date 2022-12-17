#pragma once

#ifdef MTE_PLATFORM_WINDOWS

// sandbox中定义了CreateApplication函数
extern MTE::Application* MTE::CreateApplication();

// 创建一个dll对应的Main函数，进行Engine对应的操作，同时，封装一个接口函数，用于创建对应的Application，
// 具体创建Application对象的任务交给了对象，对象需要new出自己的应用对象，继承于Engine里的Application基类，
// 然后把这个指针传过来，之后的内存释放就交给引擎来处理了，因为实际上执行的只有Sandbox.cpp文件

// 这里不用include直接使用MTE命名空间，是因为在MTE.h里已经include了MTE/Core/Application.h
// 在预编译时，这些代码会被替换成对应的代码，所以这里不用include也可以使用
int main(int argc, char** argv)
{
	MTE::Log::Init();
	MTE_CORE_WARN("Initialized Log!");
	int a = 5;
	MTE_INFO("Hello! Var={0}", a);

	// 创建一个Application对象，这个对象是由Sandbox.cpp文件中的CreateApplication()函数创建的
	auto app = MTE::CreateApplication();
	app->Run();
	delete app;
}

#endif