function bandao
%   单位eV，Ef=0.56eV，上下1eV，Ev =  0 eV， Eg=1.12eV  kt300=0.026;ef=0.56;
%   kt300=0.026 为做图好看 改为0.26
kt300=0.26;ef=0.56;
x=-1:0.01:2.12;
feymi100=1./(1+exp((x-ef)*3/kt300));%100K 电子 F(E)
figure;
plot(feymi100,x)
feymi400=1./(1+exp((x-ef)*3/(4*kt300)));%400K 电子  F(E)
hold on;plot(feymi400,x,'r')
feymi_400=1-feymi400;feymi_100=1-feymi100;%400K 100K 空穴  F(E)
plot(feymi_400,x,'r',feymi_100,x)
hold off;
figure;
xv=-1:0.01:0;xc=1.12:0.01:2.12;
xz=0.01:0.01:1.11;
gc=(xc-1.12).^0.5;  %状态密度 函数 导带
gv=(-1*xv).^0.5;  %状态密度 函数 价带
gz=zeros(1,length(xz));
g=[gv,gz,gc];
plot(gv,xv,gc,xc);
hold off;
%电子空穴浓度
gv0=zeros(1,length(gv));gc0=zeros(1,length(gc));
gv00=[gv,gz,gc0];gc00=[gv0,gz,gc];
n400=feymi400.*g.*gc00;n100=feymi100.*g.*gc00;
p400=feymi_400.*g.*gv00;p100=feymi_100.*g.*gv00;
figure;
plot(n400,x,'r',n100,x,'k',p100,x,'b',p400,x,'m');
end


