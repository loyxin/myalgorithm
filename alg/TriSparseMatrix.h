#ifndef TRI_SPARSE_MATRIX_H
#define TRI_SPARSE_MATRIX_H
#include<iostream>
#include<iomanip>
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setfill;
using std::left;

template <typename ElemType>
// 稀疏矩阵的节点结构
// 位置 r c 值 value 
struct Triple
{
	int row,col;
	ElemType value;

	Triple() 
	{
	}
	Triple(int r,int c,const ElemType &e):row(r),col(c),value(e) {}
};

template <typename ElemType>
class TriSparseMatrix
{
protected:
	// 数组指针 
	Triple<ElemType> *triElems;
	// 矩阵的行数 列数 有效节点数 
	int rows,cols,num;

public:
	TriSparseMatrix();   //默认构造一个空矩阵
	TriSparseMatrix(int _rows,int _cols,int _num);
	// 要按顺序输入
	// 其实应该写一个排序算法的 
	TriSparseMatrix(int _rows,int _cols,int _num,const Triple<ElemType> *t);
	TriSparseMatrix(const TriSparseMatrix &copy);  //深拷贝
	TriSparseMatrix & operator=(const TriSparseMatrix &other);  //深赋值
	~TriSparseMatrix();
	void SimpleTranspose(TriSparseMatrix &dest);   //转置的普通算法
	void FastTranspose(TriSparseMatrix &dest);    //转置的快速算法
	template <typename ElemType>
	friend ostream & operator<<(ostream &out,const TriSparseMatrix<T> &mat);
	
};
template <typename ElemType>
ostream & operator<<(ostream &out,const TriSparseMatrix<ElemType> &mat)
{
	int c=0;
	for(int i=0;i<mat.rows;i++)
	{
		// 所以 打印一个[ 结尾 打印 一个 ] 
		cout<<"[  ";
		for(int j=0;j<mat.cols;j++)
		{
			if(mat.triElems[c].row==i&&mat.triElems[c].col==j)
					cout<<left<<setw(3)<<mat.triElems[c++].value;
			else 
				cout<<left<<setw(3)<<"0";
		}
		cout<<"]"<<endl;
	}
	return out;
}

template <typename ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix()
{
	rows=0;
	cols=0;
	num=0;
	triElems=NULL;
}

template <typename ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(int _rows,int _cols,int _num)
{
	rows=_rows;
	cols=_cols;
	num=_num;
	triElems=new Triple<ElemType>[num];
	for(int i=0;i<num;i++)
	{
		cout<<"请输入row，col，value:\n";
		cin>>triElems[i].row>>triElems[i].col>>triElems[i].value;
	}
}

template <typename ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(int _rows,int _cols,int _num,const Triple<ElemType> *t)
{
	rows=_rows;
	cols=_cols;
	num=_num;
	triElems=new Triple<ElemType>[num];
	for(int i=0;i<num;i++)
		triElems[i]=t[i];
}

template <typename ElemType>
TriSparseMatrix<ElemType>::~TriSparseMatrix()
{
	if(triElems!=NULL)
		delete[] triElems;
}

// 深copy
// 把数组的值都copy过来，新的一个对象 
template <typename ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(const TriSparseMatrix &copy)
{
	rows=copy.rows;
	cols=copy.cols;
	num=copy.num;
	triElems=new Triple<ElemType>[num];
	for(int i=0;i<num;i++)
		triElems[i]=copy.triElems[i];
}

template <typename ElemType>
TriSparseMatrix<ElemType> & TriSparseMatrix<ElemType>::operator=(const TriSparseMatrix<ElemType> &other)
{
	//  确认是不是本身 
	if(&other==this)
		return *this;
	if(triElems!=NULL)
		delete[] triElems;
	rows=other.rows;
	cols=other.cols;
	num=other.num;
	triElems=new Triple<ElemType>[num];
	for(int i=0;i<num;i++)
		triElems[i]=other.triElems[i];
	return *this;
}

template <typename ElemType>
void TriSparseMatrix<ElemType>::SimpleTranspose(TriSparseMatrix &dest)
{
	if(dest.triElems!=NULL)
		delete[] dest.triElems;
	dest.rows=cols;
	dest.cols=rows;
	dest.num=num;
	dest.triElems=new Triple<ElemType>[num];
	int c=0;
	// 仅仅是换值是不行的，会导致数组的排序问题 
	// 所以通过扫描按行(由于顺序是列在行)矩阵，输出转置矩阵 
	for(int i=0;i<cols;i++)
		for(int j=0;j<num;j++)
			if(triElems[j].col==i)
			{
				dest.triElems[c].row=triElems[j].col;
				dest.triElems[c].col=triElems[j].row;
				dest.triElems[c].value=triElems[j].value;
				c++;
			}
}
 
template <typename ElemType>
void TriSparseMatrix<ElemType>::FastTranspose(TriSparseMatrix &dest)
{
	if(dest.triElems!=NULL)
		delete[] dest.triElems;
	dest.rows=cols;
	dest.cols=rows;
	dest.num=num;
	dest.triElems=new Triple<ElemType>[num];
	int *cNum,*cPos,i,j;
	// cnum[col]表示矩阵M中第col列中的非零元素个数。 
	cNum=new int[cols];
	cPos=new int[cols];
	for(i=0;i<cols;i++)
		cNum[i]=0;
	for(i=0;i<num;i++)
		cNum[triElems[i].col]++;
	cPos[0]=0;
	// cpos 存第 i 行前不包括i行一共有多少数
	// cpot[col]指M中第col列的第一个非零元的恰当位置 
	for(i=1;i<cols;i++)
		cPos[i]=cPos[i-1]+cNum[i-1];
	for(i=0;i<num;i++)
	{
		j=cPos[triElems[i].col];
		dest.triElems[j].row=triElems[i].col;
		dest.triElems[j].col=triElems[i].row;
		dest.triElems[j].value=triElems[i].value;
		// 确定第col列的之后非零元的恰当位置
		cPos[triElems[i].col]++;
	} 
	// 数组只能确定的数， 所以要向堆申请内存，所以要析构 
	delete[] cNum;
	delete[] cPos;
}


#endif