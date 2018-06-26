#pragma once
#include <queue>
#include <string>
class UrlQueueSource
{
public:
	UrlQueueSource();
	std::deque<std::wstring> createUrlDeque();
	~UrlQueueSource();
};

