#include "Console.h"

void setConsoleScroll() {
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(StdOut, &info);
	COORD size = { info.dwSize.X, info.dwSize.Y + 1 };
	SetConsoleScreenBufferSize(StdOut, size);
}

void setConsoleCoords(int x, int y) {

	int yPrev = getConsoleCoordY();

	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(StdOut, coord);

	int yNow = getConsoleCoordY();

	if (yPrev == yNow) {
		setConsoleScroll();
		SetConsoleCursorPosition(StdOut, coord);
	}
}

int getConsoleCoordY() {
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(StdOut, &info);
	return info.dwCursorPosition.Y;
}

int getConsoleSizeX() {
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(StdOut, &info);
	return info.dwSize.X;
}
