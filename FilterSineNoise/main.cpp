#include <stdio.h>
#include <string.h>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "filter22050.h"
#include "filter44100.h"
using namespace std;

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

void ReadHeader(ifstream &inputData,  WavHeader &waveHeaderInfo, bool &);
void ProcessData(ifstream &, ofstream &, WavHeader);
void Filter44100(ifstream &, ofstream &);
void Filter22050(ifstream &, ofstream &);

int main(int argc, char *argv[])
{
    if(argc != 2)                                                           // check for correct arguments
    {
        printf("Must have one .wav file as a command line argument.\n");
        return 0;
    }   
    
    string inputFilename = argv[1];                                         // get the input file name from the command line
    ifstream infile;                                                        // input file stream
    ofstream outfile;                                                       // output file stream
    ofstream report;
    infile.open(inputFilename);                                           

    WavHeader header;
    bool errorOccurred = false;

    auto startTime = chrono::high_resolution_clock::now();                  // start timeing execution
    ReadHeader(infile, header, errorOccurred);                              // read the wav header and check for invalid file types

    if(errorOccurred)                                                       
        return 0;

    outfile.open("processed_filewav");                                     	// open the output wav file
    outfile.write((char*)&header, sizeof(header));                          // write the original header to the output file
    ProcessData(infile, outfile, header);                                   // begin filtering data

    auto endTime = chrono::high_resolution_clock::now();                    // finish timing execution
    auto executionTime = chrono::duration_cast<chrono::milliseconds>
    (endTime-startTime).count();

    report.open("summary.txt");
    report << "File Name:" << setw(30) << inputFilename << endl;
    report << "Sampling Rate:" << setw(11) << header.SampleRate << endl;
    report << "Execution Time:" << setw(9) << executionTime << " milliseconds" << endl;

    infile.close();                                                         // close all streams
    outfile.close();
    report.close();
    return 0;
}


void ReadHeader(ifstream &inputData, WavHeader &headerInfo, bool &errorOccurred)
{
    inputData.read((char*)&headerInfo, sizeof(headerInfo));             // read in the wav header

    if(headerInfo.NumOfChan != 2)                                       // check to make sure that the file is stereo
    {
        errorOccurred = true;
        printf("The file must have two channels!\n");
    }

    else if(headerInfo.SampleRate != 44100 && headerInfo.SampleRate != 22050)
    {
        errorOccurred = true;
        printf("The file must have a sample rate of either 44100 Hz of 22050 Hz!\n");
    }
}


void ProcessData(ifstream &infile, ofstream &outfile, WavHeader header)
{
    switch(header.SampleRate)                                           // check to see what frequncy to use
    {
        case 22050:
            Filter22050(infile, outfile);
            break;
        case 44100:
            Filter44100(infile, outfile);
            break;
    }
}


void Filter44100(ifstream &infile, ofstream &outfile)
{
    short leftArray[DEN44100];                                      // array for the left channel
    short rightArray[DEN44100];                                     // array for the right channel
    memset(leftArray, 0, DEN44100);                                 // set all of left array to 0
    memset(rightArray, 0, DEN44100);                                // set all of right array to 0

    short leftInput;                                            
    short rightInput;
    short leftResult;
    short rightResult;

    infile.read((char*)&leftInput, sizeof(leftInput));              // read in left sample
    infile.read((char*)&rightInput, sizeof(rightInput));            // read in right sample

    while(!infile.eof())
    {
        leftResult = 0;
        rightResult = 0;

        for(int i = DEN44100-1; i>0; i--)                            // shift the arrays
        {
            leftArray[i] = leftArray[i-1];
            rightArray[i] = rightArray[i-1];
        }

        leftArray[0] = leftInput;                              
        rightArray[0] = rightInput;

        for(int i=0; i<DEN44100; i++)                               // perform convolution
        {
            leftResult += leftArray[i] * NUM44100[i];
            rightResult += rightArray[i] * NUM44100[i];
        }

        outfile.write((char*)&leftResult, sizeof(leftResult));      // write results to output stream
        outfile.write((char*)&rightResult, sizeof(rightResult));

        infile.read((char*)&leftInput, sizeof(leftInput));          // get new samples
        infile.read((char*)&rightInput, sizeof(rightInput));
    }
}



void Filter22050(ifstream &infile, ofstream &outfile)
{
    short leftArray[DEN22050];
    short rightArray[DEN22050];
    memset(leftArray, 0, DEN22050);
    memset(rightArray, 0, DEN22050);

    short leftInput;
    short rightInput;
    short leftResult;
    short rightResult;

    infile.read((char*)&leftInput, sizeof(leftInput));
    infile.read((char*)&rightInput, sizeof(rightInput));

    while(!infile.eof())
    {
        leftResult = 0;
        rightResult = 0;

        for(int i = DEN22050-1; i>0; i--)
        {
            leftArray[i] = leftArray[i-1];
            rightArray[i] = rightArray[i-1];
        }

        leftArray[0] = leftInput;
        rightArray[0] = rightInput;

        for(int i=0; i<DEN22050; i++)
        {
            leftResult += leftArray[i] * NUM22050[i];
            rightResult += rightArray[i] * NUM22050[i];
        }

        outfile.write((char*)&leftResult, sizeof(leftResult));
        outfile.write((char*)&rightResult, sizeof(rightResult));

        infile.read((char*)&leftInput, sizeof(leftInput));
        infile.read((char*)&rightInput, sizeof(rightInput));
    }
}