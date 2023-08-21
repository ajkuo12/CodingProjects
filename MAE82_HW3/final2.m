%% Final part b

% Setting up plot formatting
fs = 14; 
fn = 'Arial'; 
lw = 2;
primColor = [39  116 174]/255; %UCLA Blue
secColor =  [255 209   0]/255; %UCLA Gold


% Setting the time range and parameter values
t_range = [0 30];
m = 18143695;
b = 9504740;
k = 483000;

% Setting Initial Conditions
x_0  = 1.5; 
xd_0 = 0; 
y_0 = [x_0; xd_0];%% Part b
t = 0:0.01:30;


% Setting Arrays for time and torque
 torTime = t_range(1):0.01:t_range(2);
% T2 = zeros(size(torTime));
% for i=1:0.01:30
%     T2(i) = h(torTime);
% end
a = 200;
h = zeros(size(torTime));
h(t>=1 & t<3) = a;
h(t>=3 & t<4) = -a;
[anon, ah_non] = ode45(@(t,y) roboTailODEfinal2(t,y,torTime, h, m, b, k),...
    t_range, y_0);

% Plotting Figure 2 -- Nonhomogenous
figure(1)
plot(anon, ah_non(:,1),'linewidth',lw, 'color', secColor);
xlim(t_range);
legend({'Non-homogenous'},'box','off','Location','southeast','fontsize',15)
xlabel('Time in seconds');
ylabel('Position in meters');
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')