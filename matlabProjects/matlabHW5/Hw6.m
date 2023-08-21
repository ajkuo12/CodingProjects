%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Homework 3 Script 
%
%   Author: Kyle Kaihong Hu
%     Date: 4/24/2019
%      UID: 104707541
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%  Clear Cache
clear all
close all
clc
%% Switch statement to call for which problem to solve
fprintf('please uncomment line 148, 149, 158, 159 and comment the for-loop in problem 2 to display the graph of the blocks movement\n')
%Tell user which number corresponds to which problem 
fprintf('Input 1 for problem 1 and 2 for problem 2\n');

%input a number to call for which problem to solve 
x = input ('Enter a number:');

%Error check for input number 
if (x~=1) && (x~=2)
    fprintf('Error: input number can only be 1 or 2')
    fprintf('Please rerun script.\n')
return
end

%Switch Statement to call for problem
switch (x)
    case 1
%Set up vector space for the for loop
Trials = zeros(1,1*10^4);
%Set up for-loop with 10,000 trials
for k = 1:1*10^4
%Create vector space for 365 days, which are the possible outcomes of
%birthday
y = zeros(1,365);
%Define variables for while-loop use
z=0;
iter = 0;
%While loop to detect birthdays that are within the 7 day difference range
while z <=1
    %Generated randomized number between 1 and 365
    date = randi(365);
    %Increase iteration count by one for every generated radomized number
    iter = iter +1;
    %Fill the generated number value cell in the vector space with number 1
    y(date)=1;
    %Add up all the numbers with a value difference of 6 to the left and
    %right of the randomized number.
    if date > 6 && date < 360 
    z = sum(y(date-6:date+6));
    end 
    %Conditions to consider special case at the beginning and end of the
    %vector space
    if date == 1
    z = sum(1:y(date+6))+sum(y(360:365));
    end
    if date == 2
    z = sum(1:y(date+6))+sum(y(361:365));
    end 
    if date == 3
    z = sum(1:y(date+6))+sum(y(362:365));
    end 
    if date == 4
    z = sum(1:y(date+6))+sum(y(363:365));
    end 
    if date == 5
    z = sum(1:y(date+6))+sum(y(364:365));
    end 
    if date == 6
    z = sum(1:y(date+6))+sum(y(365:365));
    end 
    if date == 360
    z = sum(y(date-6):y(365))+sum(y(1:1));
    end 
    if date == 361
    z = sum(y(date-6):y(365))+sum(y(1:2));
    end 
    if date == 362
    z = sum(y(date-6):y(365))+sum(y(1:3));
    end 
    if date == 363
    z = sum(y(date-6):y(365))+sum(y(1:4));
    end 
    if date == 364
    z = sum(y(date-6:365))+sum(y(1:5));
    end 
    if date == 365
    z = sum(y(date-6):y(365))+sum(y(1:6));
    end 
end 
%Fill the trials vector space with the number of iteration
Trials(k)= iter; 
end 
%Calculate the median number of trials
t=median(Trials);
%Create histogram using the trials vector space
histogram(Trials);
%Output the result 
fprintf('Median Number of People =%d',t);

    case 2 
%%%%%%%%%%%%%
% Draw Rectangle graph
%%%%%%%%%%%%%

%Draw out the grids of the figure
figure(1)
hold on
grid on 
%Set the limit boundary of the grid
xlim([-7 7])
ylim([-7 7])
axis equal 
%insert tick marks on the grid
set(gca,'xtick', -5:1:5)
set(gca,'ytick', -5:1:5)

%Define variables for whileloop and forloop use
%the probability of each movement 
p=0.2;
%Have 5,000 trials
samplesize=5000;
%Create vector space to store the numbers of movement in trials
totnumbermoves=zeros(1,samplesize);
%the length and width of the draw rectangular function
L=1;
W=1;

%Forloop to test the while-loop with the given number of trials
for k=1:samplesize
    %Define the initial x and y values of the block
    x1=-5;
    y1=0;
    x2=5;
    y2=0;
    %Define variables for while-loop use
    nummoves=0;
    collision=0;
    %Whileloop stops when the two blocks colliade or when the movement
    %exceeds 1,000
while collision==0&&nummoves<1000
        %Generate randomized number for functions to determine how the two block moves
        shift1=rand;
        shift2=rand;
        %Functions that create the block in the grid
        DrawRect(x1,y1,L,W,'r')
         DrawRect(x2,y2,L,W,'b')
        %Functions that determine which direction the block moves
        x1 = movex(shift1,x1,p);
        y1 = movey(shift1,y1,p);
        x2 = movex(shift2,x2,p);
        y2 = movey(shift2,y2,p);
        %Count the number of movements
        nummoves=nummoves+1;
        %Functions that redraw the block in the grid after new x and yvalues are found 
         DrawRect(x1,y1,L,W,'r')
         DrawRect(x2,y2,L,W,'b')
        %if condition to determine if two blocks have collided 
        if x1==x2 && y1==y2
            collision=1;
        end 
        %Redefine variables for next while-loop
        x1=x1;
        y1=y1;
        x2=x2;
        y2=y2;
end 
%Fill in the number of movements back into the vector space
totnumbermoves(k)=nummoves;
end
%Calculate the median number of movement in the 5,000 trials
h=median(totnumbermoves);
%Output the results
fprintf('Median=%d',h)

%%%%%%%%%%%%%%%%%%%%%%%
% For part c and d (one moving point and one fixed point)
%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Use comment function to uncomment the comments below to test the number
% of trials.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% To show the figure, first uncomment the DrawRect Function and use comment
% function to disable forloop or else it is going to take forever
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% figure(1)
% hold on
% grid on 
% xlim([-7 7])
% ylim([-7 7])
% axis equal 
% set(gca,'xtick', -5:1:5)
% set(gca,'ytick', -5:1:5)
% 
% p=0.2;
% samplesize=5000;
% totnumbermoves=zeros(1,samplesize);
% L=1;
% W=1;
% 
% for k=1:samplesize
%     x1=-3;
%     y1=0;
%     x2=3;
%     y2=0;
%     nummoves=0;
%     collision=0;
% while collision==0&&nummoves<1000
%         shift1=rand;
%         shift2=rand;
% %         DrawRect(x1,y1,L,W,'r')
% %         DrawRect(x2,y2,L,W,'b')
%%%       Pause(.01);
%         x1 = movex(shift1,x1,p);
%         y1 = movey(shift1,y1,p);
%         nummoves=nummoves+1;
% %         DrawRect(x1,y1,L,W,'r')
% %         DrawRect(x2,y2,L,W,'b')
%         if x1==x2 && y1==y2
%             collision=1;
%         end 
%         x1=x1;
%         y1=y1;
%         x2=x2;
%         y2=y2;
% end 
% totnumbermoves(k)=nummoves;
% end
% h=median(totnumbermoves);
% fprintf('Median=%d',h)
end 
        