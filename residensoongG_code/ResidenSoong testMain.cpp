#include <stdio.h>
#include "genericdoublelinkedlist.h"
#include "timecheck.h"
#include "person.h"
#include "managePerson.h"
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <conio.h>
#include <windows.h>
#include "control.h"
#include "food.h"
#include "studentMode.h"
#include "post.h"


#define ESC 27

char menu(const char **mList, size_t menuCnt);	/* �޴� ��� �� �޴���ȣ �Է� �Լ� */
void login(Admin *admin, Room(*room)[ROOMS], List *lp, TimeCheck *today,FILE *datep); /*�α��� �Լ�*/
void fullScreen(TimeCheck *today,char *name); /*��ũ�� ��� �Լ�*/
void manageMode(Admin *admin, Room(*room)[ROOMS], List *lp, TimeCheck * today, char * name,Person * manager); /*�Ŵ������*/
void studentMode(Admin *admin, Room(*room)[ROOMS],List *lp, TimeCheck *today, char *name, Person *student); /*�л� ���*/
void allFileAdd(List *lp, FILE *fp); /* ���۽� ����Ʈ�� ���Ͽ������� �о�� ��� ���� ����*/
void allFileEnd(List *lp, FILE *fp); /* ����� ���Ͽ� ����Ʈ�������� �о�� ��� ���� ����*/
void allFileAddFood(List *lp, FILE *fp);/*���۽� ����Ʈ�� ���Ͽ������� �о�� �Ĵ� ����*/


int main()
{

	FILE * fp = fopen("C:\\data\\residence\\person.txt", "rt");
	FILE * fp3 = fopen("C:\\data\\residence\\food.txt", "rt");
	List residensoong[3];
	Admin admin = { 18, 18, 5, 18, 6 };
	Room room[LAYERS][ROOMS];


	/*{�ο�����, �ù� ����, �Ĵ� ����}*/

	int bres;
	TimeCheck timecheck;
	FILE * datep = fopen("C:\\data\\residence\\scenario.txt", "rt");

	initRoom(&admin, room);


	bres = createList(&(residensoong[0]));
	if (bres != TRUE) return 1;

	bres = createList(&(residensoong[1]));
	if (bres != TRUE) return 1;

	bres = createList(&(residensoong[2]));
	if (bres != TRUE) return 1;

	allFileAdd(&(residensoong[0]), fp);
	allFileAddFood(&(residensoong[2]), fp3);
	fclose(fp);
	fclose(fp3);

	textcolor(7, 0);

	login(&admin, room, residensoong, &timecheck, datep);


	fp = fopen("C:\\data\\residence\\person.txt", "wt");
	allFileEnd(&(residensoong[0]),fp);
	fclose(fp);
	fclose(datep);

	destroyList(&(residensoong[0]), personClear);	/* ����Ʈ���� ��� ������ ���� */
	destroyList(&(residensoong[1]), PostClear);
	destroyList(&(residensoong[2]), foodClear);

	return 0;
}

void login(Admin *admin, Room(*room)[ROOMS], List *residensoong, TimeCheck * today, FILE *datep)
{

	Node * resp;
	char ch;
	char name[100];
	int i;

	while (1)
	{
		i=timecheck(today, datep); //�α��� �Ҷ����� �ð��� �ٲ�� �޶����� ����縦 �� �� ����.
		if (i == 0) return;
		checkUptime(admin, room, today->hour, today->min);

		system("cls");
		gotoxy(35, 8);
		printf("<����� ���� ���α׷�>");

		resp = managePersonSearch(&(residensoong[0]), "�α���");

		if (resp != NULL)
			strcpy(name, ((Person *)(resp+1))->name);
		else break;

			if (((Person *)(resp + 1))->code[0] == '2')
				manageMode(admin, room, residensoong, today, name, ((Person *)(resp + 1)));
			else if (((Person *)(resp + 1))->code[0] == '1')
				studentMode(admin, room, residensoong,today, name, ((Person *)(resp + 1)));
			else {
				gotoxy(35, 20);
				printf(" * �ܺ����� �� �� �����ϴ� *");
			}
		
		if (ch = getch() == ESC) break;
	}

	return;
}

