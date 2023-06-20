#include <Windows.h>
#include <MinHook.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <Urlmon.h>
#include "misc.h"
#include <sstream>
#include <cstdint>
#include <nlohmann/json.hpp>

#pragma comment(lib, "urlmon.lib")
using json = nlohmann::json;