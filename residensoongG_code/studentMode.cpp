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
	printf("현재 냉방이");
	if (onOff == ON)
		printf(" ");
	else
		printf(" 불");
	printf("가능한 시각입니다.");

	gotoxy(28, 14);
	if (onOff == ON) {
		printf("현재 ");
		printAirConditioner(room, layer, roomNumber);
		gotoxy(28, 15);
		printf("ON/OFF 시키겠습니까?? (ON / OFF) : ");
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
	printf("관리자 설정온도(%d도)보다 낮은 온도 설정시", admin->min);
	gotoxy(28, 17);
	printf("관리자 설정온도로 설정됩니다.");
	gotoxy(28, 18);
	printf("에어컨 설정 온도(현재 온도 : %d도) :", room[layer][roomNumber].airConditioner.set);
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
		printf("* ㅠㅠ %s님께 아무런 택배도 오지 않았습니다", name);


		while (1)
		{
			if (getch() == ESC)
			{
				return;
			}
		}

	}


	gotoxy(30, 12);
	printf("* 현재 %s님께 택배 <%d>개가 와있습니다!", name, ((Post*)(pesp + 1))->cnt);

	gotoxy(40, 14);
	printf(" 네자리의 코드 입력 : ");
	scanf("%s", post.postcode);

	if (strcmp(post.postcode, ((Post*)(pesp + 1))->postcode) == 0)
	{
		gotoxy(40, 16);
		removeNode(lp, pesp + 1, PostPhoneNumberCompare, PostClear);
		printf(" *택배 가져가기 완료!*");

	}
	else
	{
		gotoxy(40, 16);
		printf(" *코드가 일치하지 않습니다 ㅠㅠ 다시 접속해주세요*");
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
	printf("%6s%12s%6s%5s%6s%16s%9s\n", "구분", "이름", "코드", "출입", "호수", "연락처", "등록일자");
	printf("----------------------------------------------------------------------------------\n");
	personPrint(student);

	gotoxy(30, 12);
	printf("수정을 원하시면 ESC키 외 아무키나 눌러주세요");


	if (getch() == ESC)
	{
		return;
	}
	else
	{
		gotoxy(35, 15);
		printf("호수 : ");
		scanf("%d", &(student->room));
		gotoxy(35, 16);
		printf("연락처 : ");
		scanf("%s", student->phonenumber);

		gotoxy(35, 20);
		printf(" * 수정 완료! *");
	}



	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}

	}


}