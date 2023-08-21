% Script - Homework 1
% The function of this script is to solve two types of variable dependent
% problems when prompted. The user has the choice of which problem and
% which variables to input. 
% ---Aaron Kuo 305170284---------------------------------------------------

Question = input('Which question problem would you like to solve (1 or 2):\n');
fprintf('\n')
switch Question
    
case 1
%Problem 1: Oblate Spheroid Calculations
%The function of this script section is to calculate the surface area of
%an oblate spheroid using two user-specfied radii.
%-------------------------------------------------------------------------
    % Radius Input
r1 = input('Enter value for r1:\n');
r2 = input('Enter value for r2:\n');
gamma = acos(r2/r1);
fprintf('\n')
    % Error Checks
if r2>r1 
    error('Error. r1 must be greater than r2');
else
    % Calculate Surface Area of an Oblate Spheroid
    area = 2*pi*(r1^2 + (((r2^2)/sin(gamma)) * log((cos(gamma))/(1-sin(gamma)))));
    fprintf('%s%10.1f\n','The surface area of an oblate spheroid is: ',area);
    % Calculate approximation
    approximation = 4*pi*(((r1+r2)/2)^2);
    fprintf('%s%10.1f\n','The approximation of the surface area of an oblate spheroid is: ',approximation);
end
%-------------------------------------------------------------------------

case 2
% Problem 2: Neighbor Identification
% The function of this script section is to identify neighboring cells in a
% 2D matrix given a user-specified cell.
%-------------------------------------------------------------------------
    % Value Input
M = input('Enter value for M:\n');
N = input('Enter value for N:\n');
P = input('Enter value for P:\n');
fprintf('\n')
    % Error Checks
if P/round(P) == 0 || M/round(M) == 0 || N/round(N) == 0
    error('Error. Please enter an integer for M, N, P');
end
if M <= 2 || N <= 2
    error('Error. Please enter a value greater than 2 for M, N');
end
if P < 1 || P > M * N
    error('Error. Please enter a value of P within the range of 1 to M*N');
end
    % Inputs for Neighbor Cells
P_Up         = P - 1;
P_Down       = P + 1;
P_Left       = P - M;
P_Right      = P + M;
P_UpperLeft  = P - M - 1;
P_LowerLeft  = P - M + 1;
P_UpperRight = P + M - 1;
P_LowerRight = P + M + 1;
    % Solving for Neighbor Cells
if     P == 1
    neighbors = [P_Down P_Right P_LowerRight];
elseif P == M
    neighbors = [P_Up P_Right P_UpperRight];
elseif P == M * (N-1) + 1
    neighbors = [P_Left P_Down P_LowerLeft];
elseif P == M * N
    neighbors = [P_Up P_Left P_UpperLeft];
%Left Side
elseif P > 1 && P < M 
    neighbors = [P_Up P_Down P_Right P_UpperRight P_LowerRight];
%Right Side
elseif P > M * (N-1) + 1 && P < M * N
    neighbors = [P_Up P_Down P_Left P_UpperLeft P_LowerLeft];
%Top Side
elseif (mod(P,M) == 1) && (P~=1) && (P~=(M*(N-1)+1))
    neighbors = [P_Left P_Right P_Down P_LowerLeft P_LowerRight];
%Bottom Side
elseif (mod(P,M) == 0) && (P~=M) && (P~=M*N)
    neighbors = [P_Left P_Right P_Up P_UpperLeft P_UpperRight];  
else 
    neighbors = [P_Left P_Right P_Up P_Down P_UpperLeft P_UpperRight P_LowerLeft P_LowerRight];
end
% Prints Neighbors
fprintf('Cell ID:  ')
disp(P);
fprintf('Neighbors:')
disp(sort(neighbors));

end 
        
    
