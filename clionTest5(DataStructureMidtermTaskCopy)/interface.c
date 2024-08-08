#include "fileSystem.h"

#define inputStrLen 100
#define commandsLen 10
#define instructionSetLen 10
static char inputStr[100] = { '\0' };
static char* commands[10] = { NULL };
static char* instructionSet[10] = { "ls","cd","cp","mv","ct","rm","vw","sc","hp","quit" };

void input() {
	for (int i = 0; i < inputStrLen; i++) {
		inputStr[i] = '\0';
	}
	for (int i = 0; i < commandsLen; i++) {
		commands[i] = NULL;
	}
	fgets(inputStr, inputStrLen - 1, stdin);
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
	6:vw(view)
	7:sc(search)
	8:hp(help)
*/
int executeCommand() {
	int insCode = matchInstruction();
	int* insPara = NULL;
	switch (insCode) {
	case 0:
		//ls命令有额外选项，要进行选项匹配
		insPara = (int*) malloc(2 * sizeof(int));
		if (!match_ls_para(insPara)) {
			return 1;
		};
		execute_ls(insPara, commands[insPara[1]]);
		free(insPara);
		break;
	case 1:
		//cd命令没有额外选项，直接传入路径即可
		if (commands[1] == NULL) {
			printf("you have not entered path\n");
		} else {
			execute_cd(commands[1]);
		}
		break;
	case 2:
		//cp命令没有额外选项，直接传入路径即可
		if (commands[1] == NULL || commands[2] == NULL) {
			printf("you have not entered srcPth or desPath\n");
		} else {
			execute_cp(commands[1], commands[2]);
		}
		break;
	case 3:
		//mv命令没有额外选项，直接传入路径即可
		if (commands[1] == NULL || commands[2] == NULL) {
			printf("you have not entered srcPth or desPath\n");
		} else {
			execute_mv(commands[1], commands[2]);
		}
		break;
	case 4:
		//ct命令有额外选项，要进行选项匹配
		insPara = (int*) malloc(2 * sizeof(int));
		if (!match_ct_para(insPara)) {
			return 1;
		}
		execute_ct(insPara, commands[insPara[1]]);
		free(insPara);
		break;
	case 5:
		//rm命令有额外选项，要进行选项匹配
		insPara = (int*) malloc(2 * sizeof(int));
		if (!match_rm_para(insPara)) {
			return 1;
		}
		execute_rm(insPara, commands[insPara[1]]);
		free(insPara);
		break;
	case 6:
		//vw命令有额外选项，要进行选项匹配
		insPara = (int*) malloc(2 * sizeof(int));
		if (!match_vw_para(insPara)) {
			return 1;
		}
		execute_vw(insPara, commands[insPara[1]]);
		free(insPara);
		break;
	case 7:
		//sc命令有额外选项，要进行选项匹配
		insPara = (int*) malloc(4 * sizeof(int));
		if (!match_sc_para(insPara)) {
			return 1;
		}
		execute_sc(insPara, commands[insPara[2]], commands[insPara[3]]);
		free(insPara);
		break;
	case 8:
		execute_hp();
		break;
	case 9:
		return 0;
		break;
	case -1:
		printf("no such instrcution named %s\n", commands[0]);
		break;
	case -2:
		break;
	}
	return 1;
}

int matchInstruction() {
	if (commands[0] == NULL) {
		return -2;
	}
	char* instruct = commands[0];
	for (int i = 0; i < instructionSetLen; i++) {
		if (!strcmp(instruct, instructionSet[i])) {
			return i;
		}
	}
	return -1;
}

int match_ls_para(int* insPara) {
	insPara[1] = -1;
	insPara[0] = 0;
	for (int i = 1; commands[i] != NULL; i++) {

		if (commands[i][0] == '-') {
			if (strcmp(commands[i], "-r") == 0) {
				insPara[0] = 1;
			} else {
				printf("no such para named %s\n", commands[i]);
				return 0;
			}
		} else if (insPara[1] == -1) {
			insPara[1] = i;
		} else if (insPara[1] != -1) {
			printf("you have entered more than one path\n");
			return 0;
		}
	}
	return 1;
}

int match_ct_para(int* insPara) {
	insPara[0] = 0;
	insPara[1] = -1;
	for (int i = 1; commands[i] != NULL; i++) {

		if (commands[i][0] == '-') {
			if (strcmp(commands[i], "-d") == 0) {
				insPara[0] = 1;
			} else {
				printf("no such para named %s\n", commands[i]);
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
		printf("you have not entered path\n");
		return 0;
	}
	return 1;
}

int match_rm_para(int* insPara) {
	insPara[0] = 0;
	insPara[1] = -1;
	for (int i = 1; commands[i] != NULL; i++) {

		if (commands[i][0] == '-') {
			if (strcmp(commands[i], "-r") == 0) {
				insPara[0] = 1;
			} else {
				printf("no such para named %s\n", commands[i]);
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
		printf("you have not entered path\n");
		return 0;
	}
	return 1;
}

int match_sc_para(int* insPara) {
	insPara[0] = 0;
	insPara[1] = 0;
	//时间戳 or 部分文件名
	insPara[2] = -1;
	//路径
	insPara[3] = -1;
	for (int i = 1; commands[i] != NULL; i++) {
		if (commands[i][0] == '-') {
			if (strcmp(commands[i], "-lt") == 0) {
				insPara[0] = 1;
			} else if (strcmp(commands[i], "-gt") == 0) {
				insPara[1] = 1;
			} else {
				printf("no such para named %s\n", commands[i]);
				return 0;
			}
		} else if (insPara[2] == -1) {
			insPara[2] = i;
		} else if (insPara[3] == -1) {
			insPara[3] = i;
		} else {
			printf("you have entered too many data\n");
			return 0;
		}
	}
	if (insPara[0] == 1 && insPara[1] == 1) {
		printf("-lt -gt can not be used in the same time\n");
		return 0;
	}
	if (insPara[2] == -1) {
		printf("you have not entered time or name\n");
		return 0;
	}
	return 1;
}

int match_vw_para(int* insPara) {
	insPara[0] = 0;
	insPara[1] = -1;
	for (int i = 1; commands[i] != NULL; i++) {

		if (commands[i][0] == '-') {
			if (strcmp(commands[i], "-w") == 0) {
				insPara[0] = 1;
			} else {
				printf("no such para named %s\n", commands[i]);
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
		printf("you have not entered path\n");
		return 0;
	}
	return 1;
}

int main() {
	printf("welcome! If you don't konw how to start, please enter \"hp\".\n");
	while (1) {
		init();
		input();
		splitCommand();
		if (!executeCommand()) {
			break;
		}
	}
}