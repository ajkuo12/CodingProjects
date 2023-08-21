function x = moveX(x, prob)
%The purpose of this function is to determine if the particle moves left,
%right, or does not move when prompted. 
if prob>0.2 && prob<0.4
    if x~=5
    x = x+1; 
    else
    x = x;
    end 
end 
if prob>0.6 && prob<0.8
    if x~=-5
    x = x-1;
    else
    x = x;
    end 
end 
if prob>0.8 
    x = x;
end
end
