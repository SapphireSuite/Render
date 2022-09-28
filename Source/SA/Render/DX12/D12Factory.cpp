// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include "D12Factory.hpp"

#include "Debug/Debug.hpp"
#include "Debug/D12ValidationLayers.hpp"

namespace SA
{
	namespace DX12
	{
		void Factory::Create()
		{
			UINT dxgiFactoryFlags = 0;

		#if SA_DX12_VALIDATION_LAYERS

			// Enable additional debug layers.
			dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

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
