/*************************************************************************
	> File Name: os.cpp
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2018-03-07 23:44:51
 ************************************************************************/

#include<iostream>
using namespace std;
#include"HRN.h"
#include<iostream>
#include<stdio.h>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	int n,i;
	cout<<"请输入需要调度的总工作数：";
	cin>>n;
	Job *jobs=new Job[n];
	cout<<"请按顺序输入作业名称name，到达时间AT，运行时间RT："<<endl;
	for(i=0;i<n;i++)
	{
		cin>>jobs[i].name>>jobs[i].AT>>jobs[i].RT;
	}
	HRN(jobs,n);
	for(i=0;i<n;i++)
		jobs[i].status=0;
	SJF(jobs,n);
	for(i=0;i<n;i++)
		jobs[i].status=0;
	FCFS(jobs,n);
	delete[] jobs;
	return 0;
}
