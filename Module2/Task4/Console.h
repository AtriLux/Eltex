#pragma once

#include <Windows.h>

void setConsoleCoords(int x, int y); // переместить курсор в консоли на координаты x, y
void setConsoleScroll(); // прокрутить консоль на 1 px вниз
int getConsoleCoordY(); // получить y-координату текущего расположения курсора
int getConsoleSizeX(); // получить x-размеры текущего окна консоли