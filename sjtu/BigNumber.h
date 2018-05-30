// bignumber.hh
#ifndef BIGNUMBER
#define BIGNUMBER 1
#include<iostream>
#include<string>
using namespace std;

class BigNumber{
public:
	BigNumber(string number){		//input string as constration 
		charLength=number.size();
		if(charLength%4==0){		//4 as store
			arraySize=charLength/4;
		}
		else{
			arraySize=charLength/4+1;
		}
		data=new int[arraySize];
		for(int i=0;i<arraySize;i++) data[i]=0;
		string::size_type charPoint=charLength-1;
		//define get the unique youbiao
		int weight;//define jingwei
		for(int i=arraySize-1;i>=0;i--)
		{
			weight=1;
			//store as 4
			for(int j=0;j<4;j++)
			{
				if(charPoint!=0)
				{
					data[i]+=(number[charPoint]-'0')*weight;
					weight*=10;
					charPoint--;
				}else break;
			}
		}
		data[0]+=(number[0]-'0')*weight;
	}
	BigNumber(int s)
	{
	data=new int[s];
	for(int i=0;i<s;i++) data[i]=0;
	arraySize=s; 
	} 
	~BigNumber(){delete data;
	}
	int* getData(){
		return data;
	}
	int getArraySize(){
		return arraySize;
	}
private:
	int* data;
	string::size_type charLength;
	int arraySize;
};


void add(BigNumber a, BigNumber b){
	BigNumber maxNumber=a.getArraySize()>=b.getArraySize()?a:b;
	BigNumber minNumber=a.getArraySize()<b.getArraySize()?a:b;
	
	BigNumber c(maxNumber.getArraySize());
	int* dataMax=maxNumber.getData();
	int* dataMin=minNumber.getData();
	int* dataC=c.getData();
	int i,j;
	int carray=0;
	for(i=maxNumber.getArraySize()-1,j=i-(maxNumber.getArraySize()-minNumber.getArraySize());i>=0&&j>=0;i--,j--)
	{
		dataC[i]=dataMax[i]+dataMin[j]+carray;
		if(dataC[i]<10000){
			carray=0;
		} else{
			carray=1;dataC[i]=dataC[i]-10000;
		}
	}
	while(i>=0)
	{
		dataC[i]=dataMax[i]+carray;
		if(dataC[i]<10000) carray=0;
		else{
			carray=1;dataC[i]=dataC[i]-10000; 
		}
		i--;
	}
	if(carray==1){
		int* result=new int[c.getArraySize()+1];
		result[0]=1;
		dataC[0]=dataC[0]-10000;
		for(int k=1;k<c.getArraySize()+1;k++){
			result[k]=dataC[k-1];
		}
		for(int i=0;i<c.getArraySize()+1;i++)
		{
			if(i>0&&result[i]<10000) cout<<'0'<<result[i];
			else cout<<result[i];
		}
		}else{
			for(int i=0;i<c.getArraySize();i++){
				if(i>0&&dataC[i]<10000)
				cout<<'0'<<dataC[i];
				else cout<<dataC[i];
			}
		}
		cout<<endl;
		return ;
}


#endif
