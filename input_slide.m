x = 0:.1:10;
h = [2,4,1,2];
y = zeros(1,length(x) + length(h));

for i = 1:length(x)
    for j = 1:length(h)
        y(i+j) = y(i+j) + x(i) * h(j);
    end
end