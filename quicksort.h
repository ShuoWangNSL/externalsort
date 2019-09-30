#include<algorithm>
int compare(const void* a,const void* b);


int compare(const void* a,const void* b){
	if (*(int64_t*)a - *(int64_t*)b > 0)
		return 1;
	else if (*(int64_t*)a - *(int64_t*)b < 0)
		return -1;
	else 
		return 0;
}