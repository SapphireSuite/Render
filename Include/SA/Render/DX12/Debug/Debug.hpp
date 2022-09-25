// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_DEBUG_GUARD
#define SAPPHIRE_RENDER_DX12_DEBUG_GUARD

#include <SA/Collections/Debug>

#include "Exception_DX12.hpp"

#define SA_DX12_ASSERT(_pred, ...) SA_ASSERT_EXEC(DX12, SA/Render/DX12, (_pred), ##__VA_ARGS__)

#define SA_DX12_CREATE_LOG(_name, _handle)\
	SA_LOG(SA_WSTR(_name) L" created", Infos, SA/Render/DX12, L"Handle [" << _handle << L"]")

#define SA_DX12_CREATE_DETS_LOG(_name, _handle, _dets)\
	SA_LOG(SA_WSTR(_name) L" created", Infos, SA/Render/DX12, L"Handle [" << _handle << L"]\t" << _dets)

#define SA_DX12_POST_DESTROY_LOG(_name, _handle)\
	SA_LOG_RAII(_name##_logRAII, SA_WSTR(_name) L" destroyed", Infos, SA/Render/DX12, L"Handle [" << _handle << L"]")

#endif // SAPPHIRE_RENDER_DX12_DEBUG_GUARD
