%����ȡ30��ͼƬ�����ж�ȡ��
A=imread('F:\AAA��ҵ���\test1\image.orig\1.jpg');  
B=rgb2gray(A);         %sǰ����Ŀ����ȷ��ÿһ��ͼ�Ĵ�С����ȷ������C0�Ĵ�С��
C=dctfuzadu(B);
[m,n]=size(C);
C0juzhen=zeros(1,30*m*n);
t=1;                        %��¼ÿ��ͼ��������Ժ�co�����λ��
for i=1:30
    shiwei=fix(rand(1)*100/10)*10;
    gewei=fix(rand(1)*100/10);
    baiwei=fix(rand(1)*100/10)*100;
    name=shiwei+gewei+baiwei;
    str=['F:\AAA��ҵ���\test1\image.orig\' num2str(name) '.jpg']

    A=imread(str);
    B=rgb2gray(A);
    C=dctfuzadu(B);
    [m,n]=size(C);
    D=reshape(C,1,m*n);
    for n=1:m*n
        C0juzhen(t)=D(n);
        t=t+1;
    end  
end
 [count,xout]=hist(D,170);