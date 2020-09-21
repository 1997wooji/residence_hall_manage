#pragma warning (disable:4996)
#include "genericdoublelinkedlist.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>  // printf(), scanf()
#include <stdlib.h>  // malloc(), free()




//linkedlist generic �⺻�Լ�


/*----------------------------------------------------------------------------------
Function name	: createList - ���� ����Ʈ �ʱ�ȭ
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
int createList(List *lp)
{
	if (lp == NULL) {  /* lp������ NULL check */
		return FALSE; // *�׻� check���ٰ�!*
	}
	lp->head = (Node *)calloc(1,sizeof(Node));	/* head node ���� */
	if (lp->head == NULL) { //malloc���� calloc!(clear) �׻� calloc�Ұ� ��������(*����*,size)
		return FALSE;
	}
	lp->tail = (Node *)calloc(1, sizeof(Node));	/* tail node ���� */
	if (lp->tail == NULL) {
		free(lp->head);
		return FALSE;
	}

	lp->head->next = lp->tail; /* head node�� tail node ���� */
	lp->tail->prev = lp->head; 
	lp->head->prev = lp->head; /* head node�� prev�� �ڱ� �ڽ��� ����Ű���� ���� */
	lp->tail->next = lp->tail; /* tail node�� next�� �ڱ� �ڽ��� ����Ű���� ���� */
	lp->size = 0;	/* ���� ����Ʈ ũ�� 0���� �ʱ�ȭ */

	return TRUE;
}
/*----------------------------------------------------------------------------------
Function name	: addFirst - head node �ڿ� node �߰�(���� ����)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - �߰��� ������
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
int addFirst(List *lp, void * data, size_t size, void(*memCpy)(void *, void *))
{
	Node *newp;

	if (lp == NULL) { /* lp������ NULL check */
		return FALSE;
	}

	newp = (Node *)malloc(sizeof(Node)+size); /* �� ��� ���� ���(����,����)+person������ ����������� size */
	if (newp != NULL) {		/* �� ��� ���� ���� �� ó�� */
		memCpy(newp+1, data);				/* �� ��忡 data ���� */
		newp->prev = lp->head;			/* �� ����� prev ���� */
		newp->next = lp->head->next;	/* �� ����� next ���� */
		lp->head->next->prev = newp;	/* �� ����� �� ��尡 �� ��带 ����Ű���� ����*/
		lp->head->next = newp;			/* head ndoe �ڿ� �� ��� ���� */
		++lp->size;						/* ����Ʈ size ���� */
		return TRUE;
	}
	else {					/* �� ��� ���� ���� �� ó�� */
		return FALSE;
	}
}
/*----------------------------------------------------------------------------------
Function name	: addLast - tail node �տ� �� node �߰�(���� ����)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - �߰��� ������
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
int addLast(List *lp, void * data, size_t size, void (*memCpy)(void *, void *))
{
	Node *newp;	/* �� ��� �ּ������ ������ */
	
	if (lp == NULL) { /* lp������ NULL check */
		return FALSE;
	}

	newp = (Node *)calloc(1,sizeof(Node)+size);	/* �� ��� ���� */
	//generic�̹Ƿ� person size�� �������ڸ� �޾ƾ���!
	if (newp != NULL) {	/*  �� ��� ���� ���� �� ó�� */
		// newp->data = data;->�̷� �� intŸ�Կ����� ���ɤ� ���� ���� �ؾ���
		memCpy(newp+1,data);
		//***** ���� �߿� newp+1->��� �ϳ� �ǳ� �� ���¿� data�� copy�ϰԵ� *****
		/* �� ��忡 data ���� */
		newp->prev = lp->tail->prev;	/* �� ����� prev ���� */
		newp->next = lp->tail;			/* �� ����� next ���� */
		lp->tail->prev->next = newp;	/* �� ����� �� ��尡 �� ��带 ����Ű���� ���� */
		lp->tail->prev = newp;			/* tail ndoe �տ� �� ��� ���� */
		++lp->size;						/* ����Ʈ size ���� */
		return TRUE;
	}
	else {	/* �� ��� ���� ���� �� ó�� */
		return FALSE;
	}
}
/*----------------------------------------------------------------------------------
Function name	: displayList - ����Ʈ ���� ��� ������ ���
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
Returns			: ����
----------------------------------------------------------------------------------*/
void displayList(List *lp,void (*dataPrint)(void *p))
{
	Node *curp;
	if (lp == NULL) { /* lp������ NULL check */
		return;
	}

	curp = lp->head->next;  /* data �ִ� ù��带 curp�� ����Ű�� �� */
							/* ����Ʈ�� ������ ������ curp�� �ű�鼭 data���� ����ϱ� */
	while (curp != lp->tail) {
		//printf("%8d\n", curp->data);
		//��¿� �����Լ�
		dataPrint(curp+1); //data�� �����Ŷ�! data��������!
		//Node+1->�������� ������ �������� �Ѿ
		curp = curp->next;
	}
	printf("\n");
	return;
}



