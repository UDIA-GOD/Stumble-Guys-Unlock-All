#include "Drawing.h"
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include "misc.h"

LPCSTR Drawing::lpWindowName = "StumbleUnlocker";
ImVec2 Drawing::vWindowSize = { 300, 200 };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;

void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw == true;
}

bool IsProcessRunning(const std::wstring& processName) {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE) {
		return false;
	}

	PROCESSENTRY32 processEntry = { sizeof(PROCESSENTRY32) };
	if (Process32First(snapshot, &processEntry)) {
		do {
			std::wstring currentProcessName(processEntry.szExeFile);
			if (currentProcessName == processName) {
				CloseHandle(snapshot);
				return true;
			}
		} while (Process32Next(snapshot, &processEntry));
	}

	CloseHandle(snapshot);
	return false;
}

BOOL InjectDLL(DWORD dwProcessId, const char* dllPath)
{
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
    if (hProcess == NULL)
    {
        return FALSE;
    }

    LPVOID pDllPath = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
    if (pDllPath == NULL)
    {
        CloseHandle(hProcess);
        return FALSE;
    }

    if (!WriteProcessMemory(hProcess, pDllPath, dllPath, strlen(dllPath) + 1, NULL))
    {
        VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return FALSE;
    }

    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    FARPROC pLoadLibraryA = GetProcAddress(hKernel32, "LoadLibraryA");
    if (pLoadLibraryA == NULL)
    {
        VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return FALSE;
    }

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibraryA, pDllPath, 0, NULL);
    if (hThread == NULL)
    {
        VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return FALSE;
    }

    WaitForSingleObject(hThread, INFINITE);

    VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);

    return TRUE;
}

DWORD processId = 0;
const char* dllPath = "C:\\Temp\\StumbleUnlocker.dll";

void Drawing::Draw()
{
	if (isActive())
	{
		ImGui::SetNextWindowSize(vWindowSize);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
		{
			std::wstring processName = L"Stumble Guys.exe";
			if (IsProcessRunning(processName)) {
				ImGui::Text("Game Detected");
				if (ImGui::Button("Inject")) {
					if (GetDll()) {
						HWND hWnd = FindWindowA(NULL, "Stumble Guys");
						if (hWnd == NULL)
						{
							MBox(L"Failed to find Stumble Guys", MB_OK | MB_ICONERROR);
							exit(1);
						}
						GetWindowThreadProcessId(hWnd, &processId);
						if (!InjectDLL(processId, dllPath))
						{
							MBox(L"Failed to Inject", MB_OK | MB_ICONERROR);
							exit(1);
						}
						exit(0);
					} else {
						MBox(L"Could not download DLL", MB_OK | MB_ICONERROR);
						exit(1);
					}
				}
			}
			else {
				ImGui::Text("Please Launch Stumble Guys");
			}
		}
		ImGui::End();
	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
