#include "food.h"
#define X_NUM 5
#define Y_NUM 10
#define ESC 27

void manageFood(List *lp, TimeCheck *today, char *name) {
	system("cls");
	const char *menuList[] = { "�Ĵ� Ȯ��","�Ĵ� ����"};
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
		case '1': showFood(lp, today, name); break;		/* �Է¸޴� ���� */
		case '2': editFood(lp, today, name); break;		/* ��¸޴� ���� */
		case ESC:break;
		}
	}
	
}
void showFood(List *lp, TimeCheck *today, char *name) {
	system("cls");
	fullScreen(today, name);

	displayFoodList(lp, today, foodPrint);
	gotoxy(X_NUM + 12, Y_NUM + 12);
	printf("�ƹ�Ű�� ������ �ڷ� ���ư��ϴ�.");
	getch();
}
void editFood(List *lp, TimeCheck *today, char *name) {
	system("cls");
	fullScreen(today, name);
	Food temp = { "","","","","","","" };
	Node *resp;
	int i;
	gotoxy(X_NUM + 10, Y_NUM );
	printf("������ �Ĵ��� ��¥�� �Է��ϼ���(YYYYDDMM) : ");
	scanf("%s", &temp.day);
	gotoxy(X_NUM + 10, Y_NUM + 2);
	printf("�Ĵ��� �Է��Ͻÿ� : ");
	for (i = 0; i < 6; i++) {
		gotoxy(X_NUM + 30, Y_NUM + 2 + i);
		scanf("%s", temp.food[i]);
	}
	resp = searchNode(lp, &temp, foodDayCompare);
	foodMemcpy(resp + 1, &temp);
	gotoxy(X_NUM + 10, Y_NUM + 10);
	printf("* ���� �Ϸ�! *");
	gotoxy(X_NUM + 12, Y_NUM + 12);
	printf("�ƹ�Ű�� ������ �ڷ� ���ư��ϴ�.");
	getch();
}
void foodMemcpy(void *p1, void *p2) 
{
	int i;
	strcpy(((Food *)p1)->day, ((Food *)p2)->day);
	for (i = 0; i < 6; i++) {
		strcpy(((Food *)p1)->food[i], ((Food *)p2)->food[i]);
	}
	return;
}
void foodPrint(void *p) // ����ü ��� �� ��� ����Ʈ
{
	static int k = 0;
	
	if (k == 20 * 4) k = 0;
	gotoxy(X_NUM + k, Y_NUM -2);
	printf("%s", ((Food *)p)->day);
	for (int j = 0; j < 6; ++j) {
		gotoxy(X_NUM + k, Y_NUM + j);
		printf("%s", ((Food *)p)->food[j]);
	}
	k += 20;
}
int foodDayCompare(void *p1, void *p2) {
	if (strcmp(((Food *)p1)->day, ((Food *)p2)->day) == 0)
		return 0;
	else return -1;
}

void displayFoodList(List *lp, TimeCheck *today, void(*dataPrint)(void *p))
{
	Node *resp;
	resp = searchNode(lp, today, foodDayCompare);
	int i = 0;
	if (lp == NULL) { 
		return;
	}
	while (i < 4) {   // 4��ġ ���
		dataPrint(resp + 1); 
		resp = resp->next;
		i++;
	}
	printf("\n");
	return;
}

void foodClear(void *p)
{
	memset(((Food*)p)->day, 0, strlen(((Food *)p)->day));
	memset(((Food *)p)->food[0], 0, strlen(((Food *)p)->food[0]));
	memset(((Food *)p)->food[1], 0, strlen(((Food *)p)->food[1]));
	memset(((Food *)p)->food[2], 0, strlen(((Food *)p)->food[2]));
	memset(((Food *)p)->food[3], 0, strlen(((Food *)p)->food[3]));
	memset(((Food *)p)->food[4], 0, strlen(((Food *)p)->food[4]));
	memset(((Food *)p)->food[5], 0, strlen(((Food *)p)->food[5]));
}