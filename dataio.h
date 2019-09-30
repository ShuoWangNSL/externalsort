#include<memory.h>
#include<stdlib.h>
#include<stdio.h>


//int64_t MemSize = 2147483648;
//int64_t ExSize = 17179869184;
//int64_t MergeSize = 268435456;
extern int64_t MemSize;
extern int64_t ExSize;
extern int64_t MergeSize;
extern int64_t MemSizeBlock;
extern int64_t ExSizeBlock;
extern int64_t MergeSizeBlock;
int input(int64_t* ,FILE *);
int64_t call(int64_t*,FILE* );
int output(int64_t* ,FILE *);
int send(int64_t* ,FILE * );