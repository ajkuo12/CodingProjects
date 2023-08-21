%[t,x] = ode45('F',[t0,tf],[x10, x20]);
[t,x] = ode45('F',[0,10],[0.05, 0.1]);
tspan = 0:0.001:10;

fx = 0.05*exp(-0.15*tspan).*cos(3.87*tspan) + 0.027.*exp(-0.15.*tspan).*sin(3.87.*tspan);

plot(t,x(:,1),'color','b');
title('Final','fontsize',18);
xlabel('Time')
ylabel('something');
hold on
plot(tspan,fx,'color','g');
hold off