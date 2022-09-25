// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_DEVICE_GUARD
#define SAPPHIRE_RENDER_ARENDER_DEVICE_GUARD

#include <vector> // QueryDevices

#include <SA/HI/Object.hpp>

namespace SA
{
	class ARenderDevice : private HI::Object
	{
		using HI::Object::Create;

	protected:
		void Create() override;
		void Destroy() override;
	};
}

#endif // SAPPHIRE_RENDER_ARENDER_DEVICE_GUARD
