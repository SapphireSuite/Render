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

			SA_DX12_CREATE_LOG(Factory, mHandle)
		}
		
		void Factory::Destroy()
		{
			SA_DX12_POST_DESTROY_LOG(Factory, mHandle)

			mHandle->Release();
			mHandle = nullptr;
		}

		IDXGIFactory6* Factory::operator->() const
		{
			return mHandle;
		}
	}
}
