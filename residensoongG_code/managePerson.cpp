#include <stdio.h>
#include "genericdoublelinkedlist.h"
#include "timecheck.h"
#include "person.h"
#include "post.h"
#include "fullscreenmenu.h"
#include "managePerson.h"

#define ESC 27

void managePerson(List *lp, TimeCheck *today, char *name)
{
	const char *menuList[] = { "��ü ��Ȳ","�ο� �߰�","�ο� ����","�ο� ����" };
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
		case '1': managePersonTotal(lp, today, name); break;		/* �Է¸޴� ���� */
		case '2': managePersonInput(lp, today, name); break;		/* ��¸޴� ���� */
		case '3': managePersonEdit(lp, today, name); break;		/* �˻��޴� ���� */
		case '4': managePersonDelete(lp, today, name); break;		/* �����޴� ���� */
		case ESC:break;/*  �ڷΰ��� ��� */
		}
	}

}

void managePersonSort(List *lp)
{
	sortList(lp, sizeof(Person), personCodeCompare, personMemcpy, personClear);
	/* ���� Sort�� �ڵ�� �����̹Ƿ� ������ ��*/

}

void managePersonTotal(List *lp, TimeCheck *today, char *name)
{
	system("cls");
	fullScreen(today, name);
	managePersonSort(lp);

	gotoxy(12, 12);

	printf("%6s%12s%6s%5s%6s%16s%9s\n", "����", "�̸�", "�ڵ�", "����", "ȣ��", "����ó", "�������");
	gotoxy(5, 13);
	printf("**************************************************************************************\n\n");
	displayList(lp, personPrint);


	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}
	}


}

void managePersonInput(List *lp, TimeCheck *today, char *name)
{

	char temp[100];
	char check[50] = { 0, };
	char code[5] = { 0, };
	Person inData = { NULL,"",1,0,"","" };
	Node * rp;


	while (strcmp(check, "�л�") != 0 && strcmp(check, "������") != 0 && strcmp(check, "�ܺ���") != 0)
	{
		system("cls");
		fullScreen(today, name);
		gotoxy(30, 8);
		printf("* �л�/������/�ܺ��� : "); scanf("%s", check);
		if (strcmp(check, "�л�") == 0) inData.code[0] = '1';
		else if (strcmp(check, "������") == 0) inData.code[0] = '2';
		else if (strcmp(check, "�ܺ���") == 0) inData.code[0] = '9';
		else { gotoxy(30, 8); printf(" * �ȹٷ� �ٽ� �Է��� �ֽʽÿ�. *"); getch(); }
	}

	gotoxy(30, 9);
	printf("* �̸� : "); scanf("%s", temp);
	inData.name = (char *)calloc(strlen(temp) + 1, sizeof(char));
	strcpy(inData.name, temp);

	gotoxy(30, 10);
	printf("* ����ó : "); scanf("%s", inData.phonenumber);
	gotoxy(30, 11);
	printf("* ȣ�� : "); scanf("%d", &(inData.room));

	strcpy(inData.registrationDate, today->date);
	while (1)
	{
		randomNumber(code, 3);
		strcpy((char *)(&(inData.code[1])), code);
		rp = searchNode(lp, &inData, personCodeCompare);
		/* �ڵ�� ��ġ�� �ȵȴ�! NULL�ϰ�� ���� �ڵ带 ���� ��尡 ���ٴ� ���̹Ƿ� OK*/
		if (rp == NULL) break;
	}
	addLast(lp, &inData, sizeof(Person), personMemcpy);
	free(inData.name); inData.name = NULL;

	gotoxy(35, 22);
	printf("* �Է� �Ϸ� ! *");
	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}
	}

}

void randomNumber(char *p, size_t size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		p[i] = 48 + rand() % 10;
		/* 48~57 ������ ���ڷ� 0~9�� ����*/
	}

}

void managePersonEdit(List *lp, TimeCheck *today, char *name)
{
	Person sData = { NULL,"",0,0,"","" };
	Node * resp;

	system("cls");
	fullScreen(today, name);

	resp = managePersonSearch(lp, "����");
	if (resp == NULL) return;

	sData.name = (char *)calloc(strlen(((Person *)(resp + 1))->name) + 1, sizeof(char));
	assert(sData.name != NULL);

	strcpy(sData.name, ((Person *)(resp + 1))->name);
	strcpy(sData.code, ((Person *)(resp + 1))->code);
	sData.inout = ((Person *)(resp + 1))->inout;
	strcpy(sData.registrationDate, ((Person *)(resp + 1))->registrationDate);
	//���Ա����� ���� �Ұ���

	gotoxy(30, 18);
	printf("* ȣ�� : ");
	scanf("%d", &(sData.room));

	gotoxy(30, 19);
	printf("* ����ó :");
	scanf("%s", sData.phonenumber);

	personMemcpy(resp + 1, &sData);
	gotoxy(35, 22);
	printf("* ���� �Ϸ� ! *");
	free(sData.name); sData.name = NULL;
	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}
	}

}

