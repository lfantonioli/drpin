

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
      /* INS_OperandReg(ins, 0); */
      for (UINT32 i = 0; i < number_of_operands; i++){
          std::cout << "Operand_" << i << " = " << INS_OperandReg(ins, i)  << " (" << REG_StringShort(INS_OperandReg(ins, i)) << ")" << (INS_OperandRead(ins, i) ? (" (READ) | ") : " (WRITE) | ");
      }
      std::cout << std::endl << std::endl << std::flush;
  }
  /* ADDRINT ins_addr_diff = INS_Address(ins) - first_ins_addr; */
  /* std::cout <<  ins_addr_diff << " " <<  ins_str.substr(0, ins_str.find(' ')) << std::endl; */
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
    }

    INS_AddInstrumentFunction(Instruction, 0);



    PIN_StartProgram();

    return 0;
}

