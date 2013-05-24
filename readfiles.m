format long g;
fid=fopen('/home/fernando/Dropbox/HC/HCImp/avgstd.dat','r');
A=[];
for i=1:969
   A=[A fscanf(fid,'%g %g %g %g %g',5)];
end
C=[];
D=[];
E=[];
for i=1:969
    C=[C A(2,i)/A(1,i)];
    D=[D A(4,i)/A(1,i)];
    E=[E (A(1,i)-1)/A(1,i)];
end
plot(A(1,:),C,A(1,:),D,A(1,:),E);
fclose(fid);