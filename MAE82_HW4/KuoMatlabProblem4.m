% Set Format Values
fs = 14;                           %Font size
fn = 'Arial';                      %Font name
lw = 2;                            %Linewidth

primColor = [159  45 201]/ 255; 
secColor  = [82  181 223]/ 255;
terColor  = [223  82  82]/ 255;

% Implicit Solution from 2b
impSolFun = @(a,t) (0.05*(log(a)+(3*a)))+t+((3.4/pi)*cos(0.5*pi*t))-0.8535;  
tImplicit = 0.75:0.001:2;
aImplicit = zeros(size(tImplicit));
uImplicit = zeros(size(tImplicit));
for tNum = 1:length(tImplicit)
    t_cur = tImplicit(tNum);
    afun = @(a) real(impSolFun(a,t_cur));
    a_guess = 0.01;
    a_cur = fzero(afun,a_guess);
    aImplicit(tNum) = a_cur;
    uFunction = 1.7*a_cur*sin(0.5*pi*t_cur);
    uImplicit(tNum) = uFunction;
end

% Set Fixed Values
a_0 = 0.01;
t_range = [0,2];
stepSizes = [0.1, 0.075, 0.05, 0.01, 0.005];
figure(1)

% Plotting First Subplot
p1 = subplot(1,2,1);
plot(tImplicit,aImplicit,'k','linewidth',lw);
legendIDs = cell(1,length(stepSizes)+1);
legendIDs{1} = 'implicit solution';
hold on
ctr = 1;

% Plotting Euler Solutions
for stepSizeNum = 1:length(stepSizes)
    curStepSize = stepSizes(stepSizeNum);
     [t_cur, a_cur] = eulerSolver(@(t,a) muscleActODEfun(t,a),...
                        t_range, a_0, curStepSize);
     plot(t_cur, a_cur, 'linewidth',lw-0.5)
     ctr = ctr + 1;
     legendIDs{ctr} = ['step size = ' num2str(curStepSize) ' s'];
    
end

% Plot Formatting
ylim([0 1.2])
hold off
title('Euler');
legend(legendIDs,'location','northwest','box','off')
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')

% Plotting Second Subplot
p2 = subplot(1,2,2);
plot(tImplicit,aImplicit,'k','linewidth',lw);
legendIDs = cell(1,length(stepSizes)+1);
legendIDs{1} = 'implicit solution';
hold on
ctr = 1;

% Plotting RK4 Solutions
for stepSizeNum = 1:length(stepSizes)
    curStepSize = stepSizes(stepSizeNum);
     [t_RK4, a_RK4] = RK4Solver(@(t,a) muscleActODEfun(t,a),...
                        t_range, a_0, curStepSize);
     plot(t_RK4, a_RK4, 'linewidth',lw-0.5)
     ctr = ctr + 1;
     legendIDs{ctr} = ['step size = ' num2str(curStepSize) ' s'];
    
end

% Plot Formatting
ylim([0 1.2])
hold off
title('RK4');
legend(legendIDs,'location','northwest','box','off')
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')