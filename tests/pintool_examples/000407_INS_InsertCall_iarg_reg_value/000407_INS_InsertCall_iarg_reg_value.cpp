#include "pin.H"
#include <iostream>
#include <fstream>
#include <map>

static UINT64 icount = 0;
static int num_instructions = 0;

std::map<ADDRINT, std::string> addr2disassemble;

VOID instr_reg_value(ADDRINT ins_addr, ADDRINT eax_value ) { 
  icount++; 
  std::cout << "===================================================="<< std::endl << std::flush;
  std::cout << ins_addr << " : " << addr2disassemble[ins_addr] << std::endl << std::flush;
  std::cout << "eax value: " << eax_value << std::endl << std::flush;
  std::cout << "===================================================="<< std::endl << std::flush;
}

VOID Instruction(INS ins, VOID *v)
{
  num_instructions ++;
  string disassembled = INS_Disassemble(ins);
  ADDRINT ins_addresss = INS_Address(ins);
  addr2disassemble[ins_addresss] = disassembled;
       
    std::cout << "instrumenting: " << disassembled << std::endl << std::flush;

    if (INS_IsMemoryWrite(ins)) {
      INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)instr_reg_value, IARG_ADDRINT, ins_addresss, IARG_REG_VALUE, REG_EAX, IARG_END);
    }

}


VOID Fini(INT32 code, VOID *v)
{
  std::cout << "=========================================" << std::endl;
  std::cout << "the number of instructions instrumented is " << num_instructions << std::endl;
  std::cout << "the number of instructions executed is " << icount << std::endl;
}


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
