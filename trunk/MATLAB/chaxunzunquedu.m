function chaxunzunquedu
%随机抽取num幅图进行返回值为10幅的试验
time=zeros(1,100);
P=zeros(1,100);
baiwei=400;
while baiwei<600           %计算1000幅图的查询精度
            for i=0:99             %此循环为 每100幅计算一次平均精度
                name=i+baiwei;
                str=['F:\AAA毕业设计\test1\image.orig\' num2str(name) '.jpg'];
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

     baiwei=baiwei+100;     %计算下100幅
end
