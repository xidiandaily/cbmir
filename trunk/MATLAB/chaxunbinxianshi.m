function [T0,P]=chaxunbinxianshi(x,num)
%对给出的照片x，按照算法算出直方图，计算相似的 num 幅照片，列出名字
load ('F:\我的文档F盘\MATLAB\赵珊方法改进\A4struct.mat');
T0=cputime;
P0=zeros(1,num);
[count,xout]=qiuzhifangtu(x);
for i=1:1000
    A(i)=qiuxiangsidu(count,A4struct(i).count);
end
[sA,index]=sort(A);
T0=cputime-T0;
for i=1:num
    %A4struct(index(i)).name
    P0(i)=tiqushuzi(A4struct(index(i)).name);  %提取名字里面的数字 101.jpg
end
P0
figure(1);
for i=1:9
    subplot(3,3,i);
    str=['F:\我的文档F盘\AAA毕业设计\test1\image.orig\' num2str(P0(i)) '.jpg'];
    imshow(str);
end

mubiao=tiqushuzi(x);
shouwei=fix(mubiao/100);                       %提取数字的百位，以确定是否命中
t=0;
for i=1:num
    if fix(P0(i)/100)==shouwei;
        t=t+1;
    else
        t=t;
    end
end
P=t/num;                                          %P为此次查询命中率
T0=T0/num;


