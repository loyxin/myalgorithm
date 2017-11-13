 
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
		// ѡ����i��С�� 
			if(more<T>(a[min],a[j])) min = j;
		exch<T>(a[i],a[min]);
	}
}
template <typename T>
void InsertSort(T* a, int length){
	for(int i = 1;i<length;++i){
		//���˿���һ������ 
		for(int j = i; j>0&&more(a[j-1],a[j]);--j)
		exch(a[j],a[j-1]);
	}
}
template <typename T>
void ShellSort(T* a, int length){
	int h = 1;
	/*
	*��֤ÿ������ȷ���ڣ�ļ��������������õģ�����Ҳ������ȫ������ã�ֻ�Ǳ�֤ÿ����������ѡ��
	���磳�ı����裬
	�ӣ账�������ף�ǰ(l-h)��Ҫ�Ⱥ�(l-h)Ҫ�������
	h����3��,�����ڼ����ˣ���ԭ��2/3��֮����ð�������һ������֤���������
	�Ƚ�ֱ�۵��Ǳ���2�֣���һ�붼����С�ĵ�����С��ÿ�ζ��ύ����ǰ�棬��֤��ÿ�ε�ǰh���棬������һλ��1
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
