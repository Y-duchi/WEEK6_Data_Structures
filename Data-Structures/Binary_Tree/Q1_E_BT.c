//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 데이터 구조
랩 테스트: Section E - 이진트리 문제
목적: 문제 1을 위한 필수 함수 구현 */

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
int identical(BTNode *tree1, BTNode *tree2);

BTNode *createBTNode(int item);

BTNode *createTree();
void push(Stack *stk, BTNode *node);
BTNode *pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c, s;
    char e;
    BTNode *root1, *root2;

    root1 = NULL;
    root2 = NULL;
    c = 1;

    printf("1: Create a binary tree1.\n");
    printf("2: Create a binary tree2.\n");
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    while (c != 0)
    {
        printf("Please input your choice(1/2/3/0): ");
        if (scanf("%d", &c) > 0)

        {

            switch (c)
            {
            case 1:
                removeAll(&root1);
                printf("Creating tree1:\n");
                root1 = createTree();
                printf("The resulting tree1 is: ");
                printTree(root1);
                printf("\n");
                break;
            case 2:
                removeAll(&root2);
                printf("Creating tree2:\n");
                root2 = createTree();
                printf("The resulting tree2 is: ");
                printTree(root2);
                printf("\n");
                break;
            case 3:
                s = identical(root1, root2);
                if (s)
                {
                    printf("Both trees are structurally identical.\n");
                }
                else
                {
                    printf("Both trees are different.\n");
                }
                removeAll(&root1);
                removeAll(&root2);
                break;
            case 0:
                removeAll(&root1);
                removeAll(&root2);
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

int identical(BTNode *tree1, BTNode *tree2)

{
    /* 두 이진트리가 모두 비어있거나, 왼쪽과 오른쪽 하위트리가 모두 비어있지 않고, 값이 같으면 -> 이진트리
        동일한 경우 return 1
        아니면 Return 0
    */

    // 트리가 둘 다 비어있다면 Return 1
    if (tree1 == NULL && tree2 == NULL) {
        return 1;
    }
    // 둘 중 하나라도 Null이라면 return 0
    if (tree1 == NULL || tree2 == NULL)
    {
        return 0;
    }
    // 트리의 아이템이 같은지 같지 않은지 확인
    if (tree1->item != tree2->item)
    {
        return 0;
    }
 
    // 트리의 왼쪽 오른쪽을 재귀를 통해 탐색
    return identical(tree1->left, tree2->left) && identical(tree1->right, tree2->right);
}

/////////////////////////////////////////////////////////////////////////////////

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
    Stack stk;
    BTNode *root, *temp;
    char s;
    int item;

    stk.top = NULL;
    root = NULL;

    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if (scanf("%d", &item) > 0)
    {
        root = createBTNode(item);
        push(&stk, root);
    }
    else
    {
        scanf("%c", &s);
    }

    while ((temp = pop(&stk)) != NULL)
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
            push(&stk, temp->right);
        if (temp->left != NULL)
            push(&stk, temp->left);
    }
    return root;
}

void push(Stack *stk, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if (temp == NULL)
        return;
    temp->btnode = node;
    if (stk->top == NULL)
    {
        stk->top = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = stk->top;
        stk->top = temp;
    }
}

BTNode *pop(Stack *stk)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stk->top;
    if (top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stk->top = temp;
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
