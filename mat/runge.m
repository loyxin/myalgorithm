function runge
clear
x=linspace(-5,5,20);
y=1./(1+x.^2);
xn=[-5:0.05:5];
yn=lagrange(x,y,xn);
fn=1./(1+xn.^2);
plot(xn,yn,'r')
hold on;
plot(x,y,'o');
i=input('swith i=1,2,3?')
switch i
    case 1
        yp=interp1(x,y,xn);
        plot(xn,yp,'*m')
        hold on 
    case 2
        c=polyfit(x,y,8);
        zn=polyval(c,xn);
        plot(xn,zn,'xg')
        hold on
    otherwise
end
