// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>
using namespace SA;

#include <SCommon/WindowRenderApplication.hpp>

class SampleApp : public SCommon::WindowRenderApplication
{
protected:
	void Init() override final
	{
		SCommon::WindowRenderApplication::Init();
	}

	void UnInit() override final
	{
		SCommon::WindowRenderApplication::UnInit();
	}

	void Loop() override final
	{
		SCommon::WindowRenderApplication::Loop();
	}

	void Update() override final
	{
		SCommon::WindowRenderApplication::Update();
	}
};

int main()
{
	SA::Debug::InitDefaultLogger();

	SampleApp app;

	return app.CreateAndRun<SCommon::SelectedWindowInterface, SA::VK::RenderInterface>();
}
