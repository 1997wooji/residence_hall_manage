#pragma warning(disable:4996)
#include "fullscreenmenu.h"
#include <stdio.h>
#include <windows.h>
#include "control.h"
void background();


void fullScreen(TimeCheck *today, char *name)
{

	background();
	gotoxy(6, 4);
	textcolor(15, 1);
	printf(" %s��, ������ ȯ���մϴ�!", name);
	gotoxy(60, 4);
	printf("�ڷΰ��� : ESC");
	gotoxy(60, 30);
	printf("%s %s��%s��", today->date, today->hour, today->min);
	textcolor(7, 0);
}

char menu(const char **mList, size_t menuCnt)
{
	char menuNum;
	int i;

	int j;
	gotoxy(28, 10);
	printf("���� ��  �� ��������������");
	for (j = 0; j < menuCnt * 2 + 1; j++) {
		gotoxy(28, 11 + j);
		printf("��                      ��");
	}
	gotoxy(28, 11 + menuCnt * 2 + 1);
	printf("��������������������������");

	for (i = 0; i < menuCnt; i++) {   /* �޴� ��� */
		gotoxy(30, 12 + i * 2);
		switch (i + 1) {
		case 1:printf("��"); break;
		case 2:printf("��"); break;
		case 3:printf("��"); break;
		case 4:printf("��"); break;
		case 5:printf("��"); break;
		default:;
		}
		gotoxy(32, 12 + i * 2);
		printf(" %s", mList[i]);
	}
	gotoxy(32, 12 + i * 2 + 2);

	menuNum = getch();

	return menuNum;

}

void background() {
	int k;

	gotoxy(1, 1);
	printf("��������������������������������������������< ����� ���� ���α׷� >�������������������������������������������� ");
	for (k = 0; k < 30; k++) {
		gotoxy(1, 2 + k);
		printf("��                                                                                                            ��");
	}
	gotoxy(1, 2 + k);
	printf("���������������������������������������������������������������������������������������������������������������� ");
	gotoxy(1, 5);
}
