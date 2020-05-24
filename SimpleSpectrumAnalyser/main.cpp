#include <stdio.h>
#include <string.h>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <valarray>
#include <complex>
using namespace std;


typedef complex <double>    Complex;   
typedef valarray<Complex>   CArray;
const double PI = 3.141592653589793238460;


struct WavHeader
{
    char                chunkID[4];                                     // chunkID Header      
    unsigned int        ChunkSize;                                      // chunkID Chunk Size  
    char                format[4];                                      // WAVE Header      
    char                subchunck1ID[4];                                // FMT header       
    unsigned int        Subchunk1Size;                                  // Size of the fmt chunk                                
    unsigned short      AudioFormat;                                    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
    unsigned short      NumOfChan;                                      // Number of channels 1=Mono 2=Sterio                   
    unsigned int        SampleRate;                                     // Sampling Frequency in Hz                             
    unsigned int        bytesPerSec;                                    // bytes per second 
    unsigned short      blockAlign;                                     // 2=16-bit mono, 4=16-bit stereo 
    unsigned short      bitsPerSample;                                  // Number of bits per sample      
    char                Subchunk2ID[4];                                 // "data"  string   
    unsigned int        Subchunk2Size;                                  // Sampled data length  
}; 


void    ReadHeader(ifstream &, WavHeader &, bool &);
void    ProcessFile(ifstream &, ofstream &, WavHeader);
void    fft(CArray &);

int main(int argc, char* argv[])
{   
    if(argc != 2)                                                           // check for correct arguments
    {
        printf("Must have one .wav file as a command line argument.\n");
        return 1;
    }  

    string inputFileName = argv[1];

    ifstream    infile;
    ofstream    outfile;
    ofstream    report;
    WavHeader   header;
    bool        error = false;

    infile.open(inputFileName);
    outfile.open("output.csv");
    outfile << "Time (Seconds), fmax (Hz), Power (db)" << endl;

    auto startTime = chrono::high_resolution_clock::now();                  // start timeing execution
    ReadHeader(infile, header, error);
    
    
    if(error)                                                       
        return 1;

    ProcessFile(infile, outfile, header);

    report.open("Summary.txt");
    auto endTime = chrono::high_resolution_clock::now();
    auto executionTime = chrono::duration_cast<chrono::milliseconds>(endTime-startTime).count();
    report << setw(25) << setprecision(2) << 
    "Total Process Time: " << executionTime << 
    " milliseconds" << endl;

    outfile.close();
    infile.close();
    report.close();
        
    return 0;
}


void ReadHeader(ifstream &inputData, WavHeader &headerInfo, bool &error)
{
    inputData.read((char*)&headerInfo, sizeof(headerInfo));             // read in the wav header

    if(headerInfo.NumOfChan != 2)                                       // check to make sure that the file is stereo
    {
        error = true;
        printf("The file must have two channels!\n");
    }

    else if(headerInfo.SampleRate != 44100 && headerInfo.SampleRate != 22050)
    {
        error = true;
        printf("The file must have a sample rate of either 44100 Hz of 22050 Hz!\n");
    }
}


void ProcessFile(ifstream &inputData, ofstream &outData, WavHeader headerInfo)
{
    int     bufferSize  = headerInfo.SampleRate / 2;                        // holds left samples only
    float   timeIndex   = 0;                                                // current base time
    int     arrIndex    = 0;

    short leftSample; 
    short rightSample; 

    while (!inputData.eof())
    {
        arrIndex = timeIndex * headerInfo.SampleRate;
        CArray buffer(bufferSize);  
        
        for(int i=0; i<bufferSize; i++)
        {
            inputData.read((char*)&leftSample, sizeof(leftSample));         // read left sample
		    inputData.read((char*)&rightSample, sizeof(rightSample));       // read right sample
            buffer[i] = leftSample;                                         // save left ignore right
        }   
    
        fft(buffer);                                                        // take fourier transform of buffer

        double  tmp = 0;
        int     maxIndex = 0;
        double  maxSpec = (buffer[0].real()) * (buffer[0].real()) + (buffer[0].imag()) * (buffer[0].imag());

        for (int i = 0; i < bufferSize; i++)                                // find max spectrum in buffer
        {
            tmp = (buffer[i].real()) * (buffer[i].real()) + (buffer[i].imag()) * (buffer[i].imag());
            if (tmp > maxSpec)
            {
                maxSpec = tmp;
                maxIndex = i;
            }
        }

        double maxFreqHZ = maxIndex * headerInfo.SampleRate / bufferSize;   // convert to Hz
        double power = pow(maxFreqHZ, 2);
        power = 10*log10(power);
        outData << timeIndex << " to " << timeIndex+1 << ", ";
        outData << maxFreqHZ << ", ";
        outData << power << ", " << endl;
        
        timeIndex+= .5;
    }   
    
}


void fft(CArray &x)                                                         // recursive fft algorithim
{
    const size_t N = x.size();
    if (N <= 1) return;
 
    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];
 
    // conquer
    fft(even);
    fft(odd);
 
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}
