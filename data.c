#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <sys/stat.h>

//----------------------------------------------------------------------------------

#include "data.h"

//----------------------------------------------------------------------------------

extern int SizeofRemaining;

//----------------------------------------------------------------------------------

tDataPath* Create_Init_DataPath(tDataHead *head) {
    //建立並初始化路徑
    tDataPath* root = (tDataPath*)malloc(sizeof(tDataPath));
    strcpy(root->folder,"root");
    root->next = NULL;
    root->prev = NULL;
    root->Head=head;

    return root;
}

tDataHead* Create_Init_DataHead(char Name[]) {
    //建立並初始化Head
    tDataHead* head = (tDataHead*)malloc(sizeof(tDataHead));
    strcpy(head->Name,Name);
    head->next = NULL;

    //需要一併存入Dump內(還原檔案時需要)
    SizeofRemaining -= sizeof(tDataHead);
    return head;
}

void Add_DataPath(tDataPath* curr_Path,char target[],tDataHead *head) {
    tDataPath* new_path = (tDataPath*)malloc(sizeof(tDataPath));

    strcpy(new_path->folder,target);
    curr_Path->next = new_path;
    new_path->prev = curr_Path;
    new_path->Head=head;
}

void Del_DataPath(tDataPath *curr_Path){
    curr_Path->prev->next=NULL;
}

void FolderSpaceFree(tDataHead* head) {
    int flag = 0;

    if (head->next != NULL) {                         //若子目錄內非空
        tDataTree* temp = head->next;
        tDataTree* prev=NULL;

        while (flag == 0) {                           
            prev = temp;                              //儲存當前節點

            if (temp->Right != NULL) {                //若非空
                temp = temp->Right;                   //繼續走訪
            }else {                                   //若空
                flag = 1;                             //舉旗標，脫離while
            }

            if (prev->parent == NULL) {     //若當前節點無子節點(即當前節點為子目錄內第一筆資料)
                head->next = NULL;          //斷開Head鏈結
            }else {                         //若非子目錄內第一筆資料
                prev->parent->Right = NULL; //斷開與前一資料之鏈結
            }

            if (prev->folder == 1) {                 //若當前節點為資料夾
                FolderSpaceFree(prev->Left);         //繼續遞迴該子目錄內資料節點
                SizeofRemaining += sizeof(tDataTree);//剩餘空間'加回'結構大小
            }else {                                  //若當前節點為檔案
                SizeofRemaining += sizeof(tDataTree);//剩餘空間'加回'結構大小
                SizeofRemaining += prev->size;       //剩餘空間'加回'content內容大小
                free(prev->content);                 //釋放content內容空間
            }
            free(prev);                              //釋放資料節點空間
        }
    }
    SizeofRemaining += sizeof(tDataHead);            //剩餘空間'加回'Head結構大小
    free(head);                                      //釋放Head結構空間
}

void OPER_LoadDump() {     //Load ().dump
    FILE* fp;
    char LoadFile[15];

    printf("Load Flie Name:");
    scanf("%s", LoadFile);

    fp = fopen(LoadFile, "r+");
    if (fp == NULL) {
        printf("failed to open the file.\n");
    }
    else {
        printf("Load Success.\n");
    }
}

void OPER_ls(tDataHead* head) {
    if (head->next == NULL) {                              //Head->next為NULL表示該路徑為空
        printf("\n");
        return;
    }
    tDataTree* temp = head->next;

    while (temp != NULL) {                                 //走訪節點
        if (temp->folder == 1) {                           //型態為資料夾
            printf("\x1B[0;34m""%s ", temp->FileName);       //藍色字型
        }else {                                            //型態非資料夾
            printf("\x1B[0m""%s ", temp->FileName);          //黑色字型
        }

        if (temp->Right == NULL) {                         //走訪完畢
            break;
        }
        temp = temp->Right;
    }
    printf("\n");
}

