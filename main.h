#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>    //結構和常數用於處理文件和文件系統的屬性信息

//------------------------------------------------------------------

typedef enum  Operator{
    ls,
    cd,
    rm,
    mkdir,
    rmdir,
    put,
    get,                                    
    cat,
    ststus,
    help,
    exit_and_store_img
}eOperator;



// |-- root
//     |-- text1.txt
//     |-- text2.txt
//     |-- folder1
//         |-- folder2
//             |-- text3.txt
//         |-- text1.txt