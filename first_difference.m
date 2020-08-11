x = exp(0:.01:10);
y = x(1);

for i = 2:length(x)
    y(i) = x(i) - x(i-1);
end