#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//小米平板6Pro到此一游
int main() {
	char str[20]; 
	fgets(str,20,stdin);

	int len = strlen(str);
	char* orders[10] = { NULL };
	int orderCount = 0;
	orders[orderCount++] = str;
	for (int i = 0; i < len; i++) {
		if (isspace(str[i]) && !isspace(str[i + 1]) && str[i + 1] != '\0' && str[i + 1] != '\n') {
			orders[orderCount++] = &(str[i + 1]);
		}
		if (isspace(str[i])) {
			str[i] = '\0';
		}
	}

	orderCount = 0;
	while (1) {
		if (orders[orderCount] != NULL) {
			printf("%s\n", orders[orderCount++]);
		} else {
			break;
		}
	}

	printf("%d", strcmp(orders[0], "cd"));
}