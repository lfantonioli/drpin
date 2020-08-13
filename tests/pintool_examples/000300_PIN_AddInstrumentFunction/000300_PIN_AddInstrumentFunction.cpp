#include "pin.H"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>


// This function is called when the application exits
static int num_instructions = 0;

VOID Fini(INT32 code, VOID *v)
{
    std::cout << "===============================" << std::endl;
    std::cout << "Number of instructions instrumented: " << num_instructions << std::endl;
}

VOID Instruction(INS ins, VOID *v)
{
    num_instructions ++;
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

    INS_AddInstrumentFunction(Instruction, 0);

    PIN_AddFiniFunction(Fini, 0);


    PIN_StartProgram();

    return 0;
}


