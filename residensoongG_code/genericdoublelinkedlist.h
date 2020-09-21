#pragma once
#pragma warning (disable:4996)

#define FALSE 0
#define TRUE 1
//enum BOOL { FALSE, TRUE };




//doublelinkedlistƯ¡->����������� ���� ���ϴ� ��ŭ �߰��ϰ� �� �� ����

typedef struct _node Node;	/* ����ü ��� ���������� */
struct  _node {				/* ��� ����ü (�ڱ����� ����ü ���) */
	Node *prev;				/* �� ��带 ����Ű�� ������ */
	//generic code-> data�� ���� stack�� ��� ������ �Է¹޾� ũ�Ⱑ Ȯ�������� �̰� �׷�������.
	Node *next;				/* �� ��带 ����Ű�� ������ */
};

typedef  struct  _list {	/* ���� ����Ʈ ���� ����ü */
	Node *head;				/* head pointer (head node ����Ŵ) */
	Node *tail; 			/* tail pointer (tail node ����Ŵ) */
	int size;				/* ���� ����Ʈ�� ũ�� - ���� data node�� ���� */
}List;


int createList(List *lp);					/* ���� ����Ʈ �ʱ�ȭ */
int addFirst(List *lp, void * data, size_t size, void (*memCpy)(void *, void *));	/* head node �ڿ� node �߰�(���� ����) */
int addLast(List *lp, void * data, size_t size, void (*memCpy)(void *, void *));			/* tail node �տ� node �߰�(���� ����) */
void displayList(List *lp, void (*dataPrint)(void *p));					/* ����Ʈ ���� ��� ������ ��� */



int removeNode(List *lp, void * data, int(*compare)(void *, void *),void(*dataFree)(void *) );		/* data ��� ���� */
Node * searchNode(List *lp, void *data,int(*compare)(void *, void *));		/* data�� ��ġ�ϴ� node �˻� */
void sortList(List *lp, size_t size,int(*compare)(void *, void *), void(*memCpy)(void *, void *),void (*dataFree)(void *));		/* ��� ���� - �������� */
void destroyList(List *lp, void(*dataFree)(void *));					/* ����Ʈ ���� ��� ��带 ���� */
