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
	const char *menuList[] = { "전체 현황","인원 추가","인원 수정","인원 삭제" };
	char menuNum = 0;	/* 메뉴번호 저장 변수 */
	int menuCnt;	/* 메뉴개수 저장 변수 */



	menuCnt = sizeof(menuList) / sizeof(menuList[0]);

	while (menuNum != ESC)
	{
		system("cls");
		fullScreen(today, name);
		menuNum = menu(menuList, menuCnt);	/* 메뉴화면을 띄우고 메뉴번호를 입력 받음 */


		switch (menuNum)
		{
		case '1': managePersonTotal(lp, today, name); break;		/* 입력메뉴 실행 */
		case '2': managePersonInput(lp, today, name); break;		/* 출력메뉴 실행 */
		case '3': managePersonEdit(lp, today, name); break;		/* 검색메뉴 실행 */
		case '4': managePersonDelete(lp, today, name); break;		/* 삭제메뉴 실행 */
		case ESC:break;/*  뒤로가기 등등 */
		}
	}

}

void managePersonSort(List *lp)
{
	sortList(lp, sizeof(Person), personCodeCompare, personMemcpy, personClear);
	/* 여기 Sort는 코드순 정렬이므로 주의할 것*/

}

void managePersonTotal(List *lp, TimeCheck *today, char *name)
{
	system("cls");
	fullScreen(today, name);
	managePersonSort(lp);

	gotoxy(12, 12);

	printf("%6s%12s%6s%5s%6s%16s%9s\n", "구분", "이름", "코드", "출입", "호수", "연락처", "등록일자");
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


	while (strcmp(check, "학생") != 0 && strcmp(check, "관리자") != 0 && strcmp(check, "외부인") != 0)
	{
		system("cls");
		fullScreen(today, name);
		gotoxy(30, 8);
		printf("* 학생/관리자/외부인 : "); scanf("%s", check);
		if (strcmp(check, "학생") == 0) inData.code[0] = '1';
		else if (strcmp(check, "관리자") == 0) inData.code[0] = '2';
		else if (strcmp(check, "외부인") == 0) inData.code[0] = '9';
		else { gotoxy(30, 8); printf(" * 똑바로 다시 입력해 주십시오. *"); getch(); }
	}

	gotoxy(30, 9);
	printf("* 이름 : "); scanf("%s", temp);
	inData.name = (char *)calloc(strlen(temp) + 1, sizeof(char));
	strcpy(inData.name, temp);

	gotoxy(30, 10);
	printf("* 연락처 : "); scanf("%s", inData.phonenumber);
	gotoxy(30, 11);
	printf("* 호수 : "); scanf("%d", &(inData.room));

	strcpy(inData.registrationDate, today->date);
	while (1)
	{
		randomNumber(code, 3);
		strcpy((char *)(&(inData.code[1])), code);
		rp = searchNode(lp, &inData, personCodeCompare);
		/* 코드는 겹치면 안된다! NULL일경우 같은 코드를 가진 노드가 없다는 뜻이므로 OK*/
		if (rp == NULL) break;
	}
	addLast(lp, &inData, sizeof(Person), personMemcpy);
	free(inData.name); inData.name = NULL;

	gotoxy(35, 22);
	printf("* 입력 완료 ! *");
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
		/* 48~57 까지가 문자로 0~9를 뜻함*/
	}

}

void managePersonEdit(List *lp, TimeCheck *today, char *name)
{
	Person sData = { NULL,"",0,0,"","" };
	Node * resp;

	system("cls");
	fullScreen(today, name);

	resp = managePersonSearch(lp, "수정");
	if (resp == NULL) return;

	sData.name = (char *)calloc(strlen(((Person *)(resp + 1))->name) + 1, sizeof(char));
	assert(sData.name != NULL);

	strcpy(sData.name, ((Person *)(resp + 1))->name);
	strcpy(sData.code, ((Person *)(resp + 1))->code);
	sData.inout = ((Person *)(resp + 1))->inout;
	strcpy(sData.registrationDate, ((Person *)(resp + 1))->registrationDate);
	//출입까지는 변경 불가능

	gotoxy(30, 18);
	printf("* 호수 : ");
	scanf("%d", &(sData.room));

	gotoxy(30, 19);
	printf("* 연락처 :");
	scanf("%s", sData.phonenumber);

	personMemcpy(resp + 1, &sData);
	gotoxy(35, 22);
	printf("* 수정 완료 ! *");
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

	resp = managePersonSearch(lp, "삭제");
	if (resp == NULL) return;


	bres = removeNode(lp, resp + 1, personCodeCompare, personClear); /* 이름은 중복 가능성이 있으니 코드로 지울 것 */
	if (bres == TRUE)
	{
		gotoxy(35, 18);
		printf(" * 삭제 성공 ! *");
	}
	else
	{
		gotoxy(35, 18);
		printf(" * 삭제 실패 *  ");
	}
	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}
	}

}

Node * managePersonSearch(List *lp, char *chp) /*코드와 이름으로 노드 찾아주기*/
{
	char temp[100];
	Node * resp; Node * pesp;
	Person sData = { NULL,"",0,0,"","" };

	gotoxy(30, 12);
	printf("* %s", chp);
	printf("할 사람의 이름을 입력하세요 : ");
	scanf("%s", temp);
	sData.name = (char *)calloc(strlen(temp) + 1, sizeof(char));
	assert(sData.name != NULL);
	strcpy(sData.name, temp);

	resp = searchNode(lp, &sData, personNameCompare);

	if (resp == NULL)
	{
		gotoxy(30, 15);
		printf(" * 존재하지 않는 이름입니다 * ");

		free(sData.name); sData.name = NULL;
		Sleep(2000);
		return NULL;
	}

	gotoxy(30, 13);
	printf("* %s", chp);
	printf("할 사람의 코드를 입력하세요 : ");
	scanf("%s", sData.code);

	pesp = searchNode(lp, &sData, personCodeCompare);

	if (pesp == NULL)
	{
		gotoxy(30, 16);
		printf(" * 존재하지 않는 코드입니다 * ");
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
		printf("이름과 코드가 일치하지 않습니다! ");
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
	printf("자동문이 열리는 시간은 05시~24시 입니다.");

	if (who->code[0] == '1') //학생의 경우
	{
		if (strcmp(today->hour, "05") == 1)
		{
			who->inout = !(who->inout);
			gotoxy(35, 20);
			printf(" * 성공! *");
		}
		else {

	
			gotoxy(35, 20);
			printf(" * 지금 시간에는 나갈 수 없습니다 *");
		}

	}
	else //관리자의 경우
	{
		who->inout = !(who->inout);
		gotoxy(35, 20);
		printf(" * 성공! *");
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
	printf(" * 받을 사람의 연락처 입력 : ");
	scanf("%s", sData.phonenumber);

	resp= searchNode(personlp, &sData, PersonPhoneNumberCompare);
	if (resp == NULL) {
		gotoxy(30, 14);
		printf("* 없는 번호입니다.");
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
		printf("* 택배 추가가 성공되었습니다. 코드는 %s 입니다!",post.postcode);

	}
	else {

		((Post *)(pesp + 1))->cnt++;
		gotoxy(30, 17);
		printf("* 택배 추가가 성공되었습니다!.");

	}


	while (1)
	{
		if (getch() == ESC)
		{
			return;
		}
	}


}
