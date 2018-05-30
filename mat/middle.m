function [xk_middle,x]=middle(xk)
step_size=xk(2)-xk(1);
xk_middle=xk(1)+(0:length(xk)-2)*step_size+0.5*step_size;
x=[xk,xk_middle];
x=sort(x);