//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 데이터 구조
랩 테스트: Section E - 이진트리 문제
목적: 문제 8을 위한 필수 함수 구현 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode; // BTNode의 정의를 변경하면 안 됩니다

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;

///////////////////////// 함수 프로토타입 ////////////////////////////////////

// 이 함수들의 프로토타입을 변경하면 안 됩니다
int hasGreatGrandchild(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push(Stack *stack, BTNode *node);
BTNode *pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    char e;
    int c, value;
    BTNode *root;

    c = 1;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Find the great grandchildren of the binary tree.\n");
    printf("0: Quit;\n");

    while (c != 0)
    {
        printf("Please input your choice(1/2/0): ");
        if (scanf("%d", &c) > 0)
        {
            switch (c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                printf("\nThe values stored in all nodes of the tree that has at least one great-grandchild are: ");
                hasGreatGrandchild(root);
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {
            scanf("%c", &e);
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int hasGreatGrandchild(BTNode *node)
{
    int left, right;
    // Base case 
    if (node == NULL)
    {
        return 0;
    }

    
    left = hasGreatGrandchild(node->left) + 1;
    right = hasGreatGrandchild(node->right) + 1;

    // 왼쪽 또는 오른쪽 중 하나라도 깊이가 4 이상이면
    // 현재 노드 아래에 증손자(great-grandchild)가 있다는 뜻
    if (left > 3 || right > 3)
    {
        printf("%d\n", node->item);
    }

    return (left > right ? left : right);
    // 현재 노드 기준으로 더 깊은 쪽의 높이를 부모에게 반환
    // 30의 왼쪽 : 25는 리프의 0+1/0+1을 비교한 1이 올라옴
    // 30의 오른쪽 : 20은 0+1/0+1 -> 1리턴, 65는 1+1/0+1 -> 2리턴
    // 따라서 30에 올라가는 레벨은 1+1/2+1 -> 3 리턴
}
//////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createTree()
{
    Stack stack;
    BTNode *root, *temp;
    char s;
    int item;

    stack.top = NULL;
    root = NULL;
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if (scanf("%d", &item) > 0)
    {
        root = createBTNode(item);
        push(&stack, root);
    }
    else
    {
        scanf("%c", &s);
    }

    while ((temp = pop(&stack)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if (scanf("%d", &item) > 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c", &s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if (scanf("%d", &item) > 0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c", &s);
        }

        if (temp->right != NULL)
            push(&stack, temp->right);
        if (temp->left != NULL)
            push(&stack, temp->left);
    }
    return root;
}

void push(Stack *stack, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if (temp == NULL)
        return;
    temp->btnode = node;
    if (stack->top == NULL)
    {
        stack->top = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = stack->top;
        stack->top = temp;
    }
}

BTNode *pop(Stack *stack)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stack->top;
    if (top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stack->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode *node)
{
    if (node == NULL)
        return;

    printTree(node->left);
    printf("%d ", node->item);
    printTree(node->right);
}

void removeAll(BTNode **node)
{
    if (*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
