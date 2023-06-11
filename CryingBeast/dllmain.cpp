//It's my first ever cheat, so dont judge. Yall can drop some suggestions tho <3

#include <Windows.h>
#include "pch.h"
#include <MinHook.h>
#include <cstdio>
#include "offsets.h"

uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
uintptr_t GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");

void CreateConsole() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
}

void init() {
    MH_Initialize();
    CreateConsole();
    printf("Free Stumble Guys Unlocker\nIf you paid for it, You've got scammed.\nOriginal link + source code: https://github.com/UDIA-GOD/Stumble-Guys-Unlock-All");
}

void(__fastcall* HasSkin_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasSkin_hook(DWORD* __this, float skinID, DWORD* method) {
    printf("Skin unlocked!\n");
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
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasSkin), &HasSkin_hook, (LPVOID*)&HasSkin_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasEmote), &HasEmote_hook, (LPVOID*)&HasEmote_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasAnim), &HasAnim_hook, (LPVOID*)&HasAnim_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasFP), &HasFP_hook, (LPVOID*)&HasFP_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasSkin));
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasEmote));
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasAnim));
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasFP));
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

