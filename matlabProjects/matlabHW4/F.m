function xp = F(t,x)
xp = zeros(2,1);
xp(1) = x(2);
xp(2) = -15*x(1) + -0.3*x(2);