/*----------------------------------------------------------------------------------
Function name	: searchNode - data�� ��ġ�ϴ� ù ��° node �˻�
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
data - �˻��� ������
Returns			: ���� - �˻��� ����� �ּ� / ���� - NULL pointer
----------------------------------------------------------------------------------*/
Node * searchNode(List *lp, void *data, int(*compare)(void *, void *))
{
	Node *curp;
	if (lp == NULL) { /* lp������ NULL check */
		return NULL;
	}

	curp = lp->head->next;  /* data �ִ� ù��带 curp�� ����Ű�� �� */
							/* ����Ʈ�� ������ ������ ������ curp�� �ű�鼭 �˻��ϱ� */
	while (curp != lp->tail) {
		if (compare(curp+1,data) == 0) {
			return curp;	/* ã�� ����� �ּ� ���� */
		}
		else {
			curp = curp->next;
		}
	}
	return NULL;	/* ��ã���� NULL pointer ���� */
}
/*----------------------------------------------------------------------------------
Function name	: removeNode - data�� ��ġ�ϴ� ù ��° ��� ����
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
data - ������ ������
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
int removeNode(List *lp, void * data, int(*compare)(void *, void *), void(*dataFree)(void *))
{
	Node *delp;

	if (lp == NULL) { /* lp������ NULL check */
		return FALSE;
	}

	delp = searchNode(lp, data, compare);  /* ������ node�� �˻� �� */ //���⼭ data->pointer->�׷��ϱ� &data���� data�� ��������
	if (delp != NULL) {
		/* ������ ��带 ã������ �����ϱ� */
		/* ������ ����� �� ���� ������ ����� �� ��带 ����*/
		delp->prev->next = delp->next; 
		delp->next->prev = delp->prev;
		dataFree(delp + 1); //�߿��~~ generic���� �߿� (��� �ΰ� �޸� ����)
		free(delp);	/* ��� ���� */
		--(lp->size);	/* ����Ʈ size ���� */
		return TRUE;
	}
	else {	/* ������ ����� ��ã������ ���� ���� */
		return FALSE;
	}
}
/*----------------------------------------------------------------------------------
Function name	: sortList - ��� ����(��������)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
Returns			: ����
----------------------------------------------------------------------------------*/
void sortList(List *lp,size_t size, int(*compare)(void *, void *), void(*memCpy)(void *, void *),void (*dataFree)(void *))
{
	//sort�ÿ� ����� ��Ȯ�� �𸣴� ���� �Ҵ��ϱ����� size�� �޾ƿ�

	Node *curp;
	Node *nextp;
	void *cData;

	cData = calloc(1, size); //data��ŭ�� ����ָ�� �� ��� �߰��ϴ°� �ƴ�

	if (lp == NULL) { /* lp������ NULL check */
		return;
	}

	curp = lp->head->next;
	while (curp->next != lp->tail) {
		nextp = curp->next;
		while (nextp != lp->tail) {
			if (compare(curp + 1, nextp + 1) == 1)
			{
				memCpy(cData, curp + 1);
				memCpy(curp + 1,nextp+1);
				memCpy(nextp+1, cData); //�����͸� ��ü

			}

			nextp = nextp->next;
		}
		curp = curp->next;
	}
	dataFree(cData); //cData���� �ΰ� �޸𸮰� ������������Ŷ�
	free(cData); //�� ����!!

}
/*----------------------------------------------------------------------------------
Function name	: destroyList - ����Ʈ ���� ��� ���(head, tail ��� ����)�� ����
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
Returns			: ����
----------------------------------------------------------------------------------*/

void destroyList(List *lp, void(*dataFree)(void *))
{
	Node *curp;
	Node *nextp;
	if (lp == NULL) { /* lp������ NULL check */
		return;
	}
	curp = lp->head->next;
	while (curp != lp->tail) {
		nextp = curp->next;
		dataFree(curp+1); //������ curp+1! ������ ������ ����ų��
		free(curp); //size�� node+person �س��� �ѹ��� free!
		curp = nextp;
	}
	free(lp->head);
	free(lp->tail);

	lp->head = lp->tail = NULL;
	lp->size = 0;
	return;
}