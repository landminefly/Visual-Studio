#include "fileSystem.h"

#define instructionSetLen 9
static char* instructionSet[9] = { "ls","cd","cp","mv","ct","rm","vw","sc","hp" };
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
static char workingDirPath[100] = "./";
static Node* workingDir = &ROOT;
static Node* preWorkingDir = NULL;

void init() {
	printf("%s >:", workingDirPath);
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
			printf("you can not create root\n");
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
					printf("%s is not a dir\n", tempNode->content);
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
			printf("%s has already existed\n", splitPath[depthCount]);
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
	Node* tempNode;
	if (insPara[1] == -1) {
		tempNode = workingDir;
	} else {
		toSplitPath(path);
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
						printf("%s is not a dir\n", splitPath[depthCount]);
						isSucess = 0;
						break;
					}
					depthCount++;
				} else {
					printf("no such dir named %s\n", splitPath[depthCount]);
					isSucess = 0;
					break;
				}
			} else {
				printf("no such dir named %s\n", splitPath[depthCount]);
				isSucess = 0;
				break;
			}
		}
		if (!isSucess) {
			return 0;
		}
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

int execute_cd(char* path) {
	char tempPath[100] = { '\0' };
	int tempIndex = 0;
	toSplitPath(path);
	Node* tempNode;
	int depthCount;
	if (strcmp(splitPath[0], ".") == 0) {
		strncpy(tempPath, workingDirPath, 2);
		tempIndex = 2;
		tempNode = &ROOT;
		depthCount = 1;
	} else {
		strncpy(tempPath, workingDirPath, strlen(workingDirPath));
		tempIndex = strlen(workingDirPath);
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
					printf("%s is not a dir\n", splitPath[depthCount]);
					isSucess = 0;
					break;
				}
				for (int i = 0; i < strlen(splitPath[depthCount]); i++) {
					tempPath[tempIndex++] = splitPath[depthCount][i];
				}
				tempPath[tempIndex++] = '/';
				depthCount++;
			} else {
				printf("no such dir named %s\n", splitPath[depthCount]);
				isSucess = 0;
				break;
			}
		} else {
			printf("no such dir named %s\n", splitPath[depthCount]);
			isSucess = 0;
			break;
		}
	}
	if (!isSucess) {
		return 0;
	}
	workingDir = tempNode;
	strcpy(workingDirPath, tempPath);
	return 1;
}

void rm_recur(Node* node) {
	if (node) {
		rm_recur(node->firstChild);
		rm_recur(node->rightSibling);
		free(node);
	}
}

int execute_rm(int* insPara, char* path) {
	toSplitPath(path);
	Node* tempNode;
	Node* preTempNode;
	int depthCount;
	if (strcmp(splitPath[0], ".") == 0) {
		if (splitPath[1] == NULL) {
			printf("you can not remove root\n");
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
					printf("%s is not a dir\n", tempNode->content);
					isSucess = 0;
					break;
				}
				depthCount++;
			} else {
				printf("no such dir named %s\n", splitPath[depthCount]);
				isSucess = 0;
				break;
			}
		} else {
			printf("no such dir named %s\n", splitPath[depthCount]);
			isSucess = 0;
			break;
		}
	}
	if (!isSucess) {
		return 0;
	}

	if (tempNode->firstChild != NULL) {
		preTempNode = tempNode;
		tempNode = tempNode->firstChild;
		int isFound = 1;
		while (strcmp(tempNode->name, splitPath[depthCount]) != 0) {
			if (tempNode->rightSibling == NULL) {
				isFound = 0;
				break;
			}
			preTempNode = tempNode;
			tempNode = tempNode->rightSibling;
		}
		if (isFound) {
			if (insPara[0] == 0) {
				if (tempNode->isDir == 1 && tempNode->firstChild != NULL) {
					printf("remove failed, this dir is not empty.\n");
					printf("if you want to remove all files in this dir while removing the dir, please use para -r\n");
					return 0;
				} else {
					if (preTempNode->firstChild == tempNode) {
						preTempNode->firstChild = tempNode->rightSibling;
						free(tempNode);
					} else {
						preTempNode->rightSibling = tempNode->rightSibling;
						free(tempNode);
					}
				}
			} else {
				if (preTempNode->firstChild == tempNode) {
					preTempNode->firstChild = tempNode->rightSibling;
					rm_recur(tempNode);
				} else {
					preTempNode->rightSibling = tempNode->rightSibling;
					rm_recur(tempNode);
				}
			}
		} else {
			printf("no such dir or file named %s\n", splitPath[depthCount]);
			return 0;
		}
	} else {
		printf("no such dir or file named %s\n", splitPath[depthCount]);
		return 0;
	}
	return 1;
}

int execute_vw(int* insPara, char* path) {
	toSplitPath(path);
	Node* tempNode;
	int depthCount;
	if (strcmp(splitPath[0], ".") == 0) {
		if (splitPath[1] == NULL) {
			printf("you can not view or change root\n");
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
					printf("%s is not a dir\n", tempNode->content);
					isSucess = 0;
					break;
				}
				depthCount++;
			} else {
				printf("no such dir named %s\n", splitPath[depthCount]);
				isSucess = 0;
				break;
			}
		} else {
			printf("no such dir named %s\n", splitPath[depthCount]);
			isSucess = 0;
			break;
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
			if (tempNode->isDir == 1) {
				printf("%s is a dir not a file\n", splitPath[depthCount]);
				return 0;
			} else {
				if (insPara[0] == 0) {
					printf("%s\n", tempNode->content);
				} else {
					printf("origin content: %s\n", tempNode->content);
					char input[100] = { '\0' };
					printf("please input the new content of this file:", tempNode->content);
					fgets(input, 99, stdin);
					strcpy(tempNode->content, input);
					time_t t;
					time(&t);
					tempNode->lastUpdate = t;
					printf("write complete\n");
				}
			}
		} else {
			printf("no such file named %s\n", splitPath[depthCount]);
			return 0;
		}
	} else {
		printf("no such file named %s\n", splitPath[depthCount]);
		return 0;
	}
	return 1;
}

