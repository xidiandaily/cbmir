function num=tiqushuzi(str)
%对str里面的数字提取出来
xie=findstr(str,'\');
dian=findstr(str,'.');
K=xie(length(xie));
J=dian(length(dian));
num=str2num(str(K+1:J-1));