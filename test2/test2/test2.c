#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
	int value;
	struct Node* next;
} Node, * List;

Node* maxValue(List list, int len) {
	Node* temp = list->next;
	int max = INT_MIN;
	Node* maxNode = NULL;
	for (int i = 0; i < len; i++) {
		if (temp->value > max) {
			max = temp->value;
			maxNode = temp;
		}
		temp = temp->next;
	}
	return maxNode;
}

void reverse(List list) {
	if (list->next == NULL || list->next->next == NULL) {
		return;
	}
	Node* lastAfterReverse = list->next;
	Node* temp = lastAfterReverse->next;
	lastAfterReverse->next = NULL;
	while (temp != NULL) {
		Node* tempNext = temp->next;
		temp->next = list->next;
		list->next = temp;
		temp = tempNext;
	}
}

int main() {
	srand((unsigned int) time(NULL));

	List list = (Node*) malloc(sizeof(Node));
	list->next = NULL;
	for (int i = 0; i < 10; i++) {
		Node* newNode = (Node*) malloc(sizeof(Node));
		newNode->value = rand() % 100 + 1;
		newNode->next = list->next;
		list->next = newNode;
	}

	Node* temp = list->next;
	while (temp != NULL) {
		printf("%d ", (temp->value));
		temp = temp->next;
	}
	printf("\n");

	reverse(list);

	temp = list->next;
	while (temp != NULL) {
		printf("%d ", (temp->value));
		temp = temp->next;
	}
	printf("\n");

	Node* maxNode = maxValue(list, 10);
	if (maxNode != NULL) {
		printf("%d", maxNode->value);
	}
}