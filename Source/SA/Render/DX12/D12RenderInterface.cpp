// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <DX12/D12RenderInterface.hpp>

#include <SA/Collections/Debug>

namespace SA
{
	namespace DX12
	{
		void RenderInterface::Create()
		{
			SA_LOG(L"Render Interface created.", Infos, SA/Render/DX12);
		}

		void RenderInterface::Destroy()
		{
			SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/DX12);
		}
	}
}
