//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 데이터 구조
랩 테스트: Section A - 연결 리스트 문제
목적: 문제 2를 위한 필수 함수 구현 */

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

//////////////////////// 함수 프로토타입 /////////////////////////////////////

// 이 함수의 프로토타입을 변경하면 안 됩니다
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	// 연결 리스트 1을 빈 연결 리스트로 초기화합니다
	ll1.head = NULL;
	ll1.size = 0;

	// 연결 리스트 2를 빈 연결 리스트로 초기화합니다
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: 연결 리스트 1에 정수 삽입:\n");
	printf("2: 연결 리스트 2에 정수 삽입:\n");
	printf("3: 번갈아 병합된 연결 리스트 생성:\n");
	printf("0: 종료:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
			printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // 이 함수를 코드해야 합니다
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	// 첫 번째 리스트가 두 번째 리스트보다 클 때, 두 번째 리스트는 비어 있어야 한다
	/* List1 = 1,2,3	List2 = 4,5,6,7 
	   List1 = 1,4,2,5,3,6	List2 = 7
	*/
	ListNode *cur2;
	int s = ll1->size;
	int index=1;

	cur2 = ll2->head;

	while (s && cur2 != NULL){
		
		insertNode(ll1, index, cur2->item);
		cur2 = cur2->next;
		removeNode(ll2, 0);

		index += 2;
		s --;

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
