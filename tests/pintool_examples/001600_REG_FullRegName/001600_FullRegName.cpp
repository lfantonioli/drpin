#include "pin.H"
#include <iostream>
#include <fstream>


int main(int argc, char *argv[])
{

    if( PIN_Init(argc,argv) )
    {
        std::cout << "initialization invalid" << std::endl;
    }

    REG reg = REG_AL;
    REG other_reg = REG_FullRegName(reg);
    std::cout << "Before reg: " << reg << std::endl << std::flush;
    std::cout << "After reg: " << other_reg << std::endl << std::flush;



    PIN_StartProgram();

    return 0;
}

