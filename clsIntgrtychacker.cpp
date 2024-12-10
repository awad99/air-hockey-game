#include "clsIntgrtychacker.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <unordered_map>

unsigned char* clsIntgrtychacker::_currentAddr = nullptr;
_MEMORY_BASIC_INFORMATION clsIntgrtychacker::_Meminfo;
void* clsIntgrtychacker::_hprocess = nullptr;
_SYSTEM_INFO clsIntgrtychacker::_Sysinfo;

int clsIntgrtychacker::_previousValue = 0;  // Initialize the previous value to 0

void clsIntgrtychacker::Initialize() {
    _currentAddr = nullptr;
    GetSystemInfo(&_Sysinfo);  // Initialize system info
    _previousValue = 0;  // Set the initial value to 0
}

void clsIntgrtychacker::CheckMemoryIntegrity(int currentValue, std::unordered_map<uintptr_t, int>& foundAddresses) {
    DetectValueChange(currentValue, foundAddresses);
    CheckPointsValidity(currentValue);
}

void clsIntgrtychacker::DetectValueChange(int currentValue, std::unordered_map<uintptr_t, int>& foundAddresses) {
    uintptr_t address = reinterpret_cast<uintptr_t>(_currentAddr);

    // Check if the value has been modified by an external process
    if (foundAddresses.find(address) != foundAddresses.end()) {
        ErrorMessage(L"Memory tampering detected!");
    }
    else {
        // Update the stored value in the map
        foundAddresses[address] = currentValue;
    }
}

void clsIntgrtychacker::ErrorMessage(const std::wstring& message) {
    MessageBox(NULL, message.c_str(), L"Anti-Tamper Alert", MB_OK | MB_ICONERROR);
    PostQuitMessage(0);  // Terminate the application
}

void clsIntgrtychacker::CheckPointsValidity(int currentValue) {
    int delta = currentValue - _previousValue;  // Calculate the difference

    // Check if the increment is by 1 or 100
    if (delta != 1 && delta != 100) {
        ErrorMessage(L"Invalid points increment! Only 1 or 100 are valid increments.");
    }

    _previousValue = currentValue;  // Update the previous value after validation
}

void clsIntgrtychacker::TemporarilyAllowWrite(void* address, SIZE_T size, DWORD& oldProtect) {
    // Temporarily allow write access to the memory region
    if (!VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        std::wcerr << L"Failed to change memory protection!" << std::endl;
    }
}

void clsIntgrtychacker::RestoreProtection(void* address, SIZE_T size, DWORD& oldProtect) {
    // Restore the original protection settings after modifying memory
    if (!VirtualProtect(address, size, oldProtect, &oldProtect)) {
        std::wcerr << L"Failed to restore memory protection!" << std::endl;
    }
}
