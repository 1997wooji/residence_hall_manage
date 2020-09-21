#pragma warning(disable:4996)
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "control.h"
#include "fullscreenmenu.h"


/*----------------------------------------------------------------------------------
Function name	: manageBuilding - 건물 관리 메뉴 출력하는 함수
Parameters		: admin - 관리자가 설정한 에어컨 최소 온도 및 에어컨, 조명의 가동시간을
저장하는 구조체의 주소
room - 각 방의 조명, 에어컨, 환풍기 ON/OFF 여부 및 설정 온도를 저장하는
구조체 배열의 주소
today - 시간을 저장하는 구조체의 주소
name - 현재 사용자의 이름을 저장하는 배열의 주소
Returns			: 없음
----------------------------------------------------------------------------------*/
void manageBuilding(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name)
{
	const char *controlMenu[] = { "전체 현황", "냉방 관리", "조명 관리", "환풍기 관리" };
	int menuCnt, menuNum;

	menuCnt = sizeof(controlMenu) / sizeof(controlMenu[0]);
	while (1) {
		system("cls");
		fullScreen(today, name);
		menuNum = menuControl(controlMenu, menuCnt);
		switch (menuNum) {
		case 1: printWholeConditon(room, today, name); break;
		case 2: airConditionerControl(admin, room, today, name);  break;
		case 3: switching(room, printLight, lightSwitchONOFF, today, name); break;
		case 4: switching(room, printVentilator, ventilatorSwitchONOFF, today, name); break;
		case -1: return;
		}
	}
}


/*----------------------------------------------------------------------------------
Function name	: initRoom - 프로그램 실행시 각 방의 정보를 초기화하는 함수
Parameters		:
Returns			: 없음
----------------------------------------------------------------------------------*/
void initRoom(Admin *admin, Room(*room)[ROOMS])
{
	int i, j;

	for (i = 0; i < LAYERS; ++i) {
		for (j = 0; j < ROOMS; ++j) {
			room[i][j].airConditioner.switchOn = OFF;
			room[i][j].airConditioner.set = admin->min;
			room[i][j].ventilator.switchOn = OFF;
			room[i][j].light.switchOn = OFF;
		}
	}
}

/*----------------------------------------------------------------------------------
Function name	: menuControl - 건물관리에서 메뉴를 출력하고 메뉴 번호를 입력 받는 함수
Parameters		: menuList - 메뉴명이 저장 되어있는 배열의 주소
menuCnt - 메뉴의 개수가 저장되어 있는 변수
Returns			: 실행할 메뉴의 번호를 리턴
----------------------------------------------------------------------------------*/
int menuControl(const char **menuList, int menuCnt)
{
	int menuNum = 0;	/* 존재하지 않는 메뉴 번호 저장 */
	int i, res, x = 40, y = 8;

	for (i = 0; i < menuCnt; i++) {	/* 메뉴 출력 */
		gotoxy(x, y + i);
		printf("%d. %s\n", i + 1, menuList[i]);
	}
	while (menuNum<1 || menuNum>menuCnt) {	/* 메뉴번호가 유효하지 않을 동안 반복 */
		clearLine(y + menuCnt);
		gotoxy(x, y + menuCnt);
		printf("# 메뉴 선택 : ");
		res = inputInt(&menuNum);
		switch (res) {
		case -1: return -1;
		case 1: break;
		}
	}
	return menuNum;
}

/*----------------------------------------------------------------------------------
Function name	: printLight - 해당하는 곳의 조명 ON/OFF 여부를 출력하는 함수
Parameters		: layer - 출력하고자 하는 층
roomNum - 출력하고자하는 방의 번호
Returns			: 없음
----------------------------------------------------------------------------------*/
void printLight(Room(*room)[ROOMS], int layer, int roomNum)
{
	printf("조명 : ");
	if (room[layer][roomNum].light.switchOn == OFF) {
		textcolor(YELLOW, BLACK);
		printf("OFF\t");
	}
	else {
		textcolor(LIGHTRED, BLACK);
		printf("ON\t");
	}
	textcolor(LIGHTGRAY, BLACK);
}

