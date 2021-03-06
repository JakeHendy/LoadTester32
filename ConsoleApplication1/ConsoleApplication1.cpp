// ConsoleApplication1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <windows.h>
#include <queue>
#include <string>
#include "HttpConnection.h"
#include "FileUrlQueueSource.h"
#include "spdlog/spdlog.h"

namespace spd = spdlog;

int wmain(int argc, wchar_t* argv[])
{
	auto console = spd::stdout_color_mt("console");

	FileUrlQueueSource queueSource(L"E:\\urls.txt");


	std::deque<std::wstring> urls = queueSource.createUrlDeque();

	urls.push_front(L"www.metoffice.gov.uk");
	urls.push_front(L"www.gov.uk");
	urls.push_front(L"www.google.com");
	urls.push_front(L"www.microsoft.com");

	printf("There are %d URLs in the queue\n", urls.size());

	switch (argc) {
	case 0:
		printf("There are no arguments");
		break;
	case 1:
		printf("There is %d argument\n", argc);
		break;
	default:
		printf("There are %d arguments\n", argc);
	};
	
	for (int i = 0; i < argc; i++) {
		printf("%S\n", argv[i]);
	}

	HttpConnection httpConnection;
	for (auto it = urls.begin(); it != urls.end(); it++)
	{
		std::wstring url = *it;
		ULONGLONG connectiondiff = httpConnection.makeRequest(url);
		wprintf(L"%lldms to connect to %s\n", connectiondiff/10000, url.c_str());
	}
	
}

