function da_dt = muscleActODEfun(t,a)


da_dt = (1.7*a*sin(0.5*pi*t)-a)/(0.05+0.15*a); %**Fill in your differential equation from part a. Don't forget
            % to delete the brackets first, or the code won't work**.