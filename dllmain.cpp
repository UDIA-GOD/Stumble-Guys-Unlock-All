#include "includes.h"

uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
uintptr_t GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");

void(__fastcall* HasSkin_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasSkin_hook(DWORD* __this, float skinID, DWORD* method) {
    return true;
}

void(__fastcall* HasVariant_o)(DWORD*, const char*, const char*, INT32, DWORD*);
bool __stdcall HasVariant_hook(DWORD* __this, float skinID, const char* variantName, INT32 variantID, DWORD* method) {
    return true;
}

void(__fastcall* HasEmote_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasEmote_hook(DWORD* __this, float emoteID, DWORD* method) {
    return true;
}

void(__fastcall* HasAnim_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasAnim_hook(DWORD* __this, float animationID, DWORD* method) {
    return true;
}

void(__fastcall* HasFP_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasFP_hook(DWORD* __this, float footstepID, DWORD* method) {
    return true;
}

void Unlock() {
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + hasSkin), &HasSkin_hook, (LPVOID*)&HasSkin_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + hasVariant), &HasVariant_hook, (LPVOID*)&HasVariant_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + hasEmote), &HasEmote_hook, (LPVOID*)&HasEmote_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + hasAnimation), &HasAnim_hook, (LPVOID*)&HasAnim_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + hasFootstep), &HasFP_hook, (LPVOID*)&HasFP_o);
    MH_EnableHook(MH_ALL_HOOKS);
}

void main() {
    if (MH_Initialize() != MH_OK) {
        MBox("Could Not Hook, Please open GitHub Issue. Error code: MHIErr", MB_OK | MB_ICONERROR);
        ShellExecute(NULL, "open", "https://github.com/UDIA-GOD/Stumble-Guys-Unlock-All/issues/new/?title=Minhook%20Initialize%20error%20(Could%20Not%20Hook),%20Error%20code:%20MHIErr", NULL, NULL, SW_SHOWNORMAL);
        exit(1);
    }
    Updater();
    Unlock();
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}