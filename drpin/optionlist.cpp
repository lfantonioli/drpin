#include <iostream>
#include "options.h"

int
main(int argc, const char *argv[])
{
    std::cout << droption_parser_t::usage_long(DROPTION_SCOPE_ALL,
                                               "- <b>", "</b>\n",
                                               "  <br><i>", "</i>\n",
                                               "  <br>", "\n")
              << std::endl;
    return 0;
}
