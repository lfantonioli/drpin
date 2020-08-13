

#include "pin.H"
#include <iostream>
#include <fstream>

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    std::cout << "this is the fini function call" << std::endl;
}


/*!
 * The main procedure of the tool.
 * This function is called when the application image is loaded but not yet started.
 * @param[in]   argc            total number of elements in the argv array
 * @param[in]   argv            array of command line arguments, 
 *                              including pin -t <toolname> -- ...
 */
int main(int argc, char *argv[])
{
    // Initialize PIN library. Print help message if -h(elp) is specified
    // in the command line or the command line is invalid 
    if( PIN_Init(argc,argv) )
    {
        std::cout << "initialization invalid" << std::endl;
    }else {
        std::cout <<  "initialization valid" << std::endl;
    }

    PIN_AddFiniFunction(Fini, 0);


    PIN_StartProgram();

    return 0;
}

