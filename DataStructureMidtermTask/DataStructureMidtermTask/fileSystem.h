#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
	int isDir;
	char name[50];
	char content[100];
	time_t lastUpdate;
	struct Node* firstChild;
	struct Node* rightSibling;
}Node, * Root;

void init();

int toSplitPath(char*);

int execute_ct(int*, char*);

int execute_ls(int*, char*);
void ls_r(Node*);

int execute_cd(char*);

int execute_rm(int*, char*);
void rm_recur(Node*);

int execute_vw(int*, char*);

int execute_mv(char*, char*);

int execute_cp(char*, char*);

int execute_sc(int*, char*, char*);
void time_sc_recur(Node*, char*, char*, int);
void name_sc_recur(Node*, char*, char*);
int kmp(char*, char*);

int execute_hp();


void input();

void splitCommand();

int executeCommand();

int matchInstruction();

int match_ls_para(int*);

int match_ct_para(int*);

int match_rm_para(int*);

int match_sc_para(int*);

int match_vw_para(int*);
