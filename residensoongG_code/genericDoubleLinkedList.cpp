#pragma warning (disable:4996)
#include "genericdoublelinkedlist.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>  // printf(), scanf()
#include <stdlib.h>  // malloc(), free()




//linkedlist generic 기본함수


/*----------------------------------------------------------------------------------
Function name	: createList - 연결 리스트 초기화
Parameters		: lp - 리스트 관리 구조체의 주소
Returns			: 성공 - TRUE / 실패 - FALSE
----------------------------------------------------------------------------------*/
int createList(List *lp)
{
	if (lp == NULL) {  /* lp포인터 NULL check */
		return FALSE; // *항상 check해줄것!*
	}
	lp->head = (Node *)calloc(1,sizeof(Node));	/* head node 생성 */
	if (lp->head == NULL) { //malloc말고 calloc!(clear) 항상 calloc할것 전달인자(*개수*,size)
		return FALSE;
	}
	lp->tail = (Node *)calloc(1, sizeof(Node));	/* tail node 생성 */
	if (lp->tail == NULL) {
		free(lp->head);
		return FALSE;
	}

	lp->head->next = lp->tail; /* head node와 tail node 연결 */
	lp->tail->prev = lp->head; 
	lp->head->prev = lp->head; /* head node의 prev는 자기 자신을 가리키도록 설정 */
	lp->tail->next = lp->tail; /* tail node의 next는 자기 자신을 가리키도록 설정 */
	lp->size = 0;	/* 연결 리스트 크기 0으로 초기화 */

	return TRUE;
}
/*----------------------------------------------------------------------------------
Function name	: addFirst - head node 뒤에 node 추가(역순 저장)
Parameters		: lp - 리스트 관리 구조체의 주소
				  data - 추가할 데이터
Returns			: 성공 - TRUE / 실패 - FALSE
----------------------------------------------------------------------------------*/
int addFirst(List *lp, void * data, size_t size, void(*memCpy)(void *, void *))
{
	Node *newp;

	if (lp == NULL) { /* lp포인터 NULL check */
		return FALSE;
	}

	newp = (Node *)malloc(sizeof(Node)+size); /* 새 노드 생성 노드(꼬리,테일)+person데이터 저장까지위해 size */
	if (newp != NULL) {		/* 새 노드 생성 성공 시 처리 */
		memCpy(newp+1, data);				/* 새 노드에 data 저장 */
		newp->prev = lp->head;			/* 새 노드의 prev 설정 */
		newp->next = lp->head->next;	/* 새 노드의 next 설정 */
		lp->head->next->prev = newp;	/* 새 노드의 뒷 노드가 새 노드를 가리키도록 설정*/
		lp->head->next = newp;			/* head ndoe 뒤에 새 노드 연결 */
		++lp->size;						/* 리스트 size 증가 */
		return TRUE;
	}
	else {					/* 새 노드 생성 실패 시 처리 */
		return FALSE;
	}
}
/*----------------------------------------------------------------------------------
Function name	: addLast - tail node 앞에 새 node 추가(정순 저장)
Parameters		: lp - 리스트 관리 구조체의 주소
				  data - 추가할 데이터
Returns			: 성공 - TRUE / 실패 - FALSE
----------------------------------------------------------------------------------*/
int addLast(List *lp, void * data, size_t size, void (*memCpy)(void *, void *))
{
	Node *newp;	/* 새 노드 주소저장용 포인터 */
	
	if (lp == NULL) { /* lp포인터 NULL check */
		return FALSE;
	}

	newp = (Node *)calloc(1,sizeof(Node)+size);	/* 새 노드 생성 */
	//generic이므로 person size를 전달인자를 받아야함!
	if (newp != NULL) {	/*  새 노드 생성 성공 시 처리 */
		// newp->data = data;->이런 건 int타입에서나 가능ㅋ 깊은 복사 해야함
		memCpy(newp+1,data);
		//***** 정말 중요 newp+1->노드 하나 건너 뛴 상태에 data를 copy하게됨 *****
		/* 새 노드에 data 저장 */
		newp->prev = lp->tail->prev;	/* 새 노드의 prev 설정 */
		newp->next = lp->tail;			/* 새 노드의 next 설정 */
		lp->tail->prev->next = newp;	/* 새 노드의 앞 노드가 새 노드를 가리키도록 설정 */
		lp->tail->prev = newp;			/* tail ndoe 앞에 새 노드 연결 */
		++lp->size;						/* 리스트 size 증가 */
		return TRUE;
	}
	else {	/* 새 노드 생성 실패 시 처리 */
		return FALSE;
	}
}
/*----------------------------------------------------------------------------------
Function name	: displayList - 리스트 내의 모든 데이터 출력
Parameters		: lp - 리스트 관리 구조체의 주소
Returns			: 없음
----------------------------------------------------------------------------------*/
void displayList(List *lp,void (*dataPrint)(void *p))
{
	Node *curp;
	if (lp == NULL) { /* lp포인터 NULL check */
		return;
	}

	curp = lp->head->next;  /* data 있는 첫노드를 curp로 가리키게 함 */
							/* 리스트의 마지막 노드까지 curp를 옮기면서 data영역 출력하기 */
	while (curp != lp->tail) {
		//printf("%8d\n", curp->data);
		//출력용 보조함수
		dataPrint(curp+1); //data만 찍을거라서! data만찍어야햇!
		//Node+1->노드다음인 데이터 영역으로 넘어감
		curp = curp->next;
	}
	printf("\n");
	return;
}



