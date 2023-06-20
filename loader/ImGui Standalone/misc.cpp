#include "misc.h"
#include <Windows.h>
#include <iostream>

void MBox(LPCWSTR message, long params) {
	MessageBox(NULL, message, L"StumbleUnlocker Loader", params);
}

const char* FetchLatest() {
    const char* LatestVer;
    IStream* pStream = nullptr;
    HRESULT result = URLOpenBlockingStream(NULL, L"https://raw.githubusercontent.com/UDIA-GOD/Stumble-Guys-Unlock-All/main/LatestVersion", &pStream, 0, NULL);
    if (result == S_OK) {
        STATSTG stat;
        pStream->Stat(&stat, STATFLAG_DEFAULT);
        ULONG size = stat.cbSize.LowPart;
        char* buffer = new char[size];
        ULONG bytesRead = 0;
        pStream->Read(buffer, size, &bytesRead);
        buffer[bytesRead] = '\0';
        LatestVer = buffer;
        delete[] buffer;
        pStream->Release();
        return LatestVer;
    }
    else {
        MBox(L"Couldn't get latest version, It may be caused by a bad internet connection/no internet connection.", MB_OK | MB_ICONERROR);
        exit(1);
    }
}

LPCSTR MergeLPC(LPCSTR lpcstr, const std::string& str) {
    std::string mergedString = std::string(lpcstr) + str;
    return mergedString.c_str();
}

LPCWSTR ConvertToLPCWSTR(LPCSTR str)
{
    int size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    if (size == 0)
    {
        MBox(L"Error with getting url", MB_OK | MB_ICONERROR);
        return NULL;
    }

    LPWSTR wideStr = new WCHAR[size];
    if (MultiByteToWideChar(CP_UTF8, 0, str, -1, wideStr, size) == 0)
    {
        MBox(L"Error with getting url", MB_OK | MB_ICONERROR);
        delete[] wideStr;
        return NULL;
    }

    return wideStr;
}

bool GetDll() {
    const wchar_t* filePath = L"C:\\Temp\\StumbleUnlocker.dll";
    if (GetFileAttributes(filePath) != INVALID_FILE_ATTRIBUTES)
    {
        DeleteFile(filePath);
    }
    HRESULT hr = URLDownloadToFile(NULL, ConvertToLPCWSTR(MergeLPC("https://github.com/UDIA-GOD/Stumble-Guys-Unlock-All/releases/download/", FetchLatest())), filePath, 0, NULL);
    if (hr == S_OK) {
        return true;
    }
    else {
        return false;
    }
}