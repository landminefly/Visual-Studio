//#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//typedef struct SortTreeNode {
//	int value;
//	struct SortTreeNode* left;
//	struct SortTreeNode* right;
//} SortTreeNode, *SortTree;
//
//SortTree init() {
//	return NULL;
//}
//
//void add(SortTree* t, int value) {
//	SortTreeNode* nodeToAdd = (SortTreeNode*) malloc(sizeof(SortTreeNode));
//	nodeToAdd->value = value;
//	nodeToAdd->left = NULL;
//	nodeToAdd->right = NULL;
//	if (*t == NULL) {
//		*t = nodeToAdd;
//	} else if(value < (*t)->value) {
//		add(&((*t)->left), value);
//	} else if (value > (*t)->value) {
//		add(&((*t)->right), value);
//	}
//}
//
//void inorder(SortTree t) {
//	if (t == NULL) {
//		return;
//	}
//	inorder(t->left);
//	printf("%d\t", t->value);
//	inorder(t->right);
//}
//
////length表示当前的查找长度，由searchLength调用
//int searchLengthReverse(SortTree t, int key, int length) {
//	if (t == NULL) {
//		//key在二叉树中不存在，返回-1
//		return -1;
//	} else if (key == t->value) {
//		//找到key
//		return length + 1;
//	} else if (key > t->value) {
//		//往右递归
//		return searchLengthReverse(t->right, key, length + 1);
//	} else if (key < t->value) {
//		//往左递归
//		return searchLengthReverse(t->left, key, length + 1);
//	}
//}
//
////返回key的查找长度
//int searchLength(SortTree t, int key) {
//	searchLengthReverse(t, key, 0);
//}
//
////返回从根节点到 key 路径上的下一个节点，由commonAnces调用
//SortTreeNode* nextChild(SortTreeNode* t, int key) {
//	if (key < t->value) {
//		return t->left;
//	} else if (key > t->value) {
//		return t->right;
//	} else {
//		return t;
//	}
//}
//
////该函数默认 key1 和 key2 都在二叉树中
////因此边查边输出
////	1.当二者的祖先开始不一致时，那么它们往后的祖先都会不一致，因此可以直接停止查找
////	2.当找到二者之一时，也要停止查找
//void commonAnces(SortTree t, int key1, int key2) {
//	//key1_temp 表示从根节点到 key1 路径上的各个节点，在下面的循环中会逐步变化
//	SortTreeNode* key1_temp = t;
//	//key2_temp 同理
//	SortTreeNode* key2_temp = t;
//	while (1) {
//		//在输出之前，先判断是否找到了二者之一，避免输出 key1 或 key2 本身
//		if (key1_temp->value == key1 || key2_temp->value == key2) {
//			break;
//		}
//		//如果祖先一致，则输出；如果不一致，则停止查找
//		if (key1_temp == key2_temp) {
//			printf("%d\t", key1_temp->value);
//		} else {
//			break;
//		}
//		//key1 和 key2 分别向下查找一步
//		key1_temp = nextChild(key1_temp, key1);
//		key2_temp = nextChild(key2_temp, key2);
//	}
//}
//
//int main() {
//	SortTree t = init();
//	add(&t, 12);
//	add(&t, 7);
//	add(&t, 17);
//	add(&t, 2);
//	add(&t, 11);
//	add(&t, 4);
//	add(&t, 9);
//	add(&t, 16);
//	add(&t, 21);
//	add(&t, 13);
//	inorder(t);
//	printf("\n");
//	printf("%d", searchLength(t, 21));
//	printf("\n");
//	commonAnces(t, 4, 9);
//}