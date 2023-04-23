#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
	int value;
	struct Node* next;
} Node, * List;

List intersection(List a, List b) {
	Node* tempA = a->next;
	Node* tempB = b->next;
	List c = a;
	while (tempA != NULL && tempB != NULL) {
		if (tempA->value > tempB->value) {
			Node* nodeToDel = tempB;
			tempB = tempB->next;
			free(nodeToDel);
		} else if (tempA->value < tempB->value) {
			Node* nodeToDel = tempA;
			tempA = tempA->next;
			free(nodeToDel);
		} else {
			Node* nodeToDel = tempB;
			tempB = tempB->next;
			c->next = tempA;
			tempA = tempA->next;
			c = c->next;
			free(nodeToDel);
		}
	}
	c->next = NULL;
	free(b);
	while (tempA != NULL) {
		Node* nodeToDel = tempA;
		tempA = tempA->next;
		free(nodeToDel);
	}
	while (tempB != NULL) {
		Node* nodeToDel = tempB;
		tempB = tempB->next;
		free(nodeToDel);
	}
	return a;
}

List* resolve(List list) {
	List lists[2];
	List b = malloc(sizeof(Node));
	List c = malloc(sizeof(Node));
	b->next = NULL;
	c->next = NULL;
	lists[0] = b;
	lists[1] = c;
	Node* temp = list->next;
	while (temp != NULL) {
		if (temp->value < 0) {
			Node* tempNext = temp->next;
			temp->next = b->next;
			b->next = temp;
			temp = tempNext;
		} else {
			Node* tempNext = temp->next;
			temp->next = c->next;
			c->next = temp;
			temp = tempNext;
		}
	}
	return lists;
}

//int main() {
//	srand((unsigned int) time(NULL));
//
//	//Á´±í1
//	List list1 = (Node*) malloc(sizeof(Node));
//	list1->next = NULL;
//	Node* newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 23;
//	newNode->next = list1->next;
//	list1->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 17;
//	newNode->next = list1->next;
//	list1->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 15;
//	newNode->next = list1->next;
//	list1->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 9;
//	newNode->next = list1->next;
//	list1->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 5;
//	newNode->next = list1->next;
//	list1->next = newNode;
//
//	Node* temp = list1->next;
//	while (temp != NULL) {
//		printf("%d ", (temp->value));
//		temp = temp->next;
//	}
//	printf("\n");
//
//	//Á´±í2
//	List list2 = (Node*) malloc(sizeof(Node));
//	list2->next = NULL;
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 17;
//	newNode->next = list2->next;
//	list2->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 9;
//	newNode->next = list2->next;
//	list2->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 7;
//	newNode->next = list2->next;
//	list2->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 5;
//	newNode->next = list2->next;
//	list2->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 3;
//	newNode->next = list2->next;
//	list2->next = newNode;
//
//	temp = list2->next;
//	while (temp != NULL) {
//		printf("%d ", (temp->value));
//		temp = temp->next;
//	}
//	printf("\n");
//
//	intersection(list1, list2);
//	temp = list1->next;
//	while (temp != NULL) {
//		printf("%d ", (temp->value));
//		temp = temp->next;
//	}
//	printf("\n");
//
//	//Á´±í3
//	List list3 = (Node*) malloc(sizeof(Node));
//	list3->next = NULL;
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = -5;
//	newNode->next = list3->next;
//	list3->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 9;
//	newNode->next = list3->next;
//	list3->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 7;
//	newNode->next = list3->next;
//	list3->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = -2;
//	newNode->next = list3->next;
//	list3->next = newNode;
//
//	newNode = (Node*) malloc(sizeof(Node));
//	newNode->value = 6;
//	newNode->next = list3->next;
//	list3->next = newNode;
//
//	temp = list3->next;
//	while (temp != NULL) {
//		printf("%d ", (temp->value));
//		temp = temp->next;
//	}
//	printf("\n");
//
//	List* lists = resolve(list3);
//	temp = (lists[0])->next;
//	while (temp != NULL) {
//		printf("%d ", (temp->value));
//		temp = temp->next;
//	}
//	printf("\n");
//	temp = (lists[1])->next;
//	while (temp != NULL) {
//		printf("%d ", (temp->value));
//		temp = temp->next;
//	}
//	printf("\n");
//}