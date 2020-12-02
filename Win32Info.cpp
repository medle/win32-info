/*
https://docs.microsoft.com/en-us/sysinternals/downloads/psexec
*/

#include <windows.h>
#include <stdio.h>
#include <VersionHelpers.h>
#pragma comment(lib, "user32.lib")
#include <intrin.h>

int main()
{
    CHAR compName[100];
    DWORD compNameLen = 100;
    GetComputerNameA(compName, &compNameLen);

    int cpuInfo[4] = { -1 };
    char CPUBrandString[0x40];

    memset(CPUBrandString, 0, sizeof(CPUBrandString));

    __cpuid(cpuInfo, 0x80000002);
    memcpy(CPUBrandString, cpuInfo, sizeof(cpuInfo));

    __cpuid(cpuInfo, 0x80000003);
    memcpy(CPUBrandString + 16, cpuInfo, sizeof(cpuInfo));

    __cpuid(cpuInfo, 0x80000004);
    memcpy(CPUBrandString + 32, cpuInfo, sizeof(cpuInfo));

    ULONGLONG ramKb;
    GetPhysicallyInstalledSystemMemory(&ramKb);

    char os[100];
    if (IsWindows10OrGreater())
    {
        strcpy_s(os, "Win10");
    }
    else if (IsWindows8OrGreater())
    {
        strcpy_s(os, "Win8");
    }
    else if (IsWindows7OrGreater())
    {
       strcpy_s(os, "Win7");
    }
    else if (IsWindowsXPOrGreater())
    {
        strcpy_s(os, "WinXP");
    }

    printf("%s;", compName);
    printf("%s;", CPUBrandString);
    printf("%dGb;", (int)(ramKb / (1024 * 1024)));
    printf("%s\n", os);

    return 0;
}
   