#pragma once

#include <Windows.h>

void setConsoleCoords(int x, int y); // ����������� ������ � ������� �� ���������� x, y
void setConsoleScroll(); // ���������� ������� �� 1 px ����
int getConsoleCoordY(); // �������� y-���������� �������� ������������ �������
int getConsoleSizeX(); // �������� x-������� �������� ���� �������