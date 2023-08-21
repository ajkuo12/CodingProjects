% Script - Homework Extra Credit
% The function of this script is to solve two types of variable dependent
% problems when prompted. The user has the choice of which problem and
% which variables to input.
% -//Aaron Kuo 305170284//-------------------------------------------------


%Extra Credit: The Ranked-Choice Vote
%This script aims to model a ranked voting system where participants rank
%arbitrary values from 1 to 8, 1 begin the most favorable. The value with
%over 50% of the votes wins. For each round, if one winner does not emergt,
%the lowest performing candidate is eliminated and the second most favored
%values of each participant is considered. The script stops when a winner
%is found and prints the results
%--------------------------------------------------------------------------

load('votes1.mat');
%Arrays for Vote Win/Loss
Candidates = (1:8);
Losers     = zeros(1,8);
VoteRank   = zeros(1,8);
rows       = length(votes(:,1));
columns    = length(votes(1,:));
%Number of Votes
tally1 = 0;
tally2 = 0;
tally3 = 0;
tally4 = 0;
tally5 = 0;
tally6 = 0;
tally7 = 0;
tally8 = 0;
Finish = 0;
%Display Candidates
fprintf('    Candidates:');
fprintf('%5.0f ',Candidates);
%Begin Loops
if Finish == 0
for w = 1:8
for j = 1 : 8
    B = votes(:,j);
    Voters       = length(votes(:,j));
    MajorityVote = Voters / 2;
    losingCandidate = 0;
    sorted = sort(votes);
    for m = 1 : length(votes(:,j))
        % Count number of votes for each value
        if B(m) == 1
            tally1 = tally1 + 1;
        end
        if B(m) == 2
            tally2 = tally2 + 1;
        end
        if B(m) == 3
            tally3 = tally3 + 1;
        end
        if B(m) == 4
            tally4 = tally4 + 1;
        end
        if B(m) == 5
            tally5 = tally5 + 1;
        end
        if B(m) == 6
            tally6 = tally6 + 1;
        end
        if B(m) == 7
            tally7 = tally7 + 1;
        end
        if B(m) == 8
            tally8 = tally8 + 1;
        end
    end
    %Tally up results of the round
    VoteRank(1) = tally1;
    VoteRank(2) = tally2;
    VoteRank(3) = tally3;
    VoteRank(4) = tally4;
    VoteRank(5) = tally5;
    VoteRank(6) = tally6;
    VoteRank(7) = tally7;
    VoteRank(8) = tally8;
    
    %Determine and assign eliminated value for future
    for x = 1:8
        if Losers(x) == 1
            VoteRank(x) = 0;
        end
    end
    
    %Determine winning and losing value
    loser = min(VoteRank);
    winner = max(VoteRank);
    for q = 1:8
        if VoteRank(q) == loser
            losingCandidate = q;
        end
        if VoteRank(q) == winner
            winningCandidate = q;
        end
    end
    Losers(q-1) = 1;
% Print Results of each round

fprintf('\n');
fprintf('Round %1.0f Totals: ', j);
fprintf('%5.0f ',VoteRank);
% Conditions to end or continue script
if max(VoteRank) > MajorityVote
    Finish = Finish + 1;
    fprintf('\n');
    fprintf('The Winning Candidate is: %1.0f\n',winningCandidate);
    return
else
    
    removeCandidate(votes,losingCandidate);
end
end
end
end


   
        
    

