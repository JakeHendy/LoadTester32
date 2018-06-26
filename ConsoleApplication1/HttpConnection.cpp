#include "stdafx.h"
#include "HttpConnection.h"
#include <winhttp.h>

HttpConnection::HttpConnection()
{
}

ULONGLONG HttpConnection::makeRequest(std::wstring url)
{
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	BOOL  bResults = FALSE;
	LPCWSTR connectAddress = url.c_str();
	//LPCWSTR connectAddress = L"www.metoffice.gov.uk";
	SYSTEMTIME reqStart,
		reqEnd;
	HINTERNET  hSession = NULL,
		hConnect = NULL,
		hRequest = NULL;

	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(L"WinHTTP Example/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);

	// Specify an HTTP server.
	if (hSession)
		hConnect = WinHttpConnect(hSession, connectAddress,
			INTERNET_DEFAULT_HTTPS_PORT, 0);

	// Create an HTTP request handle.
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL,
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_SECURE);

	// Send a request.
	if (hRequest)
		bResults = WinHttpSendRequest(hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS,
			0, WINHTTP_NO_REQUEST_DATA, 0,
			0, 0);
	GetSystemTime(&reqStart);

	// End the request.
	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);

	// Keep checking for data until there is nothing left.
	if (bResults)
		do
		{
			// Check for available data.
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
				printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());

			// Allocate space for the buffer.
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer)
			{
				printf("Out of memory\n");
				dwSize = 0;
			}
			else
			{
				printf("Size of response: %d\n", dwSize);
				// Read the Data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
					dwSize, &dwDownloaded))
					printf("Error %u in WinHttpReadData.\n", GetLastError());
				else
					printf("Download successful! Downloaded %d bytes\n", strlen(pszOutBuffer));

				// Free the memory allocated to the buffer.
				delete[] pszOutBuffer;
			}

		} while (dwSize > 0);
		GetSystemTime(&reqEnd);

		// Report any errors.
		if (!bResults)
			printf("Error %d has occurred.\n", GetLastError());

		// Close any open handles.
		if (hRequest) WinHttpCloseHandle(hRequest);
		if (hConnect) WinHttpCloseHandle(hConnect);
		if (hSession) WinHttpCloseHandle(hSession);
		FILETIME ftReqStart, ftReqEnd;
		SystemTimeToFileTime(&reqStart, &ftReqStart);
		SystemTimeToFileTime(&reqEnd, &ftReqEnd);
		ULARGE_INTEGER uiReqStart, uiReqEnd;
		uiReqStart.HighPart = ftReqStart.dwHighDateTime;
		uiReqStart.LowPart = ftReqStart.dwLowDateTime;
		uiReqEnd.HighPart = ftReqEnd.dwHighDateTime;
		uiReqEnd.LowPart = ftReqEnd.dwLowDateTime;
		ULONGLONG diff = uiReqEnd.QuadPart - uiReqStart.QuadPart;
		printf("Taken: %llu\n", diff);

		printf("In milliseconds: %llu", diff / 10000);

		return diff;
}


HttpConnection::~HttpConnection()
{
}
