#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TreeNode {
	int value;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode, * Tree;

//===========================================================

typedef struct QueueNode {
	TreeNode* node;
	struct QueueNode* next;
} QueueNode, * List;

typedef struct Queue {
	QueueNode* rear;
}*Queue;

Queue initQueue() {
	List list = (List) malloc(sizeof(QueueNode));
	list->next = list;
	Queue q = (Queue) malloc(sizeof(struct Queue));
	q->rear = list;
	return q;
}

int isEmpty(Queue q) {
	if (q->rear->next == q->rear) {
		return 1;
	} else {
		return 0;
	}
}

void enQueue(Queue q, TreeNode* node) {
	QueueNode* newNode = (QueueNode*) malloc(sizeof(QueueNode));
	newNode->node = node;
	newNode->next = q->rear->next;
	q->rear->next = newNode;
	q->rear = newNode;
}

TreeNode* deQueue(Queue q) {
	if (!isEmpty(q)) {
		QueueNode* headNode = q->rear->next;
		QueueNode* nodeToDel = q->rear->next->next;
		TreeNode* valueToReturn = nodeToDel->node;
		headNode->next = headNode->next->next;
		if (nodeToDel == q->rear) {
			q->rear = headNode;
		}
		free(nodeToDel);
		return valueToReturn;
	}
}

//===========================================================
void preorder(Tree tree) {
	if (tree == NULL) {
		return;
	}
	printf("%d\t", tree->value);
	preorder(tree->left);
	preorder(tree->right);
}

//判断俩树是否相等（0表示不相等，1表示相等）
int isEqual(Tree t1, Tree t2) {
	int flag = ((t1 == NULL ? t1 : t1->value) == (t2 == NULL ? t2 : t2->value));
	if (flag) {
		if (t1 == NULL && t2 == NULL) {
			return 1;
		}
		return isEqual(t1->left, t2->left) & isEqual(t1->right, t2->right);
	} else {
		return 0;
	}
}

int maxWidth(Tree t) {
	if (t == NULL) {
		return 0;
	}
	//记录最大宽度，初始化为第一层的宽度1
	int max = 1;
	//记录下一层的宽度，初始化为0
	int cur_count = 0;
	//记录当前层的最后一个节点，初始化为第一层的最后一个节点，即树根
	TreeNode* end = t;
	//使用BFS的思想进行遍历
	Queue q = initQueue();
	enQueue(q, t);
	while (!isEmpty(q)) {
		TreeNode* temp = deQueue(q);
		if (temp->left != NULL) {
			enQueue(q, temp->left);
			cur_count++;
		}
		if (temp->right != NULL) {
			enQueue(q, temp->right);
			cur_count++;
		}
		//到达end时，此时的cur_count就是下一层的节点个数
		//更新max、end，重置cur_count，然后进入下一层的循环
		if (temp == end) {
			//下一层的最后一个节点就是当前的队尾元素
			end = q->rear->node;
			max = max > cur_count ? max : cur_count;
			cur_count = 0;
		}
	}
	return max;
}

int main() {
	Tree tree1 = (TreeNode*)malloc(sizeof(TreeNode));
	tree1->value = 1;

	tree1->left = (TreeNode*)malloc(sizeof(TreeNode));
	tree1->left->value = 2;
	tree1->right = (TreeNode*) malloc(sizeof(TreeNode));
	tree1->right->value = 3;

	tree1->left->left = (TreeNode*) malloc(sizeof(TreeNode));
	tree1->left->left->value = 4;
	tree1->left->right = (TreeNode*) malloc(sizeof(TreeNode));
	tree1->left->right->value = 5;
	tree1->right->left = NULL;
	tree1->right->right = NULL;

	tree1->left->left->left = NULL;
	tree1->left->left->right = NULL;
	tree1->left->right->left = NULL;
	tree1->left->right->right = NULL;

	Tree tree2 = (TreeNode*) malloc(sizeof(TreeNode));
	tree2->value = 1;

	tree2->left = (TreeNode*) malloc(sizeof(TreeNode));
	tree2->left->value = 2;
	tree2->right = (TreeNode*) malloc(sizeof(TreeNode));
	tree2->right->value = 3;

	tree2->left->left = NULL;
	tree2->left->right = NULL;
	tree2->right->left = NULL;
	tree2->right->right = NULL;

	printf("%d\n", isEqual(tree1, tree2));
	printf("%d\n", maxWidth(tree2));
}