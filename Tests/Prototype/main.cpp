// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>
using namespace SA;

#include <SCommon/WindowRenderApplication.hpp>

class SampleApp : public SCommon::WindowRenderApplication
{
protected:
	ARenderDevice* mDevice = nullptr;

	void CreateDevice()
	{
		const auto deviceInfo = mRenderIntf->QueryDevices();

		for (const auto& info : deviceInfo)
			SA_LOG(L"Device ID [" << info->ID << "] Vendor ID [" << info->vendorID << "] name [" << info->name << "]");

		mDevice = mRenderIntf->CreateDevice(deviceInfo[0]);
	}

	void Init() override final
	{
		SCommon::WindowRenderApplication::Init();

		CreateDevice();
	}

	void UnInit() override final
	{
		mRenderIntf->DestroyDevice(mDevice);

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
