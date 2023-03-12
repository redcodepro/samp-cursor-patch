#ifndef __MAIN_H__
#define __MAIN_H__

#define DIRECTINPUT_VERSION 0x0800

#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <d3d9.h>
#include <dinput.h>

#include "minhook/minhook.h"

#include "game_sa/CPad.h"

#include "samp.h"
#include "stuff.h"

#include "ci_cursorpatch.h"

extern CSAMP *SAMP;

extern struct ___vars___
{
	HMODULE					hModule	= NULL;
	IDirect3DDevice9*		&d3ddev	= *reinterpret_cast<IDirect3DDevice9**>(0xC97C28);
	D3DPRESENT_PARAMETERS	&d3dpp	= *reinterpret_cast<D3DPRESENT_PARAMETERS*>(0xC9C040);
} G;

#endif
