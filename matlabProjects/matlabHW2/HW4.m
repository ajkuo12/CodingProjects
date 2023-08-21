% In this problem, we are going to use several numerical tools to find a
% solution to a complex initial value problem.

% As before, define some things to make our plots look nice
fs = 14; % Font size
fn = 'Arial'; %Font name
lw = 2; % Linewidth
primColor = [39 116 174]/255; %UCLA Blue
secColor = [255 209 0]/255; %UCLA Gold


% First, we want to numerically solve our implicit solution to the
% differential equation. Hint: the ln function in matlab is "log()"
impSolFun = @(a,t) (0.05*(log(a)+(3*a)))+t+((3.4/pi)*cos(0.5*pi*t))-0.8535;  % **put F_imp in place of the brackets, and delete 
                        % the brackets. Do not include the "=0" part of
                        % your eqn - only enter the left hand side. The
                        % only variables in this equation should be a and
                        % t**

% For this part, we're only interested in looking at a limited time window
t_range = 0.75:0.001:2;
a_0 = 1;
stepSizeVals = [0.1, 0.075, 0.01, 0.005];
hold on
ctr = 1;

for stepSizeNum = 1:length(stepSizeVals)
    curStepSize = stepSizeVals(stepSizeNum);
[t_euler, a_euler] = eulerSolver(@(t,a) muscleActODEfun(t,a),...
                        t_range, a_0, curStepSize);
[t_RK4, a_RK4] = RK4solver(@(t,a) muscleActODEfun(t,a),...
                        t_range, a_0, curStepSize);

end


figure(2); subplot(2,2,1)
plot(t_euler,a_euler, 'linewidth', lw-0.5);
ylim([0 1.2]);
xlim([0 2]);

hold off
ylim([0 1.2]);
xlabel('Time in seconds');
grid on
title('Kuo Problem 2B','Fontsize',20);