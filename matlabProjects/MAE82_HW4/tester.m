theta_ic = [15; 0]; % initial conditions: theta(t=0)=0.5; dtheta(t=0)=0.
tspan = [0 10];
[t, theta] = ode45(@odeFun, tspan, theta_ic);
plot(t, theta);
legend({'$\theta$', '$\dot{\theta}$'}, ...
    'Location', 'best', ...
    'Interpreter', 'latex', ...
    'FontSize', 16)
function dtheta = odeFun(t, theta)
    g = 9.7979;
    l = 0.3;
    % theta(1) = theta, theta(2) = dtheta
    
    dtheta = zeros(2, 1);
    dtheta(1) = theta(2);
    dtheta(2) = -g/l*theta(1);
end