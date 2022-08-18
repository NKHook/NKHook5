#include "Logger.h"

#include <stdio.h>
#include <iostream>
#include <Windows.h>

using namespace Common::Logging;

size_t* Logger::GetCursor()
{
	size_t loc[2];
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(hOutput, &cbsi);
    loc[0] = cbsi.dwCursorPosition.X;
    loc[1] = cbsi.dwCursorPosition.Y;
	return loc;
}

void Logger::SetCursor(size_t x, size_t y)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hOutput, coord);
}

size_t Logger::Print(const char* fmt, ...)
{
	va_list lst;
	va_start(lst, fmt);
	size_t len = Logger::VPrint(LogLevel::INFO, fmt, lst);
	va_end(lst);
    return len;
}

size_t Logger::Print(LogLevel level, const char* fmt, ...)
{
	va_list lst;
	va_start(lst, fmt);
	size_t len = Logger::VPrint(level, fmt, lst);
	va_end(lst);
    return len;
}

size_t Logger::VPrint(LogLevel level, const char* fmt, va_list lst)
{
    size_t required = vsnprintf(nullptr, 0, fmt, lst) + 1;
    if (required < 2) {
        return 0;
    }
    char* buffer = new char[required];
    vsprintf_s(buffer, required, fmt, lst);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (level) {
    case LogLevel::SUCCESS: {
        SetConsoleTextAttribute(hConsole, 10);
        break;
    }
    case LogLevel::DEBUG:
#ifndef _DEBUG
    {
        break;
    }
#endif
    case LogLevel::WARNING: {
        SetConsoleTextAttribute(hConsole, 14);
        break;
    }
    case LogLevel::ERR: {
        SetConsoleTextAttribute(hConsole, 12);
        break;
    }
    case LogLevel::INFO:
    default: {
        SetConsoleTextAttribute(hConsole, 7);
        break;
    }
    }
    std::cout << buffer << std::endl << std::flush;
    return required;
}

void Logger::Progress(size_t index, size_t max, const char* fmt, ...)
{
    size_t* pos = Logger::GetCursor();
    Logger::SetCursor(pos[0], pos[1] - 1);
    va_list lst;
    va_start(lst, fmt);
    size_t len = Logger::Print(LogLevel::INFO, fmt, lst);
    va_end(lst);
    pos = Logger::GetCursor();
    Logger::SetCursor(pos[0]+len-1, pos[1]-1);
    Logger::Print("( %d / %d )", index, max);
}
