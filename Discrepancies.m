size =10;
sub=0
A=zeros(1,size+1);
B=zeros(size+1,size);
D=ones(size+1,1);
B=[D B];
for i=1:size
    for j=1:size
        if((i-j)>=0)
            A(1,j+1)=A(1,j+1)+factorial(i-1)/(factorial(j-1)*factorial(i-j));
        end
    end
    B(i+1,1:size+1)=B(i+1,1:size+1)+A;
    
end

for(i=1:length(B(:,1)))
     B(i,:)=B(i,:)/(sum(B(i,:)))*100;
end
% cc=hsv(size);
% %hold on;
% size=size-sub;
% h=11*ones(11,1);
% %bar([1:size+1],B,'stacked');
% yticks = [get(gca,'ytick')]'; % There is a transpose operation here.
% xticks = [get(gca,'xtick')]'; % There is a transpose operation here.
% xticks =h-xticks;
% percentsy = repmat('%', length(yticks),1); % equal to the size
% 
% yticklabel = [num2str(yticks) percentsy]; % concatenates the tick labels 
% xticklabel = [num2str(xticks)];
% set(gca,'yticklabel',yticklabel);
% set(gca,'xticklabel',xticklabel);

% Sets tick labels back on the Axis
%dlmwrite('teste.txt',B,';');