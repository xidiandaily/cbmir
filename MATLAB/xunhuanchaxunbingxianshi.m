function xunhuanchaxunbingxianshi(num)
% ˳���ͼ���ѯ��ÿ��һ����ʾ9��
i=num;
while 1    
    str=['F:\�ҵ��ĵ�F��\AAA��ҵ���\test1\image.orig\' num2str(i) '.jpg']
    [T0,P]=chaxunbinxianshi(str,9)    %���ļ�str���в�ѯ����ʾ
    i=i+1;
    pause;
end