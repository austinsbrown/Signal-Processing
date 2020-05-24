CC = g++

SpectrumAnalyser: main.o
	$(CC) main.o -o SpectrumAnalyser

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm *.o SpectrumAnalyser Summary.txt output.csv