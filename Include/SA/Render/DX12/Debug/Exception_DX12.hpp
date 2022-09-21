// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_EXCEPTION_VULKAN_GUARD
#define SAPPHIRE_RENDER_EXCEPTION_VULKAN_GUARD

#include <SA/Logger/Exceptions/Exception.hpp>

#include <SA/Support/API/Windows.hpp>

namespace SA
{
	namespace DX12
	{
		class Exception_DX12 : public Exception
		{
		public:
			Exception_DX12(BaseInfos&& _infos,
				HRESULT _hrRes,
				std::string&& _predStr,
				std::wstring&& _details = L""
			) noexcept;
		};


		#define __SA_CREATE_EXCEPTION_DX12(_baseInfos, _hrRes, ...) SA::DX12::Exception_DX12(\
			_baseInfos,\
			_hrRes,\
			#_hrRes,\
			##__VA_ARGS__\
		)
	}
}

#endif // SAPPHIRE_RENDER_EXCEPTION_VULKAN_GUARD
