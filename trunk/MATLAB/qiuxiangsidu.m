function y=qiuxiangsidu(x1,x2)
%��x1��x2��ֱ��ͼ���ƶȽ��м��㣬����ԽСԽ�ӽ�
[n,m]=size(x1);
sum1=0;
for i=1:m
    if x1(i)<x2(i)
        sum1=sum1+x1(i);
    else
        sum1=sum1+x2(i);
    end
end
T1=sum(x1);
T2=sum(x2);
if T1<T2
    T=T1;
else
    T=T2;
end
dpq=1-sum1/T;
y=dpq;