/*----------------------------------------------------------------------------------
Function name	: printVentilator - 해당하는 곳의 환풍기 ON/OFF 여부를 출력하는 함수
Parameters		: layer - 출력하고자 하는 층
roomNum - 출력하고자하는 방의 번호
Returns			: 없음
----------------------------------------------------------------------------------*/
void printVentilator(Room(*room)[ROOMS], int layer, int roomNum)
{
	printf("환풍기 : ");
	if (room[layer][roomNum].ventilator.switchOn == OFF) {
		textcolor(YELLOW, BLACK);
		printf("OFF\t");
	}
	else {
		textcolor(LIGHTRED, BLACK);
		printf("ON\t");
	}
	textcolor(LIGHTGRAY, BLACK);
}

/*----------------------------------------------------------------------------------
Function name	: printAirConditioner - 해당하는 곳의 에어컨 ON/OFF 여부를 출력하는 함수
Parameters		: layer - 출력하고자 하는 층
roomNum - 출력하고자하는 방의 번호
Returns			: 없음
----------------------------------------------------------------------------------*/
void printAirConditioner(Room(*room)[ROOMS], int layer, int roomNum)
{
	printf("에어컨 : ");
	if (room[layer][roomNum].airConditioner.switchOn == OFF) {
		textcolor(YELLOW, BLACK);
		printf("OFF\t");
	}
	else {
		textcolor(LIGHTRED, BLACK);
		printf("ON\t");
	}
	textcolor(LIGHTGRAY, BLACK);
}

/*----------------------------------------------------------------------------------
Function name	: printWholeCondition - 모든 곳의 조명, 환풍기, 에어컨 ON/OFF 여부를 출력하는 함수
Parameters		:
Returns			: 없음
----------------------------------------------------------------------------------*/
void printWholeConditon(Room(*room)[ROOMS], TimeCheck *today, char *name)
{
	int i, j;
	int x = 0, y = 5;

	system("cls");
	fullScreen(today, name);
	for (i = LAYERS - 1; i > 0; --i) {
		gotoxy(x, ++y);
		for (j = 0; j < ROOMS - 1; ++j) {
			printf("%d번방 상태\t", ((i + 1) * 100 + j + 1));
		}
		printf("%d층 복도 상태", i + 1);
		gotoxy(x, ++y);
		for (j = 0; j < ROOMS; ++j) {
			printLight(room, i, j);
		}
		gotoxy(x, ++y);
		for (j = 0; j < ROOMS; ++j) {
			printAirConditioner(room, i, j);
		}
		gotoxy(x, ++y);
		for (j = 0; j < ROOMS; ++j) {
			printVentilator(room, i, j);
		}
		gotoxy(x, ++y);
	}
	printf("\n\t\t\t\t\t1층 로비 상태\n\t\t\t\t\t ");
	printLight(room, 0, ROOMS - 1);
	printf("\n\t\t\t\t\t ");
	printAirConditioner(room, 0, ROOMS - 1);
	printf("\n\t\t\t\t\t ");
	printVentilator(room, 0, ROOMS - 1);
	getch();
}

/*----------------------------------------------------------------------------------
Function name	: airConditionerSwitchONOFF - 에어컨 ON, OFF를 조절하는 함수
Parameters		: category - 시행할 작업의 종류를 저장하는 변수
(-1일 경우 ON/OFF 반전, 0 일경우 OFF, 1일 경우 ON)
Returns			: 없음
----------------------------------------------------------------------------------*/
void airConditionerSwitchONOFF(Room(*room)[ROOMS], int roomNumber, int category)
{
	int layer, roomNum;
	layer = roomNumber / 100 - 1;
	roomNum = roomNumber % 100 - 1;
	if (layer < 0) {
		layer = roomNumber - 1;
		roomNum = ROOMS - 1;
	}

	if (layer >= 0 && layer < LAYERS  && roomNum >= 0 && roomNum < ROOMS) {
		switch (category) {
		case -1:
			room[layer][roomNum].airConditioner.switchOn = !room[layer][roomNum].airConditioner.switchOn;
			break;
		case 0:
			room[layer][roomNum].airConditioner.switchOn = OFF;
			break;
		case 1:
			room[layer][roomNum].airConditioner.switchOn = ON;
		}
	}
}

