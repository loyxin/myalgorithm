#include <iostream>
#include <queue>
using namespace std;
#define DEFAULT_SIZE 4

struct AdjListArcNode    //边结点定义
{
	// 连接的边的顶点 
	int adjVex;
	// next 有误导
	// 其实是一个栈，所以 next 是上一个 
	AdjListArcNode *nextArc;

	AdjListArcNode():nextArc(NULL) {}

	AdjListArcNode(int _adjVex,AdjListArcNode *_nextArc=NULL)
	{
		adjVex=_adjVex;
		nextArc=_nextArc;
	}
};

struct AdjListVexNode   //顶点结点定义
{
	char data;
	// 访问连接 这个顶点的无向边的顶点的栈顶指针 
	AdjListArcNode *firstArc;

	AdjListVexNode():firstArc(NULL) {}
	
	AdjListVexNode(char VexValue,AdjListArcNode *_firstArc=NULL)
	{
		data=VexValue;
		firstArc=_firstArc;
	}
};


// 用于搜索算法 
enum VisitStatus{VISIT,UNVISIT};
 
class AdjListUndirGraph     //邻接表实现无向图定义
{
public:
    AdjListUndirGraph(int _vexMaxNum=DEFAULT_SIZE);
	AdjListUndirGraph(char *Vexs,int _vexMaxNum,int _vexNum);
	~AdjListUndirGraph();
	void InsertArc(int vex1,int vex2);   //输入需合法，不考虑平行边，且vex1不等于vex2
	void Show();
	void DFSTraverse();
	void BFSTraverse();
	//friend istream& operator>>(istream &in,)

private:
	// 点有 最多vexMaxNum，所以用于访问 tag 也要有 
	VisitStatus *tag;
	//  邻接表 数组连头，链表，连可以连接的边 
	AdjListVexNode *vexTable;
	//  目前只是用在 打印时，展现几个顶点上 
	//  还有知道有多少边
	int vexNum;
	// 最大顶点数 
	int vexMaxNum;
	// 边数 
	int arcNum;

	void DFS(int startVex);    //深度优先搜索
	void BFS(int startVex);    //广度优先搜索
};

AdjListUndirGraph::AdjListUndirGraph(int _vexMaxNum)
{
	vexMaxNum=_vexMaxNum;
	vexNum=0;
	arcNum=0;
	tag=new VisitStatus[vexMaxNum];
	vexTable=new AdjListVexNode[vexMaxNum];
}

AdjListUndirGraph::AdjListUndirGraph(char *Vexs,int _vexMaxNum,int _vexNum)
{
	vexMaxNum=_vexMaxNum;
	vexNum=_vexNum;
	arcNum=0;
	tag=new VisitStatus[vexMaxNum];
	vexTable=new AdjListVexNode[vexMaxNum];
	for(int i=0;i<vexNum;i++)
	{
		tag[i]=UNVISIT;
		vexTable[i].data=Vexs[i];
	}
}

AdjListUndirGraph::~AdjListUndirGraph()
{
	if(tag!=NULL)
		delete[] tag;
	if(vexTable!=NULL)
		delete[] vexTable;
}

void AdjListUndirGraph::InsertArc(int vex1,int vex2)
{
	vexTable[vex1].firstArc=new AdjListArcNode(vex2,vexTable[vex1].firstArc);
	vexTable[vex2].firstArc=new AdjListArcNode(vex1,vexTable[vex2].firstArc);
	arcNum++;
}

void AdjListUndirGraph::Show()
{
	for(int i=0;i<vexNum;i++)
	{
		cout<<vexTable[i].data<<": ";
		AdjListArcNode *p=vexTable[i].firstArc;
		while(p!=NULL)
		{
			cout<<p->adjVex<<" ";
			p=p->nextArc;
		}
		cout<<endl;
	}
}
// 广度优先算法 
void AdjListUndirGraph::DFS(int startVex)
{
	if(tag[startVex]!=VISIT)
	{
		cout<<vexTable[startVex].data;
		tag[startVex]=VISIT;
		AdjListArcNode *p=vexTable[startVex].firstArc;
		for(;p!=NULL;p=p->nextArc)
		     DFS(p->adjVex);
	}
}

void AdjListUndirGraph::DFSTraverse()
{
	for(int i=0;i<vexNum;i++)
		if(tag[i]==UNVISIT)
		{
			DFS(i);
	        cout<<endl;
		}
}
// 深度优先算法  
void AdjListUndirGraph::BFS(int startVex)
{
	if(tag[startVex]!=VISIT)
	{
		queue<int> q;
		q.push(startVex);
		tag[startVex]=VISIT;
		cout<<vexTable[startVex].data;
		int i;
		AdjListArcNode *p;
		while(!q.empty())
		{
			i=q.front();
			q.pop();
			for(p=vexTable[i].firstArc;p!=NULL;p=p->nextArc)
			{
				if(tag[p->adjVex]==UNVISIT)
				{
					tag[p->adjVex]=VISIT;
					cout<<vexTable[p->adjVex].data;
					q.push(p->adjVex);
				}
			}
		}
	}
	
}

void AdjListUndirGraph::BFSTraverse()
{
	for(int i=0;i<vexNum;i++)
		if(tag[i]==UNVISIT)
		{	
			BFS(i);
			cout<<endl;
	    }
}

