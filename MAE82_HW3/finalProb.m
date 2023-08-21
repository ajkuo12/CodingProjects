%% Final

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
y_0 = [x_0; xd_0];

% Setting Arrays for time and torque
torTime = t_range(1):0.01:t_range(2);
T1 = zeros(size(torTime));
for i=1:size(torTime,2)
    T1(i) = 200*sin(0.5*torTime(i));
end

[xd_non, xdd_non] = ode45(@(t,y) roboTailODEfinal(t,y,torTime, T1, m, b, k),...
    t_range, y_0);

% Plotting Figure 1 -- Nonhomogenous
figure(1)
plot(xd_non, xdd_non(:,1),'linewidth',lw, 'color', primColor);
xlim(t_range);
legend({'Non-homogenous'},'box','off','Location','southeast','fontsize',fs)
xlabel('Time in seconds');
ylabel('Position in meters');
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')

%% Part b
time = 0:0.01:30;
a = 200;
h = zeros(size(time));
h(time>=1 & time<3) = a;
h(time>=3 & time<4) = -a;

[x_hnon, xhd_non] = ode45(@(t,y) roboTailODEfinal(t,y,torTime, h, m, b, k),...
    t_range, y_0);

% Plotting Figure 2 -- Nonhomogenous
figure(2)
plot(x_hnon,xhd_non(:,1),'linewidth',lw, 'color', primColor);
xlim(t_range);
legend({'Non-homogenous'},'box','off','Location','southeast')
xlabel('Time in seconds');
ylabel('Position in meters');
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')
%% Part d
bVals = linspace(b/10,10*b,100);
RSMEs = zeros(size(bVals));
for bVal = 1:length(bVals)
    b_cur = bVals(bVal);
    [t_cur,y_cur]= ode45(@(t,y) roboTailODEfinal(t,y,torTime,h,...
                            m, b_cur, k),t_range, y_0);
    yInt_cur = interp1(t_cur, y_cur, bVals,'pchip','extrap');
    error = yInt_cur(:,1);
    RSMEcur = sqrt(mean(error.^2));
    RSMEs(bVal) = RSMEcur;
end

% Plotting Figure 3 -- B values
figure(3)
plot(bVals,RSMEs,'linewidth',lw, 'color', primColor);
xlabel('B Values');
ylabel('RMSEs');
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')

minRSMEs = max(RSMEs(:));
min1 = find(RSMEs==minRSMEs);
minb = bVals(min1);
%% Part b
time = 0:0.01:30;
a = 200;
h = zeros(size(time));
h(time>=1 & time<3) = a;
h(time>=3 & time<4) = -a;

[x_bhnon, xhdb_non] = ode45(@(t,y) roboTailODEfinal(t,y,torTime, h, m, minb, k),...
    t_range, y_0);

% Plotting Figure 4 -- Optimization
figure(2)
plot(x_hnon,xhd_non(:,1),'linewidth',lw, 'color', primColor);
hold on
plot(x_bhnon,xhdb_non(:,1),'linewidth',lw, 'color', secColor);
hold off
xlim(t_range);
legend({'Original','Optimized'},'box','off','Location','southeast')
xlabel('Time in seconds');
ylabel('Position in meters');
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')