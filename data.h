#ifndef __DATA_S__
#define __DATA_S__

typedef struct DataPath{
    struct DataPath *next;
    struct DataPath *prev;
    char folder[10];
}tDataPath;

typedef struct DataTree{
    struct DataTree *Right;  //右樹定義為同階層
    struct DataTree *Left;   //左樹定義為子階層
    int size;                //資料大小 
    char folder;             //資料夾或資料
    void *content;           //資料指標 
}tDataTree;

//----------------------------------------------------------------------------------

void Init_DataPath(tDataPath *root);
void Add_DataPath(tDataPath *curr_Path);
void OPER_LoadDump(void);
void OPER_put(tDataTree *head,char target[]);
void OPER_cat(tDataTree *head,char target[]);

#endif