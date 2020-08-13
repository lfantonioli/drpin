#include "pin.H"
#include <iostream>

using namespace std;

UINT64 cond_br_counter;

VOID count_cond_br() { 
  cond_br_counter ++;
}

VOID Instruction(INS ins, VOID *v)
{
  if ( INS_Category(ins) == XED_CATEGORY_COND_BR ){
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)count_cond_br, IARG_END);
  }
}

VOID PrintStatistics(INT32 exit_code, VOID *v){
  cout << "=====================================================" << endl;
  cout << "Number of executed conditional branches: " << cond_br_counter << endl;
  cout << "=====================================================" << endl;
}



int main(int argc, char *argv[])
{
    if( PIN_Init(argc,argv) )
    {
        cout << "initialization invalid" << endl;
    }
    
    cond_br_counter = 0;
    
    INS_AddInstrumentFunction(Instruction, 0);

    PIN_AddFiniFunction(PrintStatistics, 0);

    PIN_StartProgram();

    return 0;
}

