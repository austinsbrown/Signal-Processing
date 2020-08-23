from math import sin, cos, pi
import matplotlib.pyplot as p

m = int(input("Enter the filter length (must be an odd number): "))            # must have an odd number of elements, be careful of indexing
fc = float(input("Enter the cuttoff frequncy: ") )                             # cutoff frequincy                              
                             
h = []                                                                         # holds the filter                                 

for i in range(m):
    if(i-m/2 == 0):
        h.append(2*pi*fc)

    if(i-m/2 != 0):
        h.append(sin(2*pi*fc * (i-m/2)) / (i-m/2))
        h[i] = h[i] * (0.54 - 0.46*cos(2*pi*i/m))
    
for i in range(m):                                                             # normalize the filter
    h[i] = h[i]/sum(h)

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

p.plot(h, color='red')
p.xlabel('Sample Number')
p.ylabel('Filter Coefficient')
p.grid(True)
p.style.use('ggplot')
p.savefig('filter.png')