function [tout, yout] = eulerSolver(ODEfunIn, solveTime, y0, stepSize)
% This in an implementation of euler's method. Inputs are as follows:
% - ODEfunIn is a function handle to a differential equation
% - solveTime is the range of interest of the independent variable
% - y0 is the initial condition
% - stepSize is step size for the solver, in the same units as solveTime

% Define the values of t at which we will evaluate our function
tVals = solveTime(1):stepSize:solveTime(end); % ** Fill in code here to generate a vector of the relevant
            % t points, using your range of interest and step size.

% Allocate an array
yout = zeros(size(tVals));

% Start us off at our initial conditions
yout(1) = y0;

% How many steps will I be taking?
nSteps = length(tVals)-1; % ** Fill in code here to determine how many steps you'll take.
             % Keep in mind that we are already starting at y_0.**
             
for stepNum = 1:nSteps
    
    % Grab the last value of y and current value of t (we'll need this).
   
    k1 = -2*yout(stepNum);
    y1 = yout(stepNum) + k1 * stepSize/2;
    k2 = -2 * y1;
    y2 = yout(stepNum) + k2 * stepSize/2;
    k3 = -2 * y2;
    y3 = yout(stepNum) + k3 * stepSize/2;
    k4 = -2 * y3;
    yout(stepNum + 1) = yout(stepNum) + (k1+2*k2+2*k3+k4)*stepSize/6;
end

% We just rename this to be more intuitive as output
tout = tVals;