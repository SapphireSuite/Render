// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include "D12Factory.hpp"

#include "Debug/Debug.hpp"

namespace SA
{
	namespace DX12
	{
		void Factory::Create()
		{
			UINT dxgiFactoryFlags = 0;

		#if SA_DEBUG

			ID3D12Debug* debugController0 = nullptr;
			SA_DX12_ASSERT(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController0)), L"Failed to query debug interface ID3D12Debug");

			ID3D12Debug1* debugController1 = nullptr;
			SA_DX12_ASSERT(debugController0->QueryInterface(IID_PPV_ARGS(&debugController1)), L"Failed to query interface ID3D12Debug1");

			debugController0->EnableDebugLayer();
			debugController1->SetEnableGPUBasedValidation(true);

			// Enable additional debug layers.
			dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

			debugController1->Release();
			debugController0->Release();

		#endif

			SA_DX12_ASSERT(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&mHandle)), L"Failed to create DX12 factory.");

			SA_LOG(L"Factory [" << mHandle << "] created.", Infos, SA/Render/DX12);
		}
		
		void Factory::Destroy()
		{
			const uint64_t addr = reinterpret_cast<uint64_t>(mHandle);

			mHandle->Release();
			mHandle = nullptr;

			SA_LOG(L"Factory [" << addr << "] destroyed.", Infos, SA/Render/DX12);
		}
	}
}
