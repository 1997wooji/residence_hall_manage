#pragma once
#include "timecheck.h"
#include "fullscreenmenu.h"
#include "genericdoublelinkedlist.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
struct Food {
	char day[10];
	char food[6][30];
};

void gotoxy(int x, int y);
void manageFood(List *, TimeCheck *, char *);
void foodMemcpy(void *p1, void *p2); 
void foodPrint(void *p); 
int foodDayCompare(void *p1, void *p2);
void showFood(List *lp, TimeCheck *t, char *name);
void editFood(List *lp, TimeCheck *t, char *name);
void foodClear(void *);
void displayFoodList(List *lp, TimeCheck *today, void(*dataPrint)(void *p));  // 4일치 출력해주는 함수