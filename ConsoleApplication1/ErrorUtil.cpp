#include "stdafx.h"
#include "ErrorUtil.h"
#include <string>
#include "spdlog/spdlog.h"

namespace spd = spdlog;

ErrorUtil::ErrorUtil()
{
	this->log = spd::get("console");
}

void ErrorUtil::PrintErrorMessage(DWORD message)
{
	LPWSTR messageAsTChars = NULL;
	if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, message, 0, (LPWSTR)&messageAsTChars, 128, NULL)) {
		std::wprintf(L"Couldn't get message for last error, code: 0x%x\n", GetLastError());
	}
	ErrorUtil::log->error()
	std::wprintf(L"Error opening file: %s", messageAsTChars);
}


ErrorUtil::~ErrorUtil()
{
}
