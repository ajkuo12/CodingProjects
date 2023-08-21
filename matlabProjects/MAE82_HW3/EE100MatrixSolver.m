
syms x y z
eqn1 = 2*x + y + z == 2;
eqn2 = -x + y - z == 3;
eqn3 = x + 2*y + 3*z == -10;
[A,B] = equationsToMatrix([eqn1, eqn2, eqn3], [x, y, z]);
X = linsolve(A,B);
disp(X);

syms a b 
eeqn1 = 7*a + (-5)*b == 40;
eeqn2 = (-5*a) + 6*b == 30;
[C,D] = equationsToMatrix([eeqn1, eeqn2], [a, b]);
Y = linsolve(C,D);
disp(Y);