#include "pin.H"
#include <iostream>
#include <fstream>
#include <map>

static UINT64 icount = 0;
static int num_instructions = 0;

std::map<ADDRINT, std::string> addr2disassemble;

VOID instr_read(ADDRINT ins_addr, THREADID tid,  ADDRINT address_of_read ) { 
  std::cout << "cheguei aqui" <<  std::endl << std::flush;
  icount++; 
  std::cout << "===================================================="<< std::endl << std::flush;
  std::cout << ins_addr << " : " << addr2disassemble[ins_addr] << std::endl << std::flush;
  std::cout << "Thread ID: " << tid << std::endl << std::flush;
  std::cout << "ADDRESS OF READ: "  << address_of_read << std::endl << std::flush;
  std::cout << "===================================================="<< std::endl << std::flush;
}

/* VOID docount_read2(ADDRINT ins_addr, THREADID tid, ADDRINT reg_value_inst_ptr, BOOL will_be_executed, ADDRINT address_of_read2,  ADDRINT inst_address, BOOL branch_taken, ADDRINT branch_target , ADDRINT fallthrough_address, ADDRINT reg_value_ecx, ADDRINT reg_value_eax, PIN_REGISTER* reg_eax_ref, PIN_REGISTER* reg_ebx_ref, PIN_REGISTER* reg_ecx_ref, PIN_REGISTER* reg_edx_ref, void* num_instructions, ADDRINT reg_rdi_value, ADDRINT reg_rsi_value, PIN_REGISTER* reg_rax_ref ) { */ 
/*   icount++; */ 
/*   std::cout << ins_addr << " : " << addr2disassemble[ins_addr] << std::endl << std::flush; */
/* } */

/* VOID docount_write(ADDRINT ins_addr, THREADID tid, ADDRINT reg_value_inst_ptr,  BOOL will_be_executed,  ADDRINT inst_address, BOOL branch_taken, ADDRINT branch_target , ADDRINT fallthrough_address, ADDRINT reg_value_ecx, ADDRINT reg_value_eax, PIN_REGISTER* reg_eax_ref, PIN_REGISTER* reg_ebx_ref, PIN_REGISTER* reg_ecx_ref, PIN_REGISTER* reg_edx_ref, void* num_instructions, ADDRINT reg_rdi_value, ADDRINT reg_rsi_value, PIN_REGISTER* reg_rax_ref ) { */ 
/*   icount++; */ 
/*   std::cout << ins_addr << " : " << addr2disassemble[ins_addr] << std::endl << std::flush; */
/* } */

/* VOID docount_else(ADDRINT ins_addr, THREADID tid, ADDRINT reg_value_inst_ptr, BOOL will_be_executed, ADDRINT inst_address, BOOL branch_taken, ADDRINT branch_target , ADDRINT fallthrough_address, ADDRINT reg_value_ecx, ADDRINT reg_value_eax, PIN_REGISTER* reg_eax_ref, PIN_REGISTER* reg_ebx_ref, PIN_REGISTER* reg_ecx_ref, PIN_REGISTER* reg_edx_ref, void* num_instructions, ADDRINT reg_rdi_value, ADDRINT reg_rsi_value, PIN_REGISTER* reg_rax_ref ) { */ 
/*   icount++; */ 
/*   std::cout << ins_addr << " : " << addr2disassemble[ins_addr] << std::endl << std::flush; */
/* } */



VOID Instruction(INS ins, VOID *v)
{
  num_instructions ++;
  string disassembled = INS_Disassemble(ins);
  ADDRINT ins_addresss = INS_Address(ins);
  addr2disassemble[ins_addresss] = disassembled;

  /* if (INS_HasMemoryRead2(ins) ) { */
  /*   std::cout << "eh memoria 2" << std::endl << std::flush; */
  /*   INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount_read2, IARG_ADDRINT, ins_addresss, IARG_THREAD_ID, IARG_REG_VALUE, REG_INST_PTR, IARG_EXECUTING, IARG_MEMORYREAD2_EA, IARG_INST_PTR, IARG_BRANCH_TAKEN, IARG_BRANCH_TARGET_ADDR, IARG_FALLTHROUGH_ADDR, IARG_REG_VALUE, REG_ECX, IARG_REG_VALUE, REG_EAX, IARG_REG_REFERENCE, REG_EAX, IARG_REG_REFERENCE, REG_EBX, IARG_REG_REFERENCE, REG_ECX, IARG_REG_REFERENCE, REG_EDX, IARG_PTR, &num_instructions, IARG_REG_VALUE, REG_RDI, IARG_REG_VALUE, REG_RSI, IARG_REG_REFERENCE, REG_RAX,  IARG_END); */
  /* } */
   if (INS_IsMemoryRead(ins) ) {
    std::cout << "instrumenting: " << disassembled << std::endl << std::flush;
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)instr_read, IARG_ADDRINT, ins_addresss, IARG_THREAD_ID, IARG_MEMORYREAD_EA,  IARG_END);
  }
  /* else if (INS_IsMemoryWrite(ins)) { */
  /*   std::cout << "eh write 2" << std::endl << std::flush; */
  /*   INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount_write, IARG_ADDRINT, ins_addresss, IARG_THREAD_ID, IARG_REG_VALUE, REG_INST_PTR, IARG_EXECUTING,  IARG_MEMORYWRITE_EA, IARG_INST_PTR, IARG_BRANCH_TAKEN, IARG_BRANCH_TARGET_ADDR, IARG_FALLTHROUGH_ADDR, IARG_REG_VALUE, REG_ECX, IARG_REG_VALUE, REG_EAX, IARG_REG_REFERENCE, REG_EAX, IARG_REG_REFERENCE, REG_EBX, IARG_REG_REFERENCE, REG_ECX, IARG_REG_REFERENCE, REG_EDX, IARG_PTR, &num_instructions, IARG_REG_VALUE, REG_RDI, IARG_REG_VALUE, REG_RSI, IARG_REG_REFERENCE, REG_RAX,  IARG_END); */
  /* } */
  /* else { */
  /*   std::cout << "eh nada" << std::endl << std::flush; */
  /*   INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount_else, IARG_ADDRINT, ins_addresss, IARG_THREAD_ID, IARG_REG_VALUE, REG_INST_PTR,  IARG_EXECUTING, IARG_INST_PTR, IARG_BRANCH_TAKEN, IARG_BRANCH_TARGET_ADDR, IARG_FALLTHROUGH_ADDR, IARG_REG_VALUE, REG_ECX, IARG_REG_VALUE, REG_EAX, IARG_REG_REFERENCE, REG_EAX, IARG_REG_REFERENCE, REG_EBX, IARG_REG_REFERENCE, REG_ECX, IARG_REG_REFERENCE, REG_EDX, IARG_PTR, &num_instructions, IARG_REG_VALUE, REG_RDI, IARG_REG_VALUE, REG_RSI, IARG_REG_REFERENCE, REG_RAX,  IARG_END); */
  /* } */

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
