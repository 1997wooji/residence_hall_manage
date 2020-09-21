#pragma warning (disable:4996)

#include "person.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>
#include <windows.h>
#include <assert.h>

int personNameCompare(void *vp1, void *vp2)
{
	if( strcmp(((Person *)vp1)->name,((Person *)vp2)->name)==0)
		return 0;
	else return -1;

}

int personCodeCompare(void *p1, void *p2)
{
	if (strcmp(((Person *)p1)->code, ((Person *)p2)->code) == 0)
		return 0;
	else if (strcmp(((Person *)p1)->code, ((Person *)p2)->code) == 1) return 1;
	else return -1;

}

int PersonPhoneNumberCompare(void *vp1, void *vp2)
{
	if( strcmp(((Person *)vp1)->phonenumber,((Person *)vp2)->phonenumber)==0)
		return 0;
	else return -1;

}

int personRoomCompare(void *p1, void *p2)
{
	if (((Person *)p1)->room == ((Person *)p2)->room)
		return 0;
	else return -1;
}

int personDayCompare(void *p1, void *p2)
{
	if (strcmp(((Person *)p1)->registrationDate, ((Person *)p2)->registrationDate) == 0)
		return 0;
	else return -1;

}


// ����ü �����Լ�


void personMemcpy(void *p1, void *p2) //p2->p1���� ����
{

	if(((Person *)p1)->name!=NULL)
	{
		memset(((Person *)p1)->name,0,strlen(((Person *)p1)->name));
		free(((Person *)p1)->name);
		((Person *)p1)->name=NULL;
	}

	((Person *)p1)->name = (char *)calloc(1,strlen(((Person *)p2)->name)+1);
	//strlen(((Person *)p2)->name)+1 �ٺ����� strel()�ȿ� +1���� ����......
		assert(((Person *)p1)->name!=NULL);
		strcpy(((Person *)p1)->name,((Person *)p2)->name);

		((Person *)p1)->inout = ((Person *)p2)->inout;
		((Person *)p1)->room=((Person *)p2)->room;
		strcpy(((Person *)p1)->code, ((Person *)p2)->code);
		strcpy(((Person *)p1)->phonenumber,((Person *)p2)->phonenumber);
		strcpy(((Person *)p1)->registrationDate, ((Person *)p2)->registrationDate);

		return;

}

void personClear(void *p) // �޸� ����(�̸�), �ʱ�ȭ
{


	if (((Person *)p)->name != NULL)
	{ //NULL�� �ƴ� ���->���� �޸� �Ҵ�� ���
		memset(((Person *)p)->name, 0, strlen(((Person *)p)->name));
		free(((Person *)p)->name);
		((Person *)p)->name=NULL;
	}

	((Person *)p)->inout=0;
	((Person *)p)->room = 0;
	memset(((Person *)p)->code, 0, strlen(((Person *)p) -> code));
	memset(((Person *)p)->phonenumber, 0, strlen(((Person *)p)->phonenumber));
	memset(((Person *)p)->registrationDate, 0, strlen(((Person *)p)->registrationDate));
}

void personPrint(void *p) // ����ü ��� �� ��� ����Ʈ
{
	printf("\t");
	if ((((Person *)p)->code)[0] == '1') printf("%6s", "�л�");
	else if ((((Person *)p)->code)[0] == '2') printf("%6s", "������");
	else printf("%6s", "�ܺ���");

	printf("%12s%6s", ((Person *)p)->name, ((Person *)p)->code);

	if (((Person *)p)->inout == 0) printf("%5s", "out");
	else printf("%5s", "in");

	if ((((Person *)p)->code)[0] == '1') printf("%6d", ((Person *)p)->room);
	else printf("%6s", "-");
	
	printf("%16s %9s\n", ((Person *)p)->phonenumber, ((Person *)p)->registrationDate);

}
