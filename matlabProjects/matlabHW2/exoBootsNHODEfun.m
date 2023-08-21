function dydt = exoBootsNHODEfun(t,y,exoTime,exoTorque,exoAngle,N)
I = y(1);
w_out = y(2);
theta_out = y(3);

b  = 0.001;
R  = 1.03;
J  = 1.01*10^-5;
Kv = 22.305;
Kt = .0448;
L  = 2.04*10^-4;

theta_des = interp1(exoTime, exoTorque, t);
T_out = interp1(exoTime, exoAngle, t);

e_in = 5*(theta_des - theta_out)*N;
if e_in > 48
    e_in = 48;
elseif e_in <-48
    e_in = -48;
end

dI_dt = (1/L) * (e_in - R*I - (N*w_out)/Kv);
dw_out_dt = (Kt*I)/(J*N) - (b*w_out)/J - T_out/(J*N^2);
dtheta_out_dt = w_out;

dydt = [dI_dt, dw_out_dt, dtheta_out_dt];