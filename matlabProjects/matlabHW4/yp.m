function xp = F(t,x)
xp = zeros(2,1);
xp(1) = x(2);
xp(2) = -t*x(1) + exp(t)*x(2) + 3*sin(2*t);
