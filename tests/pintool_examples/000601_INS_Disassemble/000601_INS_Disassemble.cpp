

#include "pin.H"
#include <iostream>
#include <fstream>

bool flag = true;
ADDRINT first_ins_addr;

VOID Instruction(INS ins, VOID *v)
{
  if(flag){
      flag  = false;
      std::cout << "First instruction ever: " << INS_Disassemble(ins) << std::endl;
      first_ins_addr = INS_Address(ins);
      std::cout << "First Address: " << first_ins_addr << std::endl;
  }
  std::string ins_str = INS_Disassemble(ins);
  ADDRINT ins_addr_diff = INS_Address(ins) - first_ins_addr;
  std::cout <<  ins_addr_diff << " " <<  ins_str.substr(0, ins_str.find(' ')) << std::endl;
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

