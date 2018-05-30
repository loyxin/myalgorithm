/*************************************************************************
	> File Name: basic_operator.cpp
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2018-03-05 23:33:10
 ************************************************************************/

//basic_operator

const double eps = 1e-8;
const double pi = acos(-1);// cos 的反函数

struct CPoint{double x, y;};

double min(double x, double y){
	if( x<y ) return x;
	else return y;
}

double max(double x, double y){
	if( x>y ) return x;
	else return y;
}

double sqr(double x){
	return x*x;
}
// -1 1 的大于误差, 只不过 -1 是负数大于
// 0 是 在 -eps eps 之间
int dcmp(double x){
	if( x<-eps ) return -1;
	else return ( x>eps );
}
// 比较两点, 小于误差则认为是一点
int PointEqual(const CPoint& p1, const CPoint& p2){
	return dcmp( p1.x-p2.x )==0 && dcmp(p1.y-p2.y)==0;
}
// 叉积 二维
double cross(CPoint p0, CPoint p1, CPoint p2){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

// 点积
double dot(CPoint p0, CPoint p1, CPoint p2){
	return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}

double dissqr(CPoint p1, CPoint p2){
	return sqr(p1.x-p2.x)+sqr(p1.y-p2.y);
}

double dis(CPoint p1, CPoint p2){
	return sqrt( sqr(p1.x-p2.x)+sqr(p1.y-p2.y) );
}

// extended operations
// cross angle of p_0p_1->p_0p_2 range in (-pi,pi)
double angle(CPoint p0, CPoint p1, CPoint p2){
	double cr = cross( p0, p1, p2 );
	double dt = dot( p0, p1, p2 );
	if( dcmp(cr)==0 ) cr = 0.0;
	if( dcmp(dt)==0 ) dt = 0.0;
	return atan2( cr, dt );
}

int PointOnLine(CPoint p0, CPoint p1, CPoint p2){
	return dcmp( cross(p0, p1, p2) )==0;
}

int PonitOnSegment(CPoint p0, CPoint p1, CPoint p2){
		return dcmp( cross(p0, p1, p2) )==0 && dcmp( dot(p0, p1, p2))<=0;
}
// 1 = cross; 0 = parallel; -1 = overlap 重叠
// cp cross point 
int LineIntersection(CPoint p0, CPoint p1, CPoint p2, CPoint p3, CPoint p4, CPoint& cp){
	double u = cross(p1, p2, p3), v = cross(p2, p1, p4);
	if( dcmp(u+v) ){
		cp.x = (p3.x*v+p4.x*u)/(v+u);
		cp.y = (p3.y*v+p4.y*u)/(v+u);
		return 1;
	}
	if( dcmp(u) ) return 0; // else u = v =0;
	if( dcmp( cross(p3, p4, p1) ) ) return 0;
	return -1;
}


