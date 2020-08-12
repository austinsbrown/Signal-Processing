x = sin(0:1:510);
rex = zeros(1, 256);
imx = zeros(1, 256);

n = length(x);

for k = 1:256
    for i = 1:511
        rex(k) = rex(k) + x(i) * cos(2*pi*k*i/2);
        imx(k) = imx(k) + x(i) * sin(2*pi*k*i/2);
    end
end