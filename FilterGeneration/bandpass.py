from math import pi, cos, sin

a = []
b = []
h = []

m = 801                                         # filter length
fca = .196                                      # cutoff 
for i in range(m):                              # calculate first filter kernel
    if(i-m/2 == 0):
        a.append(2*pi*fca)

    if(i-m/2 != 0):
        a.append(sin(2*pi*fca * (i-m/2)) / (i-m/2))
        a[i] = a[i] * (0.54 - 0.46*cos(2*pi*i/m))
    
for i in range(m):                              # normalize the filter
    a[i] = a[i]/sum(a)
    
fcb = .204
for i in range(m):                              # calculate first filter kernel
    if(i-m/2 == 0):
        b.append(2*pi*fcb)

    if(i-m/2 != 0):
        b.append(sin(2*pi*fcb * (i-m/2)) / (i-m/2))
        b[i] = b[i] * (0.54 - 0.46*cos(2*pi*i/m))
        
for i in range(m):                              # normalize the filter
    b[i] = b[i]/sum(b)
    
for i in range(m):                              # convert to high pass filter
    b[i] = b[i] * -1
b[int((m-1)/2)] = b[int((m-1)/2)] + 1

for i in range(m):                              # add together to form band stop filter
    h.append(a[i] + b[i])
    
for i in range(m):                              # convert to band pass filter
    h[i] = h[i] * -1
h[int((m-1)/2)] = h[int((m-1)/2)] + 1

file = open('header.h', 'w')                
file.write("const double FILTER[" + str(m) + "] = \n")
file.write("{")

for i in range(m):
    file.write(str(h[i]))
    if(i != m-1):
        file.write(', ')
    if((i+1) % 4 == 0):
        file.write('\n')

file.write('}')

file.close()