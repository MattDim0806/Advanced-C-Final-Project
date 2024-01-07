#ifndef __DATA_S__
#define __DATA_S__

typedef struct DataPath{     //路徑索引(double linked-list)
    struct DataPath *next;   
    struct DataPath *prev;
    char folder[10];         
    struct DataHead *Head;
}tDataPath;

typedef struct DataTree{
    struct DataTree *Right;  //右樹定義為同階層
    struct DataHead *Left;   //左樹定義為子階層
    struct DataTree *parent;
    char FileName[10];       //檔案名稱
    char folder;             //資料夾或資料
    int size;                //資料大小 
    void *content;           //資料指標 
}tDataTree;

typedef struct DataHead{
    struct DataTree *next;
    char Name[10];
}tDataHead;


//----------------------------------------------------------------------------------

tDataPath* Create_Init_DataPath(tDataHead *head);                         //
tDataHead* Create_Init_DataHead(char Name[]);                             //
void Add_DataPath(tDataPath *curr_Path,char target[],tDataHead *head);    //
void Del_DataPath(tDataPath *curr_Path);                                  //
void FolderSpaceFree(tDataHead *head);                                    //
void OPER_LoadDump(void);
void OPER_ls(tDataHead *head);                                            //
int OPER_cd(char target[],tDataPath *root,tDataPath *curr_Path);          //
void OPER_rm(tDataHead *head,char target[]);                              //
void OPER_mkdir(tDataHead *head,char target[]);                           //
void OPER_rmdir(tDataHead *head,char target[]);                           //
void OPER_put(tDataHead *head,char target[]);                             //
void OPER_get(tDataHead *head,char target[]);                             //                          
void OPER_cat(tDataHead *head,char target[]);                             //

#endif