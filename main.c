#include "main.h"
#include "ui.h"
#include "data.h"

//---------------------------------------------------------------------

void main() {
    int SizeOfPartition=-1;           //空間大小
    char *ptr_Partition;              //空間指標
    char oper[2][10];           //輸入command轉換運算及引數
    
    tDataPath *root=(tDataPath*)malloc(sizeof(tDataPath));   //路徑暫存
    tDataPath *curr_Path=root;
    Init_DataPath(root);                                     //初始化

    //------------------------------------------------------------------

    ptr_Partition=UI_SelectFunc_Init(&SizeOfPartition);      //空間初始化
    UI_Help();
    
    //------------------------------------------------------------------
    

    while(1){
        UI_SelectFunc_Oper(oper,root,curr_Path);
        printf("%s",oper);
    } 
 
}