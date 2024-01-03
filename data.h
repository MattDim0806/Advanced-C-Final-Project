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
    struct DataTree *parent;
    char FileName[10];       //檔案名稱
    char folder;             //資料夾或資料
    int size;                //資料大小 
    void *content;           //資料指標 
}tDataTree;

typedef struct DataHead{
    struct DataTree *next;
}tDataHead;


//----------------------------------------------------------------------------------

tDataPath* Create_Init_DataPath();
tDataHead* Create_Init_DataHead();
void Add_DataPath(tDataPath *curr_Path);
void OPER_LoadDump(void);
void OPER_ls(tDataHead *head);
void OPER_mkdir(tDataHead *head,char target[]);
void OPER_put(tDataHead *head,char target[]);
void OPER_cat(tDataHead *head,char target[]);

#endif