#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct SortTreeNode {
	int value;
	struct SortTreeNode* left;
	struct SortTreeNode* right;
} SortTreeNode, *SortTree;

SortTree init() {
	return NULL;
}

void add(SortTree* t, int value) {
	SortTreeNode* nodeToAdd = (SortTreeNode*) malloc(sizeof(SortTreeNode));
	nodeToAdd->value = value;
	nodeToAdd->left = NULL;
	nodeToAdd->right = NULL;
	if (*t == NULL) {
		*t = nodeToAdd;
	} else if(value < (*t)->value) {
		add(&((*t)->left), value);
	} else if (value > (*t)->value) {
		add(&((*t)->right), value);
	}
}

void inorder(SortTree t) {
	if (t == NULL) {
		return;
	}
	inorder(t->left);
	printf("%d\t", t->value);
	inorder(t->right);
}

//length��ʾ��ǰ�Ĳ��ҳ��ȣ���searchLength����
int searchLengthReverse(SortTree t, int key, int length) {
	if (t == NULL) {
		//key�ڶ������в����ڣ�����-1
		return -1;
	} else if (key == t->value) {
		//�ҵ�key
		return length + 1;
	} else if (key > t->value) {
		//���ҵݹ�
		return searchLengthReverse(t->right, key, length + 1);
	} else if (key < t->value) {
		//����ݹ�
		return searchLengthReverse(t->left, key, length + 1);
	}
}

//����key�Ĳ��ҳ���
int searchLength(SortTree t, int key) {
	searchLengthReverse(t, key, 0);
}

//���شӸ��ڵ㵽 key ·���ϵ���һ���ڵ㣬��commonAnces����
SortTreeNode* nextChild(SortTreeNode* t, int key) {
	if (key < t->value) {
		return t->left;
	} else if (key > t->value) {
		return t->right;
	} else {
		return t;
	}
}

//�ú���Ĭ�� key1 �� key2 ���ڶ�������
//��˱߲�����
//	1.�����ߵ����ȿ�ʼ��һ��ʱ����ô������������ȶ��᲻һ�£���˿���ֱ��ֹͣ����
//	2.���ҵ�����֮һʱ��ҲҪֹͣ����
void commonAnces(SortTree t, int key1, int key2) {
	//key1_temp ��ʾ�Ӹ��ڵ㵽 key1 ·���ϵĸ����ڵ㣬�������ѭ���л��𲽱仯
	SortTreeNode* key1_temp = t;
	//key2_temp ͬ��
	SortTreeNode* key2_temp = t;
	while (1) {
		//�����֮ǰ�����ж��Ƿ��ҵ��˶���֮һ��������� key1 �� key2 ����
		if (key1_temp->value == key1 || key2_temp->value == key2) {
			break;
		}
		//�������һ�£�������������һ�£���ֹͣ����
		if (key1_temp == key2_temp) {
			printf("%d\t", key1_temp->value);
		} else {
			break;
		}
		//key1 �� key2 �ֱ����²���һ��
		key1_temp = nextChild(key1_temp, key1);
		key2_temp = nextChild(key2_temp, key2);
	}
}

int main() {
	SortTree t = init();
	add(&t, 12);
	add(&t, 7);
	add(&t, 17);
	add(&t, 2);
	add(&t, 11);
	add(&t, 4);
	add(&t, 9);
	add(&t, 16);
	add(&t, 21);
	add(&t, 13);
	inorder(t);
	printf("\n");
	printf("%d", searchLength(t, 21));
	printf("\n");
	commonAnces(t, 4, 9);
}