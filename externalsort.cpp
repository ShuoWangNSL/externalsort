#include<iostream>
#include<stdlib.h>
#include<string>
#include"quicksort.h"
#include"generate.h"
#include"Loserheap.h"
#include"dataio.h"
using namespace std;
string data_orgin = "data_orgin.bin";
string data_out = "data_out.bin";

int main(){

	int64_t k,i,j =0;
	int index;
	string filename[16];
	int64_t *mem = (int64_t *) malloc(MemSize);
	if (mem == NULL)cout<<"memory is not allocated!"<<endl;
    else cout<<"sucess"<<endl;
//	int64_t *mergemem = (int64_t *) malloc(MergeSize);
    int64_t *mergemem = (int64_t *) malloc(MemSize);
    if (mergemem == NULL)cout<<"mergememory is not allocated!"<<endl;
    else cout<<"mergemem sucess"<<endl;
	int64_t **memptr =(int64_t**)malloc(16*sizeof(int64_t *));
	for(i=0;i<16;i++)
		memptr[i]=mem + MemSizeBlock/16*i;

	FILE * fp2 = fopen("./data_out.bin","wb+");
	if (fp2 == NULL)
		cout<<"Open error!"<<endl;
	FILE * fpb = fp2;

	for (i = 0;i<16;i++){
		filename[i] = string("./data_orgin")+to_string(i);
	}	

	FILE ** fptra = (FILE**)malloc(16*sizeof(FILE *));
	for (i = 0;i<16;i++){
		fptra[i] = fopen(filename[i].data(),"wb+"); 
	}

	if (!generate(mem,fptra))
		cout<<"Failed to generate numbers"<<endl;
	else
		cout<<"Success to generate numbers"<<endl;

	for(i=0;i<16;i++){
		if(1 != input(mem,fptra[i]))
			cout<<"Input error"<<endl;
		fclose(fptra[i]);
		fptra[i] = fopen(filename[i].data(),"wb+");
		qsort((void*)mem,MemSizeBlock,sizeof(int64_t),compare);
		if(1 != output(mem,fptra[i]))
			cout<<"Output error"<<endl;	
	}

	for(i=0;i<16;i++)
		fclose(fptra[i]);

	for(i=0;i<16;i++){
		fptra[i] = fopen(filename[i].data(),"rb+");

	}
	
	int Exflag[16]={0};
	int Memflag[16] ={0};
	int64_t length[16] = {MergeSizeBlock};
	for (i = 0; i < 16; i++) {
		length[i] = MergeSizeBlock;
	}

	for(i=0;i<16;i++){
		int64_t t = 0;
		t = call(memptr[i],fptra[i]);
		if (t == 0){
			Exflag[i] = 1;
			cout<<"Call Error or File EOF."<<endl;
		}
		else if (t < MergeSizeBlock){
			Exflag[i] = 1;
			cout <<"FILE EOF."<<endl;
		}
	}

	for (i=0;i<16;i++)
		cout<<memptr[i][0]<<endl;

	int64_t a[16]={0};
	for (i=0;i<16;i++)
			a[i] = memptr[i][0];
	k = 0;
	for(i = 1;i<16;i++)
		if (a[i]<a[k])k= i;
	Loserheap lp(a);

	int64_t count = 0;

	int64_t cnt[16] ={0};
	mergemem[0] = memptr[k][0];
	count++;
	index = k;
	cnt[index] = 1;
	int64_t loop = 1;
	while(true){
		if(cnt[index] == length[index]){
			cout<<"memptr "<<index<<" is empty!Please Call!"<<endl;
			length[index] = call(memptr[index],fptra[index]);
			if (length[index] == 0){
				Exflag[index] = 1;
				if (Exflag[0]==1 && Exflag[1]==1 && Exflag[2]==1 && Exflag[3]==1 && Exflag[4]==1 && Exflag[5]==1 && Exflag[6]==1 && Exflag[7]==1)//all are 1
					break;
				cout<<"File slice "<<index<<" is over!"<<endl;
				index = lp.adjust(index,1125899906842679);
				mergemem[loop] = lp.getwinner();
				count++;
				cnt[index]++;
				loop++;
				continue;
			}
			else{
				cnt[index] = 0;
				index = lp.adjust(index,memptr[index][cnt[index]]);
				mergemem[loop] = lp.getwinner();
				count++;
				cnt[index]++;
			}
		}
		else{
			index = lp.adjust(index,memptr[index][cnt[index]]);
			mergemem[loop] = lp.getwinner();
			count++;
			cnt[index]++;
		}
		loop++;
		if ( loop == MemSizeBlock ){
			loop = 0;
//			if(1 != send(mergemem,fpb))
            if(1 != output(mergemem,fpb))
			cout<<"Send error"<<endl;
		}
	}

	cout<<count<<endl;
	fclose(fpb);

    fpb = fopen("./data_out.bin","rb");
    if(calhash(mem,fpb))
        cout<<"get hash"<<endl;
	return 0;
}
