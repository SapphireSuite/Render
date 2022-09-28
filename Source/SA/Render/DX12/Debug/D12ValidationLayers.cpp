// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Debug/D12ValidationLayers.hpp>

#if SA_DX12_VALIDATION_LAYERS

namespace SA
{
	namespace DX12
	{
		void ValidationLayers::Create()
		{
			SA_DX12_ASSERT(D3D12GetDebugInterface(IID_PPV_ARGS(&mDebugController)), L"Failed to query debug interface ID3D12Debug");

			mDebugController->EnableDebugLayer();
			mDebugController->SetEnableGPUBasedValidation(true);

			SA_LOG(L"Validation layer enabled.", Infos, SA/Render/DX12);
		}

		void ValidationLayers::Destroy()
		{
			mDebugController->Release();
			mDebugController = nullptr;

			SA_LOG(L"Validation layer destroyed.", Infos, SA/Render/DX12);
		}
	}
}

#endif // SA_DX12_VALIDATION_LAYERS
