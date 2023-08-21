%Initializing Variables for 15 degrees
t = 0:0.001:10;
theta_ic_15 = [15; 0];
tspan = [0 10];
constants = 0:0.001:0.035;
g = 9.797;
approximation = g .* constants;
L1 = 0.1;
L2 = 0.2;
L3 = 0.3;
theta15 = 15;
% ODE
theta_ic_60 = [60; 0];
tspan = [0 10];
[t, theta] = ode45(@odeFun, tspan, theta_ic_60);

figure(4)
plot(t,theta);

% figure() 
% Found the period values through close analysis of the plots
% plot(t,dTheta1); hold on;  %T1 = 0.635
% plot(t,dTheta2);           %T2 = 0.898
% plot(t,dTheta3); hold off; %T3 = 1.099

% Plotting Figure 1
T1 = 0.635;
T2 = 0.898;
T3 = 1.099;
X1 = (T1/(2*pi))^2;
X2 = (T2/(2*pi))^2;
X3 = (T3/(2*pi))^2;
X = [X1, X2, X3];
Y = [L1, L2, L3];
figure(1)
grid on;
scatter(X,Y,'o','filled','s'); hold on;
plot(constants, approximation);
hold off;
axis([0 0.035 0 0.35]);
xlabel('Predicted Values of (T/2*pi)^2');
ylabel('Pendulum Length L (m)');
title('Figure 1: Initial Angle 15 Degrees');

% Initializing Variables for 60 degrees
y0 = 60;
% ODE -- used same as above to find periods
T4 = 0.6347;
T5 = 0.89761;
T6 = 1.09935;
% Plotting and finding periods
X4 = (T4/(2*pi))^2;
X5 = (T5/(2*pi))^2;
X6 = (T6/(2*pi))^2;
X60 = [X4 X5 X6];
figure(2)
grid on;
scatter(X60,Y,'o','filled','s'); hold on;
plot(constants, approximation);
hold off;
axis([0 0.035 0 0.35]);
xlabel('Predicted Values of (T/2*pi)^2');
ylabel('Pendulum Length L (m)');
title('Figure 2: Initial Angle 60 Degrees');

function dtheta = odeFun(t, theta)
    g = 9.7979;
    l = 0.3;
    dtheta = zeros(2, 1);
    dtheta(1) = theta(2);
    dtheta(2) = -((g*sin(theta(1)))/l);
end
