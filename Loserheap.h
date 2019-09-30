#include <stdlib.h>
class Loserheap{
public:
	Loserheap(int64_t* a);
	int adjust(int i,int64_t insertnum);
	int getindex();
	int64_t getwinner();
private:
	int heap[16];
	int64_t leaves[16];
};