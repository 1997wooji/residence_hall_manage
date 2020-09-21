#pragma once
#include <conio.h>
#include <windows.h>
#include "timecheck.h"

void fullScreen(TimeCheck *today, char *name);
char menu(const char **mList, size_t menuCnt);
void gotoxy(int x, int y);