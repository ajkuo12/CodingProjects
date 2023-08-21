function y = moveAY(y, prob)
%The purpose of this function is to determine if the particle moves up,
%down, or does not move when prompted. 
if prob < 0.2
    if y~=5
    y = y+1; 
    else
    y = y;
    end 
end 
if prob>0.4 && prob<0.6
    if y~=-5
    y = y-1;
    else
    y = y;
    end 
end
if prob>0.8 
    y = y;
end
end