#include <fstream>
#include <iostream>
#include <cmath>
#include <stdlib.h>   
#include <iomanip>
#include <chrono>
#include <time.h>
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

const int FREQ = 2000;                                            
const float PI = 3.14159;                                          

void ReadHeader(ifstream &inputData, string filename, WavHeader &waveHeaderInfo, bool &);
void ProcessData(string, ifstream &, ofstream &, ofstream &, WavHeader);
void AddNoise(ofstream &, short, short, short, float);
void FindMaxAmp(string, short &, WavHeader, string &);


int main(int argc, char *argv[])                      
{     
    if(argc != 2)                                                       // check for correct arguments
    {
        cout << "Must have one .wav file as a command line argument." << endl;
        return 0;
    }   

    ifstream infile;                                                    // declare input stream  
    ofstream outfile, report;                                           // declare output streams
    bool error = false;                                                 // error flag
    string filename = argv[1];                                          // name of audio file

    infile.open(filename.c_str());                                      // attempt to open wav file in binary mode
    outfile.open("processed_file.wav");                                 // attempt to open output file in binary mode
    report.open("summary.txt");                                         // create report file 

    if (!infile.is_open())                                              // handle input file errors   
	{
		cout << "Error - unable to open input file" << endl;            // output error message
		outfile.close();                                                // close outfile stream
		return 0;                                                       // return from main
	}   

    WavHeader headerInfo;                                               // create instance of WavHeader type

    auto startTime = chrono::high_resolution_clock::now();
    ReadHeader(infile, filename, headerInfo, error);                    // read the header part of the wav file

    if(error)
    {
        cout << "File must have 2 channels" << endl;
        report << "File must have 2 channels" << endl;
        infile.close();                                                 // close all data streams
        outfile.close();
        report.close();
        return 0;                                                       // exit the program
    }

    unsigned long NumOfSamples = (headerInfo.Subchunk2Size /            // calculate the total number of samples
    headerInfo.NumOfChan) / (headerInfo.bitsPerSample / 8);
    double playtime = (double)NumOfSamples / headerInfo.SampleRate;     // calculate the total playtime

    report << left;                                                     // write information to the report
    report << setw(25) << "Filename: " << filename << endl;                        
    report << setw(25) << "Sampling Frequency: " <<                              
    headerInfo.SampleRate << endl;
    report << setw(25) << "Number of Channels: " << 
    headerInfo.NumOfChan << endl;  
    report << setw(25) << "Bits Per Sample: " << 
    headerInfo.bitsPerSample << endl; 
    report << setw(25) << "Total Time of the Song" <<
    playtime << " seconds"<< endl;

    outfile.write((char*)&headerInfo, sizeof(headerInfo));              // write the header to the new wav file

    ProcessData(filename, infile, outfile, report, headerInfo);         // begin processing the file

    auto endTime = chrono::high_resolution_clock::now();
    auto executionTime = chrono::duration_cast<chrono::milliseconds>(endTime-startTime).count();
    report << setw(25) << setprecision(2) << 
    "Total Process Time: " << executionTime << 
    " milliseconds" << endl;

    infile.close();                                                     // close all data streams
    outfile.close(); 
    report.close();
    return 0;  
}    


void ReadHeader(ifstream &inputData, string filename, WavHeader &headerInfo, bool &errorOccurred)
{
    inputData.read((char*)&headerInfo, sizeof(headerInfo));             // read in the wav header

    if(headerInfo.NumOfChan != 2)                                       // check to make sure that the file is stereo
        errorOccurred = true;
}


void ProcessData(string filename, ifstream &infile, ofstream &outfile, ofstream &report, WavHeader header)
{
    short sampleLeft, sampleRight;                                      // left and right samples to be processed
    short maxAmplitude;                                                 // maximum amplitude 
    short sinAmp;                                                       // 10% of maximum amplitude
    float time = 0.0;                                                   // time for the sine noise generator
    string channel;

    FindMaxAmp(filename, maxAmplitude, header, channel);                // find the max amplitude
    sinAmp = maxAmplitude / 10;                                         // take 10 % of the max amplitude

    report << "The maximum amplitude is " << maxAmplitude <<            // write to report
    ". It occurs in the " << channel << " channel." << endl;

    infile.read((char*)&sampleLeft, sizeof(sampleLeft));                // get the left sample
	infile.read((char*)&sampleRight, sizeof(sampleRight));              // get the right sample
    AddNoise(outfile, sinAmp, sampleLeft, sampleRight, time);           // add noise to the file

    while(!infile.eof())
    {
        time = time + (1.0f / header.SampleRate);

        infile.read((char*)&sampleLeft, sizeof(sampleLeft));
	    infile.read((char*)&sampleRight, sizeof(sampleRight));
        AddNoise(outfile, sinAmp, sampleLeft, sampleRight, time); 
    }
}


void AddNoise(ofstream &outfile, short amplitude, short sampleLeft, short sampleRignt, float time)
{
    short inT;                                                          // input at time t
    short nT;                                                           // sine noise at time t
    short rnT;                                                          // random noise at time t

    inT = sampleLeft;                                                   // original sample
    nT = short(amplitude * sin(time*FREQ*2.0f*PI));                     // generate sine wave
    rnT = short((rand() % amplitude)*2-amplitude);                      // generate random noise and handle overflow
    sampleLeft = short(inT + .1*nT + .05*rnT);                          // combine components for left channel
    

    inT = sampleRignt;                                                
    nT = short(amplitude * sin(time*FREQ*2.0f*PI));   
    rnT = short((rand() % amplitude)*2- amplitude);
    sampleRignt = short(inT + .1*nT + .05*rnT);

    outfile.write((char*)&sampleLeft, sizeof(sampleLeft));              // write modified samples to the new wav file
    outfile.write((char*)&sampleRignt, sizeof(sampleRignt));
}


void FindMaxAmp(string filename, short &maxAmp, WavHeader header, string &channel)                          
{                                                                       // finds the maximum value in the file
    ifstream in;                                                        // delcare new input stream for audio file
    short temp;
    in.open(filename.c_str());         
    int channelNum = 0;                                                 // 0 if on left channel, 1 if on right                                    

    in.read((char*)&header, sizeof(header));                            // read in the wav file header

    in.read((char*)&maxAmp, sizeof(maxAmp));                            // load in a value
    channelNum = channelNum ^ 1;                                        // flip the channel bit     
    maxAmp = abs(maxAmp);                                               // take the absolute value
    in.read((char*)&temp, sizeof(temp));                                
    channelNum = channelNum ^ 1; 

    if(abs(temp > maxAmp))
        maxAmp = abs(temp);

    while (!in.eof())
    {
        in.read((char*)&temp, sizeof(temp));
        channelNum = channelNum ^ 1; 
        if(abs(temp > maxAmp))
            maxAmp = abs(temp);
            
    }
    if(channelNum == 0)
        channel = "left";
    else
        channel = "right";
}