int OPER_cd(char target[],tDataPath *root,tDataPath *curr_Path){
    if(!strcmp("\0",target)){                    //輸入之目標路徑"名稱"不可為空
        printf("Path Name cannot be empty!\n");
        return -1;
    }
    
    int exit=0;                                  
    tDataTree *temp;
    tDataHead *head=curr_Path->Head;

    
    if(!strcmp(target,"..")){                                           //往上層
        if(!strcmp(head->Name,"root")){                                 //使用Head確認是否已在根目錄
            printf("already in the root\n");
        }else{                                   
            Del_DataPath(curr_Path);                                    //若否，先使用副程式移除DataPath連接
            return 0;                                                   //0表示路徑往上層
        }
    }else{                                                              //往下層
        if (head->next != NULL) {
            temp = head->next;
            while(1){
                if((!strcmp(temp->FileName,target)) && temp->folder==1){//尋找子目錄 
                    exit=1;                                             //找到目標資料夾
                    break;
                }
                if(temp->Right!=NULL){                                  //非空，繼續搜尋
                    temp=temp->Right;
                }else{
                    break;
                }
            }
        }
        if(exit==1){                                                    //存在子目錄
            Add_DataPath(curr_Path,temp->FileName,temp->Left);          //添加路徑               
            return 1;                                                   //1表示路徑往下走
        }
    }
    printf("Folder does not exist !\n");                                //找不到目標資料夾
    return -1;                                                          //-1表示失敗
}

void OPER_rm(tDataHead *head,char target[]){
    if(!strcmp("\0",target)){                           //輸入之目標檔案"名稱"不可為空
        printf("File Name cannot be empty!\n");
        return;
    }

    int exit=0;
    tDataTree *temp;

    if (head->next != NULL) {
        temp = head->next;

        while(temp!=NULL)
        {                                               //尋找目標檔案
            if(!strcmp(temp->FileName,target) && temp->folder==0){    
                exit=1;                                 //找到
                break;
            }
            if(temp->Right!=NULL){                      //非空，繼續搜尋
                temp=temp->Right;
            }else{
                break;
            }
        }
    }
    if(exit==1){                                       //目標檔案存在
        if(temp->parent==NULL){                        //處理鏈結
            head->next = temp->Right;
        }else if(temp->Right==NULL){
            temp->parent->Right=NULL;
        }else{
            temp->parent->Right=temp->Right;
            temp->Right->parent=temp->parent;
        }
        SizeofRemaining+=sizeof(tDataTree);            //剩餘空間'加回'結構大小
        SizeofRemaining+=temp->size;                   //剩餘空間'加回'content內容大小
        free(temp->content);                           //釋放結構空間
        free(temp);                                    //釋放content內容空間
        return;
    }else{
        printf("File does not exist !\n");
        return;
    }
}

void OPER_mkdir(tDataHead *head,char target[]){
    if(!strcmp("\0",target)){                                 //輸入之目標檔案"名稱"不可為空
        printf("Folder Name cannot be empty!\n");
        return;
    }
    
    tDataTree* new = (tDataTree*)malloc(sizeof(tDataTree));   //動態存取(樹狀資料節點)
    SizeofRemaining -= sizeof(tDataTree);                     //剩餘空間'減去'結構大小

    strcpy(new->FileName, target);                            //資料夾名稱
    new->content = NULL;                                      //將資料指標為NULL
    new->folder = 1;                                          //是資料夾
    new->Left = Create_Init_DataHead(target);                 //子階層建立並初始化Head"folder"
    new->Right = NULL;                                        //同階層預設為NULL
    new->size = 0;                                            //content之資料大小

    if (head->next == NULL) {                                 //Head為空=>此檔案為該目錄之第一個檔案
        new->parent = NULL;                                   //此節點無前一節點
        head->next = new;                                     //將Haed指向此節點
    }else{
        tDataTree* temp = head->next;            

        while ((temp->Right) != NULL) {                       //走訪至最後一節點位置
            temp = temp->Right;
        }
        new->parent=temp;                                     //與最後一節點建立雙向鏈結
        temp->Right = new;
    }
}

void OPER_rmdir(tDataHead *head,char target[]){
    if(!strcmp("\0",target)){                                  //輸入之資料夾"名稱"不可為空
        printf("Folder Name cannot be empty!\n");
        return;
    }

    int exit=0;
    tDataTree *temp;

    if (head->next != NULL) {
        temp = head->next;

        while(temp!=NULL)
        {                                                     //尋找目標子目錄
            if((!strcmp(temp->FileName,target)) && temp->folder==1){
                exit=1;                                       //找到
                break;
            }
            if(temp->Right!=NULL){                            //非空，繼續搜尋
                temp=temp->Right;
            }else{
                break;
            }
        }
        if(exit==1){                                          //目標子目錄存在
            if(temp->parent==NULL){                           //處理樹狀結構鏈結
                head->next = temp->Right;
            }else if(temp->Right==NULL){
                temp->parent->Right=NULL;
            }else{
                temp->parent->Right=temp->Right;
                temp->Right->parent=temp->parent;
            }
            FolderSpaceFree(temp->Left);                      //使用遞回處理子目錄內剩餘檔案
            SizeofRemaining+=sizeof(tDataTree);               //剩餘空間'加回'結構大小
            free(temp);                                       //釋放結構
            return;
        }
    }
    printf("Folder does not exist !\n");
}

