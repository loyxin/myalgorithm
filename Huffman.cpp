// ������������һ����ǰ׺���롣����ʱ�������

#include<iostream>
using namespace std;

template<class T>


/**
 * @brief ���Ľڵ�Ķ���
 * @details
 *
 * @param data ����
 * @param rchild �Ҷ���
 * @param lchild �����
 * @param nonlchild �ݴ�������lchild,Ϊ�˷�������
 */
class tree{

	public:
		/**
		 * @brief ���ݲ�Ĭ�ϣ�����Ĭ��NULL,
		 */
		tree(T data, tree<T>* parent = NULL,
		tree<T>* lchild = NULL, tree<T>* rchild = NULL):
		data(data),parent(parent),lchild(lchild),rchild(rchild)
		{
		}
		/**
		 * @brief ����
		 * @details delete �ڵ���ĸ�׵Ĺ�ϵ���ٵݹ�ɾ���ýڵ�Ķ���
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
	 * @details ��ʼ��������������ݵĴ�С����С����ȫ�����������,�������Ƿ������Ϊ100
	 * @param proba ���ݵ�ͷָ��
	 * @param length ���ݵĳ���
	 */
	Huffman(double* proba,int length):
	length(length){
		//���� 
		sort(proba,proba+length);
		this->p = new tree<double>(*proba);
		tree<double>* temp = p;
		//�ڵ㸳ֵ 
		for(int i=1;i<length;++i){
			temp = new tree<double>(*(proba+i),temp, NULL, NULL);
			temp->parent->lchild = temp;
		}
		//�����ֵΪ100 
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
	 * @details ���ɻ������� 
	 */
	void TreeGe(){
        
        for(;p->lchild!=NULL;){
            double x = p->data+p->lchild->data;
            //�����µĽڵ�
            tree<double>* temp = new tree<double>(x);
            //ȷ���ڵ�Ķ���
            temp->nonlchild=p->lchild;
            temp->rchild=p;
            //ȷ�����ӵ�ĸ���Ǹýڵ�
            temp->nonlchild->parent=temp;
            temp->rchild->parent=temp;
            //����ӵ�����Ӹ�ֵ���ýڵ������ӣ�ʵ����������
            if(temp->nonlchild->lchild!=NULL){
            	temp->lchild=temp->nonlchild->lchild;
            	temp->nonlchild->lchild=NULL;
            }
            //���ӵ����������NULL
            temp->rchild->lchild=NULL;
            insertsort(temp);
		}
	}

	/**
	 * @brief ��������
	 *
	 * @param insert ����Ľڵ�
	 */
	void insertsort(tree<double>* insert){
		if(insert==NULL) return ;
		tree<double>* temp = insert->lchild;
		//ȷ����ָ��
		if(temp==NULL) {p=insert;return;}
		if(insert->data>=temp->data)
            p=temp;
        else
            p=insert;
		// ���������ڵ��λ�� ������� 
		for(;insert->data>=temp->data;temp=temp->lchild){
				//������temp����һ���ڵ�Ϊinsert 
                if(temp==insert)temp=temp->lchild;
                if(temp==NULL) break;
                if(insert->parent==NULL){
                	//��ĸ�� 
                    temp->parent=insert->parent;
                    insert->parent=temp;
 					//������ 
                    insert->lchild=temp->lchild;
                    temp->lchild=insert;
                    //���temp�������Ľڵ��Ҫ�����ӵ�ĸ�� 
                    if(insert->lchild!=NULL)
                        insert->lchild->parent=insert;
					// ��ֹ����ڶ����ж� 
					if(temp->lchild ==NULL) break;
                }
				else if(temp->lchild==NULL){
					//��ĸ�׵Ķ��� 
                    insert->parent->lchild=temp;
                    //��ĸ��
                    temp->parent=insert->parent;
					insert->parent=temp;
					//������ 
                    insert->lchild=NULL;
                    temp->lchild=insert;
                    
                    return;
                }
				else{
					//��ĸ�׵Ķ���
                    insert->parent->lchild=temp;
                    //��ĸ��
                    insert->parent=temp;
                    temp->parent=insert->parent;
					//������ 
					insert->lchild=temp->lchild;
					temp->lchild=insert;
					//�����ӵ�ĸ��
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
## �ܽ�

�ڴ�ڵ�����ݵ�ʱ��Ϊ�˽�Լ�ڴ棬д��ָ�룬������
```cpp
double x = *(p->data)+*(p->lchild->data);
//�����µĽڵ�
tree<double>* temp = new tree<double>(&x);
```
�н��ÿ��û���¿���һ���ڴ棬���Ż�

�ݹ������ýڵ�

���򽻻�
*/