function DrawRectAK(a,b,L,W,c)
%The purpose of this function in this scenario is to color in each
%particle's position on the grid.
x = [a a+L a+L a a];
y = [b b b+W b+W b];
fill (x,y,c)
end 