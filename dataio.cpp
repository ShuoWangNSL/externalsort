#include"dataio.h"

int64_t MemSize = 1073741824;
int64_t ExSize = 17179869184;
int64_t MergeSize = 67108864;
int64_t MemSizeBlock = 134217728;
int64_t ExSizeBlock = 2147483648;
int64_t MergeSizeBlock = 8388608;
/*
int64_t MemSize = 2097152/2*1024;
int64_t ExSize = 16777216*1024;
int64_t MergeSize = 262144/4*1024;
int64_t MemSizeBlock = MemSize/8;
int64_t ExSizeBlock = ExSize/8;
int64_t MergeSizeBlock = MergeSize/8;
*/
int input(int64_t* mem,FILE * fp){
	int64_t nReaded=0;
	nReaded = fread(mem,sizeof(int64_t),MemSizeBlock,fp);
	fseek(fp,0,SEEK_SET);
	
	if (nReaded == 0)
		return 0;
	else if (nReaded == MemSizeBlock)
		return 1;
	else
		return -1;
}

int output(int64_t* mem,FILE * fp){
	int64_t nWrited=0;
	nWrited = fwrite(mem,sizeof(int64_t),MemSizeBlock,fp);
	
	if (nWrited == 0)
		return 0;
	else if (nWrited == MemSizeBlock)
		return 1;
	else
		return -1;
}

int64_t call(int64_t* addr,FILE* fp){
	int64_t nReaded=0;
	nReaded = fread(addr,sizeof(int64_t),MergeSizeBlock,fp);
//	fseek(fp,0,SEEK_SET);
/*	if (nReaded == 0)
		return 0;
	else if (nReaded == MergeSizeBlock)
		return 1;
	else
		return -1;
*/
	return nReaded;
}

int send(int64_t* addr,FILE * fp){
	int64_t nWrited=0;
	nWrited = fwrite(addr,sizeof(int64_t),MergeSizeBlock,fp);
	if (nWrited == 0)
		return 0;
	else if (nWrited == MergeSizeBlock)
		return 1;
	else
		return -1;
}