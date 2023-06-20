#pragma once

void MBox(LPCSTR, long);
std::string version();
LPCSTR MergeLPC(LPCSTR, const std::string&);
uintptr_t Hexify(uintptr_t);
LPCSTR MergeLPCL(LPCSTR, const std::string&, LPCSTR);

//shit for updater
void Updater();
extern int hasSkin;
extern int hasVariant;
extern int hasAnimation;
extern int hasFootstep;
extern int hasEmote;