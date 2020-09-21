
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



void managePersonSort(List *lp); /*�ڵ������ sort�ϴ� �Լ�*/
void managePerson(List *lp, TimeCheck *today, char *name);
void managePersonTotal(List *lp, TimeCheck *today, char *name); /* ��¸޴� ó�� �Լ� */
void managePersonInput(List *lp, TimeCheck *today, char *name); /* ��ϸ޴� ó�� �Լ� */
void managePersonEdit(List *lp, TimeCheck *today, char *name); /* �����޴� ó�� �Լ� */
void managePersonDelete(List *lp, TimeCheck *today, char *name); /* �����޴� ó�� �Լ� */
Node * managePersonSearch(List *lp, char *p); /*�˻� �Լ�*/
void randomNumber(char *p, size_t size); /*size��ŭ ������ �߻����� p�� �־���*/

void inoutBuilding(List *lp, TimeCheck *today, char *name, Person * who); /*���� ���� �Լ� (�л��ϰ�� �ð��� ���� ����)*/
void managePost(List *postlp,List *personlp, TimeCheck *today, char *name); /*�ù� ��� �Լ�*/
void gotoxy(int x, int y); /*Ŀ�� �ű�� �Լ�*/
