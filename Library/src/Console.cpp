#include "Console.h"

#include <iostream>
#include <Windows.h>

namespace ZGF
{
	void ConsoleInterface::SetConsoleTextColor(bool stdout_stream, Color color)
	{
		static UInt32 WinColorFG[15] =
		{
			0,                                                  // BLACK
			FOREGROUND_RED,                                     // RED
			FOREGROUND_GREEN,                                   // GREEN
			FOREGROUND_RED | FOREGROUND_GREEN,                  // BROWN
			FOREGROUND_BLUE,                                    // BLUE
			FOREGROUND_RED |                    FOREGROUND_BLUE,// MAGENTA
			FOREGROUND_GREEN | FOREGROUND_BLUE,                 // CYAN
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,// WHITE
			// YELLOW
			FOREGROUND_RED | FOREGROUND_GREEN |                   FOREGROUND_INTENSITY,
			// RED_BOLD
			FOREGROUND_RED |                                      FOREGROUND_INTENSITY,
			// GREEN_BOLD
			FOREGROUND_GREEN |                   FOREGROUND_INTENSITY,
			FOREGROUND_BLUE | FOREGROUND_INTENSITY,             // BLUE_BOLD
			// MAGENTA_BOLD
			FOREGROUND_RED |                    FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			// CYAN_BOLD
			FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			// WHITE_BOLD
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
		};

		HANDLE hConsole = GetStdHandle(stdout_stream ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE );
		SetConsoleTextAttribute(hConsole, WinColorFG[color]);
	}

	void ConsoleInterface::ResetConsoleTextColor(bool stdout_stream)
	{
		HANDLE hConsole = GetStdHandle(stdout_stream ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE );
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED );
	}
}