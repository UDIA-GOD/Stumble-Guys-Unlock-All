#include "includes.h"

void MBox(LPCSTR message, long params) {
	MessageBox(NULL, message, MergeLPC("StumbleUnlocker for ", version()), params);
}

std::string version() {
    std::string versionbuffer;
    std::ifstream versionmanager("version.txt");
    if (versionmanager.is_open()) {
        versionmanager >> versionbuffer;
        versionmanager.close();
    }
    else {
        MBox("Could not check game version, Please open an issue on GitHub. Error Code: Ver01", MB_OK | MB_ICONERROR);
    }
    return versionbuffer;
}

LPCSTR MergeLPC(LPCSTR lpcstr, const std::string& str) {
    std::string mergedString = std::string(lpcstr) + str;
    return mergedString.c_str();
}

LPCSTR MergeLPCL(LPCSTR lpcstr, const std::string& str, LPCSTR lpcstrl) {
    std::string mergedString = std::string(lpcstr) + str + std::string(lpcstrl);
    return mergedString.c_str();
}

uintptr_t Hexify(uintptr_t decimal) {
    std::stringstream ss;
    ss << std::hex << decimal;
    uintptr_t hexValue;
    ss >> hexValue;
    return hexValue;
}