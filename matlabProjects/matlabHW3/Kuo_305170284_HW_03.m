% Script - Homework 3
% The function of this script is to solve two types of variable dependent
% problems when prompted. The user has the choice of which problem and
% which variables to input.
% -//Aaron Kuo 305170284//-------------------------------------------------

Question = input('Which question problem would you like to solve (1 or 2):\n');
fprintf('\n')
switch Question
    
       case 1
           
%Problem 1: The Pendulum Physics Problem
%The function of this script section is to observe the many characteristics
%of a physical pendulum, for example, its kinematics. There will be two
%methods used to calculate the results and both versions will be printed
%out in the form of a graph.
%-------------------------------------------------------------------------
% Value Inputs
        penLength    = input('Enter pendulum length:\n');
        timestep     = input('Enter timestep duration:\n');
% Error Checks
        if penLength <= 0 || timestep <= 0 
        error('Error. Inputted values cannot be equal or less than 0');
        end
% Set Values
        finalTime    = 20;
        interval     = finalTime/timestep;
        time         = 1:timestep:20;
        arraySize    = length(time);
% Set Arrays
        tx           = linspace(0,20,interval+1);
        Position     = zeros(1,arraySize);
        Velocity     = zeros(1,arraySize);
        Acceleration = zeros(1,arraySize);
        Energy       = zeros(1,arraySize);
        Position(1)  = pi/3;
        
 % Explicit Euler
 % --------------        
 for k= 1:1:interval
       Position(k+1)     = Position(k) + (timestep * Velocity(k));
       Velocity(k+1)     = Velocity(k)-(9.81/penLength * sin(Position(k)))*timestep;
       Acceleration(k+1) = (-9.81/penLength) * sin(Position(k));
       Energy(k+1)       = (9.81 * penLength * (1-cos(Position(k)))+((0.5) * (penLength*Velocity(k)^2)));
 end
        figure;
        % Plots
        plot(tx, Position,'r', tx, Velocity,'g--', tx, Acceleration,'y-.o');
            title   ({'Explicit Method','Angular Position, Angular Velocity, and Angular Acceleration vs. Time'});
            xlabel  ('Time in seconds')
            ylabel  ('Position, Velocity, Acceleration (radians')
            legend  ('Pendulum Position','Angular Velocity','Angular Acceleration')
        figure; 
        plot(tx, Energy,'b--o');
            title   ({'Explicit Method','Total Energy of Pendulum vs. Time'}) 
            xlabel  ('Time in seconds')
            ylabel  ('Total Energy in Joules')
            legend  ('Total Energy')
           
 % Implicit Euler
 % --------------
 for k = 1:1:interval
       Position(k+1)       = Position(k) + timestep*Velocity(k+1);
       Velocity(k+1)       = Velocity(k) - (9.81/penLength*sin(Position(k+1))) * timestep;
       Acceleration(k+1)   = (-9.81/penLength) * sin(Position(k));
       height              = 1-cos(Position(k));
       Energy(k+1)         = (9.81 * penLength * height)+((0.5)*(penLength*Velocity(k)^2));
 end
        % Plots
        figure;
        plot(tx,Position,'r', tx,Velocity,'g--',tx,Acceleration,'y-.o');
            title    ({'Implicit Method','Angular Position, Angular Velocity, and Angular Acceleration vs. Time'});
            xlabel   ('Time in seconds)')
            ylabel   ('Position, Velocity, Acceleration (radians)')
            legend   ('Pendulum Position','Angular Velocity','Angular Acceleration')
        figure; 
        plot(tx, Energy,'b--o');
            title    ({'Implicit Method','Total Energy of Pendulum vs. Time'}) 
            xlabel   ('Time in seconds')
            ylabel   ('Total Energy in Joules')


case 2
    
%Problem 2: DNA Analysis
%The function of this script section is to identify certain codons
%(three-based segments) in a given section of a DNA strand. The script will
%be able to specify listed strands and its starting and ending point. All
%statistics and results will be printed below.
%-------------------------------------------------------------------------

% Setup Variables
    load('chr1_sect.mat');
    Bases = length(dna);
    StopCodonTAA = 0;
    StopCodonTAG = 0;
    StopCodonTGA = 0;
    Segments = 0;
    startPoint = 0;
% DNA conversion
        A = 1;
        C = 2;
        G = 3;
        T = 4;
% Begin for loop calculations
    for k = 1 : 3 : Bases - 2
        if startPoint == 0
            if dna(k) == A && dna(k+1) == T && dna(k+2) == G
            startPoint = k;
            Segments = Segments + 1;
            end
        else
            if dna(k) == T && dna(k+1) == A && dna(k+2) == A || dna(k) == T && dna(k+1) == A && dna(k+2) == G || dna(k) == T && dna(k+1) == G && dna(k+2) == A
            if dna(k) == T && dna(k+1) == A && dna(k+2) == A
            StopCodonTAA = StopCodonTAA + 1;
            end
            if dna(k+1) == A && dna(k+2) == G
            StopCodonTAG = StopCodonTAG + 1;
            end
            if dna(k+1) == G && dna(k+2) == A
            StopCodonTGA = StopCodonTGA + 1;
            end
            stopPoint = k;
            length(Segments) = stopPoint - startPoint + 3;
            startPoint = 0;
            end
        end
    end
% Statistics Calculations
Mean = mean(length);
Max  = max(length);
Min  = min(length);
Percentage = ((sum(length))/Bases) * 100;
%Print All Results
fprintf('Total Protein-Coding Segments: %.2f\n',Segments);
fprintf('Average Length:     %16.2f\n',Mean);
fprintf('Maximum Length:    %16d\n',Max);
fprintf('Minimum Length: %16d\n',Min);
fprintf('Percentage of DNA used:        %4.2f%%\n',Percentage);
fprintf('Amount of TAA codons:    %10d\n', StopCodonTAA);
fprintf('Amount of TAG codons:    %10d\n', StopCodonTAG);
fprintf('Amount of TGA codons:    %10d\n', StopCodonTGA);
end