function score = differ(x, y)
% 
% whos x;
% whos y;

Nfeatures = 512;
score = 0.0;
for i=1:Nfeatures
    score = score + (x(i)-y(i))^2;
end
score = sqrt(score);

end

% differ(gists(1), gists(1))