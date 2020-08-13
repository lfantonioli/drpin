#include "pin.H"
#include <iostream>
#include <fstream>


static UINT64 exec_inst_count = 0;


VOID docount() { 
  exec_inst_count ++;
}


VOID Instruction(INS ins, VOID *v)
{
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_END);
}


VOID Fini(INT32 code, VOID *v)
{
    std::cout << "=========================================" << std::endl;
    std::cout << "the number of instructions executed is " << exec_inst_count << std::endl;
}


int main(int argc, char *argv[])
{
    if( PIN_Init(argc,argv) )
    {
        std::cout << "initialization invalid" << std::endl;
    }

    INS_AddInstrumentFunction(Instruction, 0);

    PIN_AddFiniFunction(Fini, 0);


    PIN_StartProgram();

    return 0;
}

