function num=tiqushuzi(str)
%��str�����������ȡ����
xie=findstr(str,'\');
dian=findstr(str,'.');
K=xie(length(xie));
J=dian(length(dian));
num=str2num(str(K+1:J-1));