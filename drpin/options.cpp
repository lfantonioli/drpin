#include <string>
#include "droption.h"
#include "options.h"

#ifdef WINDOWS
# define IF_WINDOWS_ELSE(x,y) x
#else
# define IF_WINDOWS_ELSE(x,y) y
#endif


droption_t<unsigned int> op_verbose
(DROPTION_SCOPE_CLIENT, "verbose", 0, 0, 64, "Verbosity level",
 "Verbosity level for notifications.");

droption_t<bool> drpin_debug
(DROPTION_SCOPE_CLIENT, "drpin_debug", false, "Print debug information about the tool",
 "Print debug information useful for developing drpin");

droption_t<std::string> drpin_pintool_op
(DROPTION_SCOPE_CLIENT, "pintool_op", "", "pintool options", "options to be passed to the pintool");

droption_t<std::string> drpin_pintool
(DROPTION_SCOPE_CLIENT, "pintool", "drpin_none", "pintool to execute", "the pintool that should be executed");
