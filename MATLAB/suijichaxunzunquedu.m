function suijichaxunzunquedu
%�����ȡnum��ͼ���з���ֵΪ10��������
time=zeros(1,100);
P=zeros(1,100);
baiwei=0;
while baiwei< 1000           %����1000��ͼ�Ĳ�ѯ����
            for i=1:10            %��ѭ��Ϊ ÿ100������ʮ��һ��ƽ������
                shiwei= fix(rand(1)*100); %ʮλ���λ          
                name=shiwei+baiwei;
                str=['F:\AAA��ҵ���\test1\image.orig\' num2str(name) '.jpg'];
                [time(i),P(i)]=chaxun(str,10);
                Time=time(i)
                P0=P(i)
            end
            sumtime=0;
            sumP=0;
            for i=1:100
                sumtime=time(i)+sumtime;
                sumP=P(i)+sumP;
            end
            pjP=sumP/10
            pjtime=sumtime/10

     baiwei=baiwei+100;     %������100��
end
