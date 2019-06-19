//hpgl file parser
//zxsq june 2019
#include <iostream>
#include <unistd.h>//not needed? idk
#include <fstream>
#include <string>
using namespace std;
int main(){
    char stopchar = 59; //semicolon
    string datacarrier; //ferries one chunk of data at a time
    string datapacket;
    int packetlength;//# of chunks added to packet
    bool eofreached = 0;
    ifstream hpglfile("input.hpgl");
    ofstream serialout("/dev/ttyUSB0");
    while (eofreached != 1){ //read in data, chunk out, send, repeat
        std::getline(hpglfile, datacarrier, stopchar);
        datapacket += (datacarrier += ";"); //adds datacarrier chunk to packet, appends lost ";"
        packetlength++;
        eofreached = hpglfile.eofbit;//check if we hit eof
        usleep(25000);
        if ((packetlength >= 15 && eofreached == 0) || eofreached == 1){
            serialout << datapacket; //prints blocks of 15 instructions to plotter. also prints any remainders when eof is reached             
            datapacket.clear();      //clears out packet string
        }
        datacarrier.clear();
    }
};