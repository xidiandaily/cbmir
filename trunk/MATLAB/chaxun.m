function [T0,P]=chaxun(x,num)
%�Ը�������Ƭx�������㷨���ֱ��ͼ���������Ƶ� num ����Ƭ���г�����
load ('F:\�ҵ��ĵ�F��\MATLAB\��ɺ�����Ľ�\A4struct.mat');
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
    P0(i)=tiqushuzi(A4struct(index(i)).name);  %��ȡ������������� 101.jpg
end
P0
mubiao=tiqushuzi(x);
shouwei=fix(mubiao/100);                       %��ȡ���ֵİ�λ����ȷ���Ƿ�����
t=0;
for i=1:num
    if fix(P0(i)/100)==shouwei;
        t=t+1;
    else
        t=t;
    end
end
P=t/num;                                          %PΪ�˴β�ѯ��׼��
T0=T0/num;


