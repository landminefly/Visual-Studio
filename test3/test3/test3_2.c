#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode {
	char ch;
	struct StackNode* next;
}StackNode, *Stack;

Stack newStack() {
	return NULL;
}

//void push(Stack* s, char ch) {
//	StackNode* newNode = (StackNode*) malloc(sizeof(StackNode));
//	newNode->ch = ch;
//	newNode->next = *s;
//	*s = newNode;
//}
//
//char pop(Stack* s) {
//	if (*s == NULL) {
//		return NULL;
//	}
//	StackNode* nodeToDel = *s;
//	char popCh = (*s)->ch;
//	*s = (*s)->next;
//	free(nodeToDel);
//	return popCh;
//}

int isPlalindrome(char str[]) {
	int len = strlen(str);
	int isOdd = strlen(str) % 2 != 0 ? 1 : 0;
	Stack strStack = newStack();
	int index = 0;
	for (index = 0; index < len / 2; index++) {
		enQueue(&strStack, str[index]);
	}
	if (isOdd) {
		index++;
	}
	for (; index < len; index++) {
		if (str[index] != deQueue(&strStack)) {
			return 0;
		}
		return 1;
	}
}

//int main() {
//	char str[] = "abcbba";
//	int flag = isPlalindrome(str);
//	printf("%d", flag);
//}