// 霍夫曼编码是一种无前缀编码。解码时不会混淆

#include<iostream>
using namespace std;

template<class T>


/**
 * @brief 树的节点的定义
 * @details
 *
 * @param data 数据
 * @param rchild 右儿子
 * @param lchild 左儿子
 * @param nonlchild 暂存真正的lchild,为了方便排序
 */
class tree{

	public:
		/**
		 * @brief 数据不默认，其他默认NULL,
		 */
		tree(T data, tree<T>* parent = NULL,
		tree<T>* lchild = NULL, tree<T>* rchild = NULL):
		data(data),parent(parent),lchild(lchild),rchild(rchild)
		{
		}
		/**
		 * @brief 析构
		 * @details delete 节点与母亲的关系，再递归删除该节点的儿子
		 */
		~tree(){
			cout<<"delete";
			cout<<this->data<<endl;
			this->data = 0.0;
			if(this->parent != NULL){
			if(this->parent->lchild == this)
				this->parent->lchild = NULL;
			else if(this->parent->rchild == this)
				this->parent->rchild = NULL;
			else if(this->parent->nonlchild==this)
				this->parent->nonlchild = NULL;
			else
				cout<<"error,this leaf "<< this
				<<"has error parent"<<endl;
			this->parent=NULL;
			}

			if(this->lchild!=NULL){
				delete this->lchild;
			}
			if(this->rchild!=NULL){
				delete this->rchild;
			}
			if(this->nonlchild!=NULL){
				delete this->nonlchild;
			}

		}
		T data;
		tree<T>* parent;
		tree<T>* lchild;
		tree<T>* rchild;
		tree<T>* nonlchild = NULL;
};


#include<algorithm>

class Huffman{
	public:
	/**
	 * @details 初始化，并排序好数据的大小，从小到大，全部置于左儿子,并检验是否加起来为100
	 * @param proba 数据的头指针
	 * @param length 数据的长度
	 */
	Huffman(double* proba,int length):
	length(length){
		//排序 
		sort(proba,proba+length);
		this->p = new tree<double>(*proba);
		tree<double>* temp = p;
		//节点赋值 
		for(int i=1;i<length;++i){
			temp = new tree<double>(*(proba+i),temp, NULL, NULL);
			temp->parent->lchild = temp;
		}
		//检查总值为100 
		double x=0.0;
		temp = p;
		for(int i =0;i<length;++i){
			x+=temp->data;
			temp=temp->lchild;
		}
 
		if(fabs(x-100.0)>1e-5){
			cout<<string("not equal to 1")<<endl;
		}
	}
	~Huffman(){
		delete p;
	}
	/**
	 * @details 生成霍夫曼树 
	 */
	void TreeGe(){
        
        for(;p->lchild!=NULL;){
            double x = p->data+p->lchild->data;
            //构建新的节点
            tree<double>* temp = new tree<double>(x);
            //确定节点的儿子
            temp->nonlchild=p->lchild;
            temp->rchild=p;
            //确定儿子的母亲是该节点
            temp->nonlchild->parent=temp;
            temp->rchild->parent=temp;
            //左儿子的左儿子赋值给该节点的左儿子，实现排序链接
            if(temp->nonlchild->lchild!=NULL){
            	temp->lchild=temp->nonlchild->lchild;
            	temp->nonlchild->lchild=NULL;
            }
            //儿子的左儿子置于NULL
            temp->rchild->lchild=NULL;
            insertsort(temp);
		}
	}

	/**
	 * @brief 插入排序
	 *
	 * @param insert 插入的节点
	 */
	void insertsort(tree<double>* insert){
		if(insert==NULL) return ;
		tree<double>* temp = insert->lchild;
		//确定根指针
		if(temp==NULL) {p=insert;return;}
		if(insert->data>=temp->data)
            p=temp;
        else
            p=insert;
		// 根据两个节点的位置 三种情况 
		for(;insert->data>=temp->data;temp=temp->lchild){
				//交换后temp的下一个节点为insert 
                if(temp==insert)temp=temp->lchild;
                if(temp==NULL) break;
                if(insert->parent==NULL){
                	//换母亲 
                    temp->parent=insert->parent;
                    insert->parent=temp;
 					//换儿子 
                    insert->lchild=temp->lchild;
                    temp->lchild=insert;
                    //如果temp不是最后的节点就要换儿子的母亲 
                    if(insert->lchild!=NULL)
                        insert->lchild->parent=insert;
					// 防止进入第二个判断 
					if(temp->lchild ==NULL) break;
                }
				else if(temp->lchild==NULL){
					//换母亲的儿子 
                    insert->parent->lchild=temp;
                    //换母亲
                    temp->parent=insert->parent;
					insert->parent=temp;
					//换儿子 
                    insert->lchild=NULL;
                    temp->lchild=insert;
                    
                    return;
                }
				else{
					//换母亲的儿子
                    insert->parent->lchild=temp;
                    //换母亲
                    insert->parent=temp;
                    temp->parent=insert->parent;
					//换儿子 
					insert->lchild=temp->lchild;
					temp->lchild=insert;
					//换儿子的母亲
					insert->lchild->parent=insert;		
				}
		}
	}
	private:
		tree<double>* p;
		int length;
};

#ifndef MAIN
#define N 5
int main(){
	double* pro = new double[N];
	// for(int i=0;i<N;++i)
	// 	cin>>pro[i];
	pro[0] = 20.0;
	pro[1] = 15.0;
	pro[2] = 25.0;
	pro[3] = 36.0;
	pro[4] = 4.0;


	Huffman* test = new Huffman(pro,N);
	test->TreeGe();
	delete test;
	for(int i = 0; i<N;++i)
	cout<<pro[i]<<endl;

return 0;
}

#endif

/*
## 总结

在存节点的数据的时候为了节约内存，写成指针，但是在
```cpp
double x = *(p->data)+*(p->lchild->data);
//构建新的节点
tree<double>* temp = new tree<double>(&x);
```
中结果每次没有新开辟一个内存，会优化

递归析构该节点

排序交换
*/