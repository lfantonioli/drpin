#include "pin.H"
#include <iostream>
#include <fstream>


int main(int argc, char *argv[])
{

    if( PIN_Init(argc,argv) )
    {
        std::cout << "initialization invalid" << std::endl;
    }

    std::cout << "REG name: " << REG_StringShort(REG_AL) << std::endl << std::flush;
    std::cout << "REG name: " << REG_StringShort(REG_EAX) << std::endl << std::flush;



    PIN_StartProgram();

    return 0;
}

