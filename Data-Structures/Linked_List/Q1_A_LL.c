//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 데이터 구조
랩 테스트: Section A - 연결 리스트 문제
목적: 문제 1을 위한 필수 함수 구현 */

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
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() 함수 ///////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	// 연결 리스트 1을 빈 연결 리스트로 초기화합니다
	ll.head = NULL;
	ll.size = 0;

	printf("1: 정렬된 연결 리스트에 정수를 삽입:\n");
	printf("2: 가장 최근에 입력한 값의 인덱스 출력:\n");
	printf("3: 정렬된 연결 리스트 출력:\n");
	printf("0: 종료:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			// removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	// 올바른 위치에 노드 삽입 
	// Item : 새롭게 추가할 노드

	ListNode *cur = ll->head;
	int index = 0;

	// 
	while (cur != NULL) {
		if (cur->item == item)
		{
			return -1;
		}
		else if (cur->item < item) {
			cur = cur->next;
			index ++;
		} else {
			break;
		}
	}
	insertNode(ll, index, item);
	return index;
	
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
