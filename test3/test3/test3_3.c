#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
	int value;
	struct Node* next;
} Node, * List;


int maxValue(List list) {
	if (list->next == NULL) {
		return -1;
	} else {
		return maxValueRe(list->next, INT_MIN);
	}
}
int maxValueRe(Node* node, int max) {
	if (node->next == NULL) {
		return node->value > max ? node->value : max;
	}
	max = node->value > max ? node->value : max;
	return maxValueRe(node->next, max);
}


int nodeCount(List list) {
	if (list->next == NULL) {
		return -1;
	} else {
		return nodeCountRe(list->next, 0);
	}
}
int nodeCountRe(Node* node, int count) {
	if (node->next == NULL) {
		return ++count;
	}
	return nodeCountRe(node->next, ++count);
}


float avgValue(List list) {
	if (list->next == NULL) {
		return -1;
	} else {
		return avgValueRe(list->next, 0, 0);
	}
}
float avgValueRe(Node* node, int count, int sum) {
	if (node->next == NULL) {
		return (sum + (node->value)) / (count + 1);
	}
	return avgValueRe(node->next, ++count, sum + (node->value));
}


//int main() {
//	//创建链表
//	srand((unsigned int) time(NULL));
//
//	List list = (Node*) malloc(sizeof(Node));
//	list->next = NULL;
//	for (int i = 0; i < 10; i++) {
//		Node* newNode = (Node*) malloc(sizeof(Node));
//		newNode->value = rand() % 100 + 1;
//		newNode->next = list->next;
//		list->next = newNode;
//	}
//	//打印链表
//	Node* temp = list->next;
//	while (temp != NULL) {
//		printf("%d ", (temp->value));
//		temp = temp->next;
//	}
//	printf("\n");
//
//	printf("%d\n", maxValue(list));
//	printf("%d\n", nodeCount(list));
//	printf("%f\n", avgValue(list));
//}