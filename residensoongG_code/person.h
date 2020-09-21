
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


void personMemcpy(void *p1, void *p2); //p2->p1으로 복사
void personClear(void *p); // 메모리 해제, 초기화
void personPrint(void *p); // 구조체 멤버 값 모두 프린트
int personNameCompare(void *p1, void *p2); // p1성명 크면 1 같음 0 작음 -1
int personCodeCompare(void *p1, void *p2);
int PersonPhoneNumberCompare(void *p1, void *p2);
int personRoomCompare(void *p1, void *p2);
int personDayCompare(void *p1, void *p2);


/* 보조 함수 포인터 명
void (*memCpy)(void *, void *);
int (*compare)(void *, void *);
void (*dataPrint)(void *);
void (*dataFree)(void *); */

