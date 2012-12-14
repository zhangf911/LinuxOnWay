#ifndef LIBRARY_CONSOLE_H
#define LIBRARY_CONSOLE_H

#include "BaseType.h"

namespace ZGF
{
	enum Color
	{
		BLACK,
		RED,
		GREEN,
		BROWN,
		BLUE,
		MAGENTA,
		CYAN,
		GREY,
		YELLOW,
		LRED,
		LGREEN,
		LBLUE,
		LMAGENTA,
		LCYAN,
		WHITE
	};

	class ConsoleInterface
	{
	public:
		static void SetConsoleTextColor(bool stdout_stream, Color color);

		static void ResetConsoleTextColor(bool stdout_stream);
	};
}



#endif
