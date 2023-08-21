function [tout, yout] = exoBootsODEfun(ODEfunIn, solveTime, y0, stepSize) % This in an implementation of euler's method. Inputs are as follows: % - ODEfunIn is a function handle to a differential equation
% - solveTime is the range of interest of the independent variable
% - y0 is the initial condition
% - stepSize is step size for the solver, in the same units as solveTime
% Define the values of t at which we will evaluate our function
tVals = solveTime(1):stepSize:solveTime(2); % ** Fill in code here to generate a vector of the relevant
% t points, using your range of interest and step size. % Allocate an array
y_a = zeros(length(y0));
yout = zeros(y_a,size(tVals));

% Start us off at our initial conditions
yout(:,1) = y0;
% How many steps will I be taking?
nSteps = length(tVals)-1; % ** Fill in code here to determine how many steps you'll take.
% Keep in mind that we are already starting at y_0.**
for stepNum = 1:nSteps
% Grab the last value of y and current value of t (we'll need this).
y_n = yout(stepNum); 
t_n = tVals(stepNum);
% Calculate dydt using the ODE function you passed in dydt = ODEfunIn(t_n,y_n);
kn1 = ODEfunIn(t_n,y_n);
kn2 = ODEfunIn(t_n + stepSize/2, y_n + kn1*stepSize/2);
kn3 = ODEfunIn(t_n + stepSize/2, y_n + kn2*stepSize/2);
kn4 = ODEfunIn(t_n + stepSize,y_n + stepSize*kn3);
% Calculate y_nplus1 using euler's method, and store it in your output
% array
y_nplus1 = y_n+stepSize*(kn1+2*kn2+2*kn3+kn4)/6;
yout(:,stepNum+1) = y_nplus1;%** Fill this in according to RK4's formula.** yout(stepNum+1) = y_nplus1;
end
% We just rename this to be more intuitive as output
tout = tVals;