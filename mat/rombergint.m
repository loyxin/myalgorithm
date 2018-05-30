%Îó²î²»Òª³¬¹ýe-9
function I=rombergint(f_name,int_low,int_high,eps_error)
%default settings
if nargin<2 int_low=0;end;if nargin<3 int_high=1;end;if nargin<4 eps_error=1e-6;end;
%error input
if eps_error==0 fprintf('error\n');return;end;
fprintf('eps=%.17f\n',eps_error);
%declare variables
i=1;j=1;T2=1;T1=2;err=1.0;
% initialization x
x=(int_low:(int_high-int_low)/100:int_high);
T(1,1)=Trapezd(f_name,int_low,int_high,length(x));
while(err>eps_error)
    [xmiddle,x]=middle(x);%x middle variable
    fmiddle=feval(f_name,xmiddle);
    step_size=x(2)-x(1);
    T(i+1,1)=0.5*T(i,j)+step_size*sum(fmiddle);%calculating formula
    for j=2:i+1
    T(i+1,j)=4^j/(4^j-1)*T(i+1,j-1)-1/(4^j-1)*T(i,j-1);%regursive formule
    end
    T2=T(i+1,i);T1=T(i,i);
    err=abs(T2-T1);%
    i=i+1;
end
I=T;