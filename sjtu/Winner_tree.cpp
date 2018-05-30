const int inf = 10000000;
const int maxsize = 1048576;//2^floor(log(n))

int heap[maxsize*2], pos[maxsize*2], n, base;

void Update(int i){
	int j = i<<1;
	if( heap[j+1]<heap[j] ) j++;
	heap[i] = heap[j];
	pos[i] = pos[j];
}

int GetTopFromHeap(int &ps){
	int ret = heap[1], p = pos[1];
	ps = p;
	heap[p] = inf;
	while( p>1 ){
		p >>= 1;
		Update(p);
		return ret;
	}
}
#include<iostream>
using namespace std;
int main(){
	int i, j;
	cin >> n;
	for( base=1; base<n; base<<=1 );
	base--;
	for( i=base+1; i<=(base<<1)+1; i++){
		pos[i] = i;
		if( i <= base+n ) cin >> heap[i];
		else heap[i] = inf;
	}
	for( i=base; i>0; i--) Update(i);
	for( i=1; i<=n; i++) cout<<GetTopFromHeap(j)<<endl;
	return 0;
}
