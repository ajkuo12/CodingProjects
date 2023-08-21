function dydt = exoBootsODEfun(t,y,exoTime,exoTorque,exoAngle,N)
I=y(1);
w_out=y(2);
theta_out=y(3);

b  = 0.001;
R  = 1.03;
J  = 1.01*10^-5;
Kv = 22.305;
Kt = 0.0448;
L  = 2.04*10^-4;
N  = 1;

theta = interp1(exoTime, exoTorque, t);
t_out = interp1(exoTime, exoAngle, t);

e_in = 1*(theta-theta_out)*N;
if e_in > 48
    e_in = 48;
elseif e_in < -48
    e_in = -48;
end

dIdt = (1/L) * (e_in - R*I - (N*w_out)/Kv);
dwout = (Kt*I)/(J*N) - (b*w_out)/J - t_out/(J*N^2);
dthetaout = w_out;
dydt = [dIdt, dwout, dthetaout];
end
