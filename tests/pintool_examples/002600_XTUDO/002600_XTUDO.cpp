#include "pin.H"
#include <iostream>
#include <fstream>
#include <map>

ADDRINT first_ins_addr;

int seen = 0;

std::map<std::string, int> instruction_per_img;
/* VOID Instruction(INS ins, VOID *v) */
/* { */
/*   if(seen < 10){ */
/*       seen ++; */
/*       std::cout << "Dissassemble: " << INS_Disassemble(ins) << std::endl << std::flush; */
/*       UINT32 number_of_operands = INS_OperandCount(ins); */
/*       std::cout << "Number of operands: " << number_of_operands << std::endl; */
/*       for (UINT32 i = 0; i < number_of_operands; i++){ */
/*           std::cout << "Operand_" << i << " = " << INS_OperandReg(ins, i) << (INS_OperandRead(ins, i) ? (" (READ) | ") : " (WRITE) | "); */
/*       } */
/*       std::cout << std::endl << std::endl << std::flush; */
/*   } */
/*   /1* ADDRINT ins_addr_diff = INS_Address(ins) - first_ins_addr; *1/ */
/*   /1* std::cout <<  ins_addr_diff << " " <<  ins_str.substr(0, ins_str.find(' ')) << std::endl; *1/ */
/* } */

/*!
 * The main procedure of the tool.
 * This function is called when the application image is loaded but not yet started.
 * @param[in]   argc            total number of elements in the argv array
 * @param[in]   argv            array of command line arguments, 
 *                              including pin -t <toolname> -- ...
 */
VOID imagefn(IMG img, VOID *v){
  std::cout << "------------" << std::endl << std::endl;
  std::cout << "achei imagem nova " << std::endl;
  if (IMG_IsMainExecutable(img)){
    std::cout << "(IMAGE IS MAIN EXECUTABLE)" << std::endl;
  }
  const string& image_name = IMG_Name(img);
  std:: cout << "Image Name: " << image_name << std::endl;
  IMG_TYPE img_type = IMG_Type(img);
    if (img_type ==  IMG_TYPE_INVALID){
      std::cout << "IMG_TYPE_INVALID" << std::endl;
    } else if ( img_type ==  IMG_TYPE_STATIC){
      std::cout << "IMG_TYPE_STATIC" << std::endl;
    } else if ( img_type ==  IMG_TYPE_SHARED){
      std::cout << "IMG_TYPE_SHARED" << std::endl;
    } else if ( img_type ==  IMG_TYPE_SHAREDLIB){
      std::cout << "IMG_TYPE_SHAREDLIB" << std::endl;
    } else if ( img_type ==  IMG_TYPE_RELOCATABLE){
      std::cout << "IMG_TYPE_RELOCATABLE" << std::endl;
    } else if ( img_type ==  IMG_TYPE_DYNAMIC_CODE){
      std::cout << "IMG_TYPE_DYNAMIC_CODE" << std::endl;
    } else if ( img_type ==  IMG_TYPE_API_CREATED){
      std::cout << "IMG_TYPE_API_CREATED" << std::endl;
    } else if ( img_type ==  IMG_TYPE_LAST) {
      std::cout << "IMG_TYPE_LAST" << std::endl;
    } else {
      std::cout << "IMG_TYPE: undefined" << std::endl;
    }
    ADDRINT high_address = IMG_HighAddress(img);
    ADDRINT low_address = IMG_LowAddress(img);
    std::cout << "IMG Low Address: " << low_address << std::endl;
    std::cout << "IMG High Address: " << high_address << std::endl;
    SEC sec = IMG_SecHead(img);
    bool sec_valid = SEC_Valid(sec);
    bool img_valid = IMG_Valid(img);
    std::cout << "IMG valid: " << img_valid << std::endl; 
    std::cout << "SEC Valid: " << sec_valid << std::endl;
    std::cout << std::endl;
}

VOID imageunloadfn(IMG img, VOID *v){
    std::cout << "----------------------------" << std::endl;
    std::cout << "IMG: " << IMG_Name(img) << " Unloaded " << std::endl;
}


VOID instructionfn(INS ins, VOID *v){
  ADDRINT ins_address = INS_Address(ins);
  IMG containing_img = IMG_FindByAddress(ins_address);
  if (IMG_Valid(containing_img)){
    instruction_per_img[IMG_Name(containing_img)] += 1;
  } else {
    instruction_per_img["INVALID_IMG"] += 1;
  }
}

VOID finifn(INT32 code, VOID* v){
  std::cout << std::endl;
  for(std::map<std::string, int>::iterator  it = instruction_per_img.begin(); it != instruction_per_img.end(); it++){
    std::cout << "------------------------------" << std::endl;
    std::cout << it->first << ": " << it->second << " instructions" << std::endl;
  }
}

int main(int argc, char *argv[])
{
    // Initialize PIN library. Print help message if -h(elp) is specified
    // in the command line or the command line is invalid 
    if( PIN_Init(argc,argv) )
    {
        std::cout << "initialization invalid" << std::endl;
    }

    IMG_AddInstrumentFunction(imagefn, 0);

    IMG_AddUnloadFunction(imageunloadfn, 0);

    INS_AddInstrumentFunction(instructionfn, 0);

    PIN_AddFiniFunction(finifn, 0);


    PIN_StartProgram();

    return 0;
}

