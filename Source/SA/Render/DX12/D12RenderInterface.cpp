// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <D12RenderInterface.hpp>

#include <d3d12.h>
#include <dxgi1_6.h>

#include <Debug/Debug.hpp>

namespace SA
{
	namespace DX12
	{
		void RenderInterface::Create(AWindowInterface* _win_intf)
		{
			ARenderInterface::Create(_win_intf);

			CreateFactory();

			SA_LOG(L"Render Interface created.", Infos, SA/Render/DX12);
		}

		void RenderInterface::Destroy()
		{
			ARenderInterface::Destroy();

			DestroyFactory();

			SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/DX12);
		}

		void RenderInterface::Clear()
		{
			ARenderInterface::Clear();

			SA_LOG(L"Render Interface cleared.", Infos, SA/Render/DX12);
		}


	//{ Factory

		void RenderInterface::CreateFactory()
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

   			SA_DX12_ASSERT(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&mFactory)), L"Failed to create DX12 factory.");

			SA_LOG(L"Factory created.", Infos, SA/Render/DX12);
		}

		void RenderInterface::DestroyFactory()
		{
			mFactory->Release();
			mFactory = nullptr;

			SA_LOG(L"Factory destroyed.", Infos, SA/Render/DX12);
		}

	//}
	}
}
