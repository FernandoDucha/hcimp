format long g;
%cd('/home/fernando/Dropbox/HC/HCImp/results');
figure1 = figure;

% Create axes
axes1 = axes('Parent',figure1,'XScale','log','XMinorTick','on');
box(axes1,'on');
xlabel('Tempo Log_{10}');
ylabel('Resultado Log_{2}');
title('Instancia 01, 100 bits');
hold(axes1,'all');
Arquivos = {'inst-0100-001.dfs','inst-0100-001.lds','inst-0100-001.bfs'};
sizeArqVector= length(Arquivos);
temp = hsv(sizeArqVector);
minY=2^31;
maxY=-2^31;
maxX=-2^31;
minX=2^31;

for i=1:sizeArqVector
    C=[];
    fid=fopen(char(Arquivos(i)),'r');
    A=[];
    C=fscanf(fid,'%g;%g;%g;%g',4);
    while(~isempty(C))
        A=[A C];
        C=fscanf(fid,'%g;%g;%g;%g',4);
    end
    A=A';
    if max(A(:,1))>maxY
        maxY =max(A(:,1));
    end
    if min(A(:,1))<minY
        minY =min(A(:,1));
    end
    if max(A(:,2))>maxX
        maxX =max(A(:,2));
    end
    if min(A(:,2))<minX
        minX =min(A(:,2));
    end
    if(mod(i,3)==1)
        stairs(A(:,2),A(:,1),'Color',temp(i,:),'DisplayName','DFS');
    elseif(mod(i,3)==2)
        stairs(A(:,2),A(:,1),'Color',temp(i,:),'DisplayName','LDS');
    elseif(mod(i,3)==0)
        stairs(A(:,2),A(:,1),'Color',temp(i,:),'DisplayName','BFS');
    end
    
    fclose(fid);
end
xlim([minX-1 maxX+100]);
ylim([minY+1 maxY+1]);
legend(axes1,'show');
% Create figure
% Create stairs

