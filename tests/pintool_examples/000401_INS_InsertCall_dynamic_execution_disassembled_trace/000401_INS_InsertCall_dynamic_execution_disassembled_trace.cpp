

#include "pin.H"
#include <iostream>
#include <fstream>
#include <map>

static UINT64 icount = 0;
static int num_instructions = 0;

std::map<ADDRINT, std::string> addr2disassemble;

VOID docount(ADDRINT ins_addr) { 
  icount++; 
  std::cout << ins_addr << " : " << addr2disassemble[ins_addr] << std::endl << std::flush;
}


VOID Instruction(INS ins, VOID *v)
{
    num_instructions ++;
    string disassembled = INS_Disassemble(ins);
    ADDRINT ins_addresss = INS_Address(ins);
    addr2disassemble[ins_addresss] = disassembled;
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_ADDRINT, ins_addresss, IARG_END);
}


VOID Fini(INT32 code, VOID *v)
{
    std::cout << "=========================================" << std::endl;
    std::cout << "the number of instructions instrumented is " << num_instructions << std::endl;
    std::cout << "the number of instructions executed is " << icount << std::endl;
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

