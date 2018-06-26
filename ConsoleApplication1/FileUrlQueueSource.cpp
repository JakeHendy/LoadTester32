#include "stdafx.h"
#include "FileUrlQueueSource.h"
#include <string>
#include <sstream>>
#include <deque>
#include <Windows.h>
#include "ErrorUtil.h"

#define BUFFERSIZE 128

FileUrlQueueSource::FileUrlQueueSource(std::wstring url)
{
	this->url = url;
}

std::deque<std::wstring> FileUrlQueueSource::createUrlDeque()
{
	std::deque<std::wstring> result;

	HANDLE fileHandle;

	fileHandle = CreateFile(this->url.c_str(), GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_READONLY, NULL);
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		DWORD e = GetLastError();
		ErrorUtil::PrintErrorMessage(e);
		return std::deque<std::wstring>();
	}

	LARGE_INTEGER fileSize;
	if (!GetFileSizeEx(fileHandle, &fileSize)) {
		DWORD e = GetLastError();
		ErrorUtil::PrintErrorMessage(e);
		return std::deque<std::wstring>();
	}
	std::wprintf(L"Reading in file of size: %llu\n", fileSize.QuadPart);

	std::wstring fileContents;
	
	char buffer[BUFFERSIZE] = { 0 };
	DWORD bytesRead = 0;
	BOOL readResult = ReadFile(fileHandle, &buffer, BUFFERSIZE, &bytesRead, NULL);
	std::string bufferAsString = std::string(buffer);
	std::istringstream tokenStream(bufferAsString);
	std::string token;
	while (std::getline(tokenStream, token, '\n'))
	{
		std::wstring convertedLine(token.length(), L' ');
		std::copy(token.begin(), token.end(), convertedLine.begin());
		result.push_front(convertedLine);
	}
	delete[] buffer;
	return result;
}

FileUrlQueueSource::~FileUrlQueueSource()
{
}
