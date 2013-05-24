A=zeros(100,1);
C=[1:100]-ones(1,100);
S=[1:100]
B=zeros(100,100);
for i=1:100
    for j=1:100
        if((i-j)>=0)
            A(j,1)=A(j,1)+factorial(i-1)/(factorial(j-1)*factorial(i-j));
        end
    end
    B(i,:)=A;
end
D=ones(100,1);
B=[D B];
cc=hsv(100);
hold on;
plot(C(1:50),log2(B(1:50,1:10)));
