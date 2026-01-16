#pragma once
#include <string>
#include <iostream>
#include <Windows.h>


enum ConsoleColor
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    LightGrey = 60,
    Default = 9
};

class Console
{
public:
    static void enableANSI()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }

    static void SetQuestion()  { SetForegroundColor(LightGrey); }

    static void SetAnswer() { SetForegroundColor(White); }

    static void SetDataNumber_Header() { SetForegroundColor(White); }

    static void SetData() { SetForegroundColor(Green); }

    static void SetError() { SetForegroundColor(Red);  }

    static void PrintNumber(int num)
    {
        SetDataNumber_Header();
        std::cout << "\n" << num << ": ";
    }

    static void PrintData(std::string data)
    {
        SetData();
        std::cout << data << "\n";
    }

    static void PrintError(std::string data)
    {
        SetError();
        std::cout << data << "\n";
    }

    static int iUserInput(std::string data)
    {
        SetQuestion();
        int val;
        std::cout << "\n" << data << "? ";
        SetAnswer();
        std::cin >> val;
        std::cout << "\n";
        return val;
    }

    static std::string sUserInput(std::string data)
    {
        SetQuestion();
        std::string val;
        std::cout << "\n" << data << "? ";
        SetAnswer();
        std::cin >> val;
        std::cout << "\n";
        return val;
    }

    static void PrintHeader(std::string data)
    {
        SetDataNumber_Header();
        std::cout << "=====" << data << "=====" << "\n";
    }

    static void SetForegroundColor(ConsoleColor foreColor);
    static void SetForegroundColor(int r, int g, int b);
    static void SetBackgroundColor(ConsoleColor backColor);
    static void SetBackgroundColor(int r, int g, int b);

private:
    static const std::string ESC;

    static int windowWidth, windowHeight;
};

