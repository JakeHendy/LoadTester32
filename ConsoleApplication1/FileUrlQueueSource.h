#pragma once
#include "UrlQueueSource.h"
class FileUrlQueueSource :
	public UrlQueueSource
{
public:
	FileUrlQueueSource(std::wstring url);
	virtual std::deque<std::wstring> createUrlDeque();
	~FileUrlQueueSource();
private:
	std::wstring url;
};

