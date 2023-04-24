#include "fileSystem.h"

#define inputStrLen 100
#define commandsLen 10
#define instructionSetLen 9
static char inputStr[100] = { '\0' };
static char* commands[10] = { NULL };
static char* instructionSet[9] = { "ls","cd","cp","mv","ct","rm","cg","sc","hp" };

void input() {
	for (int i = 0; i < inputStrLen; i++) {
		inputStr[i] = '\0';
	}
	for (int i = 0; i < commandsLen; i++) {
		commands[i] = NULL;
	}
	fgets(inputStr, 100, stdin);
}

void splitCommand() {
	int len = strlen(inputStr);
	int commandCount = 0;
	if (!isspace(inputStr[0])) {
		commands[commandCount++] = inputStr;
	}
	for (int i = 0; i < len; i++) {
		if (isspace(inputStr[i]) && !isspace(inputStr[i + 1]) && inputStr[i + 1] != '\0' && inputStr[i + 1] != '\n') {
			commands[commandCount++] = &(inputStr[i + 1]);
		}
		if (isspace(inputStr[i])) {
			inputStr[i] = '\0';
		}
	}
}

/*
	0:ls(list)
	1:cd(change dir)
	2:cp(copy)
	3:mv(move)
	4:ct(create)
	5:rm(remove)
	6:cg(change)
	7:sc(search)
	8:hp(help)
*/
void executeCommand() {
	int insCode = matchInstruction();
	int* insPara = NULL;
	switch (insCode) {
	case 0:
		//ls命令有额外选项，要进行选项匹配
		insPara = (int*) malloc(2 * sizeof(int));
		if (!match_ls_para(insPara)) {
			return;
		};
		execute_ls(insPara, commands[insPara[1]]);
		free(insPara);
		break;
	//case 1:
	//	//cd命令没有额外选项，直接传入路径即可
	//	execute_cd(commands[1]);
	//	break;
	//case 2:
	//	//cp命令没有额外选项，直接传入路径即可
	//	execute_cp(commands[1], commands[2]);
	//	break;
	//case 3:
	//	//mv命令没有额外选项，直接传入路径即可
	//	execute_mv(commands[1], commands[2]);
	//	break;
	case 4:
		//ct命令有额外选项，要进行选项匹配
		insPara = (int*) malloc(2 * sizeof(int));
		if (!match_ct_para(insPara)) {
			return;
		}
		execute_ct(insPara, commands[insPara[1]]);
		free(insPara);
		break;
	//case 5:
	//	//rm命令有额外选项，要进行选项匹配
	//	insPara = (int*) malloc(2 * sizeof(int));
	//	match_rm_para(insPara);
	//	execute_rm(insPara, commands[insPara[1]]);
	//	free(insPara);
	//case 6:
	//	//ch命令没有额外选项，直接传入路径即可
	//	excute_mv(commands[1]);
	//	break;
	//case 7:
	//	//sc命令有额外选项，要进行选项匹配
	//	insPara = (int*) malloc(2 * sizeof(int));
	//	match_sc_para(insPara);
	//	execute_sc(insPara, commands[insPara[1]]);
	//	free(insPara);
	//case 8:
	//	execute_hp();
	case -1:
		printf("no such instrcution like %s\n", commands[0]);
		break;
	}
}

int matchInstruction() {
	char* instruct = commands[0];
	for (int i = 0; i < instructionSetLen; i++) {
		if (!strcmp(instruct, instructionSet[i])) {
			return i;
		}
	}
	return -1;
}

int match_ls_para(int* insPara) {
	//将记录路径下标的元素值先置为-1
	insPara[1] = -1;
	insPara[0] = 0;
	for (int i = 1; commands[i] != NULL; i++) {

		if (commands[i][0] == '-') {
			if (strcmp(commands[i], "-r") == 0) {
				insPara[0] = 1;
			} else {
				printf("no such para like %s\n", commands[i]);
				return 0;
			}
		} else if (insPara[1] == -1) {
			insPara[1] = i;
		} else if (insPara[1] != -1) {
			printf("you have entered more than one path\n");
			return 0;
		}
	}
	if (insPara[1] == -1) {
		printf("please enter path\n");
		return 0;
	}
	return 1;
}

int match_ct_para(int* insPara) {
	//将记录路径下标的元素值先置为-1
	insPara[0] = 0;
	insPara[1] = -1;
	for (int i = 1; commands[i] != NULL; i++) {

		if (commands[i][0] == '-') {
			if (strcmp(commands[i], "-d") == 0) {
				insPara[0] = 1;
			} else {
				printf("no such para like %s\n", commands[i]);
				return 0;
			}
		} else if (insPara[1] == -1) {
			insPara[1] = i;
		} else if (insPara[1] != -1) {
			printf("you have entered more than one path\n");
			return 0;
		}
	}
	if (insPara[1] == -1) {
		printf("please enter path\n");
		return 0;
	}
	return 1;
}

int match_rm_para(int* insPara) {
	//将记录路径下标的元素值先置为-1
	insPara[0] = 0;
	insPara[1] = -1;
	for (int i = 1; commands[i] != NULL; i++) {

		if (commands[i][0] == '-') {
			if (strcmp(commands[i], "-r") == 0) {
				insPara[0] = 1;
			} else {
				printf("no such para like %s\n", commands[i]);
				return 0;
			}
		} else if (insPara[1] == -1) {
			insPara[1] = i;
		} else if (insPara[1] != -1) {
			printf("you have entered more than one path\n");
			return 0;
		}
	}
	if (insPara[1] == -1) {
		printf("please enter path\n");
		return 0;
	}
	return 1;
}

int match_sc_para(int* insPara) {
	//将记录路径下标的元素值先置为-1
	insPara[0] = 0;
	insPara[1] = -1;
	for (int i = 1; commands[i] != NULL; i++) {

		if (commands[i][0] == '-') {
			if (strcmp(commands[i], "-t") == 0) {
				insPara[0] = 1;
			} else {
				printf("no such para like %s\n", commands[i]);
				return 0;
			}
		} else if (insPara[1] == -1) {
			insPara[1] = i;
		} else if (insPara[1] != -1) {
			printf("you have entered more than one path\n");
			return 0;
		}
	}
	if (insPara[1] == -1) {
		printf("please enter path\n");
		return 0;
	}
	return 1;
}

int main() {
	while (1) {
		init();
		input();
		splitCommand();
		//int commandCount = 0;
		//while (1) {
		//	if (commands[commandCount] != NULL) {
		//		printf("%s\n", commands[commandCount++]);
		//	} else {
		//		break;
		//	}
		//}
		executeCommand();
	}

}