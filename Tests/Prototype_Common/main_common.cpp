// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include "main_common.hpp"

#include <SA/Collections/Debug>
using namespace SA;

static ConsoleLogStream cslStream;
static FileLogStream fileStream;
static Logger logger;

void InitLogger()
{
	SA::Debug::logger = &logger;
	logger.Register(cslStream);
	logger.Register(fileStream);
}

void Init(ARenderInterface* _interface)
{
	_interface->Create();
}

void UnInit(ARenderInterface* _interface)
{
	_interface->Destroy();
}

int main_common(ARenderInterface* _interface, bool bInitLogger)
{
	if(bInitLogger)
		InitLogger();

	Init(_interface);
	UnInit(_interface);

	return 0;
}
