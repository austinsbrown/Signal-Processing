from math import sin, cos, pi

m = 101                                     # must have an odd number of elements, be careful of indexing
fc = .14                                    # cutoff frequincy
h = []                                     

for i in range(m):
    if(i-m/2 == 0):
        h.append(2*pi*fc)

    if(i-m/2 != 0):
        h.append(sin(2*pi*fc * (i-m/2)) / (i-m/2))
        h[i] = h[i] * (0.54 - 0.46*cos(2*pi*i/m))
    
for i in range(m):                          # normalize the filter
    h[i] = h[i]/sum(h)