add_library(drpin SHARED 
  drpin.cpp 
  optionlist.cpp
  options.cpp
  pin.cpp
  )
find_package(DynamoRIO)
if (NOT DynamoRIO_FOUND)
  message(FATAL_ERROR "DynamoRIO package required to build")
endif(NOT DynamoRIO_FOUND)
configure_DynamoRIO_client(drpin)
use_DynamoRIO_extension(drpin drmgr)
use_DynamoRIO_extension(drpin drutil)
use_DynamoRIO_extension(drpin drsyms) 

