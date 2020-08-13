#ifndef _OPTIONS_H_
#define _OPTIONS_H_ 1

#include <string>
#include "droption.h"

extern droption_t<unsigned int> op_verbose;
extern droption_t<bool> drpin_debug;
extern droption_t<std::string> drpin_pintool_op;
extern droption_t<std::string> drpin_pintool;

#endif /* _OPTIONS_H_ */
