#include "control.h"
#include "person.h"
#include "post.h"
#include "genericdoublelinkedlist.h"
#include "fullscreenmenu.h"
#include <stdlib.h>
#include <string.h>
#include "studentMode.h"

#define ESC 27

void manageBuildingStudent(Admin *admin, Room(*room)[ROOMS], Person *student, TimeCheck *today, char *name)
{
	SWITCH onOff;
	char switchOn;
	double h, min;
	int layer, roomNumber, set, res;
	char temp[10];

	h = atof(today->hour);
	min = atof(today->min);
	h += min / 60;

	layer = student->room / 100 - 1;
	roomNumber = student->room % 100 - 1;

	onOff = checkTime(admin->startTime, admin->endTime, h);
	switchOn = room[layer][roomNumber].airConditioner.switchOn;

	system("cls");
	fullScreen(today, student->name);
	gotoxy(28, 13);
	printf("���� �ù���");
	if (onOff == ON)
		printf(" ");
	else
		printf(" ��");
	printf("������ �ð��Դϴ�.");

	gotoxy(28, 14);
	if (onOff == ON) {
		printf("���� ");
		printAirConditioner(room, layer, roomNumber);
		gotoxy(28, 15);
		printf("ON/OFF ��Ű�ڽ��ϱ�?? (ON / OFF) : ");
		scanf("%s", temp);
		if (strcmp(temp, "ON") == 0) {
			airConditionerSwitchONOFF(room, student->room, 1);
		}
		else if (strcmp(temp, "OFF") == 0) {
			airConditionerSwitchONOFF(room, student->room, 0);
		}
		else
			return;
	}

	gotoxy(28, 16);
	printf("������ �����µ�(%d��)���� ���� �µ� ������", admin->min);
	gotoxy(28, 17);
	printf("������ �����µ��� �����˴ϴ�.");
	gotoxy(28, 18);
	printf("������ ���� �µ�(���� �µ� : %d��) :", room[layer][roomNumber].airConditioner.set);
	res = scanf("%d", &set);
	if (res != 1) {
		myflush();
		return;
	}
	setStudentAirConditioner(admin, room, set, layer, roomNumber);
}

void setStudentAirConditioner(Admin *admin, Room(*room)[ROOMS], int set, int layer, int roomNumber)
{
	if (set < admin->min)
		room[layer][roomNumber].airConditioner.set = admin->min;
	else
		room[layer][roomNumber].airConditioner.set = set;
}

void checkMyPost(List *lp, Person *student, TimeCheck *today, char *name)
{
	Node * pesp;
	Post post = { "","",0 };

	system("cls");
	fullScreen(today, name);

	strcpy(post.phonenumber, student->phonenumber);

	pesp = searchNode(lp, &post, PostPhoneNumberCompare);
	if (pesp == NULL) {
		gotoxy(30, 12);
		printf("* �Ф� %s�Բ� �ƹ��� �ù赵 ���� �ʾҽ��ϴ�", name);


		while (1)
		{
			if (getch() == ESC)
			{
				return;
			}
		}

	}


	gotoxy(30, 12);
	printf("* ���� %s�Բ� �ù� <%d>���� ���ֽ��ϴ�!", name, ((Post*)(pesp + 1))->cnt);

	gotoxy(40, 14);
	printf(" ���ڸ��� �ڵ� �Է� : ");
	scanf("%s", post.postcode);

	if (strcmp(post.postcode, ((Post*)(pesp + 1))->postcode) == 0)
	{
		gotoxy(40, 16);
		removeNode(lp, pesp + 1, PostPhoneNumberCompare, PostClear);
		printf(" *�ù� �������� �Ϸ�!*");

	}
	else
	{
		gotoxy(40, 16);
		printf(" *�ڵ尡 ��ġ���� �ʽ��ϴ� �Ф� �ٽ� �������ּ���*");
	}


	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}
	}
}

void checkMyInform(List *lp, Person *student, TimeCheck *today, char *name)
{

	system("cls");
	fullScreen(today, name);

	gotoxy(1, 8);
	printf("%6s%12s%6s%5s%6s%16s%9s\n", "����", "�̸�", "�ڵ�", "����", "ȣ��", "����ó", "�������");
	printf("----------------------------------------------------------------------------------\n");
	personPrint(student);

	gotoxy(30, 12);
	printf("������ ���Ͻø� ESCŰ �� �ƹ�Ű�� �����ּ���");


	if (getch() == ESC)
	{
		return;
	}
	else
	{
		gotoxy(35, 15);
		printf("ȣ�� : ");
		scanf("%d", &(student->room));
		gotoxy(35, 16);
		printf("����ó : ");
		scanf("%s", student->phonenumber);

		gotoxy(35, 20);
		printf(" * ���� �Ϸ�! *");
	}



	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}

	}


}