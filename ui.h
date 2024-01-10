#include "data.h"

tDataTree* UI_SelectFunc_Init(int *SizeOfPartition);                                 
void UI_SelectFunc_Oper(char oper[][10],tDataPath *root,tDataPath *curr_Path);  
void UI_Help();                                                                 
void UI_status(int SizeOfPartition);