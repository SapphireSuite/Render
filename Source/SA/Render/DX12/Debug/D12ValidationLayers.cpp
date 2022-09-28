// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include "D12ValidationLayers.hpp"

#include <d3d12.h>

#include <Debug/Debug.hpp>

namespace SA
{
	namespace DX12
	{
		void ValidationLayers::Initialize()
		{
#if SA_DX12_VALIDATION_LAYERS

			ID3D12Debug1* debugController = nullptr;

			if (D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)) == S_OK)
			{
				debugController->EnableDebugLayer();
				debugController->SetEnableGPUBasedValidation(true);

				debugController->Release();

				SA_LOG(L"Validation layer initialized.", Infos, SA/Render/DX12);
			}
			else
				SA_LOG(L"Validation layer initialization failed.", Error, SA/Render/DX12);

#endif // SA_DX12_VALIDATION_LAYERS
		}

		void ValidationLayers::Uninitialize()
		{
#if SA_DX12_VALIDATION_LAYERS

			SA_LOG(L"Validation layer uninitialized.", Infos, SA/Render/DX12);

#endif // SA_DX12_VALIDATION_LAYERS
		}
	}
}
