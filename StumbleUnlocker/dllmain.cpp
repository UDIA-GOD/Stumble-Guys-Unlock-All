#include <Windows.h>
#include <MinHook.h>
#include <cstdio>

uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
uintptr_t GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");
HMODULE g_hModule = NULL;
int ConsoleState = 0;

//offsets
uintptr_t HasSkin = 0x681d90;
uintptr_t HasEmote = 0x681bf0;
uintptr_t HasAnim = 0x681ac0;
uintptr_t HasVar = 0x681e30;
uintptr_t HasFP = 0x681d00;
//too lazy to add it to the file :P

void OpenConsole() {
    if (!ConsoleState) {
        ConsoleState = 1;
        AllocConsole();
        FILE* f;
        freopen_s(&f, "CONOUT$", "w", stdout);
        printf("StumbleUnlocker for 0.50.3-0 stage :P\n");
    }
}

void init() {
    if (MH_Initialize() != MH_OK) {
        MessageBox(NULL, "Couldn't Hook", "StumbleUnlocker", MB_OK | MB_ICONHAND);
        if (g_hModule != NULL)
        {
            FreeLibrary(g_hModule);
            g_hModule = NULL;
        }
    }
    OpenConsole();
    printf("If you paid for it, You've got scammed!!!\nSource code: https://github.com/UDIA-GOD/Stumble-Guys-Unlock-All");
}

void(__fastcall* HasSkin_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasSkin_hook(DWORD* __this, float skinID, DWORD* method) {
    printf("Skin unlocked!\n");
    return true;
}

void(__fastcall* HasVariant_o)(DWORD*, const char*, const char*, INT32, DWORD*);
bool __stdcall HasVariant_hook(DWORD* __this, float skinID, const char* variantName, INT32 variantID, DWORD* method) {
    printf("Variant unlocked!\n");
    return true;
}

void(__fastcall* HasEmote_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasEmote_hook(DWORD* __this, float emoteID, DWORD* method) {
    printf("Emote unlocked!\n");
    return true;
}

void(__fastcall* HasAnim_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasAnim_hook(DWORD* __this, float animationID, DWORD* method) {
    printf("Animation unlocked!\n");
    return true;
}

void(__fastcall* HasFP_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasFP_hook(DWORD* __this, float footstepID, DWORD* method) {
    printf("Footstep unlocked!\n");
    return true;
}

void main() {
    init();
    MessageBox(NULL, "Welcome to StumbleUnlocker", "StumbleUnlocker", MB_OK | MB_ICONMASK);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasSkin), &HasSkin_hook, (LPVOID*)&HasSkin_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasVar), &HasVariant_hook, (LPVOID*)&HasVariant_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasEmote), &HasEmote_hook, (LPVOID*)&HasEmote_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasAnim), &HasAnim_hook, (LPVOID*)&HasAnim_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasFP), &HasFP_hook, (LPVOID*)&HasFP_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasSkin));
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasVar));
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasEmote));
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasAnim));
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasFP));
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        g_hModule = hModule;
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
