function c0=xiaojuzhenfuzadu(x)
%对矩阵x进行读取，傅里叶变换，反变换，再求复杂度C0；
[m,n]=size(x);
image=x;
FMN=fft2(double(image));
FMNT=zeros(m,n);
FMN3=abs(FMN);       %对FMN取模，以便进行均方直与条件判定只用
SUM2=sum(sum(FMN3));
GMN=SUM2/(m*n);
for i=1:1:m
    for j=1:1:n
        if FMN3(i,j)<GMN
            FMNT(i,j)=0;
        else
            FMNT(i,j)=FMN(i,j);
    end
    end
end
fmn=ifft2(FMNT);
image2=zeros(m,n);
for i=1:1:m
    for j=1:1:n
        image2(i,j)=abs(image(i,j)-fmn(i,j));
    end
end
SUM2=sumsum2(image2);
di=sumsum2(image);
c0=SUM2/di;
function y=sumsum2(x)
%对x进行按行求平方和
[m,n]=size(x);
sum1=0;
temp=zeros(m,n);
for i=1:1:m
    for j=1:1:n
       temp(i,j)=x(i,j)*x(i,j);
       sum1=sum1+temp(i,j);
    end
end
y=sum1;



