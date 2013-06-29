function DiscrepanciesGraph(ymatrix1)
%CREATEFIGURE(YMATRIX1)
%  YMATRIX1:  bar matrix data

%  Auto-generated by MATLAB on 28-Jun-2013 23:57:55

% Create figure
figure1 = figure;

% Create axes
axes1 = axes('Parent',figure1,...
    'YTickLabel',['  0%';' 10%';' 20%';' 30%';' 40%';' 50%';' 60%';' 70%';' 80%';' 90%';'100%'],...
    'XTickLabel',['10';' 9';' 8';' 7';' 6';' 5';' 4';' 3';' 2';' 1';' 0'],...
    'XTick',[1 2 3 4 5 6 7 8 9 10 11],...
    'LineWidth',2,...
    'GridLineStyle','--',...
    'FontSize',16);
%% Uncomment the following line to preserve the X-limits of the axes
xlim(axes1,[0.5 11.5]);
box(axes1,'on');
grid(axes1,'on');
hold(axes1,'all');

% Create multiple lines using matrix input to bar
bar1 = bar(ymatrix1,'BarWidth',0.4,'BarLayout','stacked','Parent',axes1);
set(bar1(1),'DisplayName','d_1');
set(bar1(2),'DisplayName','d_2');
set(bar1(3),'DisplayName','d_3');
set(bar1(4),'DisplayName','d_4');
set(bar1(5),'DisplayName','d_5');
set(bar1(6),'DisplayName','d_6');
set(bar1(7),'DisplayName','d_7');
set(bar1(8),'DisplayName','d_8');
set(bar1(9),'DisplayName','d_9');
set(bar1(10),'DisplayName','d_{10}');
set(bar1(11),'DisplayName','d_{11}');

% Create xlabel
xlabel('Depth - \textbf{k}','Interpreter','latex','FontWeight','bold',...
    'FontSize',24,...
    'FontAngle','italic');

% Create ylabel
ylabel('$\mathbf{\frac{n_{d_i}^k}{\sum_{d_j\in k}n_{d_j}}}$','Interpreter','latex',...
    'FontWeight','light',...
    'FontSize',30);

% Create title
title('Evolution of discrepancies growth in relation to depth.',...
    'FontWeight','bold',...
    'FontSize',24);

% Create legend
legend1 = legend(axes1,'show');
set(legend1,...
    'Position',[0.916387959866221 0.204821717990276 0.0681438127090301 0.642220421393841]);
