function I=simpson(f_name,int_low,int_high,num)
if num==0 fprintf('error\n');return;end;
if nargin<2 int_low=0;end;if nargin<3 int_high=1;end;if nargin<4 num=100;end;
step_size=(int_high-int_low)/num;
xk_middle=int_low+(0:num-2)*step_size+0.5*step_size;%
fxk_middle=feval(f_name,xk_middle);
T1=1/3*Trapezd(f_name,int_low,int_high,num);
T2=2/3*step_size*(sum(fxk_middle));
I=T1+T2;
%¸ÄÐ´ÊäÈë£ø