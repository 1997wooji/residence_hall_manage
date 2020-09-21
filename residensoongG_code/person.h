
#pragma once

typedef struct _person
{
	char *name;
	char code[5];
	int inout;
	int room;
	char phonenumber[16];
	char registrationDate[9];
	

}Person;


void personMemcpy(void *p1, void *p2); //p2->p1���� ����
void personClear(void *p); // �޸� ����, �ʱ�ȭ
void personPrint(void *p); // ����ü ��� �� ��� ����Ʈ
int personNameCompare(void *p1, void *p2); // p1���� ũ�� 1 ���� 0 ���� -1
int personCodeCompare(void *p1, void *p2);
int PersonPhoneNumberCompare(void *p1, void *p2);
int personRoomCompare(void *p1, void *p2);
int personDayCompare(void *p1, void *p2);


/* ���� �Լ� ������ ��
void (*memCpy)(void *, void *);
int (*compare)(void *, void *);
void (*dataPrint)(void *);
void (*dataFree)(void *); */

