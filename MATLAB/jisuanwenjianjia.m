files=dir('F:\AAA��ҵ���\test1\image.orig\*.jpg');
A4struct(1000)=struct('name','','count',0);
for i=1:1:length(files) 
        wj=files(i).name;
        wjming=['F:\AAA��ҵ���\test1\image.orig\' wj];
        A4struct(i).name=wjming;
        [A4struct(i).count,n]=qiuzhifangtu(wjming);
        if mod(i,50)==0
            i
        end
end