#pragma warning(disable:4996)
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "control.h"
#include "fullscreenmenu.h"


/*----------------------------------------------------------------------------------
Function name	: manageBuilding - �ǹ� ���� �޴� ����ϴ� �Լ�
Parameters		: admin - �����ڰ� ������ ������ �ּ� �µ� �� ������, ������ �����ð���
�����ϴ� ����ü�� �ּ�
room - �� ���� ����, ������, ȯǳ�� ON/OFF ���� �� ���� �µ��� �����ϴ�
����ü �迭�� �ּ�
today - �ð��� �����ϴ� ����ü�� �ּ�
name - ���� ������� �̸��� �����ϴ� �迭�� �ּ�
Returns			: ����
----------------------------------------------------------------------------------*/
void manageBuilding(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name)
{
	const char *controlMenu[] = { "��ü ��Ȳ", "�ù� ����", "���� ����", "ȯǳ�� ����" };
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
Function name	: initRoom - ���α׷� ����� �� ���� ������ �ʱ�ȭ�ϴ� �Լ�
Parameters		:
Returns			: ����
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
Function name	: menuControl - �ǹ��������� �޴��� ����ϰ� �޴� ��ȣ�� �Է� �޴� �Լ�
Parameters		: menuList - �޴����� ���� �Ǿ��ִ� �迭�� �ּ�
menuCnt - �޴��� ������ ����Ǿ� �ִ� ����
Returns			: ������ �޴��� ��ȣ�� ����
----------------------------------------------------------------------------------*/
int menuControl(const char **menuList, int menuCnt)
{
	int menuNum = 0;	/* �������� �ʴ� �޴� ��ȣ ���� */
	int i, res, x = 40, y = 8;

	for (i = 0; i < menuCnt; i++) {	/* �޴� ��� */
		gotoxy(x, y + i);
		printf("%d. %s\n", i + 1, menuList[i]);
	}
	while (menuNum<1 || menuNum>menuCnt) {	/* �޴���ȣ�� ��ȿ���� ���� ���� �ݺ� */
		clearLine(y + menuCnt);
		gotoxy(x, y + menuCnt);
		printf("# �޴� ���� : ");
		res = inputInt(&menuNum);
		switch (res) {
		case -1: return -1;
		case 1: break;
		}
	}
	return menuNum;
}

/*----------------------------------------------------------------------------------
Function name	: printLight - �ش��ϴ� ���� ���� ON/OFF ���θ� ����ϴ� �Լ�
Parameters		: layer - ����ϰ��� �ϴ� ��
roomNum - ����ϰ����ϴ� ���� ��ȣ
Returns			: ����
----------------------------------------------------------------------------------*/
void printLight(Room(*room)[ROOMS], int layer, int roomNum)
{
	printf("���� : ");
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
Function name	: printVentilator - �ش��ϴ� ���� ȯǳ�� ON/OFF ���θ� ����ϴ� �Լ�
Parameters		: layer - ����ϰ��� �ϴ� ��
roomNum - ����ϰ����ϴ� ���� ��ȣ
Returns			: ����
----------------------------------------------------------------------------------*/
void printVentilator(Room(*room)[ROOMS], int layer, int roomNum)
{
	printf("ȯǳ�� : ");
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
Function name	: printAirConditioner - �ش��ϴ� ���� ������ ON/OFF ���θ� ����ϴ� �Լ�
Parameters		: layer - ����ϰ��� �ϴ� ��
roomNum - ����ϰ����ϴ� ���� ��ȣ
Returns			: ����
----------------------------------------------------------------------------------*/
void printAirConditioner(Room(*room)[ROOMS], int layer, int roomNum)
{
	printf("������ : ");
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
Function name	: printWholeCondition - ��� ���� ����, ȯǳ��, ������ ON/OFF ���θ� ����ϴ� �Լ�
Parameters		:
Returns			: ����
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
			printf("%d���� ����\t", ((i + 1) * 100 + j + 1));
		}
		printf("%d�� ���� ����", i + 1);
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
	printf("\n\t\t\t\t\t1�� �κ� ����\n\t\t\t\t\t ");
	printLight(room, 0, ROOMS - 1);
	printf("\n\t\t\t\t\t ");
	printAirConditioner(room, 0, ROOMS - 1);
	printf("\n\t\t\t\t\t ");
	printVentilator(room, 0, ROOMS - 1);
	getch();
}

/*----------------------------------------------------------------------------------
Function name	: airConditionerSwitchONOFF - ������ ON, OFF�� �����ϴ� �Լ�
Parameters		: category - ������ �۾��� ������ �����ϴ� ����
(-1�� ��� ON/OFF ����, 0 �ϰ�� OFF, 1�� ��� ON)
Returns			: ����
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
Function name	: lightSwitchONOFF - ���� ON, OFF�� �����ϴ� �Լ�
Parameters		: category - ������ �۾��� ������ �����ϴ� ����
(-1�� ��� ON/OFF ����, 0 �ϰ�� OFF, 1�� ��� ON)
Returns			: ����
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
Function name	: ventilatorSwitchONOFF - ȯǳ�� ON, OFF�� �����ϴ� �Լ�
Parameters		: category - ������ �۾��� ������ �����ϴ� ����
(-1�� ��� ON/OFF ����, 0 �ϰ�� OFF, 1�� ��� ON)
Returns			: ����
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
Function name	: switchjing - �ش��ϴ� ��ɿ� ���� ��ü ����ϰ�, ������ ���̳� ������
�Է¹޾� ON/OFF��Ű�� �Լ�
Parameters		: switchOnOff - ????
dataPrint - ?????
Returns			: ����
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
				printf("%d���� ����\t", ((i + 1) * 100 + j + 1));
			}
			printf("%d�� ���� ����", i + 1);
			gotoxy(x, y += 1);
			for (j = 0; j < ROOMS; ++j) {
				dataPrint(room, i, j);
			}
		}
		gotoxy(x, y += 2);
		printf("\t\t\t\t\t1�� �κ� ����\n\t\t\t\t\t ");
		dataPrint(room, 0, ROOMS - 1);

		gotoxy(x, y += 3);
		printf("���¸� �ٲ� ȣ���� �Է��ϼ���(������ ��� ����)\n");
		res = inputInt(&roomNumber);
		switch (res) {
		case -1: return;
		case 1:	switchOnOff(room, roomNumber, -1); break;
		}
	}
}

/*----------------------------------------------------------------------------------
Function name	: checkTemperature - �ù� ���۽� ���� ���� �µ��� �ּ� �µ����� ���� ���
�������� ������ �ּ� �µ��� ����
Parameters		:
Returns			: ����
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
Function name	: setMinimalTemperature - �����ڰ� �ù� �� �ּҿµ��� �����ϴ� �Լ�
Parameters		:
Returns			: ����
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
		printf("���� �ּ� �µ��� %d���Դϴ�.\n", admin->min);
		gotoxy(x, ++y);
		printf("������ �ּ� �µ��� �Է��ϼ���(�ּ� 18��, �ִ� 28��) : ");

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
Function name	: switchWholeONOFF - �ش��ϴ� ����� �ǹ� ��ü ON/OFF�ϴ� �Լ�
Parameters		: switchONOFF - ?????
Returns			: ����
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
Function name	: checkTime - �Է� ���� �ð��� �ش� ��ɿ� ���� ���� �ð������� �����ϴ� �Լ�
Parameters		: s - ���� ���� �ð�
e - ���� ���� �ð�
h - ���� �ð�
Returns			: ���� �ð��� ��� ON, �ƴ� ��� OFF ����
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
Function name	: checkUptime - �ð��� ���� �Է� �޾� �ش� �ð� ����� ��������
ON/OFF�ϴ� �Լ�???
Parameters		: hour - �Է� ���� �ð�
min - �Է� ���� ��
Returns			: ����
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
Function name	: setAirConditionerUptime - �����ڰ� �ù� ���� �ð��� ���� �ð��� �����ϴ� �Լ�
Parameters		:
Returns			: ����
----------------------------------------------------------------------------------*/
void setAirConditionerUptime(Admin *admin, TimeCheck *today, char *name)
{
	int res, startTime, endTime;
	int x = 30, y = 7;

	system("cls");
	fullScreen(today, name);
	gotoxy(x, y);
	printf("���� �ù� ���� �ð��� %d ~ %d �ñ��� �Դϴ�.", admin->startTime, admin->endTime);
	gotoxy(x, ++y);
	printf("�ù� ����� ���� �ð��� ���� �ð��� ���� ��� �� �̻� �ù��� �۵����� �ʽ��ϴ�.");
	gotoxy(x, ++y);
	printf("���� �Է½� ���� �޴��� �̵�");
	gotoxy(x, ++y);
	printf("�ù� ���� �ð��� �Է��ϼ��� : ");

	res = inputInt(&startTime);
	switch (res) {
	case -1: return;
	case 1:	admin->startTime = startTime; break;
	case 4: return;
	}
	gotoxy(x, ++y);
	printf("�ù� ���� �ð��� �Է��ϼ��� : ");
	res = inputInt(&endTime);
	switch (res) {
	case -1: return;
	case 1:	admin->endTime = endTime; break;
	case 4: return;
	}
}

/*----------------------------------------------------------------------------------
Function name	: airConditionerControl - ������ �ù� ������ ���� �޴� ����ϴ� �Լ�
Parameters		:
Returns			: ����
----------------------------------------------------------------------------------*/
void airConditionerControl(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name)
{
	const char *controlMenu[] = { "�µ� ����", "�ð� ����", "ON/OFF" };
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
Function name	: inputInt - ���� �Է� ó�� �Լ�
Parameters		: num - �Է� ���� ������ �ּ�
Returns			:  �ڷΰ��� �� -1, �Է� ������ 1, ���н� 4 ����
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
Function name	: checkInt - �Է� ���� �迭�� ���� ���� üũ
Parameters		: temp - üũ�� ���ڿ�
size - üũ�� ���ڿ��� ũ��
Returns			: ���� ���� �� ��� 1, ���ڰ� ���� ��� 0 ����
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