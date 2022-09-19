#include "main.h"

bool lock_mouse = false;
bool move_available = false;
bool move_active = false;
bool dialog_moving = false;

BYTE  CurMode_Offs = 0;
BYTE  WaitFrames_Offs = 0;
DWORD CurMode_Addr = 0;
DWORD EnterVeh_Addr = 0; // CLocalPlayer::EnterVehicleAsPassenger()

HRESULT(__cdecl* orig_getMouseState)(DIMOUSESTATE2* dm) = nullptr;
HRESULT __cdecl hooked_getMouseState(DIMOUSESTATE2 *dm)
{
	static int lock_state = 0;
	static POINT move_pos = { 0, 0 };
	static DIMOUSESTATE2 mouse_state;

	HRESULT hr = orig_getMouseState(dm);

	if (lock_mouse)
		lock_state = 10;
	else
		if (lock_state > 0)
			lock_state--;

	if (lock_state)
	{
		if (move_active && dm->rgbButtons[1])
		{
			SetCursorPos(move_pos.x, move_pos.y);
			ZeroMemory(dm->rgbButtons, sizeof(dm->rgbButtons));
		}
		else
		{
			if (move_available && (move_active = dm->rgbButtons[1]))
				GetCursorPos(&move_pos);
			ZeroMemory(dm, sizeof(DIMOUSESTATE2));
		}

		memcpy(&mouse_state, dm, sizeof(DIMOUSESTATE2));
	}
	else
	{
		for (size_t i = 0; i < 5; ++i)
			if (mouse_state.rgbButtons[i])
				if (dm->rgbButtons[i])
					dm->rgbButtons[i] = 0;
				else
					mouse_state.rgbButtons[i] = 0;
		move_active = false;
	}

	return hr;
}

void __fastcall hooked_SetCursorMode(void* ecx, void* edx, int nMode, BOOL bHide)
{
	if (nMode > 4)
		return;

	if (nMode == CURSOR_NONE)
	{
		lock_mouse = false;
		move_available = false;
		dialog_moving = false;
		G.d3ddev->ShowCursor(FALSE);

		__memset(EnterVeh_Addr, 0x53, 1);
		CPad::GetPad(0)->bDisablePlayerEnterCar = 0;
		__memcpy(0x541DF5, "\xE8\x46\xF3\xFE\xFF", 5);

		*(int*)((UINT)ecx + WaitFrames_Offs) = bHide ? 0 : 10; // m_nInputEnableWaitFrames
	}
	else if (nMode == CURSOR_LOCKKEYS_NOCURSOR)
	{
		__memcpy(0x541DF5, "\x90\x90\x90\x90\x90", 5);
	}
	else
	{
		if (nMode == CURSOR_LOCKCAMANDCONTROL)
		{
			// disable enter car
			__memset(EnterVeh_Addr, 0xC3, 1);
			CPad::GetPad(0)->bDisablePlayerEnterCar = 1;

			__memcpy(0x541DF5,
				(bHide < 2) || SAMP->isAnyInputEnabled() ?
				"\x90\x90\x90\x90\x90" :
				"\xE8\x46\xF3\xFE\xFF", 5);
			dialog_moving = (bHide > 2);
		}

		lock_mouse = true;
		*(BYTE*)0x6194A0 = 0xC3;
		//CPad::GetPad(0)->UpdatePads();

		if (nMode != CURSOR_LOCKCAM_NOCURSOR)
		{
			move_available = (bHide > 1);
			G.d3ddev->ShowCursor(!move_active);
		}
		else
		{
			move_available = false;
		}
	}
	*(int*)((UINT)ecx + CurMode_Offs) = nMode; // m_nCursorMode
}

