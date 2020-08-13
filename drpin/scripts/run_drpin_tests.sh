source ./scripts/pretty_print.sh

print_information "
-------------------------------------
           Running DrPin tests
-------------------------------------
"

print_information "
           Finding tests
"

reference_dir=$PWD
for i in $(ls -d ../tests/pintool_examples/*/);
do 
  if [ -f $i"/SKIP" ]; then
    print_information "Will skip test $i"
    continue
  fi
  echo ${i}
done

print_information "
           Running tests
"

for i in $(ls -d ../tests/pintool_examples/*/);
do 
  if [ -f $i"/SKIP" ]; then
    continue
  fi
  print_information "
          Test: $i
  "
  cd ${i}
  ./run_drpin.sh
  cd $reference_dir
done



print_information "
-------------------------------------
           End tests
-------------------------------------
"
