/*************************************************************************
	> File Name: fraction.cpp
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2018-03-04 22:02:05
 ************************************************************************/
/**
** 递归求最小公约数
** a,b>0 其实应该写成 unsigned int 
**/ 

int gcd(int a, int b){
	if( b==0 ) return a;//if a==0 后面会交换顺序
	return gcd(b, a%b);//递归求最小公约数 
}

/** 
** 利用 gcd 求最小公倍数
**/

int lcm(int a, int b){
	return a/gcd(a,b)*b;
} 
// 给两个数，知道它们的最简分数 给出四则运算， 和输出<< 
class Fraction{
	public:
		int a,b;// a/b = numberator/denominator
		// 符号函数 返回  1 为正， -1 为负 
		int sign(int x){ return(x>0?1:-1);}
		int get_denominator(){return b;}
		int get_numberator(){return a;}
		 
		Fraction():a(0),b(1){}
		Fraction(int x):a(x),b(1){}
		Fraction(int x, int y){
			int m = gcd(abs(x),abs(y));
			a = x/m * sign(y); // 分子得两个数的符号 
			if( a==0 ) b = 1; // if a==0 then x==0
			else b = abs(y/m); 
		}
		
		Fraction operator+(const Fraction &f){
			int m = gcd(b,f.b);
			return Fraction(f.b/m * a + b/m * f.a, b/m*f.b);
		}
		
		Fraction operator-(const Fraction &f){
			int m = gcd(b,f.b);
			return Fraction(f.b/m * a - b/m * f.a, b/m*f.b);
		}
		
		Fraction operator*(const Fraction &f){
			int m1 = gcd(abs(a),f.b);
			int m2 = gcd(b,abs(f.a));
			return Fraction( (a/m1)*(f.a/m2), (b/m2)*(f.b/m1) );
		}
		
		Fraction operator/(const Fraction &f){
			return (*this)*Fraction(f.b,f.a);
		}
		
		friend ostream& operation<<(ostream &out, const Fraction &f){
			if( f.a==0 ) cout<<0;
			else if( f.b==1 ) cout<<f.a;
			else cout<<f.a<<'/'<<f.b;
			return out;
		}
};

