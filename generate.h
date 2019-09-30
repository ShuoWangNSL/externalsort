#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include"dataio.h"
using namespace std;
int64_t modnum = 1125899906842679;
int64_t ID = 2016211131;
int64_t hfunc(int64_t X){
	return (3 * X + 5) % modnum;
}

bool generate(int64_t* mem,FILE ** fptra){

    int64_t i,j = 0;
	int64_t nWrited=0;
	int64_t nSize=0;
	mem[0] = ID;
	for (i = 1;i < MemSizeBlock;i++)
		mem[i] = hfunc(mem[i-1]);	
	nWrited = fwrite(mem,sizeof(int64_t),MemSizeBlock,fptra[0]);
	fseek(fptra[0],0,SEEK_SET);
	nSize = nSize + nWrited;
	for (j=1;j<16;j++){
		mem[0] = hfunc(mem[MemSizeBlock-1]);
		for (i = 1;i < MemSizeBlock;i++)
			mem[i] = hfunc(mem[i-1]);
		nWrited = fwrite(mem,sizeof(int64_t),MemSizeBlock,fptra[j]);
		fseek(fptra[j],0,SEEK_SET);
		nSize = nSize + nWrited;
	}
	if (nSize == ExSizeBlock)
		return true;
	else
		return false;
}

bool calhash(int64_t*mem,FILE *fptrb){
    int64_t i,j = 0;
    int64_t nReaded=0;
    int64_t nSize=0;
    int64_t tmp =0;
    int64_t cnt=0;

    nReaded = fread(mem,sizeof(int64_t),MemSizeBlock,fptrb);
    nSize = nSize + nReaded;
    tmp = mem[0];
    cout<<mem[0]<<endl;
    for (i = 1;i < MemSizeBlock;i++){
        if(i<30)cout<<mem[i]<<endl;
        cnt++;
        tmp = (3*tmp+mem[i]) % modnum;
    }

    for (j=1;j<16;j++){
        nReaded = fread(mem,sizeof(int64_t),MemSizeBlock,fptrb);
        nSize = nSize + nReaded;
        for (i = 0;i < MemSizeBlock;i++){
            if(i<30)cout<<mem[i]<<endl;
            cnt++;
            tmp = (3*tmp+mem[i]) % modnum;
        }
    }
    cout<<tmp<<endl;
    if (nSize == ExSizeBlock && cnt+1 ==ExSizeBlock)
        return true;
    else
        return false;
}