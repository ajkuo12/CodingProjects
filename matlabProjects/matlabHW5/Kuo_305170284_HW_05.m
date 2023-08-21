% Script - Homework 5
% The function of this script is to solve two types of variable dependent
% problems when prompted. The user has the choice of which problem and
% which variables to input. 
% Aaron Kuo 305170284------------------------------------------------------

Question = input('Which question problem would you like to solve (1 or 2):\n');
fprintf('\n')
switch Question
    
    case 1
%Problem 1: The Shared Birthdays Problem
%The purpose of this script is to solve a Monte Carlo simulation to
%determine how many have to be added into a group before two share the same
%birthday week. This code will run this simulation 10,000 times to
%calculate and print the average amount of people as well as plot a
%histogram of the results.
%--------------------------------------------------------------------------
    %Set up Arrays
trialSpace = zeros(1,10000);
days = zeros(1,365);
    %Begin for loop for 10,000 trials    
for trials = 1:10000 
    %Begin for loop for randomization of date selection
    for k = 1:53
        days(k) = randi(365);
        for b = (1 : k-1)
            if (abs(days(b) - days(k)) < 7)
            trialSpace(trials) = k;
            end
            if (abs(days(b) - 365 - days(k)) < 7) || (abs(days(k)- 365 - days(b)) < 7)
            trialSpace(trials) = k;   
            end
        end
     %End loop once match is found
        if trialSpace(trials) >  0
        break
        end
    end
end
    %Calculate and print the median of all trials
        x = median(trialSpace);
        fprintf('Median Number of People = %2i\n', x);
    %Plot histogram with results
        histogram(trialSpace);
        title('Histogram for Shared Birthday Week Problem')
        xlabel('Number of people added per group')
        ylabel('Number of Trials')


    case 2 
%Problem 2: Random Walk Collisions
%The purpose of this script is to model the probabilites of two particles
%colliding in a grid. There are two scenarios present in this case, one
%where one particle is moving while the other remain stationary, and one
%where both particles are moving. The script will run each scenario 5000
%times based on which scenario is chosen by the user and print the average
%amount of steps needed for a collision. 
%-------------------------------------------------------------------------
fprintf('Scenario 1: One particle moving, one fixed\n');
fprintf('Scenario 2: Both particles are moving\n');
fprintf('\n')
SubQuestion = input('Which scenario would you like to run? 1 or 2?\n');

fprintf('\n');
switch SubQuestion
case 1    
%Scenario 1 : One moving, one stationary
%-------------------------------------------------------------------------
%Set up grid 
 figure(1)
 hold on
 grid on 
 xlim([-5 5])
 ylim([-5 5])
 axis equal 
 set(gca,'xtick', -5 : 1 : 5)
 set(gca,'ytick', -5 : 1 : 5)
%Set up arrays
numberOfTrials = 5;
numberOfMoves = zeros(1,numberOfTrials);
%Begin loop of steps
for k = 1 : numberOfTrials
%Initial positions of both particles
xa = -5;
ya =  0;
xb =  5;
yb =  0;
collisions = 0;
moves      = 0;
%While loop continues as long as there are no collisions and steps are
%under 1000
           while collisions == 0 && moves < 1000
                randomMoveA = rand;
                DrawRectAK(xa,ya,1,1,'b')
                DrawRectAK(xb,yb,1,1,'r')
                xa = moveAX(xa,randomMoveA);
                ya = moveAY(ya,randomMoveA);
                moves = moves + 1;
                DrawRectAK(xa,ya,1,1,'b')
                DrawRectAK(xb,yb,1,1,'r')
                if xa == xb && ya == yb
                collisions = 1;
                end
            end
            numberOfMoves(k) = moves;
end
%Print results
results = median(numberOfMoves);
fprintf('Median = %2.2f\n', results);
%---------------------------------------------------------
case 2
%Scenario 2: Both Particles Moving
%--------------------------------------------------------
%Set up Grid
 figure(1)
 hold on
 grid on 
 xlim([-5 5])
 ylim([-5 5])
 axis equal 
 set(gca,'xtick', -5 : 1 : 5)
 set(gca,'ytick', -5 : 1 : 5)
%Set up Arrays
numberOfTrials = 10;
numberOfMoves = zeros(1,numberOfTrials);
%For loop begins for steps
for k = 1 : numberOfTrials
%Initial positions of both particles
xa = -5;
ya =  0;
xb =  5;
yb =  0;
collisions = 0;
moves      = 0;
%While loop continues as long as there are no collisions and steps are
%under 1000
           while collisions == 0 && moves < 1000
         randomMoveA = rand;
         randomMoveB = rand;
         DrawRectAK(xa,ya,1,1,'b')
         DrawRectAK(xb,yb,1,1,'r')
                xa = moveAX(xa,randomMoveA);
                ya = moveAY(ya,randomMoveA);
                xb = moveAX(xb,randomMoveA);
                yb = moveAY(yb,randomMoveA);
                xa = moveAX(xa,randomMoveB);
                ya = moveAY(ya,randomMoveB);
                xb = moveAX(xb,randomMoveB);
                yb = moveAY(yb,randomMoveB);
                moves = moves + 1;
                DrawRectAK(xa,ya,1,1,'b')
                DrawRectAK(xb,yb,1,1,'r')
                if xa == xb && ya == yb
                    collisions = 1;
                end
            end
            numberOfMoves(k) = moves;
end
%Print Results
        results = median(numberOfMoves);
        fprintf('Median = %2.2f\n', results);
end
end

