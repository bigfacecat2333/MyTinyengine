#pragma once
#include <stdio.h>
#ifdef MTE_PLATFORM_WINDOWS

extern MTE::Application* MTE::CreateApplication();

// ����һ��dll��Ӧ��Main����������Engine��Ӧ�Ĳ�����ͬʱ����װһ���ӿں��������ڴ�����Ӧ��Application��
// ���崴��Application��������񽻸��˶��󣬶�����Ҫnew���Լ���Ӧ�ö��󣬼̳���Engine���Application���࣬
// Ȼ������ָ�봫������֮����ڴ��ͷžͽ��������������ˣ���Ϊʵ����ִ�е�ֻ��Sandbox.cpp�ļ�

int main(int argc, char** argv)
{
	printf("start!");
	auto app = MTE::CreateApplication();
	app->Run();
	delete app;
}

#endif