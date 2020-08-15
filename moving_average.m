x = sin(0:.01:10);

for i = 1:length(x)
    ran(i) = rand(1);
end

x = x+ran;

filterlength = 5;
for i = 1:length(x) - filterlength
    y(i) = 0;
    for j=0:filterlength
        y(i) = y(i) + x(i+j);
    end
    y(i) = y(i) / filterlength;
end    