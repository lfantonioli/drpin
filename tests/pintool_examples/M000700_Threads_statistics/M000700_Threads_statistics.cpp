#include "pin.H"
#include <iostream>

using namespace std;

UINT64 cur_num_of_threads;

VOID ThreadStartHandler (THREADID threadIndex, CONTEXT *ctxt, INT32 flags, VOID *v){
  cur_num_of_threads ++;
  cout << "Currently running Threads: " << cur_num_of_threads << endl;
}

VOID ThreadStopHandler (THREADID threadIndex, const CONTEXT *ctxt, INT32 code, VOID *v){
  cur_num_of_threads --;
  cout << "Currently running Threads: " << cur_num_of_threads;
}


int main(int argc, char *argv[])
{
    if( PIN_Init(argc,argv) )
    {
        cout << "initialization invalid" << endl;
    }
    
    cur_num_of_threads = 0;
    
    // Register the ThreadStartHandler function to be called
    // when a thread starts in application code
    PIN_AddThreadStartFunction(ThreadStartHandler, 0);

    // Register the ThreadStopHandler function to be called
    // when a thread exits in application code
    PIN_AddThreadFiniFunction(ThreadStopHandler, 0);

    PIN_StartProgram();

    return 0;
}

