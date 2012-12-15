/*
 * Console.h
 *
 *  Created on: 2012-12-15
 *      Author: king
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

namespace LOW
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



#endif /* CONSOLE_H_ */
