//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 데이터 구조
랩 테스트: Section C - 스택과 데주 문제
목적: 문제 7을 위한 필수 함수 구현 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000

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

typedef struct stack
{
	LinkedList ll;
} Stack; // Stack의 정의를 변경하면 안 됩니다

//////////////////////// 함수 프로토타입 /////////////////////////////////////

// 이 함수들의 프로토타입을 변경하면 안 됩니다
int balanced(char *expression);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	char ch, str[256];
	int c, i;
	c = 1;

	LinkedList ll;
	Stack s;

	// 연결 리스트를 빈 연결 리스트로 초기화합니다
	ll.head = NULL;
	ll.size = 0;

	// 스택을 빈 스택으로 초기화합니다
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Enter a string:\n");
	printf("2: Check whether expressions comprised of the characters ()[]{} is balanced:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Enter expressions without spaces to check whether it is balanced or not: ");
			scanf("%s", str);
			break;
		case 2:
			if (balanced(str))
				printf("not balanced!\n");
			else
				printf("balanced!\n");
			break;
		case 0:
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

////////////////////////////////////////////////////////////
int balanced(char *expression)
{
	Stack s;
	s.ll.head = NULL;
	s.ll.size = 0;

	char *cur = expression;

	// 문자열의 마지막을 만나기 전까지 반복
	while (*cur != '\0')
	{
		// 여는 괄호들은 스택에 넣기
		if (*cur == '(' || *cur == '[' || *cur == '{') {
			push(&s, *cur);
		}
		// 닫는 괄호를 만났을 때
		else if (*cur == ')' || *cur == ']' || *cur == '}'){
			// 스택에서 마지막 원소가 ( 이면서 현재 들어온 원소가 ) 라면 균형
			if (peek(&s) == '(' && *cur == ')') {
				pop(&s);		// 원소 삭제
			} else if (peek(&s) == '{' && *cur == '}') {
				pop(&s);
			} else if (peek(&s) == '[' && *cur == ']') {
				pop(&s);
			} else {
				return 0;
			}
		}
		cur ++;		
	}

	return !isEmptyStack(&s);	// 스택이 모두 비어있다면 모두 짝이 맞은것 
	
}

////////////////////////////////////////////////////////////

void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
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

/////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int peek(Stack *s)
{
	if (isEmptyStack(s))
		return MIN_INT;
	else
		return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}

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

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
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

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
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
