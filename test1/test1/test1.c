#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct List {
	int* value;
	int length;
};

void deleteAll(struct List* list, int item) {
	int* left = list->value;
	int* right = (list->value) + list->length - 1;
	while (left < right) {
		if (*left != item) {
			left++;
		} else {
			*left = *right;
			left++;
			right--;
			list->length--;
		}
	}
}

int main() {
	struct List list = { (int*) malloc(MAX_SIZE * sizeof(int)), 5 };
	list.value[0] = 1;
	list.value[1] = 2;
	list.value[2] = 1;
	list.value[3] = 5;
	list.value[4] = 6;
	for (int i = 0; i < list.length; i++) {
		printf("%d ", list.value[i]);
	}
	printf("\n");
	deleteAll(&list, 1);
	for (int i = 0; i < list.length; i++) {
		printf("%d ", list.value[i]);
	}
}