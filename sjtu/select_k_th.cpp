/*************************************************************************
	> File Name: select_k_th.cpp
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2018-03-04 22:06:18
 ************************************************************************/

//  select k_th smallest element
// a 数组指针
// b e 在 [b,e]范围内寻找第 k 个 
int select(int* a, int b, int e, int k){
	if(b==e) return a[b];//其实应该判断一下 b e 的大小
	//因为后面有递归调用，所以最后返回值是从上一行返回的
	// 设置随机哨兵
	int x = a[b+rand()%(e-b+1)], i = b, j = e;
	i--;j++;
	while(i<j){
		// 交换哨兵之间的值，使得在哨兵前的都是小于，后面的都是大于的
		//  < > 不可能同时满足，所以 i < j 
		while( a[++i]<x );
		while( a[--j]>x );
		// 交换 值
		if( i<j ) std::swap(a[i], a[j]); 
	} 
	if( j==e ) j--;//让 i 不会溢出 
	// i 和 k 比较，选出大于部分的，还是小于部分的，递归 
	i = j-b+1;
	if( k<=i ) return select(a, b, j, k);
	else return select(a, j+1, e, k-i);
} 

