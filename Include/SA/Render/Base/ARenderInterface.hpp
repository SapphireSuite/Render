// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SA_RENDER_ARENDER_INTERFACE_GUARD
#define SA_RENDER_ARENDER_INTERFACE_GUARD

#include <SA/HI/Interface.hpp>

namespace SA
{
	class ARenderInterface : private HI::Interface
	{
	protected:
		using HI::Interface::CheckCreated;

	public:
		void Create() override;
		void Destroy() override;

		void Clear() override;
	};
}

#endif // SA_RENDER_ARENDER_INTERFACE_GUARD
