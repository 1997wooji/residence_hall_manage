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

char menu(const char **mList, size_t menuCnt);	/* 메뉴 출력 및 메뉴번호 입력 함수 */
void login(Admin *admin, Room(*room)[ROOMS], List *lp, TimeCheck *today,FILE *datep); /*로그인 함수*/
void fullScreen(TimeCheck *today,char *name); /*스크린 출력 함수*/
void manageMode(Admin *admin, Room(*room)[ROOMS], List *lp, TimeCheck * today, char * name,Person * manager); /*매니저모드*/
void studentMode(Admin *admin, Room(*room)[ROOMS],List *lp, TimeCheck *today, char *name, Person *student); /*학생 모드*/
void allFileAdd(List *lp, FILE *fp); /* 시작시 리스트에 파일에서부터 읽어온 사람 정보 저장*/
void allFileEnd(List *lp, FILE *fp); /* 종료시 파일에 리스트에서부터 읽어온 사람 정보 저장*/
void allFileAddFood(List *lp, FILE *fp);/*시작시 리스트에 파일에서부터 읽어온 식단 저장*/


int main()
{

	FILE * fp = fopen("C:\\data\\residence\\person.txt", "rt");
	FILE * fp3 = fopen("C:\\data\\residence\\food.txt", "rt");
	List residensoong[3];
	Admin admin = { 18, 18, 5, 18, 6 };
	Room room[LAYERS][ROOMS];


	/*{인원관리, 택배 관리, 식단 관리}*/

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

	destroyList(&(residensoong[0]), personClear);	/* 리스트내의 모든 데이터 삭제 */
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
		i=timecheck(today, datep); //로그인 할때마다 시간이 바뀌어 달라지는 기숙사를 볼 수 있음.
		if (i == 0) return;
		checkUptime(admin, room, today->hour, today->min);

		system("cls");
		gotoxy(35, 8);
		printf("<기숙사 관리 프로그램>");

		resp = managePersonSearch(&(residensoong[0]), "로그인");

		if (resp != NULL)
			strcpy(name, ((Person *)(resp+1))->name);
		else break;

			if (((Person *)(resp + 1))->code[0] == '2')
				manageMode(admin, room, residensoong, today, name, ((Person *)(resp + 1)));
			else if (((Person *)(resp + 1))->code[0] == '1')
				studentMode(admin, room, residensoong,today, name, ((Person *)(resp + 1)));
			else {
				gotoxy(35, 20);
				printf(" * 외부인은 들어갈 수 없습니다 *");
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
		free(inData.name); //메모리 누수 방지
		inData.name = NULL; 

	}

	return;

}

void allFileEnd(List *lp, FILE *fp)
{
	Node *curp;
	Person inData = { NULL,"",1,0,"","" };

	if (lp == NULL) { /* lp포인터 NULL check */
		return;
	}
	curp = lp->head->next;
	while (curp != lp->tail) {
		personMemcpy(&inData,curp+1);
		fprintf(fp, "%s %s %d %d %s %s\n",inData.name,inData.code, inData.inout, inData.room, inData.phonenumber, inData.registrationDate);
		curp=curp->next;
	}

	free(inData.name); /*메모리 누수 주의!*/
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
	const char *menuList[] = { "인원 관리","건물 관리","택배 등록","식단 관리", "출　 　입" };
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
		case '1': managePerson(&(lp[0]), today, name); break;		/* 인원관리 실행 */
		case '2': manageBuilding(admin, room, today, name); break;		/* 건물관리 실행 */
		case '3': managePost(&(lp[1]),&(lp[0]),today,name); break;		/* 택배등록 실행 */
		case '4': manageFood(&(lp[2]), today, name); break;		/* 식단 관리 실행 */
		case '5':inoutBuilding(&(lp[0]), today, name,manager); break; /*출입 실행*/
		case ESC: return;												/*  뒤로가기 */
		}
	}
	
}

void studentMode(Admin *admin, Room(*room)[ROOMS],List *lp,TimeCheck *today, char *name, Person *student)
{
	const char *menuList[] = { "내 정보 관리","냉난방 설정","내 택배 확인","식단 확인", "출　 　입" };
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
		case '1': checkMyInform(&(lp[0]), student, today, name); break;		/* 내 정보 관리 실행 */
		case '2': manageBuildingStudent(admin, room,student, today, name); break;		/* 냉난방 설정 실행 */
		case '3': checkMyPost(&(lp[1]), student, today, name); break;		/* 택배확인 실행 */
		case '4':showFood(&(lp[2]), today, name); break;		/* 식단 확인 실행 */
		case '5':inoutBuilding(&(lp[0]), today, name, student); break; /*출입 실행*/
		case ESC: return;												/*  뒤로가기 */
		}
	}


}