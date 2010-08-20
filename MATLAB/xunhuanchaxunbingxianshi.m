function xunhuanchaxunbingxianshi(num)
% 顺序对图像查询，每按一次显示9幅
i=num;
while 1    
    str=['F:\我的文档F盘\AAA毕业设计\test1\image.orig\' num2str(i) '.jpg']
    [T0,P]=chaxunbinxianshi(str,9)    %对文件str进行查询并显示
    i=i+1;
    pause;
end