/*----------------------------------------------------------------------------------
Function name	: lightSwitchONOFF - 조명 ON, OFF를 조절하는 함수
Parameters		: category - 시행할 작업의 종류를 저장하는 변수
(-1일 경우 ON/OFF 반전, 0 일경우 OFF, 1일 경우 ON)
Returns			: 없음
----------------------------------------------------------------------------------*/
void lightSwitchONOFF(Room(*room)[ROOMS], int roomNumber, int category)
{
	int layer, roomNum;
	layer = roomNumber / 100 - 1;
	roomNum = roomNumber % 100 - 1;
	if (layer < 0) {
		layer = roomNumber - 1;
		roomNum = ROOMS - 1;
	}

	if (layer >= 0 && layer < LAYERS  && roomNum >= 0 && roomNum < ROOMS) {
		switch (category) {
		case -1:
			room[layer][roomNum].light.switchOn = !room[layer][roomNum].light.switchOn;
			break;
		case 0:
			room[layer][roomNum].light.switchOn = OFF;
			break;
		case 1:
			room[layer][roomNum].light.switchOn = ON;
			break;
		}
	}
}

/*----------------------------------------------------------------------------------
Function name	: ventilatorSwitchONOFF - 환풍기 ON, OFF를 조절하는 함수
Parameters		: category - 시행할 작업의 종류를 저장하는 변수
(-1일 경우 ON/OFF 반전, 0 일경우 OFF, 1일 경우 ON)
Returns			: 없음
----------------------------------------------------------------------------------*/
void ventilatorSwitchONOFF(Room(*room)[ROOMS], int roomNumber, int category)
{
	int layer, roomNum;
	layer = roomNumber / 100 - 1;
	roomNum = roomNumber % 100 - 1;
	if (layer < 0) {
		layer = roomNumber - 1;
		roomNum = ROOMS - 1;
	}

	if (layer >= 0 && layer < LAYERS  && roomNum >= 0 && roomNum < ROOMS) {
		switch (category) {
		case -1:
			room[layer][roomNum].ventilator.switchOn = !room[layer][roomNum].ventilator.switchOn;
			break;
		case 0:
			room[layer][roomNum].ventilator.switchOn = OFF;
			break;
		case 1:
			room[layer][roomNum].ventilator.switchOn = ON;
			break;
		}
	}
}

/*----------------------------------------------------------------------------------
Function name	: switchjing - 해당하는 기능에 대해 전체 출력하고, 조절할 방이나 복도를
입력받아 ON/OFF시키는 함수
Parameters		: switchOnOff - ????
dataPrint - ?????
Returns			: 없음
----------------------------------------------------------------------------------*/
void switching(Room(*room)[ROOMS], void(*dataPrint)(Room(*)[ROOMS], int, int), void(*switchOnOff)(Room(*)[ROOMS], int, int), TimeCheck *today, char *name)
{
	int i, j, res, roomNumber, cnt;
	int x, y;

	while (1) {
		x = 0, y = 3;
		system("cls");
		fullScreen(today, name);
		cnt = 0;
		for (i = LAYERS - 1; i > 0; --i) {
			gotoxy(x, y += 2);
			for (j = 0; j < ROOMS - 1; ++j) {
				printf("%d번방 상태\t", ((i + 1) * 100 + j + 1));
			}
			printf("%d층 복도 상태", i + 1);
			gotoxy(x, y += 1);
			for (j = 0; j < ROOMS; ++j) {
				dataPrint(room, i, j);
			}
		}
		gotoxy(x, y += 2);
		printf("\t\t\t\t\t1층 로비 상태\n\t\t\t\t\t ");
		dataPrint(room, 0, ROOMS - 1);

		gotoxy(x, y += 3);
		printf("상태를 바꿀 호수를 입력하세요(복도의 경우 층수)\n");
		res = inputInt(&roomNumber);
		switch (res) {
		case -1: return;
		case 1:	switchOnOff(room, roomNumber, -1); break;
		}
	}
}

