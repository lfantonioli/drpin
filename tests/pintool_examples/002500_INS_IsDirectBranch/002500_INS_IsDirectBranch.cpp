#include "pin.H"
#include <iostream>
#include <fstream>

ADDRINT first_ins_addr;

int seen = 0;
VOID Instruction(INS ins, VOID *v)
{
  if(seen < 40){
      seen ++;
      std::cout << "Dissassemble: " << INS_Disassemble(ins) << std::endl << std::flush;
      std::cout << "isDirectBranch ? " << (INS_IsDirectBranch(ins) ? " YES " : " NO ") << std::endl << std::flush;
      std::cout << std::endl << std::endl << std::flush;
  }
}

int main(int argc, char *argv[])
{
    if( PIN_Init(argc,argv) )
    {
        std::cout << "initialization invalid" << std::endl;
    }

    INS_AddInstrumentFunction(Instruction, 0);



    PIN_StartProgram();

    return 0;
}

