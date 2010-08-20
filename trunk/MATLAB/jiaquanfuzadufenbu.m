%对任取30幅图片，进行读取，
A=imread('F:\AAA毕业设计\test1\image.orig\1.jpg');  
B=rgb2gray(A);         %s前四行目的是确认每一幅图的大小，以确定矩阵C0的大小，
C=dctfuzadu(B);
[m,n]=size(C);
C0juzhen=zeros(1,30*m*n);
t=1;                        %记录每幅图计算结束以后co保存的位置
for i=1:30
    shiwei=fix(rand(1)*100/10)*10;
    gewei=fix(rand(1)*100/10);
    baiwei=fix(rand(1)*100/10)*100;
    name=shiwei+gewei+baiwei;
    str=['F:\AAA毕业设计\test1\image.orig\' num2str(name) '.jpg']

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