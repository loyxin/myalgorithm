/*************************************************************************
	> File Name: HRN.h
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com
	> Created Time: 2018-03-07 23:44:37
 ************************************************************************/
#ifndef HRN_H
#define HRN_H
#include<iostream>
#include<iomanip>
using std::cout;
using std::endl;
using std::setw;
using std::ostream;

struct Job
{
	// 输入作业名称name，到达时间AT，运行时间RT
	char name[8];
	int AT;  //arrive time 到达时间
	int RT;  //running time 运行时间
	int ST;  //start time 开始时间
	int WT;  //waiting time 等待时间
	int ET;  //end time 结束时间
	int status;  //记录该项工作是否已被解决 0 未被解决 1 已解决
	double resp;   //响应比

	Job()
	{
		status=0;  //初始化为0，表示还未被解决
	}
	// 打印 name AT RT ST WT ET
	friend ostream & operator<<(ostream &out,const Job &job)
	{
	   out<<setw(6)<<job.name<<setw(6)<<job.AT<<setw(6)<<job.RT
		<<setw(6)<<job.ST<<setw(6)<<job.WT<<setw(6)<<job.ET<<endl;
	   return out;
	}
};

void HRN(Job *jobs,int n)  //最高响应比算法
{
	cout<<"响应比高者优先算法执行顺序："<<endl;
	cout<<setw(6)<<"JOBS"<<setw(6)<<"AT"<<setw(6)<<"RT"<<setw(6)<<"ST"<<setw(6)<<"WT"<<setw(6)<<"ET"<<endl;

	jobs[0].ST=jobs[0].AT;   //先处理第一项
	jobs[0].WT=0;
	jobs[0].ET=jobs[0].ST+jobs[0].RT;
	cout<<jobs[0];
	jobs[0].status=1;  //该项工作已解决

	int max=1,pre=0;
	for(int count=1;count<n;count++)   //还有n-1项工作待处理, 每次循环要选出一个解决
	{
		// c 是个 flag, 0 表示未能初始化 max, 因为每个循环前都是处理最高响应比的任务, 要选一个新的 max
		//  flag 表示可以找到一个最高响应比的任务, 说明有任务在等待
		// flag 0 表示没有任务在等待
		int c=0,flag=0;
		//找到一个最高响应比的任务, 判断任务是否在等待
		int i=1;
	    for(;jobs[i].AT<=jobs[pre].ET && i<n;i++)
		{
		   if(jobs[i].status==0)    //并且该项工作还未被处理
		    {
				jobs[i].resp=(jobs[pre].ET-jobs[i].AT)*1.0/jobs[i].RT;   //计算响应比
				if(c==0)     //初始化 max 方便比较
					{max=i; c =  1;}
				if(jobs[i].resp>jobs[max].resp)
					max=i;     //更新max，找到最大响应比
				flag=1;
		    }
	    }

		// 处理任务
		if(flag!=0)
		{
		   //处理该项具有最大响应比的工作
		   jobs[max].ST=jobs[pre].ET;
		   jobs[max].WT=jobs[pre].ET-jobs[max].AT;
		   jobs[max].ET=jobs[max].ST+jobs[max].RT;
		   cout<<jobs[max];    //输出这一项
		   jobs[max].status=1;   //有最大响应比的工作已处理完，status赋值为1
		   pre=max;   //将此具有最大响应比的工作记为前一项
		}
		else
		{
			//若在前一(已处理完的)工作结束之前到达的工作均已处理完，还未处理的第i项工作随后才到达
			jobs[i].ST=jobs[i].AT;   //处理第i项
			jobs[i].WT=0;     //该项等待时间为0
			jobs[i].ET=jobs[i].ST+jobs[i].RT;
			cout<<jobs[i];
			jobs[i].status=1;
			pre=i;
		}
	}

	cout<<"平均等待时间：";
	int sumWT=0;
	double aveWT;
	for(int i=0;i<n;i++)
		sumWT=sumWT+jobs[i].WT;
	aveWT=sumWT*1.0/n;
	cout<<aveWT<<endl;
	cout<<endl;
}

