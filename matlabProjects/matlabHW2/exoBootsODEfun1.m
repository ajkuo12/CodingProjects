function dx_dt = exoBootsODEfun1(t,y)

b  = 0.001;
R  = 1.03;
J  = 1.01*10^-5;
Kv = 22.305;
Kt = .0448;
L  = 2.04*10^-4;
N  = 1;

I = y(1) ;
w_out = y(2);

dIdt = ((-1*R*I) + ((-1*N*w_out)/Kv))/L;
dw_out = ((Kt * I/N) - (w_out*b))/J;
dx_dt = [dIdt; dw_out];
end