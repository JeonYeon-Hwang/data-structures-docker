//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);
void removeAndRearrayTree(BSTNode *node, BSTNode *prev);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 3:
			printf("Input an integer that you want to remove from the Binary Search Tree: ");
			scanf("%d", &i);
			removeNodeFromTree(root, i);
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root){
	Stack s1;
	Stack s2;
	BSTNode *node = root;

	s1.top = 0;
	s2.top = 0;

	push(&s1, node);

	while(!isEmpty(&s1)){
		node = pop(&s1);
		push(&s2, node);

		if(node->left != NULL) push(&s1, node->left);
		if(node->right != NULL) push(&s1, node->right);
	}

	while(!isEmpty(&s2)){
		BSTNode *n = pop(&s2);
		printf("%d ", n->item);
	}
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value){
	BSTNode *curr = root;
	BSTNode *prev;

	prev = curr;

	if(curr == NULL) return NULL;

	if(curr->item > value){
		curr = curr->left;

		if(curr->item == value){
			// printf("찾았습니다, 현 -- 이전: %d -- %d\n", prev->item, curr->item);
			removeAndRearrayTree(curr, prev);
			return curr;
		}
		removeNodeFromTree(curr, value);
	}else if(curr->item < value){
		curr = curr->right;

		if(curr->item == value){
			// printf("찾았습니다, 현 -- 이전: %d -- %d\n", prev->item, curr->item);
			removeAndRearrayTree(curr, prev);
			return curr;
		}
		removeNodeFromTree(curr, value);
	}else{
		return NULL;
	}

}

void removeAndRearrayTree(BSTNode *target, BSTNode *prev){
	// 추가문제: 특정 값인 노드를 삭제하는 로직
	// 1 - leafNode시, 2 - child가 하나일 때, 3 - child가 두개 일 때 각각
	// 3 번 케이스의 경우 총 4가지 케이스로 나눠짐

	// 3번 케이스 => 노가다 처럼 직접 구해야 한다고 함:
	if (target->left != NULL && target->right != NULL) {
        // 여기서'대역(Successor) 찾기' 노가다 진행
        // 1 - 오른쪽 자식 중 가장 작은 놈(minNode)과 그 부모(minParent)를 찾는다
		BSTNode *minNode = target;
		BSTNode *minParent = target;

		while(minNode->left != NULL){
			minParent = minNode;
			minNode = minNode->left;
		}

		// printf("중간 디거빙, minNode: %d , minParent: %d \n", minNode->item, minParent->item);

		if(minNode != minParent){
			int val = minNode->item;
			minNode->item = target->item;
			target->item = val;
			minParent->left = NULL;
		}else{
			prev->right = minNode;
		}
        return;
    }

	// 1, 2번 케이스:
	BSTNode *child = (target->left != NULL) ? target->left : target->right;
	
	if (prev->left == target) prev->left = child;
	else prev->right = child;

}
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

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


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
