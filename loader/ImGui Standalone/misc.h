#pragma once
#include <Urlmon.h>
#include <nlohmann/json.hpp>

#pragma comment(lib, "urlmon.lib")
using json = nlohmann::json;

void MBox(LPCWSTR, long);
const char* FetchLatest();
LPCSTR MergeLPC(LPCSTR, const std::string&);
LPCWSTR ConvertToLPCWSTR(LPCSTR);
bool GetDll();