void SJF(Job *jobs,int n)   //最短作业优先算法
{
	cout<<"最短作业优先算法执行顺序："<<endl;
	cout<<setw(6)<<"JOBS"<<setw(6)<<"AT"<<setw(6)<<"RT"<<setw(6)<<"ST"<<setw(6)<<"WT"<<setw(6)<<"ET"<<endl;
	//若有几项作业同时最先到达, 找出最短作业
	int min=0;
	for(int i=1;jobs[i].AT==jobs[0].AT;i++)
	{
		if(jobs[i].RT<jobs[min].RT)
			min=i;
	}
	//解决该项作业
	jobs[min].ST=jobs[min].AT;
	jobs[min].WT=0;
	jobs[min].ET=jobs[min].ST+jobs[min].RT;
	cout<<jobs[min];
	jobs[min].status=1;
	int pre=min;

	for(int count=1;count<n ;count++)
	{
		int c=0,flag=0;
		int i=0;
		for(;jobs[i].AT<=jobs[pre].ET&& i<n;i++)
		{
             if(jobs[i].status==0)   //并且该项工作还未被处理
			 {
				 if(c==0)
					 {min=i;c=1;}
				 if(jobs[i].RT<jobs[min].RT)
					 min=i;   //更新min，找出最短作业
				 flag=1;
			 }
		}
		if(flag!=0)
		{
			jobs[min].ST=jobs[pre].ET;
		    jobs[min].WT=jobs[pre].ET-jobs[min].AT;
		    jobs[min].ET=jobs[min].ST+jobs[min].RT;
		    cout<<jobs[min];
		    jobs[min].status=1;
		    pre=min;
		}
		else
		{
			jobs[i].ST=jobs[i].AT;   //处理第i项
			jobs[i].WT=0;     //该项等待时间为0
			jobs[i].ET=jobs[i].ST+jobs[i].RT;
			cout<<jobs[i];
			jobs[i].status=1;
			pre=i;
		}
	}
	cout<<"平均等待时间：";
	int sumWT=0;
	double aveWT;
	for(int i=0;i<n;i++)
		sumWT=sumWT+jobs[i].WT;
	aveWT=sumWT*1.0/n;
	cout<<aveWT<<endl;
	cout<<endl;
}

void FCFS(Job *jobs,int n)    //先来先服务算法
{
	cout<<"先来先服务算法执行顺序："<<endl;
	cout<<setw(6)<<"JOBS"<<setw(6)<<"AT"<<setw(6)<<"RT"<<setw(6)<<"ST"
		<<setw(6)<<"WT"<<setw(6)<<"ET"<<endl;
	jobs[0].ST=jobs[0].AT;   //先处理第一项
	jobs[0].WT=0;
	jobs[0].ET=jobs[0].ST+jobs[0].RT;
	cout<<jobs[0];
	int i;
	for(i=1;i<n;i++)    //依次处理接下来的n-1项
	{
		if(jobs[i].AT>jobs[i-1].ET)
		{
			jobs[i].ST=jobs[i].AT;   //处理第i项
			jobs[i].WT=0;     //该项等待时间为0
			jobs[i].ET=jobs[i].ST+jobs[i].RT;
			cout<<jobs[i];
		}
		else
		{
		    jobs[i].ST=jobs[i-1].ET;
		    jobs[i].WT=jobs[i-1].ET-jobs[i].AT;
		    jobs[i].ET=jobs[i].ST+jobs[i].RT;
		    cout<<jobs[i];
		}
	}
	cout<<"平均等待时间：";
	int sumWT=0;
	double aveWT;
	for(i=0;i<n;i++)
		sumWT=sumWT+jobs[i].WT;
	aveWT=sumWT*1.0/n;
	cout<<aveWT<<endl;
	cout<<endl;
}
#endif
