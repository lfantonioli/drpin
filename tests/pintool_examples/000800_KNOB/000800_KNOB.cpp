#include "pin.H"
#include <iostream>
#include <fstream>


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

    
    KNOB<INT32> KnobProcIdx(KNOB_MODE_WRITEONCE, "pintool",
            "procIdx", "0", "zsim process idx (internal)");

    KNOB<INT32> KnobShmid(KNOB_MODE_WRITEONCE, "pintool",
            "shmid", "0", "SysV IPC shared memory id used when running in multi-process mode");

    KNOB<string> KnobConfigFile(KNOB_MODE_WRITEONCE, "pintool",
            "config", "zsim.cfg", "config file name (only needed for the first simulated process)");


    KNOB<bool> KnobLogToFile(KNOB_MODE_WRITEONCE, "pintool",
            "logToFile", "false", "true if all messages should be logged to a logfile instead of stdout/err");

    KNOB<string> KnobOutputDir(KNOB_MODE_WRITEONCE, "pintool",
            "outputDir", "./", "absolute path to write output files into");


    PIN_StartProgram();

    return 0;
}

