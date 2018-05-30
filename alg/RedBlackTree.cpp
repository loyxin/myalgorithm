#include<iostream>
using namespace std;
enum COLOR{RED, BLACK};
struct RedBlackNode{
	int key;
	RedBlackNode* parent;
	RedBlackNode* leftChild;
	RedBlackNode* rightChild;
	COLOR color;
	RedBlackNode(int tempkey){
		key = tempkey;
		parent = NULL;
		leftChild = NULL;
		rightChild =NULL;
		color = RED;
	}
};

class RedBlackTree{
	private:
		RedBlackNode* Root;
	public:
		RedBlackTree();
		RedBlackNode* GetRoot(){return this->Root;}
		
		// 只是旋转
		void LeftRotate(RedBlackNode* );
		void RightRotate(RedBlackNode* );

		void InsertRBNode(int );
		// 修复 insert 过程造成的性质
		void InsertFixUp(RedBlackNode* );
		bool DeleteRBNode(int );
		void DeleteFixUp(RedBlackNode* );
		void DeleteNoOrOneChildNode(RedBlackNode* , RedBlackNode* );
		
		void PreOrderPrint(RedBlackNode* );
		void InOrderPrint(RedBlackNode* );
		void SufOrderPrint(RedBlackNode* );
		void RotatePrint(RedBlackNode* , int );

		RedBlackNode* FindRB(int );
		void UpdateRBNode(int , int);
};

void RedBlackTree::UpdateRBNode(int oldKey, int newKey){
	DeleteRBNode(oldKey);
	InsertRBNode(newKey);
}

RedBlackNode* RedBlackTree::FindRB(int tempkey){
	RedBlackNode* cur = this->Root;
	while(cur!=NULL){
		if(cur->key==tempkey)
			break;
		else if(cur->key>tempkey)
			cur = cur->leftChild;
		else
			cur = cur->rightChild;
	}
	return cur;
}

RedBlackTree::RedBlackTree(){
		Root=NULL;
}

void RedBlackTree::LeftRotate(RedBlackNode *tempNode)
{
		RedBlackNode *rChildNode=tempNode->rightChild;
		if(rChildNode->leftChild != NULL)//右子树的左子树不为空
			rChildNode->leftChild->parent=tempNode;
		rChildNode->parent=tempNode->parent;
		if(NULL==tempNode->parent)//当前节点为根节点
			this->Root=rChildNode;
		else if(tempNode==tempNode->parent->leftChild)
			tempNode->parent->leftChild=rChildNode;
		else 
			tempNode->parent->rightChild=rChildNode;
		tempNode->parent=rChildNode;
		tempNode->rightChild=rChildNode->leftChild;
		rChildNode->leftChild=tempNode;
}

void RedBlackTree::RightRotate(RedBlackNode* tempNode){
	RedBlackNode* lChildNode = tempNode->leftChild;
	if(lChildNode->rightChild!=NULL)
		lChildNode->rightChild->parent = tempNode;
	lChildNode->parent = tempNode->parent;
	if(NULL==tempNode->parent)
		this->Root = lChildNode;
	else if(tempNode == tempNode->parent->leftChild)
		tempNode->parent->leftChild = lChildNode;
	else
		tempNode->parent->rightChild = lChildNode;
	tempNode->parent = lChildNode;
	tempNode->leftChild = lChildNode->rightChild;
	lChildNode->rightChild = tempNode;
}


void RedBlackTree::InsertRBNode(int tempkey){
	RedBlackNode* pre = NULL, * cur = this->Root;
	while(cur != NULL){
		pre = cur;
		if(cur->key>tempkey)
			cur = cur->leftChild;
		else
			cur = cur->rightChild;
	}// 跳出循环 则 cur = NULL pre 是要插入的 parent 节点
	RedBlackNode* tempNode = new RedBlackNode(tempkey);
	tempNode->parent = pre;
	if(pre == NULL)// 插入为根节点
	{
		this->Root = tempNode;
	}
	else if( pre->key>tempNode->key )
		pre->leftChild = tempNode;
	else 
		pre->rightChild = tempNode;

	InsertFixUp(tempNode);//保持红黑树性质
}

