//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 데이터 구조
랩 테스트: Section A - 연결 리스트 문제
목적: 문제 5를 위한 필수 함수 구현 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode; // ListNode의 정의를 변경하면 안 됩니다

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList; // LinkedList의 정의를 변경하면 안 됩니다

///////////////////////// 함수 프로토타입 ////////////////////////////////////

// 이 함수의 프로토타입을 변경하면 안 됩니다
void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	// 연결 리스트를 빈 연결 리스트로 초기화합니다
	ll.head = NULL;
	ll.size = 0;
	c = 1;

	// front 리스트를 빈 연결 리스트로 초기화합니다
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// back 리스트를 빈 연결 리스트로 초기화합니다
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // 이 함수를 코드해야 합니다
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	/*
	 	단일 연결 리스트를 앞부분과 뒷부분으로 나누는 함수 frontBackSplitLL()을 작성해 주시기 바랍니다.
		원소의 개수가 홀수라면, 추가된 원소는 앞쪽 리스트에 위치해야 합니다.
		list = 1,2,3,4,5
		frontList = 1,2,3
		backList = 4,5
		5/2 = 2 인덱스 나누기 하면 됨.
		인덱스가 front 구간이면 프론트에 삽입, back이면 back에 삽입
	*/
	ListNode *cur;
	cur = ll->head;
	// 1 2 3 4 라면 2, 1 2 3 4 5 라면 3 이 나옴
	int frontCount = (ll->size + 1) / 2;
	int front_index = 0;
	int back_index = 0;

	while(cur != NULL) {
		int value = cur->item;
		cur = cur->next;
		// while 문 돌다가 front_index가 frontCount와 같아졌다면 프론트에 들어갈 원소를 모두 넣은것, 나머지는 백에 넣어야함
		if (front_index < frontCount) {
			insertNode(resultFrontList, front_index, value);
			front_index++;
		} else {
			insertNode(resultBackList, back_index, value);
			back_index++;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index)
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 빈 리스트이거나 첫 번째 노드를 삽입하는 경우, head 포인터를 업데이트해야 합니다
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// 목표 위치 이전의 노드를 찾습니다
	// 새 노드를 생성하고 링크를 다시 연결합니다
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// 제거할 수 있는 최대 인덱스는 size-1입니다
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 번째 노드를 제거하는 경우, head 포인터를 업데이트해야 합니다
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// 목표 위치 이전과 이후 노드를 찾습니다
	// 목표 노드를 해제하고 링크를 다시 연결합니다
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
