#include <iostream>
#include "ThinkGearStreamParser.h"
#include "boost/asio.hpp"
#include "PeakDetector.h"
#define BUFSIZE 512

void ThinkGearDataHandle( unsigned char extendedCodeLevel,
                            unsigned char code,
                            unsigned char numBytes,
                            const unsigned char *value,
                            void *customData )
{
    auto detector = reinterpret_cast<PeakDetector*>(customData);
    if (code == 0x80) {
        short val = (value[0] << 8) | value[1];
        detector->inputValue(val);
    }
}


int main(int argc, char **argv)
{
    std::string host, portname;
    int port;
    
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        std::cout << "Steps:\n";
        std::cout << "1. Connect ThinkGear to bluetooth\n";
        std::cout << "2. Check bluetooth SPP settings on your system\n";
        std::cout << "3. type:  ";
        std::cout << argv[0] << " portname\n\n";
    }
    
    if (argc < 2) {
        std::cout << "USAGE: ";  
        std::cout << argv[0] << " portname host port\n\n";  
        std::cout << "EXAMPLE: " << argv[0] << " /dev/rfcomm0\n"; 
        std::cout << "\n\tType " << argv[0] << " -h for more informations\n\n"; 
        return 1; 
    } 

    portname = argv[1];
    
    boost::asio::io_service serialport_service;
    boost::asio::serial_port device(serialport_service, portname);
    
    PeakDetector detector;
    
    ThinkGearStreamParser parser;
    THINKGEAR_initParser(&parser, PARSER_TYPE_PACKETS, ThinkGearDataHandle, &detector);

    std::cout << "Press Ctrl+C to quit\n";
    while( true ) {
        unsigned char data[BUFSIZE];
        int size = device.read_some(boost::asio::buffer(data, BUFSIZE));
        for (int i=0; i<size; i++) {
            THINKGEAR_parseByte(&parser, data[i]);
        }
    }
    
    return 0;
}
