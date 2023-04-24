#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

void input();
void splitCommand();
void executeCommand();
int matchInstruction();
int match_ls_para(int*);
int match_ct_para(int*);
int match_rm_para(int*);
int match_sc_para(int*);
int execute_ls(int*, char*);
int execute_ct(int*, char*);