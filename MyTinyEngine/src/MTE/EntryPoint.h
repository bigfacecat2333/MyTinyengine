#pragma once

#ifdef MTE_PLATFORM_WINDOWS

// sandbox�ж�����CreateApplication����
extern MTE::Application* MTE::CreateApplication();

// ����һ��dll��Ӧ��Main����������Engine��Ӧ�Ĳ�����ͬʱ����װһ���ӿں��������ڴ�����Ӧ��Application��
// ���崴��Application��������񽻸��˶��󣬶�����Ҫnew���Լ���Ӧ�ö��󣬼̳���Engine���Application���࣬
// Ȼ������ָ�봫������֮����ڴ��ͷžͽ��������������ˣ���Ϊʵ����ִ�е�ֻ��Sandbox.cpp�ļ�

// ���ﲻ��includeֱ��ʹ��MTE�����ռ䣬����Ϊ��MTE.h���Ѿ�include��MTE/Core/Application.h
// ��Ԥ����ʱ����Щ����ᱻ�滻�ɶ�Ӧ�Ĵ��룬�������ﲻ��includeҲ����ʹ��
int main(int argc, char** argv)
{
	MTE::Log::Init();
	MTE_CORE_WARN("Initialized Log!");
	int a = 5;
	MTE_INFO("Hello! Var={0}", a);

	// ����һ��Application���������������Sandbox.cpp�ļ��е�CreateApplication()����������
	auto app = MTE::CreateApplication();
	app->Run();
	delete app;
}

#endif