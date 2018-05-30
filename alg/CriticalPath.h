#include "AdjListDirNetwork.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void CriticalPath(AdjListDirNetwork &network)
{
     int vexNum=network.GetVexNum();
	 // 入度
	 int *indegree=new int[vexNum];
	 // 两个数组 记录工期的，具体看算法
	 // 要说明的一点 一个是正的算，一个反推 用第一个算出的最晚时间
	 // 倒退那个工程的最晚时刻
	 int *ve=new int[vexNum];
	 int *vl=new int[vexNum];
	 int i,j;
	 queue<int> q;
	 stack<int> s;
	 // 得到入度
	 network.GetVexsIndgree(indegree);
	 for(i=0;i<vexNum;i++)
		 ve[i]=0;
	 // 源点入队
	 // 其实应该是找源点
	 for(i=0;i<vexNum;i++)
		 if(indegree[i]==0)
			q.push(i);
	 while(!q.empty())
	 {
		 i=q.front();
		 //拓扑排序 入栈
		 s.push(i);
		 q.pop();
		 for(j=network.GetFirstAdjVex(i);j!=-1;j=network.GetNextAdjVex(i,j))
		 {
			 //这里处理的好
			 //类似一层一层推
			 //第一层源点完了，第二层就是源点了
			 //s 变成拓扑排序了
			 if(--indegree[j]==0)
				 q.push(j);
			 // 有多个点汇入 判断哪一个更晚
			 if(ve[i]+network.GetWeight(i,j)>ve[j])
				 ve[j]=ve[i]+network.GetWeight(i,j);
		 }
	 }
	 i=s.top();
	 s.pop();
	 // 倒序算日期
	 // 最晚日期
	 for(j=0;j<vexNum;j++)
		 vl[j]=ve[i];
	 while(!s.empty())
	 {
		 i=s.top();
		 s.pop();
		 for(j=network.GetFirstAdjVex(i);j!=-1;j=network.GetNextAdjVex(i,j))
			 // 算最早的
			 if(vl[j]-network.GetWeight(i,j)<vl[i])
				 vl[i]=vl[j]-network.GetWeight(i,j);
	 }
	 for(i=0;i<vexNum;i++)
		 cout<<ve[i]<<" ";
	 cout<<endl;
	 for(i=0;i<vexNum;i++)
		 cout<<vl[i]<<" ";
	 cout<<endl<<"关键活动有:";
	 for(i=0;i<vexNum;i++)
	 {
		 int ee,el;
		 ee=ve[i];
		 for(j=network.GetFirstAdjVex(i);j!=-1;j=network.GetNextAdjVex(i,j))
		 {
			 // el 从 最早的j 减去 i,j的之间的距离
			 // 还和最晚 ve 相等，那肯定是关键路径
			 el=vl[j]-network.GetWeight(i,j);
			 // 算法判断相同就是关键路径
			 if(ee==el)
			 {
				 char v1=network.GetElem(i),v2=network.GetElem(j);
				 cout<<"("<<v1<<","<<v2<<") ";        //输出关键活动
			 }
		 }
	 }
	 cout<<endl;
	 delete[] indegree;
	 delete[] ve;
	 delete[] vl;
}
