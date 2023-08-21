%% Problem 3b

% Setting up plot formatting
fs = 14; 
fn = 'Arial'; 
lw = 2;
primColor = [39  116 174]/ 255; 
secColor  = [255 209   0]/ 255;
terColor  = [223 82   82]/ 255;

% Setting the time range and parameter values
t_range = [0 30];
m = 0.4; 
L = 0.5; 
k = 0.2; 
b = 0.3; 
J = m * L^2; 

% Setting Initial Conditions
theta_0 = -1; 
thetaD_0 = 0; 
y_0 = [theta_0; thetaD_0];

% Setting Arrays for time and torque
torTime = t_range(1):0.01:t_range(2);
T1 = zeros(size(torTime));
T2 = zeros(size(torTime));
for i=1:size(torTime,2)
    T2(i) = 30*torTime(i)*exp(-10*torTime(i));
end

% Solving for Homogenous and Nonhomogenous system response
[theta_d, theta_dd] = ode45(@(t,y) roboTailODEfun(t,y,torTime, T1, k,b,J),...
    t_range, y_0);
[theta_d_non, theta_dd_non] = ode45(@(t,y) roboTailODEfun(t,y,torTime, T2, k, b, J),...
    t_range, y_0);

% Plotting Figure 1 -- Homogenous v. Nonhomogenous
figure(1)
plot(theta_d, theta_dd(:,1),'linewidth',lw, 'color', primColor);
hold on
plot(theta_d_non, theta_dd_non(:,1),'linewidth',lw, 'color', secColor);
hold off
xlim(t_range);
legend({'Homogenous','Non-homogenous'},'box','off','Location','southeast','fontsize',15)
xlabel('Time in seconds');
ylabel('Theta in radians');
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')


%% Problem 3c

% Setting up fixed values
testKs = [0.5 1 2]*k;
testBs = [0.5 1 2]*b;
testMs = [0.5 1 2]*m;
testLs = [0.5 1 2]*L;
cols = [primColor; 0 0 0; secColor];
    
% Plotting Figure 2 -- Varying parameters of k, b, m, L values 
figure(2); subplot(2,2,1)

% Plotting Subplot 1 -- k values
hold on    
title('Subplot 1: k-values')
for kNum = 1:length(testKs)
    k_cur = testKs(kNum);
    [t_cur, y_cur] = ode45(@(t,y) roboTailODEfun(t,y,torTime,T2,...
                            k_cur, b, J),t_range, y_0);
    plot(t_cur,y_cur(:,1),'color',cols(kNum,:),'linewidth',lw)
end
hold off
legend({['k = ' num2str(testKs(1))],['k = ' num2str(testKs(2))],...
    ['k = ' num2str(testKs(3))]},'box','off','location','northeast')
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')

% Plotting Subplot 2 -- m values
figure(2); subplot(2,2,2)
hold on   
title('Subplot 2: m-values')
for MNum = 1:length(testMs)
    M_cur = testMs(MNum);
     J1 = M_cur * L^2;
    [t_cur, y_cur] = ode45(@(t,y) roboTailODEfun(t,y,torTime,T2,...
                            k, b, J1),t_range, y_0);
    plot(t_cur,y_cur(:,1),'color',cols(MNum,:),'linewidth',lw)
end
hold off
legend({['m = ' num2str(testMs(1))],['m = ' num2str(testMs(2))],...
    ['m = ' num2str(testMs(3))]},'box','off','location','northeast')
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')

% Plotting Subplot 3 -- b values
figure(2); subplot(2,2,3)
hold on    
title('Subplot 3: b-values')
for BNum = 1:length(testBs)
    B_cur = testBs(BNum);
    [t_cur, y_cur] = ode45(@(t,y) roboTailODEfun(t,y,torTime,T2,...
                            k,B_cur, J),t_range, y_0);
    plot(t_cur,y_cur(:,1),'color',cols(BNum,:),'linewidth',lw)
end
hold off
legend({['b = ' num2str(testBs(1))],['b = ' num2str(testBs(2))],...
    ['b = ' num2str(testBs(3))]},'box','off','location','northeast')
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')

% Plotting Subplot 4 -- L values
figure(2); subplot(2,2,4)
hold on    
title('Subplot 4: L-values')
for LNum = 1:length(testLs)
    L_cur = testLs(LNum);
    J0 = m * L_cur^2;
    [t_cur, y_cur] = ode45(@(t,y) roboTailODEfun(t,y,torTime,T2,...
                            k, b, J0),t_range, y_0);
    plot(t_cur,y_cur(:,1),'color',cols(LNum,:),'linewidth',lw)
end
hold off
legend({['L = ' num2str(testLs(1))],['L = ' num2str(testLs(2))],...
    ['L = ' num2str(testLs(3))]},'box','off','location','northeast')
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')

% Setting up Fixed Values
testTime = 0:0.01:30;
bVals = 0.01:0.02:1;
RSMEs = zeros(size(bVals));

% Calculating RMSEs for bVals
for bVal = 1:length(bVals)
    b_cur = bVals(bVal);
    [t_cur,y_cur]= ode45(@(t,y) roboTailODEfun(t,y,torTime,T2,...
                            k, b_cur, J),t_range, y_0);
    yInt_cur = interp1(t_cur, y_cur, testTime,'pchip','extrap');
    error = yInt_cur(:,1);
    RSMEcur = sqrt(mean(error.^2));
    RSMEs(bVal) = RSMEcur;
