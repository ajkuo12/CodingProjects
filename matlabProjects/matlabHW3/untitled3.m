A = [1,2,3,1,2,3,1];
for x = 1:4
losoer = min(A);
fprintf('%1.0f\n',losoer);
A(A == losoer) = [];
fprintf('%1.0f\n',A);
fprintf('\n');
end