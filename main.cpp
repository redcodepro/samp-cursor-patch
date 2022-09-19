#include "main.h"

___vars___ G;
CSAMP* SAMP = new CSAMP();

void(__cdecl* orig_CGame_Proccess)() = nullptr;
void __cdecl hooked_CGame_Proccess()
{
	static int state = 2;
	if (state == 0)
	{
		HandleDialogMoving();
	}
	else if (state == 1)
	{
		// unknown samp
	}
	else if (state == 2 && SAMP->init())
	{
		if (SAMP->getVersion() != SAMP_UNKNOWN)
		{
			InstallCursorPatch(SAMP->getAddress(), SAMP->getVersion());
			state = 0;
		}
		else
		{
			MessageBox(NULL, "Unknown SA-MP version.", "samp-cursor-patch.asi", MB_OK | MB_ICONERROR);
			state = 1;
		}
	}
	return orig_CGame_Proccess();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hModule);

			MH_Initialize();
			MH_InstallHookEx(0x53BEE0, &hooked_CGame_Proccess, &orig_CGame_Proccess);
		}
		break;
	case DLL_PROCESS_DETACH:
		{
			RemoveCursorPatch();

			MH_UninstallHook(0x53BEE0);
			MH_Uninitialize();
		}
		break;
	}
	return true;
}
