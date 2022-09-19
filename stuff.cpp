#include "main.h"

void __memset(DWORD dst, int val, size_t size, bool unprotect)
{
	if (unprotect)
	{
		DWORD d;
		if (!VirtualProtect((void*)dst, size, PAGE_EXECUTE_READWRITE, &d))
			return;
	}

	memset((void*)dst, val, size);
}

void __memcpy(DWORD dst, void* src, size_t size, bool unprotect)
{
	if (unprotect)
	{
		DWORD d;
		if (!VirtualProtect((void*)dst, size, PAGE_EXECUTE_READWRITE, &d))
			return;
	}

	memcpy((void*)dst, src, size);
}
