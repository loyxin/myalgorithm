 
template<typename T>

void exch(T& x, T& y){
	// important 
	if(x.getValue() == y. getValue()) return ;
	T temp = x;
	x = y;
	y = temp;
}
#include<iostream>
template<typename T>
void show(T * a, int length){
	for(int i = 0; i< length;++i){
		std::cout<<(a+i)->getValue()<<std::endl;
	}
}
template<typename T>
bool more(T x, T y)
{
	if(x.getValue() > y.getValue() )
		return true;
	else
		return false;
}
template<typename T>

bool isSorted(T* x, int length,bool (*more)(T , T )){
	for(int i = 1; i<length; ++i){
		if(more(*(x+i-1)),*(x+i)) return false;
	return true;
	}
}


class Double{
	public:
		Double():x(0.0){
		};
		double getValue(){return x;
		}
		void setValue(double x){ this->x = x;
		}
	public:
		double x;
};

template <typename T>
void selectSort(T* a, int length){
	for(int i = 0;i<length;++i){
		int min = i;
		for(int j = i + 1; j < length; ++j)
		// 选出第i个小的 
			if(more<T>(a[min],a[j])) min = j;
		exch<T>(a[i],a[min]);
	}
}
template <typename T>
void InsertSort(T* a, int length){
	for(int i = 1;i<length;++i){
		//像扑克牌一样插入 
		for(int j = i; j>0&&more(a[j-1],a[j]);--j)
		exch(a[j],a[j-1]);
	}
}
template <typename T>
void ShellSort(T* a, int length){
	int h = 1;
	/*
	*保证每次排序确定在ｈ的间隔中整体是排序好的，但是也不是完全都排序好，只是保证每次排序　优中选优
	比如３的倍数ｈ，
	从ｈ处遍历到底，前(l-h)个要比后(l-h)要排序好了
	h减少3倍,再由于减少了，到原先2/3处之后，像冒泡排序好一样，保证整体排序好
	比较直观的是比如2分，后一半都是最小的倒叙，最小的每次都会交换到前面，保证是每次的前h里面，最后离第一位差1
	*/
	while(h<length/3) h = 3*h + 1;
	while(h>=1){
		for(int i = h;i<length;++i){
			for(int j = i; j>=h && more(a[j-h],a[j]);j-=h)
				exch(a[j],a[j-h]);
		}
		h/=3;
	}
} 
const int n = 100;
int main(){
	Double* a = new Double[n];
	for(int i = 0; i < n; ++i){
		a[i].setValue(rand()/(RAND_MAX/1000));
	}
	show(a,n);
	std::cout<<std::endl;
//	selectSort<Double> (a,n);
//	InsertSort(a,n);
	ShellSort(a,n);
	show(a,n);	
}