void managePersonDelete(List *lp, TimeCheck *today, char *name)
{
	Node * resp;
	int bres;

	system("cls");
	fullScreen(today, name);

	resp = managePersonSearch(lp, "����");
	if (resp == NULL) return;


	bres = removeNode(lp, resp + 1, personCodeCompare, personClear); /* �̸��� �ߺ� ���ɼ��� ������ �ڵ�� ���� �� */
	if (bres == TRUE)
	{
		gotoxy(35, 18);
		printf(" * ���� ���� ! *");
	}
	else
	{
		gotoxy(35, 18);
		printf(" * ���� ���� *  ");
	}
	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}
	}

}

Node * managePersonSearch(List *lp, char *chp) /*�ڵ�� �̸����� ��� ã���ֱ�*/
{
	char temp[100];
	Node * resp; Node * pesp;
	Person sData = { NULL,"",0,0,"","" };

	gotoxy(30, 12);
	printf("* %s", chp);
	printf("�� ����� �̸��� �Է��ϼ��� : ");
	scanf("%s", temp);
	sData.name = (char *)calloc(strlen(temp) + 1, sizeof(char));
	assert(sData.name != NULL);
	strcpy(sData.name, temp);

	resp = searchNode(lp, &sData, personNameCompare);

	if (resp == NULL)
	{
		gotoxy(30, 15);
		printf(" * �������� �ʴ� �̸��Դϴ� * ");

		free(sData.name); sData.name = NULL;
		Sleep(2000);
		return NULL;
	}

	gotoxy(30, 13);
	printf("* %s", chp);
	printf("�� ����� �ڵ带 �Է��ϼ��� : ");
	scanf("%s", sData.code);

	pesp = searchNode(lp, &sData, personCodeCompare);

	if (pesp == NULL)
	{
		gotoxy(30, 16);
		printf(" * �������� �ʴ� �ڵ��Դϴ� * ");
		Sleep(2000);
		free(sData.name); sData.name = NULL;
		return NULL;
	}

	if (resp == pesp)
	{
		free(sData.name); sData.name = NULL;
		return resp;

	}
	else {
		gotoxy(35, 18);
		printf("�̸��� �ڵ尡 ��ġ���� �ʽ��ϴ�! ");
	}


	free(sData.name); sData.name = NULL;
	Sleep(2000);
	return NULL;

}

void inoutBuilding(List *lp, TimeCheck *today, char *name, Person * who)
{
	

	system("cls");
	fullScreen(today, name);
	gotoxy(60, 28);
	printf("�ڵ����� ������ �ð��� 05��~24�� �Դϴ�.");

	if (who->code[0] == '1') //�л��� ���
	{
		if (strcmp(today->hour, "05") == 1)
		{
			who->inout = !(who->inout);
			gotoxy(35, 20);
			printf(" * ����! *");
		}
		else {

	
			gotoxy(35, 20);
			printf(" * ���� �ð����� ���� �� �����ϴ� *");
		}

	}
	else //�������� ���
	{
		who->inout = !(who->inout);
		gotoxy(35, 20);
		printf(" * ����! *");
	}

	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}
	}

}

void managePost(List *postlp,List *personlp, TimeCheck *today, char *name)
{
	Person sData = { NULL,"",0,0,"","" };
	Node * resp;
	Node * pesp;
	Post post = { "","",1 };

	system("cls");
	fullScreen(today, name);

	gotoxy(30, 12);
	printf(" * ���� ����� ����ó �Է� : ");
	scanf("%s", sData.phonenumber);

	resp= searchNode(personlp, &sData, PersonPhoneNumberCompare);
	if (resp == NULL) {
		gotoxy(30, 14);
		printf("* ���� ��ȣ�Դϴ�.");
		while (1)
		{
			if (getch() == ESC)
			{
				return;
			}
		}

	}
	strcpy(post.phonenumber, sData.phonenumber);
	pesp = searchNode(postlp, &post, PostPhoneNumberCompare);
	if (pesp == NULL)
	{

		randomNumber(post.postcode,4);
		addLast(postlp,&post,sizeof(Post),PostMemcpy);
		gotoxy(30, 17);
		printf("* �ù� �߰��� �����Ǿ����ϴ�. �ڵ�� %s �Դϴ�!",post.postcode);

	}
	else {

		((Post *)(pesp + 1))->cnt++;
		gotoxy(30, 17);
		printf("* �ù� �߰��� �����Ǿ����ϴ�!.");

	}


	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}
	}


}