end

% Plotting Figure 3 -- RMSE v B value
figure(3)
hold on
plot(bVals,RSMEs);
xlabel('b-Values (Nms/radians)');
ylabel('RMSEs (radians)');
set(gca, 'FontSize', fs, 'FontName', fn, 'linewidth', lw, 'box', 'off') % apply our beautiful formatting

% Solving for minimum RMSE and value that caused it
minRSMEs = min(RSMEs(:));
min1 = find(RSMEs==minRSMEs);
minb = bVals(min1);

% Solving for optimized b value function 
[t2, theta2] = ode45(@(t,y) roboTailODEfun(t,y,torTime,T2,...
                            k, minb, J),t_range, y_0);
                        
% Plotting Figure 4 -- Optimized B value v. Original Nonhomogenous Plot
figure(4)
plot(theta_d_non, theta_dd_non(:,1), 'linewidth',lw, 'color', primColor);
hold on
plot(t2, theta2(:,1),'linewidth',lw, 'color', secColor);
hold off
legend({'Original B','Optimized B'},'box','off','Location','southeast','fontsize',15)
xlabel('Time in seconds');
ylabel('Theta in radians');
set(gca, 'FontSize', fs, 'FontName', fn, 'linewidth', lw, 'box', 'off') 

%% Problem 3d

% Setting fixed values
testTime = 0:0.01:30;
t_range = [testTime(1) testTime(end)];
alphas = 3:1:16;
bVals = 1:0.2:5;
RMSEs = zeros(length(alphas),length(bVals));
T14 = zeros(size(testTime));
T24 = zeros(size(testTime));
for i=1:size(testTime,2)
    T2(i) = 30*testTime(i)*exp(-10*testTime(i));
end

% Iterating through a and b values for optimization
for alpha1 = 1:length(alphas)
    for b1 = 1:length(bVals)
        alpha1_cur = alphas(alpha1);
        b1_cur = bVals(b1);
            [t1_cur,y1_cur]= ode45(@(t,y) roboTailODEfunVarK(t,y,testTime,T2,...
                            alpha1_cur, b1_cur, J),testTime, y_0);
         ab_cur = interp1(t1_cur, y1_cur, testTime,'pchip','extrap');
         err2 = ab_cur(:,1);
         RMSE4 = sqrt(mean(err2.^2));
         RMSEs(alpha1,b1) = RMSE4;               
    end
end

% Plotting Figure 5 -- 3D surface plot of resultnat RMSEs of a and b
figure(5)
[X,Y] = meshgrid(bVals,alphas);
surf(X,Y,RMSEs);
view(3); 
xlim([0 6]);
colormap hot 
xlabel('b')
ylabel('Alpha')
zlabel('RMSE (rad)')
set(gca, 'FontSize', fs, 'FontName', fn, 'linewidth', lw, 'box', 'off')

% Calculating RMSE and values that produced it
minRMSE = min(min(RMSEs));
[x,y] = find(RMSEs==minRMSE);
minbval = bVals(y);
minAlpha = alphas(x);

% Printing RMSE value and values that produced it
fprintf('The minimum RMSE value for part 3d is: %.4f\n',minRMSE);
fprintf('The b value that produced the minimum RMSE value is: %.2f\n',minAlpha);
fprintf('The a value that produced the minimum RMSE value is: %.2f\n',minbval);

% Solving for Optimized a and b value Function
[t3, theta3] = ode45(@(t,y) roboTailODEfunVarK(t,y,testTime,T2,...
                            minAlpha, minbval, J),t_range, y_0);
                        
% Plotting Figure 6 -- Optimized Nonhomogenous Plot
figure(6)
plot(theta_d_non, theta_dd_non(:,1), 'linewidth',lw, 'color', primColor);
hold on
plot(t2, theta2(:,1),'linewidth',lw, 'color', secColor);
plot(t3, theta3(:,1),'linewidth',lw, 'color', terColor);
hold off
legend({'Original B','Optimized B','Optimized NL spring'},'box','off','Location','southeast','fontsize',15)
xlabel('Time in seconds');
ylabel('Theta in radians');
set(gca, 'FontSize', fs, 'FontName', fn, 'linewidth', lw, 'box', 'off') 


% Solving for Optimized Homogenous Cases
[theta_d_hom, theta_dd_hom] = ode45(@(t,y) roboTailODEfun(t,y,torTime, T1, k,b,J),...
                            t_range, y_0);
[t2_hom, theta2_hom] = ode45(@(t,y) roboTailODEfun(t,y,torTime,T1,...
                            k, minb, J),t_range, y_0);
[t3_hom, theta3_hom] = ode45(@(t,y) roboTailODEfunVarK(t,y,testTime,T1,...
                            minAlpha, minbval, J),t_range, y_0);
                        
% Plotting Figure 7 -- Optimized Homogenous Plot
figure(7)
plot(theta_d_hom, theta_dd_hom(:,1), 'linewidth',lw, 'color', primColor);
hold on
plot(t2_hom, theta2_hom(:,1), 'linewidth',lw, 'color', secColor);
plot(t3_hom, theta3_hom(:,1), 'linewidth',lw, 'color', terColor);
hold off
legend({'Original B','Optimized B','Optimized NL spring'},'box','off','Location','southeast','fontsize',15)
xlabel('Time in seconds');
ylabel('Theta in radians');
set(gca, 'FontSize', fs, 'FontName', fn, 'linewidth', lw, 'box', 'off') 
