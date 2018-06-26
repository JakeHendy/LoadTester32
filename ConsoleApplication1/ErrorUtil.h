#pragma once
#include <Windows.h>
#include "spdlog/logger.h"
class ErrorUtil
{
public:
	ErrorUtil();
	static void PrintErrorMessage(DWORD message);
	~ErrorUtil();
private:
	static std::shared_ptr<spd::logger> log;

};