void allFileAdd(List *lp, FILE *fp)
{
	char temp[100];
	Person inData = { NULL,"",0,0,"","" };

	while (fscanf(fp, "%s %s %d %d %s %s\n", temp,inData.code, &(inData.inout), &(inData.room), inData.phonenumber, inData.registrationDate) != EOF)
	{
		inData.name = (char *)calloc(1, strlen(temp) + 1);
		assert(inData.name != NULL);
		strcpy(inData.name, temp);

		addLast(lp, &inData, sizeof(Person), personMemcpy);
		free(inData.name); //�޸� ���� ����
		inData.name = NULL; 

	}

	return;

}

void allFileEnd(List *lp, FILE *fp)
{
	Node *curp;
	Person inData = { NULL,"",1,0,"","" };

	if (lp == NULL) { /* lp������ NULL check */
		return;
	}
	curp = lp->head->next;
	while (curp != lp->tail) {
		personMemcpy(&inData,curp+1);
		fprintf(fp, "%s %s %d %d %s %s\n",inData.name,inData.code, inData.inout, inData.room, inData.phonenumber, inData.registrationDate);
		curp=curp->next;
	}

	free(inData.name); /*�޸� ���� ����!*/
	return;


}

void allFileAddFood(List *lp, FILE *fp) {
	Food inData = { "", "", "", "", "", "" ,"" };
	while (fscanf(fp, "%s %s %s %s %s %s %s \n", inData.day, inData.food[0], inData.food[1], inData.food[2], inData.food[3], inData.food[4], inData.food[5]) != EOF)
	{
		addLast(lp, &inData, sizeof(Food), foodMemcpy);
	}
	return;
}

void manageMode(Admin *admin, Room(*room)[ROOMS], List *lp, TimeCheck * today, char * name, Person * manager)
{
	const char *menuList[] = { "�ο� ����","�ǹ� ����","�ù� ���","�Ĵ� ����", "�⡡ ����" };
	char menuNum = 0;	/* �޴���ȣ ���� ���� */
	int menuCnt;	/* �޴����� ���� ���� */


	menuCnt = sizeof(menuList) / sizeof(menuList[0]);

	while (menuNum != ESC)
	{
		system("cls");
		fullScreen(today, name);
		menuNum = menu(menuList, menuCnt);	/* �޴�ȭ���� ���� �޴���ȣ�� �Է� ���� */


		switch (menuNum)
		{
		case '1': managePerson(&(lp[0]), today, name); break;		/* �ο����� ���� */
		case '2': manageBuilding(admin, room, today, name); break;		/* �ǹ����� ���� */
		case '3': managePost(&(lp[1]),&(lp[0]),today,name); break;		/* �ù��� ���� */
		case '4': manageFood(&(lp[2]), today, name); break;		/* �Ĵ� ���� ���� */
		case '5':inoutBuilding(&(lp[0]), today, name,manager); break; /*���� ����*/
		case ESC: return;												/*  �ڷΰ��� */
		}
	}
	
}

void studentMode(Admin *admin, Room(*room)[ROOMS],List *lp,TimeCheck *today, char *name, Person *student)
{
	const char *menuList[] = { "�� ���� ����","�ó��� ����","�� �ù� Ȯ��","�Ĵ� Ȯ��", "�⡡ ����" };
	char menuNum = 0;	/* �޴���ȣ ���� ���� */
	int menuCnt;	/* �޴����� ���� ���� */


	menuCnt = sizeof(menuList) / sizeof(menuList[0]);

	while (menuNum != ESC)
	{
		system("cls");
		fullScreen(today, name);
		menuNum = menu(menuList, menuCnt);	/* �޴�ȭ���� ���� �޴���ȣ�� �Է� ���� */


		switch (menuNum)
		{
		case '1': checkMyInform(&(lp[0]), student, today, name); break;		/* �� ���� ���� ���� */
		case '2': manageBuildingStudent(admin, room,student, today, name); break;		/* �ó��� ���� ���� */
		case '3': checkMyPost(&(lp[1]), student, today, name); break;		/* �ù�Ȯ�� ���� */
		case '4':showFood(&(lp[2]), today, name); break;		/* �Ĵ� Ȯ�� ���� */
		case '5':inoutBuilding(&(lp[0]), today, name, student); break; /*���� ����*/
		case ESC: return;												/*  �ڷΰ��� */
		}
	}


}