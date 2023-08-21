t = 0:0.01:30;
t_range = [0 30];
m = 18143695;
b = 9504740;
k = 483000;
x_0  = 1.5; 
xd_0 = 0; 
y_0 = [x_0; xd_0];
a = 200;
h = zeros(size(t));
h(t>=1 & t<3) = a;
h(t>=3 & t<4) = -a;

theta = y(1);
dtheta_dt = y(2);

% Add code here to calculate T at the current time, based on the input
% values torTime and Tall.
T = interp1(torTime, Tall, t);

theta_d = dtheta_dt;
% Add your differential equation here:
theta_dd = (T - k*theta - b*theta_d)/m; % **Replace the brackets with your equation.

% Here's our output.
y_dot = [theta_d; theta_dd];

%[a, aa] = ode45(@(t,y) roboTailODEfinal(t,y,tf, h, m, b, k),...
   % t_range, y_0);