/**********************************************************
 * *参数：当前插入节点
 * *返回值：空
 * *功能：在插入节点后加以调整保持红黑树性质
 * ************************************************************/
// https://www.cnblogs.com/nullzx/p/6128416.html
// https://blog.csdn.net/v_JULY_v/article/details/6284050

void RedBlackTree::InsertFixUp(RedBlackNode* tempNode){
	RedBlackNode* parTempNode = tempNode->parent, * ancleTempNode;
	while(parTempNode!=NULL && RED == parTempNode->color){
		if( parTempNode->parent!=NULL ){
			if(parTempNode->parent->leftChild == parTempNode){
				ancleTempNode = parTempNode->parent->rightChild;
				if(ancleTempNode!=NULL && RED==ancleTempNode->color){
					parTempNode->color = BLACK;
					ancleTempNode->color = BLACK;
					parTempNode->parent->color = RED;
					tempNode = parTempNode->parent;//指向爷爷节点
					parTempNode = tempNode->parent;
				}
				else{
					if(tempNode == parTempNode->rightChild){
						LeftRotate(parTempNode);
						tempNode = tempNode->parent;
						parTempNode = tempNode->parent;
					}
					parTempNode->color = BLACK;
					parTempNode->parent->color = RED;
					RightRotate(parTempNode->parent);
					break;
				}
			}
			else{
				ancleTempNode = parTempNode->parent->leftChild;
				if(ancleTempNode!=NULL && RED==ancleTempNode->color){
					parTempNode->color = BLACK;
					ancleTempNode->color = BLACK;
					parTempNode->parent->color = RED;
					tempNode = parTempNode->parent;
					parTempNode = tempNode->parent;
				}
				else{
					if(tempNode==parTempNode->leftChild){
						RightRotate(parTempNode);
						tempNode = tempNode->rightChild;
						parTempNode = tempNode->parent;
					}
					parTempNode->color = BLACK;
					parTempNode->parent->color = RED;
					LeftRotate(parTempNode->parent);
					break;
				}
			}
		}
		else break;
	}
	this->Root->color = BLACK;
}

bool RedBlackTree::DeleteRBNode(int tempkey){
	RedBlackNode* pre = NULL, * cur = Root;
	while(cur!=NULL){
		if(cur->key==tempkey)
			break;
		else{
			pre = cur;
			if(cur->key>tempkey)
				cur = cur->leftChild;
			else
				cur = cur->rightChild;
		}
	}
	if(NULL==cur) return false;//说明没有
	RedBlackNode* tempChild;
	COLOR tempColor;
	if(NULL==cur->leftChild || NULL==cur->rightChild){
		if(NULL==cur->leftChild)// 右孩子存在
			tempChild = cur->rightChild;
		else
			tempChild = cur->leftChild;
		tempColor = cur->color;
		DeleteNoOrOneChildNode(pre,cur);
		if(tempChild!=NULL && BLACK==tempColor)
			DeleteFixUp(tempChild);
	}
	else{// 孩子非空
		RedBlackNode* rPre = cur, * rCur = cur->rightChild;
		while(rCur->leftChild!=NULL){
			rPre = rCur;
			rCur = rCur->leftChild;
		}
		cur->key = rCur->key;
		tempChild = rCur->rightChild;
		tempColor = rCur->color;
		DeleteNoOrOneChildNode(rPre, rCur);
		if(tempChild!=NULL&&BLACK==tempColor)
			DeleteFixUp(tempChild);
	}
}

void RedBlackTree::DeleteFixUp(RedBlackNode* tempNode){
	if(RED == tempNode->color)
		InsertFixUp(tempNode);
}

