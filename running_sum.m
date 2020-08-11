x = 0:.01:10;
y = x(1);

for i = 2:length(x)
    y(i) = y(i-1) + x(i);
end