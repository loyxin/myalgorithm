function I=Trapezd(f_name,int_low,int_high,num)
if num==0 fprintf('error\n');return;end
if nargin<2 int_low=0;end;if nargin<3 int_high=1;end;if nargin<4 num=100;end;
step_size=(int_high-int_low)/num;
x=int_low+(0:num)*step_size;
fx=feval(f_name,x);
%rectangle integration
I=step_size*(sum(fx)-(fx(1)+fx(length(fx)))/2);

%¸ÄÐ´ÊäÈë£ø