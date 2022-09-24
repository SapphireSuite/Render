// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include "ARenderInterface.hpp"

namespace SA
{
	void ARenderInterface::Create(AWindowInterface* _win_intf)
	{
		HI::Interface::Create();

		(void)_win_intf;
	}
	
	void ARenderInterface::Destroy()
	{
		HI::Interface::Destroy();
	}

	void ARenderInterface::Clear()
	{
		HI::Interface::Clear();
	}
}
