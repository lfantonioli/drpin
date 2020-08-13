#include "pin.H"
#include <iostream>
#include <fstream>

ADDRINT first_ins_addr;

int seen = 0;
VOID Instruction(INS ins, VOID *v)
{

  if(INS_IsAtomicUpdate(ins)){
      std::cout << "Dissassemble: " << INS_Disassemble(ins) << std::endl << std::flush;
      std::cout << "INS_opcode: " << INS_Opcode(ins) << std::endl << std::flush;
  }

  /* if(INS_Opcode(ins) == 100){ */

  /*     std::cout << std::endl << "======================================" << std::endl << std::flush; */
  /*     std::cout << "SPECIAL EDITION " << std::endl << std::flush; */
  /*     std::cout << "disassembly: " <<  INS_Disassemble(ins) << std::endl << std::flush; */
  /*     std::cout << "======================================" << std::endl << std::endl << std::flush; */
  /* } */
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

