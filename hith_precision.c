/*************************************************************************
	> File Name: hith_precision.cpp
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2018-01-15 21:07:59
 ************************************************************************/
// from standard code library
// sjtu
#include<iostream>
#define maxlen 1000

struct HP {int len,s[maxlen];};

void PrintHP(HP x){ for(int i=x.len;i>=1;i--) cout<<x.s[i]; }

void Str2HP(const char * s, HP & x){
	x.len=strlen(s);
	for(int i=1;i<=x.len;i++)x.s[i]=s[x.len-i]-'0';
}

void Int2HP(int inte, HP& x){
	if(inte==0){x.len=1;x.s[1]=0;return;};
	for(x.len=0;inte>0;){x.s[++x.len]=inte%10;inte/=10;};
}

void Multi(const HP a, const HP b, HP & c)
{
	int i,j;
}
