/*
 * Console.cpp
 *
 *  Created on: 2012-12-15
 *      Author: king
 */

#include "Console.h"

namespace LOW
{
	void ConsoleInterface::SetConsoleTextColor(bool stdout_stream, Color color)
	{
#ifdef WIN32
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
#else

#ifdef __GNUC__
		// 尚未实现
#endif

#endif
	}

	void ConsoleInterface::ResetConsoleTextColor(bool stdout_stream)
	{
#ifdef WIN32
		HANDLE hConsole = GetStdHandle(stdout_stream ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE );
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED );
#else

#ifdef __GNUC__
		// 尚未实现
#endif

#endif
	}
}


