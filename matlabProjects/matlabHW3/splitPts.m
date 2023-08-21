function [ xs ] = splitPts( x )

%xs = reshape ([x'; zeros(size(x'))], [],1);
 %fprintf('%2.0f ',xs);
 %fprintf('\n');
%max = 2*length(xs);
%fprintf('%.2f ',xs);
%fprintf('%2.2f',max);

N=length(x);
xs = zeros(1,2*N);
for k = 1:N
   xs(2*k-1) = x(k);
end

for k = 2:2:2*N
    if k == 2*N
        xs(k) = (xs(k-1) + xs(1))/2;
    else
        xs(k) = (xs(k-1) + xs(k+1))/2;
    end
    
end
fprintf('%2.0f ',xs);