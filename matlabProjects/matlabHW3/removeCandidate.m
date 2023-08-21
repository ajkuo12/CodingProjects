function [votes] = removeCandidate (votes,losingCandidate)
%The function of this script is to remove a losing candidate from the
%matrix "votes" by assigning all values equal to the losing candidate with 0.
votes(votes == losingCandidate) = [];
end