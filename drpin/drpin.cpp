/* drpin.cpp: client for simulating PIN DBI 
 */

#include "dr_api.h"
#include "dr_tools.h"
#include "drmgr.h"
#include "droption.h"
#include "options.h"
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include "include/pin/pin.H"

// XXX i#1732: make a msgbox on Windows (controlled by option for batch runs)
#define NOTIFY(level, ...) do {            \
    if (op_verbose.get_value() >= (level)) \
        dr_fprintf(STDERR, __VA_ARGS__);   \
} while (0)



DR_EXPORT void umafuncaoqualquer(){
  printf("this is just a test function\n");
}

bool drpin_debug_flag = false;

string drpin_pintool_op_flag = "";


void
drpin_debug_analyser(){
  printf("==============[DrPin Debug API Analyzer]================\n");
  printf("============================================================\n");
}



DR_EXPORT void
dr_client_main(client_id_t id, int argc, const char *argv[])
{
    
    dr_set_client_name("DynamoRIO PIN simulator", "http://dynamorio.org/issues");

    std::string parse_err;
    if (!droption_parser_t::parse_argv(DROPTION_SCOPE_CLIENT, argc, argv,
                                       &parse_err, NULL)) {
        NOTIFY(0, "Usage error: %s\nUsage:\n%s", parse_err.c_str(),
               droption_parser_t::usage_short(DROPTION_SCOPE_ALL).c_str());
        dr_abort();
    }


    drpin_debug_flag = drpin_debug.get_value();
    // drpin_debug_flag = true; // TODO: remove it 
    drpin_pintool_op_flag = drpin_pintool_op.get_value();

    if(drpin_pintool.get_value() != "drpin_none"){

      if(drpin_debug_flag) {
        printf("============================================================\n");
        printf("pintool selected: %s\n", drpin_pintool.get_value().c_str());
        printf("============================================================\n");
        drpin_debug_analyser();
      } 


      if(drpin_debug_flag){
        std::cout << "drpin_pintool " << drpin_pintool.get_value() << std::endl << std::flush;
      }

      dr_auxlib_handle_t handle =  dr_load_aux_library( drpin_pintool.get_value().c_str(), NULL, NULL);
      if (!handle) {
          printf("Cannot load pintool. Aborting\n");
      } else {
        if(drpin_debug_flag) {
          printf("Library loaded successful\n");
        }
      }

      dr_auxlib_routine_ptr_t pintool_main_fn = dr_lookup_aux_library_routine(handle, "main");
      int (*pintool_main_ptr)(int, const char*[])  = (int (*)(int, const char*[])) pintool_main_fn;
      pintool_main_ptr(argc, argv);

    } else {
      printf("============================================================\n");
      printf("No pintool selected. Doing nothing\n");
      printf("============================================================\n");
    }


}
