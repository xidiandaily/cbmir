function [count,xout]=qiuzhifangtu(x)
%��x���ж�ȡ����¼����״�ֲ�ͼcount��xout
A=imread(x);
B=rgb2gray(A);
C=dctfuzadu(B);
[m,n]=size(C);
D=reshape(C,1,m*n);
t=zeros(1,222);           %tΪ�������䷽��
h1=linspace(0,1.25,200);   %��0~1.25����200��
h2=linspace(1.25,2.25,20); %��1.25~2.25����20��
h3=linspace(6.75,7.25,4);  
t(1,1:198)=h1(1,2:199);
t(1,199:218)=h2;
t(1,219:222)=h3;
[count,xout]=hist(D,t);
