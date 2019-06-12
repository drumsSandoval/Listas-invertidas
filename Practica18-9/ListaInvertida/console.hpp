//
//  console.hpp
//  Practica18-9
//
//  Created by Oscar Sandoval on 3/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef console_h
#define console_h
#include <stdlib.h>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

#ifdef _WIN64
#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif
class Console
{
public:
#ifdef _WIN32
    Console()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode))
        {
            return;
        }
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(hOut, dwMode))
        {
            return;
        }
    }
#elif __unix
    Console(){}
#endif
    
    enum COLORS
    {
        FG_DARK_GRAY = 30,
        FG_DARK_RED,
        FG_DARK_GREEN,
        FG_DARK_YELLOW,
        FG_DARK_BLUE,
        FG_DARK_PURPLE,
        FG_DARK_CYAN,
        FG_GRAY,
        BG_DARK_GRAY = 40,
        BG_DARK_RED,
        BG_DARK_GREEN,
        BG_DARK_YELLOW,
        BG_DARK_BLUE,
        BG_DARK_PURPLE,
        BG_DARK_CYAN,
        BG_GRAY,
        FG_LIGHT_GRAY = 90,
        FG_LIGHT_RED,
        FG_LIGHT_GREEN,
        FG_LIGHT_YELLOW,
        FG_LIGHT_BLUE,
        FG_LIGHT_PURPLE,
        FG_LIGHT_CYAN,
        FG_WHITE,
        BG_LIGHT_GRAY = 100,
        BG_LIGHT_RED,
        BG_LIGHT_GREEN,
        BG_LIGHT_YELLOW,
        BG_LIGHT_BLUE,
        BG_LIGHT_PURPLE,
        BG_LIGHT_CYAN,
        BG_WHITE
    };
    
#ifdef _WIN32
    inline void clearScreen()
    {
        system("cls");
    }
    inline void setColor(COLORS color)
    {
        std::ostringstream converter;
        converter <<color;
        std::cout <<"\033[38;" + converter.str() + "m";
    }
    inline void restore()
    {
        std::cout <<"\033[m";
    }
    
#elif _WIN64
    inline void clearScreen()
    {
        system("cls");
    }
    inline void setColor(COLORS color)
    {
        std::ostringstream converter;
        converter <<color;
        std::cout <<"\033[38;" + converter.str() + "m";
    }
#elif __unix
    inline void clearScreen()
    {
        system("clear");
    }
    inline void setColor(COLORS color)
    {
        std::ostringstream converter;
        converter <<color;
        std::cout <<"\033[38;" + converter.str() + "m";
    }
    inline void restore()
    {
        std::cout <<"\033[m";
    }
    
    inline void moveTo(int x, int y)
    {
        std::ostringstream converterX;
        std::ostringstream converterY;
        std::string renglon;
        converterX <<x;
        renglon = converterX.str();
        std::string columna;
        converterY <<y;
        columna = converterY.str();
        std::cout <<"\033[" + renglon + ";" + columna + "f";
    }
#elif __APPLE__
    inline void clearScreen()
    {
        system("clear");
    }
    inline void setColor(COLORS color)
    {
        std::ostringstream converter;
        converter <<color;
        std::cout <<"\033[38;" + converter.str() + "m";
    }
    inline void restore()
    {
        std::cout <<"\033[m";
    }
    
    inline void moveTo(int x, int y)
    {
        std::ostringstream converterX;
        std::ostringstream converterY;
        std::string renglon;
        converterX <<x;
        renglon = converterX.str();
        std::string columna;
        converterY <<y;
        columna = converterY.str();
        std::cout <<"\033[" + renglon + ";" + columna + "f";
    }
#endif
};

#endif /* console_h */