/*----------------------------------------------------------------------------------
Function name	: searchNode - data와 일치하는 첫 번째 node 검색
Parameters		: lp - 리스트 관리 구조체의 주소
data - 검색할 데이터
Returns			: 성공 - 검색된 노드의 주소 / 실패 - NULL pointer
----------------------------------------------------------------------------------*/
Node * searchNode(List *lp, void *data, int(*compare)(void *, void *))
{
	Node *curp;
	if (lp == NULL) { /* lp포인터 NULL check */
		return NULL;
	}

	curp = lp->head->next;  /* data 있는 첫노드를 curp로 가리키게 함 */
							/* 리스트의 마지막 데이터 노드까지 curp를 옮기면서 검색하기 */
	while (curp != lp->tail) {
		if (compare(curp+1,data) == 0) {
			return curp;	/* 찾은 노드의 주소 리턴 */
		}
		else {
			curp = curp->next;
		}
	}
	return NULL;	/* 못찾으면 NULL pointer 리턴 */
}
/*----------------------------------------------------------------------------------
Function name	: removeNode - data와 일치하는 첫 번째 노드 삭제
Parameters		: lp - 리스트 관리 구조체의 주소
data - 삭제할 데이터
Returns			: 성공 - TRUE / 실패 - FALSE
----------------------------------------------------------------------------------*/
int removeNode(List *lp, void * data, int(*compare)(void *, void *), void(*dataFree)(void *))
{
	Node *delp;

	if (lp == NULL) { /* lp포인터 NULL check */
		return FALSE;
	}

	delp = searchNode(lp, data, compare);  /* 삭제할 node를 검색 함 */ //여기서 data->pointer->그러니까 &data말고 data를 보내야함
	if (delp != NULL) {
		/* 삭제할 노드를 찾았으면 삭제하기 */
		/* 삭제할 노드의 앞 노드와 삭제할 노드의 뒷 노드를 연결*/
		delp->prev->next = delp->next; 
		delp->next->prev = delp->prev;
		dataFree(delp + 1); //중요띠~~ generic에서 중요 (노드 부가 메모리 해제)
		free(delp);	/* 노드 삭제 */
		--(lp->size);	/* 리스트 size 감소 */
		return TRUE;
	}
	else {	/* 삭제할 노드의 못찾았으면 삭제 실패 */
		return FALSE;
	}
}
/*----------------------------------------------------------------------------------
Function name	: sortList - 노드 정렬(오름차순)
Parameters		: lp - 리스트 관리 구조체의 주소
Returns			: 없음
----------------------------------------------------------------------------------*/
void sortList(List *lp,size_t size, int(*compare)(void *, void *), void(*memCpy)(void *, void *),void (*dataFree)(void *))
{
	//sort시에 사이즈를 정확히 모르니 동적 할당하기위해 size를 받아옴

	Node *curp;
	Node *nextp;
	void *cData;

	cData = calloc(1, size); //data만큼만 잡아주면됨 새 노드 추가하는게 아님

	if (lp == NULL) { /* lp포인터 NULL check */
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
				memCpy(nextp+1, cData); //데이터만 교체

			}

			nextp = nextp->next;
		}
		curp = curp->next;
	}
	dataFree(cData); //cData에도 부가 메모리가 만들어져있을거라서
	free(cData); //꼭 해제!!

}
/*----------------------------------------------------------------------------------
Function name	: destroyList - 리스트 내의 모든 노드(head, tail 노드 포함)를 삭제
Parameters		: lp - 리스트 관리 구조체의 주소
Returns			: 없음
----------------------------------------------------------------------------------*/

void destroyList(List *lp, void(*dataFree)(void *))
{
	Node *curp;
	Node *nextp;
	if (lp == NULL) { /* lp포인터 NULL check */
		return;
	}
	curp = lp->head->next;
	while (curp != lp->tail) {
		nextp = curp->next;
		dataFree(curp+1); //무조건 curp+1! 데이터 영역을 가리킬것
		free(curp); //size를 node+person 해놓음 한번에 free!
		curp = nextp;
	}
	free(lp->head);
	free(lp->tail);

	lp->head = lp->tail = NULL;
	lp->size = 0;
	return;
}