void OPER_put(tDataHead* head, char target[]) {
    if(!strcmp("\0",target)){                    //輸入之目標檔案"名稱"不可為空
        printf("File Name connot be empty!\n");
        return;
    }

    int size;                                   //檔案大小
    char* content;                              //檔案內容存放指標
    struct stat st;                             //<sys/stat.h>獲取文件狀態
    FILE* fp;                                   //資料指標

    fp = fopen(target, "rb");                   //使用二進制格式開啟
    if (fp == NULL) {                           //若為空表示檔案不存在
        printf("failed to open file '%s'\n", target);
        return;
    }

    stat(target, &st);                          //獲取檔案大小(Byte)
    size = st.st_size;

    if (SizeofRemaining < size) {               //若大於剩餘空間無法則放入
        printf("Not enough remaining space !\n");
        return;
    }

    content = (char*)malloc(size);              //動態配置對應空間大小存放資料
    fread(content, 1, size, fp);                //使用函數將外部檔案複製進記憶體
    fclose(fp);                                 //關閉檔案

    // -----------------------------------------------------
 
    tDataTree* new = (tDataTree*)malloc(sizeof(tDataTree)); //動態存取(樹狀資料節點)
    SizeofRemaining -= sizeof(tDataTree);                   //剩餘空間'減去'結構大小

    strcpy(new->FileName, target);               //檔案名稱
    new->content = content;                      //將資料指標指向先前搬移至記憶體之位置
    new->folder = 0;                             //非資料夾
    new->Left = NULL;                            //無子階層
    new->Right = NULL;                           //同階層預設為NULL
    new->size = size;                            //儲存content之資料大小
    SizeofRemaining -= size;                     //剩餘空間'減去' content內容大小

    if (head->next == NULL) {                    //Head為空=>此檔案為該目錄之第一個檔案
        new->parent = NULL;                      //此節點無前一節點
        head->next = new;                        //將Haed指向此節點
    }else{
        tDataTree* temp = head->next;            

        while ((temp->Right) != NULL) {          //走訪至最後一節點位置
            temp = temp->Right;
        }
        new->parent=temp;                        //與最後一節點建立雙向鏈結
        temp->Right = new;
    }
}

void OPER_get(tDataHead* head, char target[]) {
    if(!strcmp("\0",target)){                           //輸入之檔案"名稱"不可為空
        printf("File Name connot be empty!\n");
        return;
    }

    int exit=0;
    tDataTree *temp;

    if (head->next != NULL) {
        temp = head->next;

        while(temp!=NULL)
        {                                               //尋找目標檔案
            if(!strcmp(temp->FileName,target) && temp->folder==0){    
                exit=1;                                 //找到
                break;
            }
            if(temp->Right!=NULL){                      //非空，繼續搜尋
                temp=temp->Right;
            }else{
                break;
            }
        }
    }
    if(exit==1){                                        //目標檔案存在
        char* content=temp->content;
        char FileName[20]="Dump\\";                     //路徑名稱
        
        strcat(FileName, target);                       //路徑名稱+檔案名稱
        CreateDirectory("Dump", NULL);                  //創建Dump子目錄
        FILE *fp = fopen(FileName, "wb");              
        fwrite(content,sizeof(char),temp->size,fp);     //檔案寫出
        fclose(fp);                                     //關閉檔案指標
    }else{
        printf("File does not exist !\n");              //目標檔案不存在
        return;
    }
}

void OPER_cat(tDataHead* head, char target[]) {
    if(!strcmp("\0",target)){                           //輸入之檔案檔案"名稱"不可為空
        printf("File Name connot be empty!\n");
        return;
    }

    int exit=0;
    tDataTree *temp;

    if (head->next != NULL) {
        temp = head->next;

        while(temp!=NULL)
        {                                               //尋找目標檔案
            if(!strcmp(temp->FileName,target) && temp->folder==0){    
                exit=1;                                 //找到
                break;
            }
            if(temp->Right!=NULL){                      //非空，繼續搜尋
                temp=temp->Right;
            }else{
                break;
            }
        }
    }
    if(exit==1){                                        //目標檔案存在
        char* content=temp->content;                    //索引至檔案位置
        for (int count = 0; count < temp->size; count++) {
            printf("%c", content[count]);               //輸出
        }
        printf("\n");
    }else{                                              //目標檔案不存在
        printf("File does not exist !\n"); 
        return;
    }
}