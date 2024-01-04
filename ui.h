#include "data.h"

char* UI_SelectFunc_Init(int *SizeOfPartition);  //操作選擇
void UI_SelectFunc_Oper(char oper[][10],tDataPath *root,tDataPath *curr_Path);  //操作選擇
void UI_Help();
void UI_ls();
void UI_status(int SizeOfPartition);