/*************************************************************************
	> File Name: test.cpp
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2017-12-10 21:17:45
 ************************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string* msg = new string("Hello World");
	cout << *msg << endl;
	delete msg;
	return 0;
}
