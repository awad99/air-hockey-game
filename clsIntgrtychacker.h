#ifndef CLSINTEGRITYHACKER_H
#define CLSINTEGRITYHACKER_H

#include <Windows.h>
#include <string>
#include <unordered_map>

class clsIntgrtychacker {
public:
    static void Initialize();
    static void CheckMemoryIntegrity(int currentValue, std::unordered_map<uintptr_t, int>& foundAddresses);
    static void DetectValueChange(int currentValue, std::unordered_map<uintptr_t, int>& foundAddresses);
    static void ErrorMessage(const std::wstring& message);
    static void TemporarilyAllowWrite(void* address, SIZE_T size, DWORD& oldProtect);
    static void RestoreProtection(void* address, SIZE_T size, DWORD& oldProtect);

private:
    static unsigned char* _currentAddr;
    static _MEMORY_BASIC_INFORMATION _Meminfo;
    static void* _hprocess;
    static _SYSTEM_INFO _Sysinfo;

    static int _previousValue;  // Variable to track the previous value
    static void CheckPointsValidity(int currentValue);
};

#endif // CLSINTEGRITYHACKER_H
