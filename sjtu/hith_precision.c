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
// 只能 int 的扩展
// len 当 0 为1 存 0-9 不能标记负数
struct HP {int len, s[maxlen];};

void PrintHP(HP x){
	for( int i=x.len; i>=1; i-- ) 
		cout<<x.s[i]; 
}

void Str2HP(const char * s, HP & x){
	x.len = strlen(s);
	for( int i=1; i<=x.len; i++ )
		x.s[i] = s[x.len-i]-'0';
}

void Int2HP(int inte, HP& x){
	if( inte==0 ){
		x.len = 1;x.s[1] = 0;
		return;
	}
	for(x.len=0; inte>0; ){
		x.s[++x.len] = inte%10;
		inte /= 10;
	}
}
// 进位
void Multi(const HP a, const HP b, HP & c)
{
	int i,j;
	c.len = a.len+b.len;
	for( i=1; i<=c.len; i++ ) c.s[i] = 0;
	for( i=1; i<=a.len; i++ ) 
		for( j=1; j<=b.len; j++ )
			c.s[i+j-1] += a.s[i]*b.s[j];
	for( i=1; i<c.len; i++ ){
		c.s[i+1] += c.s[i]/10;
		c.s[i] %= 10;
	}
	while( c.s[i] ){
		c.s[i+1] = c.s[i]/10;
		c.s[i] %= 10;
		i++;
	}
	while( i>1 && !c.s[i] ) i--;
	c.len = i;
}

void Plus(const HP a, const HP b, HP& c){
	int i;
	c.s[1] = 0;
	for( i=1; i<=a.len || i<=b.len || c.s[i]; i++ ){
		if( i<=a.len ) c.s[i] += a.s[i];
		if( i<=b.len ) c.s[i] += b.s[i];
		c.s[i+1] = c.s[i]/10;
		c.s[i]%10;
	}
	c.len = i-1;
	if( c.len == 0 )
		c.len = 1;
}

void Subtract(const HP a, const HP b, HP& c){
	for(int i=1,j=0; i<=a.len; i++){
		c.s[i] = a.s[i]-j;
		if( i<=b.len ) c.s[i] -= b.s[i];
		if(c.s[i]<0) {
			j=1;
			c.s[i] += 10;
		}else
			j = 0;
	}
	c.len = a.len;
	while(c.len > 1 && !c.s[c.len]) c.len--;
}

int HPCompare( const HP x, const HP y ){
	if( x.len>y.len ) return 1;
	if( x.len<y.len ) return -1;
	int i = x.len;
	while( (i>1) && (x.s[i]==y.s[i]) )
		i--;
	return x.s[i]-y.s[i];
}

void Divide( const HP a, const HP b, HP& c, HP& d ){
	int i,j;
	d.len = 1;
	d.s[1] = 0;
	for(i=a.len; i>0; i--){
		if(!(d.len==1 && d.s[1]==0)){
			for(j=d.len; j>0; j--)
				d.s[j+1] = d.s[j];
			++d.len;
		}
		d.s[1] = a.s[i];
		c.s[i] = 0;
		while( (j=HPCompare(d,b))>=0 ){
			Subtract(d,b,d);
			c.s[i]++;
			if( j==0 ) break;
		}
	}
	c.len = a.len;
	while( (c.len>1) && (c.s[c.len]==0) )
		c.len--;
}
