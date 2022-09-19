// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>
using namespace SA;

int main()
{
//{ Init

	Logger logger;
	SA::Debug::logger = &logger;

	ConsoleLogStream cslStream;
	logger.Register(cslStream);

	FileLogStream fileStream;
	logger.Register(fileStream);

//}

	return 0;
}
