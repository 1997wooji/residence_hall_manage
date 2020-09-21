
#pragma once


#include <stdio.h>
#include "genericdoublelinkedlist.h"
#include "timecheck.h"
#include "person.h"
#include "fullscreenmenu.h"
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <conio.h>
#include <windows.h>



void managePersonSort(List *lp); /*코드순으로 sort하는 함수*/
void managePerson(List *lp, TimeCheck *today, char *name);
void managePersonTotal(List *lp, TimeCheck *today, char *name); /* 출력메뉴 처리 함수 */
void managePersonInput(List *lp, TimeCheck *today, char *name); /* 등록메뉴 처리 함수 */
void managePersonEdit(List *lp, TimeCheck *today, char *name); /* 수정메뉴 처리 함수 */
void managePersonDelete(List *lp, TimeCheck *today, char *name); /* 삭제메뉴 처리 함수 */
Node * managePersonSearch(List *lp, char *p); /*검색 함수*/
void randomNumber(char *p, size_t size); /*size만큼 난수를 발생시켜 p에 넣어줌*/

void inoutBuilding(List *lp, TimeCheck *today, char *name, Person * who); /*출입 관리 함수 (학생일경우 시간에 따라 제약)*/
void managePost(List *postlp,List *personlp, TimeCheck *today, char *name); /*택배 등록 함수*/
void gotoxy(int x, int y); /*커서 옮기기 함수*/
