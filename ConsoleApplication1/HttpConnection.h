#pragma once
#include <windows.h>
#include <string>

class HttpConnection
{
public:
	HttpConnection();
	ULONGLONG makeRequest(std::wstring url);
	~HttpConnection();
};

