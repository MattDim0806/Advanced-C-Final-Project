#include "data.h"

char* UI_SelectFunc_Init(int *SizeOfPartition);  //操作選擇
void UI_SelectFunc_Oper(char *oper,tDataPath *root,tDataPath *curr_Path);  //操作選擇
void UI_Help(void);