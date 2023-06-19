#include "includes.h"

int hasSkin;
int hasVariant;
int hasAnimation;
int hasFootstep;
int hasEmote;

void Updater() {
    IStream* pStream = nullptr;
    HRESULT result = URLOpenBlockingStream(NULL, MergeLPCL("https://raw.githubusercontent.com/UDIA-GOD/StumbleGuys-Dump/main/public/", version(), "/UnlockAll.json"), &pStream, 0, NULL);
    if (result == S_OK) {
        STATSTG stat;
        pStream->Stat(&stat, STATFLAG_DEFAULT);
        ULONG size = stat.cbSize.LowPart;
        char* buffer = new char[size];
        ULONG bytesRead = 0;
        pStream->Read(buffer, size, &bytesRead);
        buffer[bytesRead] = '\0';
        try {
            json jsonData = json::parse(buffer);
            hasSkin = jsonData["HasSkin"];
            hasVariant = jsonData["HasVariant"];
            hasAnimation = jsonData["HasAnimation"];
            hasFootstep = jsonData["HasFootstep"];
            hasEmote = jsonData["HasEmote"];
            MBox("Initialized, Everything got unlocked. Have fun :D", MB_OK);
            delete[] buffer;
            pStream->Release();
        }
        catch (const json::exception& e) {
            MBox("Failed to parse JSON, Please open GitHub Issue. Error code: JSDR", MB_OK | MB_ICONERROR);
            ShellExecute(NULL, "open", "https://github.com/UDIA-GOD/Stumble-Guys-Unlock-All/issues/new/?title=Failed%20to%20parse%20JSON,%20Error%20code:%20JSDR", NULL, NULL, SW_SHOWNORMAL);
            exit(1);
        }
    }
    else {
        MBox("Couldn't get offsets for that version.\nIf its the latest version please wait for me to post them, usually in the 24H after the update.", MB_OK | MB_ICONERROR);
        exit(1);
    }

}
