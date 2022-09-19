#include "main.h"

void __memset(DWORD dst, int val, size_t size, bool unprotect = true);
void __memcpy(DWORD dst, void* src, size_t size, bool unprotect = true);
