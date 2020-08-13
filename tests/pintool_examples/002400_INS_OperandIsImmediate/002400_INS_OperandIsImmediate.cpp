#include "pin.H"
#include <iostream>
#include <fstream>

ADDRINT first_ins_addr;

int seen = 0;
VOID Instruction(INS ins, VOID *v)
{
  if(seen < 10){
      seen ++;
      std::cout << "Dissassemble: " << INS_Disassemble(ins) << std::endl << std::flush;
      UINT32 number_of_operands = INS_OperandCount(ins);
      std::cout << "Number of operands: " << number_of_operands << std::endl;
      for (UINT32 i = 0; i < number_of_operands; i++){
          std::cout << "Operand_is_immediate_" << i << " = " << (INS_OperandIsImmediate(ins, i)) << " | " ;
      }
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

