%% Problem 3b
% In this problem, we are going to use ODE45 to explore design prospects
% for a robotic tail.

% As before, define some things to make our plots look nice
fs = 14; % Font size
fn = 'Arial'; %Font name
lw = 2; % Linewidth
primColor = [39 116 174]/255; %UCLA Blue
secColor = [255 209 0]/255; %UCLA Gold


% Our first objective is to solve our system numerically, to see how our 
% tail handles to different external torques. Let's start by setting up 
% our system.

% Set the time range and parameter values
t_range = [0 30];
m = []; % **Replace brackets with the correct value.**
L = []; % **Replace brackets with the correct value.**
k = []; % **Replace brackets with the correct value.**
b = []; % **Replace brackets with the correct value.**
J = []; % **Calculate the rotational inertia J here from your other variables.**

% I'll help with initial conditions, because this one is a bit tricky.
theta_0 = []; % **Replace brackets with initial conditions on theta.**
thetaD_0 = []; % **Replace brackets with initial conditions on theta dot.**
y_0 = [theta_0;
       thetaD_0];

% Here, we need to create the external torque trajectories. I've done the 
% time vector and the homogeneous case for you.
torTime = t_range(1):0.01:t_range(2);
T1 = zeros(size(torTime));
T2 = []; % **Replace brackets with the nonhomogeneous external torque.**

% Use ODE45 to simulate the system response. Make sure you put your
% differential equation into robotailODEfun.m first! Hint: you'll need to 
% call ODE45 twice (once for each force input). 

% **ADD CODE HERE TO FIND NUMERICAL SOLUTIONS FOR THE HOMOGENEOUS AND
% NONHOMOGENEOUS CASEs**

% Plot your results on top of each other. Both results should be plotted on
% the same axes in UCLA blue. The homogeneous case should be a dashed
% line, and the non-homogeneous a solid line. Include a legend in the 
% top-right corner, and use our standard formatting throughout. Be sure to 
% label your axes, including units.

figure(1)
% **ADD CODE HERE TO PLOT YOUR RESULTS**


%% Problem 3c

% In this problem, our goal is to simulate system behavior as we change one
% parameter at a time. To get you started, I've done the first one for you.

% Let's test k values that are half the original, the same as the original,
% and twice the original.
testKs = [0.5 1 2]*k;

% Set up some colors that I'll use in my plots.
cols = [primColor;
        0 0 0;
        secColor];
    
% Set up the figure, create a subplot. Note: if subplot is new, try
% entering "help subplot" into the command window.
figure(2); subplot(2,2,1)
hold on    

% Iterate through values of k, simulating and plotting each time
for kNum = 1:length(testKs)
    k_cur = testKs(kNum);
    [t_cur, y_cur] = ode45(@(t,y) roboTailODEfun(t,y,torTime,T2,...
                            k_cur, b, J),t_range, y_0);
    plot(t_cur,y_cur(:,1),'color',cols(kNum,:),'linewidth',lw)
end
hold off

% Apply some formatting and add a legend
legend({['k = ' num2str(testKs(1))],['k = ' num2str(testKs(2))],...
    ['k = ' num2str(testKs(3))]},'box','off','location','northeast')
set(gca,'FontName',fn,'FontSize',fs,'linewidth',lw,'box','off')

% **ADD CODE HERE TO DO THE SAME THING AS ABOVE FOR THE REMAINING
% PARAMETERES b, m, AND L. Don't forget to switch the subplot number!**


% Now, we want to optimize our b value to reduce RMSE. I've added the time
% vector for you, and set up the range of bVals to test. You do the rest.
% Don't forget to interpolate each result to the testTime vector before
% calculating the RMSE.
testTime = 0:0.01:30;

bVals = 0.01:0.02:1;
RMSEs = zeros(size(bVals));

% **ADD CODE HERE TO ITERATE THROUGH THE bVals, CALCULATE RMSE FOR
% EACH, AND STORE THOSE VALUES**

% Now that we've optimized, take a look at the landscape. Plot your RMSEs
% versus the bVals that produced them. Use our standard formatting.
figure(3)
% **ADD CODE HERE TO PLOT YOUR RESULTS.**


% Let's look at the optimized results. Find the minimum value of RMSE, as
% well as the bVal that produced it. Re-run your simulation using this
% bVal, and plot the resultant theta (UCLA Gold) on the same plot with of 
% the nonhomogeneous solution (UCLA Blue) from 3b. Use our standard
% formatting, and label your axes. Include a legend in the top-right
% corner.
%**ADD CODE HERE TO FIND OPTIMIZED RMSE, AND THE bVal THAT PRODUCED IT.**
figure(4)
%**ADD CODE HERE TO PLOT YOUR RESULTS.**

%% Problem 3d

% Time to design a non-linear spring. Make sure yuu've already created
% roboTailODEfunVarK.m before adding code here.

% I've set up the optimization ranges for you
testTime = 0:0.01:30;
t_range = [testTime(1) testTime(end)];
alphas = 3:1:16;
bVals = 1:0.2:5;
RMSEs = zeros(length(alphas),length(bVals));

% Add your code here to optimize across alphas and bVals, calculating RMSE
% at each step. Use your new roboTailODEfunVarK.m to simulate the solutions.
% As above, don't forget to interpolate to testTime before calculating
% RMSE.
% **ADD CODE HERE AS DESCRIBED.**

% Plot your results on a surface. Use the same formatting we used in
% Matlab Problem 1d (don't forget to update your axis labels).
figure(5)

% Find the optimized RMSE, and the values of alpha and bVal that produced
% it.
% **ADD CODE HERE.**
    
% Rerun your numerical simulation using the optimized alpha and b. Plot the
% results of this optimized non-linear spring (black) on a single plot with
% your optimized results from part 3c (UCLA Gold) and your original solution
% to the non-homogeneous equation in part 3b (UCLA Blue). Use our standard 
% formatting, and don't forget to include a legend (put it in the 
% bottom-right corner).
% **ADD CODE HERE TO RE-RUN YOUR SIMULATION WITH OPTIMIZED PARAMETERS.** 
figure(6)
% **ADD CODE HERE TO PLOT YOUR RESULTS, AS DESCRIBED ABOVE.** 


% Rerun your numerical simulations for the homogeneous case. Do this for 
% the the optimized b from part 3c (using roboTailODEfun.m), and again for 
% the optimized alpha and b from 3d (using roboTailODEfunVarK.m).  Plot the
% results on a single plot with the homogeneous solution from Problem 3b,
% using the same colors as in Figure 6. Use our standard 
% formatting, and don't forget to include a legend (put it in the 
% bottom-right corner).
% **ADD CODE HERE TO RE-RUN YOUR SIMULATIONS FOR THE HOMOGENEOUS EQUATION.** 
figure(7)
% **ADD CODE HERE TO PLOT YOUR RESULTS, AS DESCRIBED ABOVE.** 