void InstallCursorPatch(uint32_t samp_address, uint32_t samp_version)
{
#define offs(n) (samp_address + n[samp_version])

	static DWORD dwSAMPEnterVehicleAddr[] = { 0, 0x6D90, 0x6D60, 0x6DA0, 0x6FD0, 0x6FE0 };

	static DWORD CurMode_SetCursorMode[] = { 0, 0x9BD30, 0x9BDD0, 0x9FFE0, 0xA0720, 0xA0750 };

	static DWORD CurModeExt_Input[] = { 0, 0x65A60, 0x65B30, 0x68F90, 0x696C0, 0x69700 };
	static DWORD CurModeExt_Dialog[] = { 0, 0x6B27C, 0x6B32C, 0x6F17C, 0x6F89C, 0x6F8CC };
	static DWORD CurModeExt_Textdraw[] = { 0, 0x6CE3E, 0x6CEDE, 0x70D2E, 0x7144E, 0x7147E };
	static DWORD CurModeExt_Scoreboard[] = { 0, 0x6AD6C, 0x6AE1C, 0x6ECBC, 0x6F3DC, 0x6F40C };

	static BYTE CurModeOffs_CursorMode[] = { 0, 0x55, 0x61, 0x61, 0x61, 0x61 };
	static BYTE CurModeOffs_WaitFrames[] = { 0, 0x59, 0x65, 0x65, 0x65, 0x65 };

	CurMode_Offs = CurModeOffs_CursorMode[samp_version];
	WaitFrames_Offs = CurModeOffs_WaitFrames[samp_version];
	CurMode_Addr = offs(CurMode_SetCursorMode);
	EnterVeh_Addr = offs(dwSAMPEnterVehicleAddr);

	__memset(offs(CurModeExt_Input) + 1, 0x02, 1);
	__memset(offs(CurModeExt_Dialog) + 1, 0x03, 1);
	__memset(offs(CurModeExt_Textdraw) + 1, 0x02, 1);
	__memset(offs(CurModeExt_Scoreboard) + 1, 0x02, 1);

	MH_InstallHookEx(0x746ED0, hooked_getMouseState, &orig_getMouseState);
	MH_InstallHookEx(CurMode_Addr, hooked_SetCursorMode, nullptr);
}

void RemoveCursorPatch()
{
	MH_UninstallHook(0x746ED0);
	MH_UninstallHook(CurMode_Addr);
}

///////////////////////////////////////////////////////////////////////////////
// DialogMoving

POINT* get_mouse_position()
{
	static POINT point;
	GetCursorPos(&point);
	ScreenToClient(GetActiveWindow(), &point);
	return &point;
}

bool is_hovered(LPPOINT lpPoint, int x, int y, int w, int h)
{
	return (lpPoint->x > x && lpPoint->x < x + w && lpPoint->y > y && lpPoint->y < y + h);
}

void HandleDialogMoving()
{
	static bool move = false;
	static int offset[2] = { 0, 0 };
	static bool key_downed = false;

	if (!SAMP->getDialog()->m_bIsActive)
	{
		move = false;
		return;
	}

	bool now_downed = (GetKeyState(VK_LBUTTON) & 0x8000);
	bool key_pressed = now_downed && !key_downed;

	key_downed = now_downed;

	POINT* cursor_pos = get_mouse_position();
	POINT* dialog_pos = (POINT*)&SAMP->getDialog()->m_pDialog->m_pos;

	if (!move)
	{
		if (key_pressed && is_hovered(cursor_pos, dialog_pos->x, dialog_pos->y, SAMP->getDialog()->m_pDialog->m_size[0], SAMP->getDialog()->m_pDialog->m_nCaptionHeight))
		{
			offset[0] = cursor_pos->x - dialog_pos->x;
			offset[1] = cursor_pos->y - dialog_pos->y;
			move = true;
		}
		return;
	}

	if (!key_downed)
	{
		move = false;
		return;
	}

	SAMP->getDialog()->m_position.x = dialog_pos->x = cursor_pos->x - offset[0];
	SAMP->getDialog()->m_position.y = dialog_pos->y = cursor_pos->y - offset[1];
}
