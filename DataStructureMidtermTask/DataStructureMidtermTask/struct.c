#include "fileSystem.h"

#define instructionSetLen 9
static char* instructionSet[9] = { "ls","cd","cp","mv","ct","rm","cg","sc","hp" };
#define pathDepth 30
static char* splitPath[pathDepth] = { NULL };


typedef struct Node {
	int isDir;
	char name[50];
	char content[100];
	time_t lastUpdate;
	struct Node* firstChild;
	struct Node* rightSibling;
}Node, * Root;

static Node ROOT = { 1,".",NULL,0,NULL,NULL };
static Node* workingDir = &ROOT;
static Node* preWorkingDir = NULL;

void init() {
	printf("Working directory: %s/ ,", workingDir->name);
	printf("please input:");
}

void toSplitPath(char* path) {
	for (int i = 0; i < pathDepth; i++) {
		splitPath[i] = NULL;
	}
	splitPath[0] = strtok(path, "/");
	for (int i = 1; i < pathDepth; i++) {
		splitPath[i] = strtok(NULL, "/");
		if (splitPath[i] == NULL) {
			break;
		}
	}
}

int execute_ct(int* insPara, char* path) {
	toSplitPath(path);
	Node* tempNode;
	int depthCount;
	if (strcmp(splitPath[0], ".") == 0) {
		if (splitPath[1] == NULL) {
			printf("your dest is root,which is wrong.\n");
			return 0;
		}
		tempNode = &ROOT;
		depthCount = 1;
	} else {
		tempNode = workingDir;
		depthCount = 0;
	}
	int isSucess = 1;
	while (splitPath[depthCount + 1] != NULL) {
		if (tempNode->firstChild != NULL) {
			tempNode = tempNode->firstChild;
			int isFound = 1;
			while (strcmp(tempNode->name, splitPath[depthCount]) != 0) {
				if (tempNode->rightSibling == NULL) {
					isFound = 0;
					break;
				}
				tempNode = tempNode->rightSibling;
			}
			if (isFound) {
				if (tempNode->isDir == 0) {
					printf("already have file which named %s\n", tempNode->content);
					isSucess = 0;
					break;
				}
				depthCount++;
			} else {
				Node* newNode = (Node*) malloc(sizeof(Node));
				newNode->isDir = 1;
				strcpy(newNode->name, splitPath[depthCount]);
				newNode->lastUpdate = -1;
				newNode->firstChild = NULL;
				newNode->rightSibling = NULL;

				tempNode->rightSibling = newNode;
				tempNode = newNode;
				depthCount++;
			}
		} else {
			Node* newNode = (Node*) malloc(sizeof(Node));
			newNode->isDir = 1;
			strcpy(newNode->name, splitPath[depthCount]);
			newNode->lastUpdate = -1;
			newNode->firstChild = NULL;
			newNode->rightSibling = NULL;

			tempNode->firstChild = newNode;
			tempNode = newNode;
			depthCount++;
		}
	}
	if (!isSucess) {
		return 0;
	}
	if (tempNode->firstChild != NULL) {
		tempNode = tempNode->firstChild;
		int isFound = 1;
		while (strcmp(tempNode->name, splitPath[depthCount]) != 0) {
			if (tempNode->rightSibling == NULL) {
				isFound = 0;
				break;
			}
			tempNode = tempNode->rightSibling;
		}
		if (isFound) {
			printf("already have file or dic which named %s\n", splitPath[depthCount]);
			return 0;
		} else {
			Node* newNode = (Node*) malloc(sizeof(Node));
			newNode->isDir = insPara[0];
			strcpy(newNode->name, splitPath[depthCount]);
			if (!insPara[0]) {
				time_t t;
				time(&t);
				newNode->lastUpdate = t;

				printf("please input the content of this file:");
				char str[100] = { '\0' };
				fgets(str, 99, stdin);
				strcpy(newNode->content, str);
			} else {
				newNode->lastUpdate = -1;
			}
			newNode->firstChild = NULL;
			newNode->rightSibling = NULL;

			tempNode->rightSibling = newNode;
			tempNode = newNode;
		}
	} else {
		Node* newNode = (Node*) malloc(sizeof(Node));
		newNode->isDir = insPara[0];
		strcpy(newNode->name, splitPath[depthCount]);
		if (!insPara[0]) {
			time_t t;
			time(&t);
			newNode->lastUpdate = t;

			printf("please input the content of this file:");
			char str[100] = { '\0' };
			fgets(str, 99, stdin);
			strcpy(newNode->content, str);
		} else {
			newNode->lastUpdate = -1;
		}
		newNode->firstChild = NULL;
		newNode->rightSibling = NULL;

		tempNode->firstChild = newNode;
		tempNode = newNode;
	}
	return 1;
}

void ls_r(Node* tempNode) {
	while (tempNode != NULL) {
		if (!(tempNode->isDir)) {
			printf("%d\t%s\t%lu\n", tempNode->isDir, tempNode->name, tempNode->lastUpdate);
		} else {
			printf("%d\t%s\t\n", tempNode->isDir, tempNode->name);
			ls_r(tempNode->firstChild);
		}
		tempNode = tempNode->rightSibling;
	}
}


int execute_ls(int* insPara, char* path) {
	toSplitPath(path);
	Node* tempNode;
	int depthCount;
	if (strcmp(splitPath[0], ".") == 0) {
		tempNode = &ROOT;
		depthCount = 1;
	} else {
		tempNode = workingDir;
		depthCount = 0;
	}
	int isSucess = 1;
	while (splitPath[depthCount] != NULL) {
		if (tempNode->firstChild != NULL) {
			tempNode = tempNode->firstChild;
			int isFound = 1;
			while (strcmp(tempNode->name, splitPath[depthCount]) != 0) {
				if (tempNode->rightSibling == NULL) {
					isFound = 0;
					break;
				}
				tempNode = tempNode->rightSibling;
			}
			if (isFound) {
				if (tempNode->isDir == 0) {
					printf("already have file which named %s\n", splitPath[depthCount]);
					isSucess = 0;
					break;
				}
				depthCount++;
			} else {
				printf("no such dic named %s\n", splitPath[depthCount]);
				isSucess = 0;
				break;
			}
		} else {
			printf("no such dic named %s\n", splitPath[depthCount]);
			isSucess = 0;
			break;
		}
	}
	if (!isSucess) {
		return 0;
	}
	if (!insPara[0]) {
		if (tempNode->firstChild == NULL) {
			printf("empty!\n");
			return 1;
		} else {
			tempNode = tempNode->firstChild;
			printf("isDir\tname\tlastUpdate\n");
			while (tempNode != NULL) {
				if (!(tempNode->isDir)) {
					printf("%d\t%s\t%lu\n", tempNode->isDir, tempNode->name, tempNode->lastUpdate);
				} else {
					printf("%d\t%s\t\n", tempNode->isDir, tempNode->name);
				}
				tempNode = tempNode->rightSibling;
			}
			return 1;
		}
	} else {
		if (tempNode->firstChild == NULL) {
			printf("empty!\n");
			return 1;
		} else {
			tempNode = tempNode->firstChild;
			printf("isDir\tname\tlastUpdate\n");
			ls_r(tempNode);
			return 1;
		}
	}
}


