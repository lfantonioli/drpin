
source ./scripts/pretty_print.sh

print_information "
-------------------------------------
           Building DrPin
-------------------------------------
"

mkdir -p ./build
export DYNAMORIO_HOME=$PWD/../dynamorio/build
print_warning "DynamoRIO HOME"
echo $DYNAMORIO_HOME
cd ./build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DDynamoRIO_DIR=$DYNAMORIO_HOME/cmake ../
make