/*----------------------------------------------------------------------------------
Function name	: checkTemperature - 냉방 시작시 방의 설정 온도가 최소 온도보다 낮을 경우
관리가가 설정한 최소 온도로 설정
Parameters		:
Returns			: 없음
----------------------------------------------------------------------------------*/
void checkTemperature(Admin *admin, Room(*room)[ROOMS])
{
	int i, j;

	for (i = LAYERS - 1; i > 0; --i) {
		for (j = 0; j < ROOMS; ++j) {
			if (room[i][j].airConditioner.set < admin->min)
				room[i][j].airConditioner.set = admin->min;
		}
	}
}

/*----------------------------------------------------------------------------------
Function name	: setMinimalTemperature - 관리자가 냉방 시 최소온도를 설정하는 함수
Parameters		:
Returns			: 없음
----------------------------------------------------------------------------------*/
void setMinimalTemperature(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name)
{
	int min, res, cnt = 0;;
	int x, y;

	while (1) {
		x = 30, y = 7;
		system("cls");
		fullScreen(today, name);
		gotoxy(x, y);
		printf("현재 최소 온도는 %d도입니다.\n", admin->min);
		gotoxy(x, ++y);
		printf("변경할 최소 온도를 입력하세요(최소 18도, 최대 28도) : ");

		res = inputInt(&min);
		switch (res) {
		case -1: return;
		case 1:
			if (min > 17 && min < 29) {
				admin->min = min;
				checkTemperature(admin, room);
				return;
			}
		}
	}
}

/*----------------------------------------------------------------------------------
Function name	: switchWholeONOFF - 해당하는 기능을 건물 전체 ON/OFF하는 함수
Parameters		: switchONOFF - ?????
Returns			: 없음
----------------------------------------------------------------------------------*/
void switchWholeONOFF(Room(*room)[ROOMS], SWITCH OnOff, void(*switchONOFF)(Room(*)[ROOMS], int, int))
{
	int i, j, roomNumber;

	for (i = LAYERS - 1; i > 0; --i) {
		for (j = 0; j < ROOMS; ++j) {
			roomNumber = ((i + 1) * 100 + j + 1);
			switchONOFF(room, roomNumber, OnOff);
		}
	}
	switchONOFF(room, 1, OnOff);
}

/*----------------------------------------------------------------------------------
Function name	: checkTime - 입력 받은 시간이 해당 기능에 대해 가동 시간인지를 구분하는 함수
Parameters		: s - 가동 시작 시간
e - 가동 종료 시간
h - 현재 시간
Returns			: 가동 시간일 경우 ON, 아닐 경우 OFF 리턴
----------------------------------------------------------------------------------*/
SWITCH checkTime(int s, int e, double h)
{
	SWITCH onOff;
	if (e > s) {
		if (s <= h && h <= e)
			onOff = ON;
		else
			onOff = OFF;
	}
	else {
		if (!(e < h && h < s))
			onOff = ON;
		else
			onOff = OFF;
	}

	return onOff;
}

/*----------------------------------------------------------------------------------
Function name	: checkUptime - 시간과 분을 입력 받아 해당 시간 조명과 에어컨을
ON/OFF하는 함수???
Parameters		: hour - 입력 받은 시간
min - 입력 받은 분
Returns			: 없음
----------------------------------------------------------------------------------*/
void checkUptime(Admin *admin, Room(*room)[ROOMS], char* hour, char* min)
{
	int i, j, roomNumber;
	double h, temp;
	SWITCH onOff;

	h = atof(hour);
	temp = atof(min) / 60;
	h += temp;

	if (admin->startTime != admin->endTime) {
		onOff = checkTime(admin->startTime, admin->endTime, h);

		for (i = LAYERS - 1; i > 0; --i) {
			for (j = 0; j < ROOMS; ++j) {
				roomNumber = ((i + 1) * 100 + j + 1);
				switchWholeONOFF(room, onOff, airConditionerSwitchONOFF);
			}
		}
	}

	if (admin->lightStartTime != admin->lightEndTime) {
		onOff = checkTime(admin->lightStartTime, admin->lightEndTime, h);

		for (i = LAYERS - 1; i > 0; --i) {
			for (j = 0; j < ROOMS; ++j) {
				roomNumber = ((i + 1) * 100 + j + 1);
				switchWholeONOFF(room, onOff, lightSwitchONOFF);
			}
		}
	}
}

