#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "bf.h"
#include "bp_file.h"
#include "bp_datanode.h"
#include "bp_indexnode.h"

#define FILE_NAME "data.db"
#define RECORDS_NUM 1000
Record test_records[RECORDS_NUM];

#define CALL_OR_DIE(call)     \
  {                           \
    BF_ErrorCode code = call; \
    if (code != BF_OK)        \
    {                         \
      BF_PrintError(code);    \
      exit(code);             \
    }                         \
  }

void testCreateFile();
void testOpenFile();
void testCloseFile();
void testInsertEntry();
void testGetEntry();

int main() {
    printf("Testing B+ Tree functions\n");
    printf("Testing CreateFile\n");
    testCreateFile();
    printf("Testing OpenFile\n");
    testOpenFile();
    printf("Testing CloseFile\n");
    testCloseFile();
    printf("Testing InsertEntry\n");
    testInsertEntry();
    printf("Testing GetEntry\n");
    testGetEntry();
    return 0;
}

void testCreateFile() {
    int result;
    BF_Init(LRU);
    if (access(FILE_NAME, F_OK) == 0) {
        printf("File already present. Aborting...\n");
        return;
    }
    result = BP_CreateFile(FILE_NAME);
    if (result == 0) {
        printf("BP_CreateFile: SUCCESS\n");
    } else {
        printf("BP_CreateFile: FAIL\n");
    }
    BF_Close();
}


void testOpenFile() {
    BF_Block *block;
     int desc;
    BPLUS_INFO* info;

    BF_Init(LRU);
    info = BP_OpenFile(FILE_NAME, &desc);
    if (info != NULL) {
        printf("BP_Openfile: SUCCESS\n");
    } else {
        printf("BP_Openfile: FAIL\n");
    }
   
    free(info);
    BF_Close();
}

void testCloseFile() {
    int desc;
    BPLUS_INFO* info;
    BF_Init(LRU);
    info = BP_OpenFile(FILE_NAME, &desc);
    if (info != NULL) {
        int result = BP_CloseFile(desc, info);
        if (result == 0) {
            printf("BP_CloseFile: SUCCESS\n");
        } else {
            printf("BP_CloseFile: FAIL\n");
        }
    } else {
        printf("Corrupted Metadata, aborting...\n");
        printf("BP_CloseFile: FAIL\n");        
    }

    BF_Close();
}

void testInsertEntry() {
    int desc,success = 1;
    Record tempRec, *result;
    BPLUS_INFO* info;

    result = &tempRec;
    BF_Init(LRU);
    info = BP_OpenFile(FILE_NAME, &desc);
    
    if (info == NULL) {
        printf("Corrupted Metadata, aborting...\n");
        printf("BP_InsertEntry: FAIL/n");   
        BF_Close();
        return;
    }

    for (int i = 0; i < RECORDS_NUM; i++) {
        test_records[i] = randomRecord();
        BP_InsertEntry(desc,info, test_records[i]);
    }

   for (int i = 0; i < RECORDS_NUM; i++) {
        if (BP_GetEntry(desc, info, test_records[i].id, &result) == -1) {
            success = 0;
            break;
        }
   }

    if (success) {
        printf("BP_InsertEntry: SUCCESS\n");
        //printf("Current state of tree leaf level:\n");
        //PrintRecsOrdered(desc,info);
    } else {
        printf("BP_InsertEntry: FAIL\n");
    }
    BP_CloseFile(desc, info);
    BF_Close();
}

void testGetEntry() {
    int desc,success = 1;
    Record tempRec,record;
    BPLUS_INFO* info;
    BF_Init(LRU);
    info = BP_OpenFile(FILE_NAME, &desc);
    if (info == NULL) {
        printf("Corrupted Metadata, aborting...\n");
        printf("BP_GetEntry: FAIL/n");           
        BF_Close();
        return;
    }

    Record* result = &tempRec;
    for (int i = 0; i < RECORDS_NUM; i++) {
        if (BP_GetEntry(desc, info, test_records[i].id, &result) == -1) {
            success = 0;
            break;
        }
    }


    if (success) {
        printf("BP_GetEntry: SUCCESS.\n");
    } else {
        printf("BP_GetEntry: FAIL.\n");
    }
    BP_CloseFile(desc, info);
    BF_Close();
}
