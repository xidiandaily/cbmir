function suijichaxunzunquedu
%随机抽取num幅图进行返回值为10幅的试验
time=zeros(1,100);
P=zeros(1,100);
baiwei=0;
while baiwei< 1000           %计算1000幅图的查询精度
            for i=1:10            %此循环为 每100幅计算十幅一次平均精度
                shiwei= fix(rand(1)*100); %十位与个位          
                name=shiwei+baiwei;
                str=['F:\AAA毕业设计\test1\image.orig\' num2str(name) '.jpg'];
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

     baiwei=baiwei+100;     %计算下100幅
end
