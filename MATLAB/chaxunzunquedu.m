function chaxunzunquedu
%�����ȡnum��ͼ���з���ֵΪ10��������
time=zeros(1,100);
P=zeros(1,100);
baiwei=400;
while baiwei<600           %����1000��ͼ�Ĳ�ѯ����
            for i=0:99             %��ѭ��Ϊ ÿ100������һ��ƽ������
                name=i+baiwei;
                str=['F:\AAA��ҵ���\test1\image.orig\' num2str(name) '.jpg'];
                [time(i+1),P(i+1)]=chaxun(str,10);
                Time=time(i+1)
                P0=P(i+1)
            end
            sumtime=0;
            sumP=0;
            for i=0:99
                sumtime=time(i+1)+sumtime;
                sumP=P(i+1)+sumP;
            end
            pjP=sumP/100
            pjtime=sumtime/100

     baiwei=baiwei+100;     %������100��
end
