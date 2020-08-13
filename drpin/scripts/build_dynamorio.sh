source ./scripts/pretty_print.sh

print_information "
-------------------------------------
           Building DynamoRIO
-------------------------------------
"

mkdir -p ../dynamorio/build
cd ../dynamorio/build
cmake -DDISABLE_WARNINGS=ON -DBUILD_DOCS=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
# cmake -DDEBUG=ON ..
make -j
