/*************************************************************************
	> File Name: test.cpp
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2018-03-05 21:09:19
 ************************************************************************/

#include<iostream>
using namespace std;

class test{
	public:
		int a;
		char* s;
		test(){*(this)=0;};
		test(int t){*(this)=t;}
		test operator=(int inte){ a = inte; }
};

int main(int argc, const char *argv[])
{
	test a;
	cout<<a.a<<endl;
	return 0;
}
