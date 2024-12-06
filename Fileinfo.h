#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Globa.h"
std::string _GetLastError1();
class Fileinfo
{
private:
   static HANDLE _OpenTheFile() {
        // Open the file
        HANDLE file = CreateFile(L"Info_Game.txt", GENERIC_WRITE, 0, NULL,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (file == INVALID_HANDLE_VALUE) {
            // Handle error
            std::cout << "Error! " << _GetLastError1() << std::endl;
            return INVALID_HANDLE_VALUE;  // Return invalid handle if file creation fails
        }
        SetFilePointer(file, 0, NULL, FILE_END);
        // If the file opened successfully, return the handle
        return file;
    }
   static void _writeTheFile(HANDLE file, std::string& data) {
        DWORD bytesWritten = 0;

        if (!WriteFile(file, data.c_str(), data.size(), &bytesWritten, NULL)) {
            std::cout << "Error! " << _GetLastError1() << std::endl;
        }
        else
            std::cout << "Successfully wrote to the file " << std::endl;
    }
   static std::string _GetLastError1() {
        DWORD err = GetLastError();

        if (!err)
            return "No error";

        char* message = nullptr;

        // Allocate buffer for error message
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            0, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, nullptr);

        std::string result(message, size);

        // Free the allocated memory for message
        LocalFree(message);

        return result;
    }
public:
   static void PrintInfo(int Timer, int ScorePlayer1,int levelGame) {
        HANDLE file = _OpenTheFile();

        if (file == INVALID_HANDLE_VALUE) {
            std::cout << "Error! " << GetLastError();
        }

        std::ostringstream oss;
        oss << "Timer: " << Timer << " | Score " << ScorePlay1 << "| level Game " << levelGame <<"\n";
        std::string data = oss.str();
        _writeTheFile(file, data);

        CloseHandle(file);
    }

};