int mv_search(Node** pointer, Node** prePointer, char* path) {
	Node* tempNode;
	Node* preTempNode;
	toSplitPath(path);
	int depthCount;
	if (strcmp(splitPath[0], ".") == 0) {
		if (splitPath[1] == NULL) {
			printf("you can not mv or rename root\n");
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
					printf("%s is not a dir\n", tempNode->content);
					isSucess = 0;
					break;
				}
				depthCount++;
			} else {
				printf("no such dir named %s\n", splitPath[depthCount]);
				isSucess = 0;
				break;
			}
		} else {
			printf("no such dir named %s\n", splitPath[depthCount]);
			isSucess = 0;
			break;
		}
	}
	if (!isSucess) {
		return 0;
	}

	if (tempNode->firstChild != NULL) {
		preTempNode = tempNode;
		tempNode = tempNode->firstChild;
		int isFound = 1;
		while (strcmp(tempNode->name, splitPath[depthCount]) != 0) {
			if (tempNode->rightSibling == NULL) {
				isFound = 0;
				break;
			}
			preTempNode = tempNode;
			tempNode = tempNode->rightSibling;
		}
		if (isFound) {
			
		} else {
			printf("no such file or dir named %s\n", splitPath[depthCount]);
			return 0;
		}
	} else {
		printf("no such file or dir named %s\n", splitPath[depthCount]);
		return 0;
	}
	return 1;
}


int execute_mv(char* desPath,char* srcPath) {
	Node* tempNode;
	Node* preTempNode;
	int depthCount;

	Node* src;
	Node* parentSrc;
	Node* preSrc;
	toSplitPath(srcPath);
	if (strcmp(splitPath[0], ".") == 0) {
		if (splitPath[1] == NULL) {
			printf("you can not mv or rename root\n");
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
					printf("%s is not a dir\n", tempNode->content);
					isSucess = 0;
					break;
				}
				depthCount++;
			} else {
				printf("no such dir named %s\n", splitPath[depthCount]);
				isSucess = 0;
				break;
			}
		} else {
			printf("no such dir named %s\n", splitPath[depthCount]);
			isSucess = 0;
			break;
		}
	}
	if (!isSucess) {
		return 0;
	}

	parentSrc = tempNode;
	if (tempNode->firstChild != NULL) {
		preTempNode = tempNode;
		tempNode = tempNode->firstChild;
		int isFound = 1;
		while (strcmp(tempNode->name, splitPath[depthCount]) != 0) {
			if (tempNode->rightSibling == NULL) {
				isFound = 0;
				break;
			}
			preTempNode = tempNode;
			tempNode = tempNode->rightSibling;
		}
		if (isFound) {
			preSrc = preTempNode;
			src = tempNode;
		} else {
			printf("no such file or dir named %s\n", splitPath[depthCount]);
			return 0;
		}
	} else {
		printf("no such file or dir named %s\n", splitPath[depthCount]);
		return 0;
	}

	Node* preDes;
	Node* parentDes;
	toSplitPath(desPath);
	if (strcmp(splitPath[0], ".") == 0) {
		if (splitPath[1] == NULL) {
			printf("you can not mv or rename root\n");
			return 0;
		}
		tempNode = &ROOT;
		depthCount = 1;
	} else {
		tempNode = workingDir;
		depthCount = 0;
	}
	isSucess = 1;
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
					printf("%s is not a dir\n", tempNode->content);
					isSucess = 0;
					break;
				}
				depthCount++;
			} else {
				printf("no such dir named %s\n", splitPath[depthCount]);
				isSucess = 0;
				break;
			}
		} else {
			printf("no such dir named %s\n", splitPath[depthCount]);
			isSucess = 0;
			break;
		}
	}
	if (!isSucess) {
		return 0;
	}

	parentDes = tempNode;
	if (parentDes == parentSrc) {
		strcpy(src->name, splitPath[depthCount]);
		if (!src->isDir) {
			time_t t;
			time(&t);
			src->lastUpdate = t;
		}
	} else {
		if (tempNode->firstChild != NULL) {
			tempNode = tempNode->firstChild;
			while (tempNode->rightSibling != NULL) {
				tempNode = tempNode->rightSibling;
			}
			preDes = tempNode;
			if (preSrc->firstChild == src) {
				preSrc->firstChild = src->rightSibling;
				preDes->rightSibling = src;
				strcpy(src->name, splitPath[depthCount]);
				if (!src->isDir) {
					time_t t;
					time(&t);
					src->lastUpdate = t;
				}
			} else {
				preSrc->rightSibling = src->rightSibling;
				preDes->rightSibling = src;
				strcpy(src->name, splitPath[depthCount]);
				if (!src->isDir) {
					time_t t;
					time(&t);
					src->lastUpdate = t;
				}
			}
		} else {
			preDes = tempNode;
			if (preSrc->firstChild == src) {
				preSrc->firstChild = src->rightSibling;
				preDes->firstChild = src;
				strcpy(src->name, splitPath[depthCount]);
				if (!src->isDir) {
					time_t t;
					time(&t);
					src->lastUpdate = t;
				}
			} else {
				preSrc->rightSibling = src->rightSibling;
				preDes->firstChild = src;
				strcpy(src->name, splitPath[depthCount]);
				if (!src->isDir) {
					time_t t;
					time(&t);
					src->lastUpdate = t;
				}
			}
		}
	}
	return 1;
}