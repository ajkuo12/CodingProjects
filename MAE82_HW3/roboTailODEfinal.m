function y_dot = roboTailODEfinal(t,y,torTime,Tall, m, b, k)

% Because this is a second-order ODE, y is now a vector that contains both
% theta and dtheta_dt. We need to extract those to use in our diff eqn.
% https://www.mathworks.com/help/matlab/math/solve-nonstiff-odes.html
theta = y(1);
dtheta_dt = y(2);

% Add code here to calculate T at the current time, based on the input
% values torTime and Tall.
T = interp1(torTime, Tall, t);

theta_d = dtheta_dt;
% Add your differential equation here:
theta_dd = (T - k*theta - b*theta_d)/m; % **Replace the brackets with your equation.

% Here's our output.
y_dot = [theta_d;
         theta_dd];