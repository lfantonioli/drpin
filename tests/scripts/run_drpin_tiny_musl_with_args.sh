#!/bin/bash
source ../../scripts/pretty_print.sh
drpin_exe="../../../executables/drpin"
pintool_file=$(find ./obj-intel64-drpin/ -iname '*.so' -type f)
tee_file=$(echo $pintool_file | tr / _ | tr . _ )

mkdir -p ./output_stdout/

print_information "\nRunning following command"

command_to_run="$drpin_exe -t $pintool_file -config /app/zsim_drpin/tests/simple.cfg -outputDir /app/zsim_drpin -shmid 14 -procIdx 21 -- ../../app_examples/tiny_musl/tiny 2>&1 | tee ./output_stdout/$tee_file.txt"

print_warning "$command_to_run"
print_information "-------------------------------------------------------------------\n"

eval $command_to_run
print_information "\n-------------------------------------------------------------------\n"