void RedBlackTree::DeleteNoOrOneChildNode(RedBlackNode *pre,RedBlackNode *cur)
{
	if(NULL==cur->leftChild&&NULL==cur->rightChild)
	{
		if(NULL==pre)
			Root=NULL;
		else if(pre->leftChild==cur)
			pre->leftChild=NULL;
		else pre->rightChild=NULL;
		delete cur;
	}
	else if(cur->rightChild!=NULL)
	{
		if(NULL==pre)
		{
			Root=cur->rightChild;
			Root->parent=NULL;
		}
		else if(pre->leftChild==cur)
		{
			pre->leftChild=cur->rightChild;
			cur->rightChild->parent=pre;
		}
		else 
		{
			pre->rightChild=cur->rightChild;
			cur->rightChild->parent=pre;
		}
		delete cur;
	}
	else if(cur->leftChild!=NULL)
	{
		if(NULL==pre)
		{
			Root=cur->leftChild;
			Root->parent=NULL;
		}
		else if(pre->leftChild==cur)
		{
			pre->leftChild=cur->leftChild;
			cur->leftChild->parent=pre;
		}
		else
		{
			pre->rightChild=cur->leftChild;
			cur->leftChild->parent=pre;
		}
		delete cur;
	}
}


void RedBlackTree::PreOrderPrint(RedBlackNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color==RED)
		cout<<"Red)  ";
	else cout<<"Black)  ";
	PreOrderPrint(tempRoot->leftChild);
	PreOrderPrint(tempRoot->rightChild);
}


void RedBlackTree::InOrderPrint(RedBlackNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	InOrderPrint(tempRoot->leftChild);
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color==RED)
		cout<<"Red)  ";
	else cout<<"Black)  ";
	InOrderPrint(tempRoot->rightChild);
}


void RedBlackTree::SufOrderPrint(RedBlackNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	SufOrderPrint(tempRoot->leftChild);
	SufOrderPrint(tempRoot->rightChild);
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color==RED)
		cout<<"Red)  ";
	else cout<<"Black)  ";
}

void RedBlackTree::RotatePrint(RedBlackNode *tempRoot,int tempColumn)
{
	if(NULL==tempRoot)
		return ;
	RotatePrint(tempRoot->leftChild,tempColumn+1);
	for(int i=0;i<tempColumn;i++)
		cout<<"    ";
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color==RED)
		cout<<"Red)";
	else cout<<"Black)";
	cout<<endl;
	RotatePrint(tempRoot->rightChild,tempColumn+1);
}

int main()
{
	int val;
	while(true)
	{
		RedBlackTree myRedBlackTree;
		while(cin>>val)
		{
			if(val==0)break;
			myRedBlackTree.InsertRBNode(val);
		}
		cout<<endl<<"*****************************"<<endl;
		cout<<endl<<"=============pre============="<<endl;
		myRedBlackTree.PreOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"=============in============="<<endl;
		myRedBlackTree.InOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"==============suf============="<<endl;
		myRedBlackTree.SufOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"==============对称+顺时针旋转============="<<endl;
		myRedBlackTree.RotatePrint(myRedBlackTree.GetRoot(),0);
		cout<<endl<<"============================="<<endl;
		cout<<"*****************************"<<endl;
		while(cin>>val)
		{
			if(!val)break;
			myRedBlackTree.DeleteRBNode(val);
			cout<<endl<<"*****************************"<<endl;
		cout<<endl<<"=============pre============="<<endl;
		myRedBlackTree.PreOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"=============in============="<<endl;
		myRedBlackTree.InOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"==============suf============="<<endl;
		myRedBlackTree.SufOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"==============对称+顺时针旋转============="<<endl;
		myRedBlackTree.RotatePrint(myRedBlackTree.GetRoot(),0);
		cout<<endl<<"============================="<<endl;
		cout<<"*****************************"<<endl;
		}
	}
	system("pause");
	return 0;
}
