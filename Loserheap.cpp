#include"Loserheap.h"
#include<iostream>
using namespace std;
Loserheap::Loserheap(int64_t * a){
	int i = 0;
	int k = 0;
	for(i = 1;i<16;i++)
		if (a[i]<a[k])k= i;
	for (i=0;i<16;i++)
		Loserheap::leaves[i] = a[i];
	for (i=0;i<16;i++)
		Loserheap::heap[i] = k;
	for (i=15;i>=0;i--)
		Loserheap::adjust(i,Loserheap::leaves[i]);
	for (i=0;i<16;i++)std::cout<<Loserheap::heap[i]<<":"<<Loserheap::leaves[Loserheap::heap[i]]<<endl;
	std::cout<<endl;
	for (i=0;i<16;i++)std::cout<<Loserheap::leaves[i]<<endl;

}

int Loserheap::getindex(){
	return heap[0];
}
int64_t Loserheap::getwinner(){
	return leaves[heap[0]];
}

int Loserheap::adjust(int i,int64_t insertnum){
	leaves[i] = insertnum;
	int parent = (i+16)/2;
	while (parent>0){
		if (leaves[i] > leaves[heap[parent]]){
			int tmp = heap[parent];
			heap[parent] = i;
			i = tmp;
		}
		parent = parent / 2;
	}
	heap[0] = i;
	return i;
}