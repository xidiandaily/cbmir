function y=dctfuzadu(x)
%计算矩阵X的DCT矩阵，然后计算复杂度矩阵
[m,n]=size(x);
X=blkproc(double(x),[8 8],@dct2);
temp=zeros(8,8);
change=zeros(m/8,n/8);
t=1;
u=1;
for i=1:8:n
    for j=1:8:m
        temp=X(j:j+7,i:i+7);
        c0=xiaojuzhenfuzadu(temp);
        jqs=jiaquanshu(temp);
        change(t)=c0*jqs;
        t=t+1;
    end
end
y=change;