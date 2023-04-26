#include "fileSystem.h"

#define instructionSetLen 9
static char* instructionSet[9] = { "ls","cd","cp","mv","ct","rm","vw","sc","hp" };
#define pathDepth 30
static char* splitPath[pathDepth] = { NULL };

static Node ROOT = { 1,".",NULL,0,NULL,NULL };
static char workingDirPath[100] = "./";
static Node* workingDir = &ROOT;
static Node* preWorkingDir = NULL;

void init() {
	printf("%s >:", workingDirPath);
}

int toSplitPath(char* path) {
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
	if (splitPath[0] == NULL) {
		printf("wrong path\n");
		return 0;
	}
	return 1;
}

int execute_ct(int* insPara, char* path) {
	if (!toSplitPath(path)) {
		return 0;
	}
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

int execute_ls(int* insPara, char* path) {
	Node* tempNode;
	if (insPara[1] == -1) {
		tempNode = workingDir;
	} else {
		if (!toSplitPath(path)) {
			return 0;
		}
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

int execute_cd(char* path) {
	char tempPath[100] = { '\0' };
	int tempIndex = 0;
	if (!toSplitPath(path)) {
		return 0;
	}
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

int execute_rm(int* insPara, char* path) {
	if (!toSplitPath(path)) {
		return 0;
	}
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

void rm_recur(Node* node) {
	if (node) {
		rm_recur(node->firstChild);
		rm_recur(node->rightSibling);
		free(node);
	}
}

int execute_vw(int* insPara, char* path) {
	if (!toSplitPath(path)) {
		return 0;
	}
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

int execute_mv(char* srcPath, char* desPath) {
	Node* tempNode;
	Node* preTempNode;
	int depthCount;

	Node* src;
	Node* parentSrc;
	Node* preSrc;
	if (!toSplitPath(srcPath)) {
		return 0;
	}
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
	if (!toSplitPath(desPath)) {
		return 0;
	}
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
				if (tempNode == src) {
					printf("the des dir is the sub-dir of the src dir\n");
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
			if (strcmp(tempNode->name, splitPath[depthCount]) == 0) {
				printf("file or dir with the same name has existed\n");
				return 0;
			}
			while (tempNode->rightSibling != NULL) {
				tempNode = tempNode->rightSibling;
				if (strcmp(tempNode->name, splitPath[depthCount]) == 0) {
					printf("file or dir with the same name has existed\n");
					return 0;
				}
			}
			preDes = tempNode;
			if (preSrc->firstChild == src) {
				preSrc->firstChild = src->rightSibling;
				preDes->rightSibling = src;
				src->rightSibling = NULL;
				strcpy(src->name, splitPath[depthCount]);
				if (!src->isDir) {
					time_t t;
					time(&t);
					src->lastUpdate = t;
				}
			} else {
				preSrc->rightSibling = src->rightSibling;
				preDes->rightSibling = src;
				src->rightSibling = NULL;
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
				src->rightSibling = NULL;
				strcpy(src->name, splitPath[depthCount]);
				if (!src->isDir) {
					time_t t;
					time(&t);
					src->lastUpdate = t;
				}
			} else {
				preSrc->rightSibling = src->rightSibling;
				preDes->firstChild = src;
				src->rightSibling = NULL;
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

int execute_cp(char* srcPath, char* desPath) {
	Node* tempNode;
	int depthCount;

	Node* src;
	if (!toSplitPath(srcPath)) {
		return 0;
	}
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
				printf("can not copy dir\n");
				return 0;
			}
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
	if (!toSplitPath(desPath)) {
		return 0;
	}
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

	if (tempNode->firstChild != NULL) {
		tempNode = tempNode->firstChild;
		if (strcmp(tempNode->name, splitPath[depthCount]) == 0) {
			printf("file or dir with the same name has existed\n");
			return 0;
		}
		while (tempNode->rightSibling != NULL) {
			tempNode = tempNode->rightSibling;
			if (strcmp(tempNode->name, splitPath[depthCount]) == 0) {
				printf("file or dir with the same name has existed\n");
				return 0;
			}
		}
		preDes = tempNode;

		Node* newNode = (Node*) malloc(sizeof(Node));
		newNode->isDir = 0;
		strcpy(newNode->name, src->name);
		strcpy(newNode->content, src->content);
		newNode->firstChild = NULL;
		newNode->rightSibling = NULL;
		time_t t;
		time(&t);
		newNode->lastUpdate = t;
		preDes->rightSibling = newNode;
	} else {
		preDes = tempNode;
		Node* newNode = (Node*) malloc(sizeof(Node));
		newNode->isDir = 0;
		strcpy(newNode->name, splitPath[depthCount]);
		strcpy(newNode->content, src->content);
		newNode->firstChild = NULL;
		newNode->rightSibling = NULL;
		time_t t;
		time(&t);
		newNode->lastUpdate = t;
		preDes->firstChild = newNode;
	}
	return 1;
}

int execute_sc(int* insPara, char* data, char* path) {
	Node* nodeToStart;
	char filePath[100];
	if (insPara[3] == -1) {
		nodeToStart = workingDir;
		strcpy(filePath, workingDirPath);
	} else {
		char tempPath[100] = { '\0' };
		int tempIndex = 0;
		if (!toSplitPath(path)) {
			return 0;
		}
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
		nodeToStart = tempNode;
		strcpy(filePath, tempPath);
	}

	if (insPara[0] == 1) {
		for (int i = 0; i < strlen(data); i++) {
			if (!isdigit(data[i])) {
				printf("wrong time");
				return 0;
			}
		}
		time_sc_recur(nodeToStart->firstChild, data, filePath, -1);
		printf("search completed");

	} else if (insPara[1] == 1) {
		for (int i = 0; i < strlen(data); i++) {
			if (!isdigit(data[i])) {
				printf("wrong time");
				return 0;
			}
		}
		time_sc_recur(nodeToStart->firstChild, data, filePath, 1);
		printf("search completed");
	} else {
		name_sc_recur(nodeToStart->firstChild, data, filePath);
	}
}


void time_sc_recur(Node* node, char* time, char* prePath, int pattern) {
	if (node != NULL) {

		char path[100] = { '\0' };
		strcpy(path, prePath);
		int tempIndex = strlen(prePath);
		for (int i = 0; i < strlen(node->name); i++) {
			path[tempIndex++] = (node->name)[i];
		}

		if (node->isDir == 0) {
			char lastUpdate[20] = { '\0' };
			sprintf(lastUpdate, "%lu", node->lastUpdate);
			if (strcmp(lastUpdate, time) == pattern) {
				printf("%s\n", path);
			}
		}

		time_sc_recur(node->rightSibling, time, prePath, pattern);

		if (node->isDir == 1) {
			path[tempIndex++] = '/';
			time_sc_recur(node->firstChild, time, path, pattern);
		}
	}
}

void name_sc_recur(Node* node, char* key, char* prePath) {
	if (node != NULL) {

		char path[100] = { '\0' };
		strcpy(path, prePath);
		int tempIndex = strlen(prePath);
		for (int i = 0; i < strlen(node->name); i++) {
			path[tempIndex++] = (node->name)[i];
		}

		if (node->isDir == 0) {
			if (kmp(node->name, key) != -1) {
				printf("%s\n", path);
			}
		}

		name_sc_recur(node->rightSibling, key, prePath);

		if (node->isDir == 1) {
			path[tempIndex++] = '/';
			name_sc_recur(node->firstChild, key, path);
		}
	}
}

int kmp(char* name, char* key) {
	int keyLength = strlen(key);
	int nameLength = strlen(name);
	int* next = (int*) malloc(sizeof(int) * keyLength);

	next[0] = -1;
	int i = -1;
	int j = 0;
	while (j < keyLength - 1) {
		if (i == -1 || key[i] == key[j]) {
			i++;
			j++;
			if (key[i] != key[j]) {
				next[j] = i;
			} else {
				next[j] = next[i];
			}
		} else {
			i = next[i];
		}
	}

	i = 0;
	j = 0;
	while (i < nameLength && j < keyLength) {
		if (j == -1 || name[i] == key[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}
	if (i == nameLength) {
		free(next);
		return -1;
	} else {
		free(next);
		return i - j;
	}
}

int execute_hp() {

	printf("����·�����ȿ���ʹ�þ���·��������./a����Ҳ��ʹ�����·��������b/c ��/b/c��\n");
	printf("ָ�:\n");

	printf("\tls [ѡ��] [Ŀ¼·��]\n");
	printf("\t\t1.��ʾָ��Ŀ¼�µ������ļ���Ŀ¼����Ϣ\n");
	printf("\t\t2.���������·������Ĭ��Ϊ��ǰ����Ŀ¼\n");
	printf("\t\t3.ѡ�\n");
	printf("\t\t\t-r �ݹ����ʾ������Ŀ¼������\n");
	printf("\n");

	printf("\tcd Ŀ¼·��\n");
	printf("\t\t���Ĺ���Ŀ¼\n");
	printf("\n");

	printf("\tcp Դ�ļ�·�� Ŀ���ļ�·��\n");
	printf("\t\t1.��Դ�ļ����Ƶ�Ŀ���ļ���\n");
	printf("\t\t2.�ļ�·��Ҫ�ṩ�ļ��������Ŀ���ļ�����Դ�ļ�����ͬ����ὫĿ���ļ��Զ�������\n");
	printf("\t\t3.���Ŀ���ļ�����Ŀ¼������ͬ���ļ���ͬ���ļ����ᱻ���ǣ�������ֹ����\n");
	printf("\t\t4.Ŀǰֻ֧�ָ����ļ�����֧�ָ���Ŀ¼\n");
	printf("\n");

	printf("\tmv Դ�ļ�/Ŀ¼·�� Ŀ���ļ�/Ŀ¼·��\n");
	printf("\t\t1.��.��Դ�ļ�/Ŀ¼�ƶ���Ŀ���ļ�/Ŀ¼��\n");
	printf("\t\t  ��.������Դ�ļ�\n");
	printf("\t\t2.�ļ�/Ŀ¼·��Ҫ�ṩ�ļ��������Ŀ���ļ�����Դ�ļ�����ͬ����ὫĿ���ļ��Զ�������\n");
	printf("\t\t3.���Դ�ļ�/Ŀ¼��Ŀ���ļ�/Ŀ¼��ͬһ����Ŀ¼�У�������ָ���Ч�����൱�ڽ�Դ�ļ�/Ŀ¼������\n");
	printf("\t\t4.�ƶ�Ŀ¼ʱ���Ὣ��Ŀ¼�µ���������һͬ�ƶ�\n");
	printf("\t\t5.�ر�أ����Ŀ��Ŀ¼ΪԴĿ¼����Ŀ¼����ô�ƶ�Ҳ����ɹ�\n");
	printf("\t\t6.���Ŀ���ļ�/Ŀ¼����Ŀ¼������ͬ���ļ���ͬ���ļ�/Ŀ¼���ᱻ���ǣ�������ֹ�ƶ�\n");
	printf("\t\t7.�ر�أ�������ǰ���£����Դ�ļ�/Ŀ¼��Ŀ���ļ�/Ŀ¼��ͬһ����Ŀ¼�У���ôʲôҲ���ᷢ��\n");
	printf("\n");

	printf("\tct [ѡ��] Ŀ���ļ�/Ŀ¼·��\n");
	printf("\t\t1.��ָ��·�������ļ�/Ŀ¼\n");
	printf("\t\t2.ѡ�\n");
	printf("\t\t\t-d ��ʾ����Ŀ¼��ȱʡ��ʾ�����ļ�\n");
	printf("\n");

	printf("\trm [ѡ��] Ŀ���ļ�/Ŀ¼·��\n");
	printf("\t\t1.ɾ��Ŀ���ļ�/Ŀ¼\n");
	printf("\t\t2.ѡ�\n");
	printf("\t\t\t-r ɾ��Ŀ¼ʱ����ʾ�ݹ�ؽ���Ŀ¼�µ���������һ��ɾ������ȱʡ����ֻ��ɾ������Ϊ�յ�Ŀ¼\n");
	printf("\n");

	printf("\tvw [ѡ��] Ŀ���ļ�\n");
	printf("\t\t1.�鿴/�޸�Ŀ���ļ�\n");
	printf("\t\t2.ѡ�\n");
	printf("\t\t\t-w ��ʾ�ڲ鿴�ļ���ͬʱ�����������޸ģ���ȱʡ�����ʾֻ�鿴�ļ�\n");
	printf("\n");

	printf("\tsc [ѡ��] �������� [��ʼ������Ŀ¼·��]\n");
	printf("\t\t1.�����������������ļ�\n");
	printf("\t\t\t��������1��ʱ���\n");
	printf("\t\t\t��������2�������ļ���\n");
	printf("\t\t2.�����д��ʼ������Ŀ¼·������Ĭ�ϴӵ�ǰ����Ŀ¼��ʼ\n");
	printf("\t\t3.ѡ�\n");
	printf("\t\t\t-lt ����ʱ�������ʱ��Ч����ʾ��������޸�ʱ���ָ��ʱ�������ļ�\n");
	printf("\t\t\t-gt ����ʱ�������ʱ��Ч����ʾ��������޸�ʱ���ָ��ʱ�������ļ�\n");
	printf("\t\t\tע�⣺-lt �� -gt ����ͬʱ��Ч\n");
	printf("\t\t4.���û��ѡ�����ݲ����ļ�����������\n");
	printf("\t\t5.ע�⣺��ʼ������Ŀ¼·�������У�һ��Ҫд����������֮�󣬷����ָ���޷�ʶ�𣬵�������ʧ��\n");
	printf("\n");

	printf("\tquit\n");
	printf("\t\t�˳�����\n");
	printf("\n");
}