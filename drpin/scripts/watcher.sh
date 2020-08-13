#! /bin/bash

trap trapint 2
function trapint {
    exit 0
}

DIRECTORY_TO_OBSERVE="../"      
function block_for_change {
  inotifywait -r  -e modify,move,create,delete --exclude '/*\.(so|o)' $DIRECTORY_TO_OBSERVE
}
function build_and_run {
  ./scripts/build_dynamorio.sh && ./scripts/build_drpin.sh && ./scripts/merge_compile_commands.sh && ./scripts/build_drpin_tests.sh && ./scripts/run_drpin_tests.sh
  # ./scripts/build_drpin.sh && ./scripts/build_drpin_tests.sh && ./scripts/run_drpin_tests.sh
}
build_and_run
while true
do
block_for_change |
  while read path action file; do
    if [[ "$file" =~ .*c$ ]] || [[ "$file" =~ .*cpp$ ]] || [[ "$file" =~ .*h$ ]] ||[[ "$file" =~ .*H$ ]]; then
      echo "changed file: $path $file"

      # commands to run
      clear
      build_and_run
    fi
  done
done
