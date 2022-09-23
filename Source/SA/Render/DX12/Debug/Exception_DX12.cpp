// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Debug/Exception_DX12.hpp>

namespace SA
{
	namespace DX12
	{
		Exception_DX12::Exception_DX12(
			BaseInfos&& _infos,
			HRESULT _hrRes,
			std::string&& _predStr,
			std::wstring&& _details
		) noexcept :
			Exception(std::move(_infos),
				SUCCEEDED(_hrRes),
				ToWString(std::move(_predStr)) + L" => SUCCEEDED",
				std::move(_details))
		{
		}
	}
}
