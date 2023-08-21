fprintf('\n');
%% Problem 1b
% In this problem, we are going to use a built-in Matlab differential
% equation solver called ode45 to quickly find specific solutions to an
% initial value problem.

% Define some things to make our plots look nice
fs = 14; % Font size
fn = 'Arial'; %Font name
lw = 2; % Linewidth
primColor = [159  45 201]/ 255; 
secColor  = [82  181 223]/ 255;
terColor  = [223  82  82]/ 255;

% First, we load in any time-dependant values (our ancillary functions).
GRF = load('GRFdata.mat');
GRFvals = GRF.GRFvals;
GRFtime = GRF.GRFtime;
bioAnkAngle = deg2rad(GRF.ankAngle);
ankAngleTime = GRF.GRFtime; % GRF and ankle angle use the same time vector

figure(1); 
subplot(2,1,1); plot(GRFtime, GRFvals, 'linewidth', lw,'color',primColor);
ylabel('Force (N)')
xlabel('Time (s)')
xlim([0 0.35])
grid on
set(gca, 'FontSize', fs, 'FontName', fn, 'linewidth', lw, 'box', 'off') % apply our beautiful formatting

subplot(2,1,2); plot(ankAngleTime, bioAnkAngle, 'linewidth', lw,'color',secColor);
ylabel('Ankle Angle (rad)')
xlabel('Time (s)')
xlim([0 0.35])
grid on
set(gca, 'FontSize', fs, 'FontName', fn, 'linewidth', lw, 'box', 'off') % apply our beautiful formatting
%% Still part 1b
% Next, we define our constants. We are going to do this outside of
% passiveProsODEfun and pass them in, so we can easily modify the values.
b = 1; %**Fill in the damping value here**
k = 100; %**Fill in the spring constant here**
theta_sp = 0; %**Fill in the spring setpoint here**
L = 0.2; %**Fill in foot length here**

% Now, define initial conditions
theta_0 = bioAnkAngle(1); %start at the same initial value as the bio ankle

% Tell the solver how long to run
tSolver = [GRFtime(1), GRFtime(end)]; % we want this to run for the full stance phase.

% This is where we solve the differential equation. Take a look at Matlab's
% ODE45 documentation for a look at how this all works: 
% https://www.mathworks.com/help/matlab/ref/ode45.html
% **You'll need to open up the passiveProsODEfun and add some code there to
% make this work!**
[t, theta] = ode45(@(t,theta) passiveProsODEfun(t,theta,b,k,theta_sp,L,GRFvals,GRFtime),...
                        tSolver, theta_0);

% Plot your results
figure(2)
plot(GRFtime, bioAnkAngle, 'linewidth',lw, 'color', secColor)
hold on
%**Write code here to add your results to the plot, in UCLA blue!**
plot(t, theta, 'linewidth',lw, 'color', primColor)
hold off
xlabel('Time (s)')
ylabel('Angle (rad)')
xlim([0 0.35])
legend({'bio','pros'}, 'box','off')
set(gca, 'FontSize', fs, 'FontName', fn, 'linewidth', lw, 'box', 'off') % apply our beautiful formatting

%% Problem 1c
% How far off are we? We can quantify this with a value called root mean
% square error (RMSE).

% We'll want to interpolate our results to the proper time vector, so we
% can compare directly with the biological ankle angle trajectory.
thetaAdj = interp1(t, theta, GRFtime,'pchip','extrap');

% Now, we find the RMSE
err = bioAnkAngle-thetaAdj;
RMSEankAng = sqrt(mean(err.^2));
fprintf('The RMSE value for part 1c is: %.4f\n',RMSEankAng);

%% Problem 1d
% Now we're going to do a brute-force search of the spring's parameter 
% space, to see if we can improve on our results.

% First, we define the space over which we will search.
kVals = linspace(10,100,20);
theta_spVals = linspace(-0.6,0.1,25); %**Fill this in with code to generate the search range,
                   % as described in the problem text.**
   
% Here, we iterate through all the combinations and calculate RMSE
RMSEs = zeros(length(kVals),length(theta_spVals)); % generate empty storage matrix
for kVal = 1:length(kVals)
    for theta_spVal = 1:length(theta_spVals)
        k_cur = kVals(kVal); % we grab the current values of k and theta_sp
        theta_sp_cur = theta_spVals(theta_spVal);
        
        % Plug those values in for k and theta_sp, and run the solver.
        [t_cur, theta_cur] = ode45(@(t,theta) passiveProsODEfun(t,theta,b,k_cur,...
            theta_sp_cur,L,GRFvals,GRFtime),tSolver,theta_0); 
        
        % Calculate the RMSE associated with these parameters
        %**Write some code to calculate RMSE, just like in part 1c.**
        thetaAdj_cur = interp1(t_cur, theta_cur, GRFtime,'pchip','extrap');
        err1 = bioAnkAngle-thetaAdj_cur;
        RMSEankAng1 = sqrt(mean(err1.^2));
        RMSE_cur = RMSEankAng1; %**Fill this in to set this variable equal to the
                       % RMSE value associated with the current parameters**
        
        % Store the RMSE values
        RMSEs(kVal,theta_spVal) = RMSE_cur;
    end
end

% add the results to a surface
figure(3)
[X,Y] = meshgrid(theta_spVals,kVals);
surf(X,Y,RMSEs);

% Make it pretty
view(3); % look at the surface from the side
colormap hot % change the colors
set(gca, 'FontSize', fs, 'FontName', fn, 'linewidth', lw, 'box', 'off') % apply our beautiful formatting
xlabel('Set Point (rad)')
ylabel('Stiffness (nm/rad)')
zlabel('RMSE (rad)')

% Find the minimum value
minRMSE = min(min(RMSEs));
fprintf('The minimum RMSE value for part 1dis: %.4f\n',minRMSE);

%**Write code here to identify the values of k and theta_sp that produce the
%minimum RMSE. Hint: check out the "min" function.**
%[SOME CODE HERE]
[x,y] = find(RMSEs==minRMSE);
minThetaSP = theta_spVals(y);
minKval = kVals(x);
fprintf('The theta_sp value that produced the minimum RMSE value is: %.4f\n',minThetaSP);
fprintf('The k value that produced the minimum RMSE value is: %.4f\n',minKval);


% Plot the optimized results
%**Write code here to re-solve the differential equation using your
%optimized values for k and theta_sp. Then, plot the results against the
%biological ankle angle, as we did at the end of part 1b.**
[t1, theta1] = ode45(@(t,theta) passiveProsODEfun(t,theta,b,minKval,minThetaSP,L,GRFvals,GRFtime),...
                        tSolver, theta_0);
figure(4)
plot(GRFtime, bioAnkAngle, 'linewidth',lw, 'color', secColor)
hold on
%**Write code here to add your results to the plot, in UCLA blue!**
plot(t1, theta1, 'linewidth',lw, 'color', primColor)
hold off
xlabel('Time (s)')
ylabel('Angle (rad)')
xlim([0 0.35])
legend({'bio','pros'}, 'box','off')
set(gca, 'FontSize', fs, 'FontName', fn, 'linewidth', lw, 'box', 'off')
