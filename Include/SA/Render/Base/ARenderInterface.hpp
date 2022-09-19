// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SA_RENDER_ARENDER_INTERFACE_GUARD
#define SA_RENDER_ARENDER_INTERFACE_GUARD

namespace SA
{
	class ARenderInterface
	{
	public:
		virtual void Create() = 0;
		virtual void Destroy() = 0;
	};
}

#endif // SA_RENDER_ARENDER_INTERFACE_GUARD
