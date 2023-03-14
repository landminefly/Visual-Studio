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
	while (left <= right) {
		if (*left == item && *right == item) {
			while (*right == item && left <= right) {
				right--;
				list->length--;
			}
		} else if (*left == item) {
			*left = *right;
			right--;
			list->length--;
		} else if (*right == item) {
			right--;
			list->length--;
		} else {
			left++;
		}
	}
}

int main() {
	struct List list = { (int*) malloc(MAX_SIZE * sizeof(int)), 10 };
	list.value[0] = 3;
	list.value[1] = 1;
	list.value[2] = 60;
	list.value[3] = 3;
	list.value[4] = 1;
	list.value[5] = 1;
	list.value[6] = 41;
	list.value[7] = 1;
	list.value[8] = 1;
	list.value[9] = 8;
	for (int i = 0; i < list.length; i++) {
		printf("%d ", list.value[i]);
	}
	printf("\n");
	deleteAll(&list, 1);
	for (int i = 0; i < list.length; i++) {
		printf("%d ", list.value[i]);
	}
}