/*----------------------------------------------------------------------------------
Function name	: setAirConditionerUptime - 관리자가 냉방 시작 시간과 종료 시간을 설정하는 함수
Parameters		:
Returns			: 없음
----------------------------------------------------------------------------------*/
void setAirConditionerUptime(Admin *admin, TimeCheck *today, char *name)
{
	int res, startTime, endTime;
	int x = 30, y = 7;

	system("cls");
	fullScreen(today, name);
	gotoxy(x, y);
	printf("현재 냉방 가동 시간은 %d ~ %d 시까지 입니다.", admin->startTime, admin->endTime);
	gotoxy(x, ++y);
	printf("냉방 모드의 시작 시간과 종료 시간이 같을 경우 더 이상 냉방이 작동하지 않습니다.");
	gotoxy(x, ++y);
	printf("문자 입력시 이전 메뉴로 이동");
	gotoxy(x, ++y);
	printf("냉방 시작 시간을 입력하세요 : ");

	res = inputInt(&startTime);
	switch (res) {
	case -1: return;
	case 1:	admin->startTime = startTime; break;
	case 4: return;
	}
	gotoxy(x, ++y);
	printf("냉방 종료 시간을 입력하세요 : ");
	res = inputInt(&endTime);
	switch (res) {
	case -1: return;
	case 1:	admin->endTime = endTime; break;
	case 4: return;
	}
}

/*----------------------------------------------------------------------------------
Function name	: airConditionerControl - 관리자 냉방 관리에 대한 메뉴 출력하는 함수
Parameters		:
Returns			: 없음
----------------------------------------------------------------------------------*/
void airConditionerControl(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name)
{
	const char *controlMenu[] = { "온도 설정", "시간 설정", "ON/OFF" };
	int menuCnt, menuNum;

	menuCnt = sizeof(controlMenu) / sizeof(controlMenu[0]);
	while (1) {
		system("cls");
		fullScreen(today, name);
		menuNum = menuControl(controlMenu, menuCnt);
		switch (menuNum) {
		case 1: setMinimalTemperature(admin, room, today, name); break;
		case 2: setAirConditionerUptime(admin, today, name);  break;
		case 3: switching(room, printAirConditioner, airConditionerSwitchONOFF, today, name); break;
		case -1: return;
		}
	}
}

/*----------------------------------------------------------------------------------
Function name	: inputInt - 정수 입력 처리 함수
Parameters		: num - 입력 받은 정수의 주소
Returns			:  뒤로가기 시 -1, 입력 성공시 1, 실패시 4 리턴
----------------------------------------------------------------------------------*/
int inputInt(int *num)
{
	char ch, temp[20];
	int cnt = 0;

	while (1) {
		ch = getch();
		if (ch == BACK)
			return -1;
		else if (ch == BACKSPACE) {
			if (cnt > 0) {
				printf("\b \b");
				--cnt;
			}
		}
		else if (ch == '\r')
			break;
		else {
			temp[cnt++] = ch;
			printf("%c", ch);
		}
	}

	temp[cnt] = '\0';
	if (checkInt(temp, strlen(temp))) {
		*num = atoi(temp);
		return 1;
	}
	else
		return 4;
}

/*----------------------------------------------------------------------------------
Function name	: checkInt - 입력 받은 배열에 대해 문자 체크
Parameters		: temp - 체크할 문자열
size - 체크할 문자열의 크기
Returns			: 전부 정수 일 경우 1, 문자가 있을 경우 0 리턴
----------------------------------------------------------------------------------*/
int checkInt(char *temp, int size)
{
	int i;

	for (i = 0; i < size; ++i) {
		if (temp[i] < '0' || temp[i] > '9')
			return 0;
	}

	return 1;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void clearLine(int y)
{
	int i;

	gotoxy(0, y);
	for (i = 0; i < 80; ++i)
		printf(" ");
}

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void myflush(void)
{
	while (getchar() != '\n');
}