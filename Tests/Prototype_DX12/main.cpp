// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>
using namespace SA;

#include <main_common.hpp>
#include <SA/Render/DX12/D12RenderInterface.hpp>

int main()
{
	DX12::RenderInterface interface;

	return main_common(&interface);
}
