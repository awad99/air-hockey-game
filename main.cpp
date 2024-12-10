#include <windows.h>
#include <unordered_map>
#include <string>
#include "clsIntgrtychacker.h"

// Global variables for the window controls
HWND hWndAdd1Button, hWndAdd100Button, hWndNumberLabel;
int number = 0;
std::unordered_map<uintptr_t, int> foundAddresses;

// Function declarations
void UpdateNumberLabel(HWND hwndLabel, int number);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// The WinMain function: Entry point of the Windows application
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    const wchar_t CLASS_NAME[] = L"AntiTamperApp";
    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        L"Anti Tamper Example",         // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Initialize anti-tamper system
    clsIntgrtychacker::Initialize();

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Update the label text
void UpdateNumberLabel(HWND hwndLabel, int number) {
    std::wstring text = L"Current Number: " + std::to_wstring(number);
    SetWindowText(hwndLabel, text.c_str());
}

// Window procedure for handling messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        hWndAdd1Button = CreateWindow(L"BUTTON", L"Add 1",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 50, 100, 50, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
        hWndAdd100Button = CreateWindow(L"BUTTON", L"Add 100",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            200, 50, 100, 50, hwnd, (HMENU)2, GetModuleHandle(NULL), NULL);
        hWndNumberLabel = CreateWindow(L"STATIC", L"Current Number: 0",
            WS_VISIBLE | WS_CHILD,
            50, 120, 250, 30, hwnd, NULL, GetModuleHandle(NULL), NULL);
        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == 1) { // Add 1 button
            number += 1;
            UpdateNumberLabel(hWndNumberLabel, number);
            clsIntgrtychacker::CheckMemoryIntegrity(number, foundAddresses);
        }
        else if (LOWORD(wParam) == 2) { // Add 100 button
            number += 100;
            UpdateNumberLabel(hWndNumberLabel, number);
            clsIntgrtychacker::CheckMemoryIntegrity(number, foundAddresses);
        }
        break;
    }
    case WM_CLOSE: {
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
