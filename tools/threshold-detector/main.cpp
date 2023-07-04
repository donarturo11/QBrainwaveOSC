#include <iostream>
#include "ThinkGearStreamParser.h"
#include "boost/asio.hpp"

#define BUFSIZE 512

int main(int argc, char **argv)
{
    std::string host, portname;
    int port;
    
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        std::cout << "Steps:\n";
        std::cout << "1. Connect ThinkGear to bluetooth\n";
        std::cout << "2. Check bluetooth SPP settings on your system\n";
        std::cout << "3. type:  ";
        std::cout << argv[0] << " portname ip_address port\n\n";
    }
    
    if (argc < 4) {
        std::cout << "USAGE: ";  
        std::cout << argv[0] << " portname host port\n\n";  
        std::cout << "EXAMPLE: " << argv[0] << " /dev/rfcomm0 127.0.0.1 7771\n"; 
        std::cout << "\n\tType " << argv[0] << " -h for more informations\n\n"; 
        return 1; 
    } 

    portname = argv[1];
    host     = argv[2];
    port     = atoi(argv[3]);
    
    boost::asio::io_service serialport_service;
    boost::asio::serial_port device(serialport_service, portname);
    
    ThinkGearStreamParser parser;

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
