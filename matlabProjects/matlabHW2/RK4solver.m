function [tout, yout] = RK4solver(ODEfunIn, solveTime, y0, stepSize)

tVals = solveTime(1):stepSize:solveTime(end);
h=stepSize;
yout = zeros(length(y0),length(tVals));
yout(:,1) = y0;
nSteps = length(tVals) - 1;

%time = length(tVals);
    for stepNums = 1:nSteps
        y_n = yout(:,stepNums);
        t_n = tVals(stepNums);
        
        y_n1 = ODEfunIn(t_n, y_n);
        y_n2 = ODEfunIn(t_n + 0.5*h, y_n+0.5*h*y_n1);
        y_n3 = ODEfunIn(t_n + 0.5*h, y_n+0.5*h*y_n2);
        y_n4 = ODEfunIn(t_n + h, y_n+h*y_n3);
        
        y_nplus1 = y_n+(h/6) * (y_n1 + 2*y_n2 + 2*y_n3 + y_n4);
        yout(:,stepNums+1) = y_nplus1;
    end
tout = tVals;