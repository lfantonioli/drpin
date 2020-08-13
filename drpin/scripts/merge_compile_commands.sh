
source ./scripts/pretty_print.sh

print_information "
-------------------------------------
   MERGING compile_commands.json
-------------------------------------
"

mkdir -p ../.vscode
TARGET_COMPILE_FILE=../.vscode/compile_commands.json

head -n -2 ./build/compile_commands.json > $TARGET_COMPILE_FILE
echo "
}," >>  $TARGET_COMPILE_FILE
tail -n +2 ../dynamorio/build/compile_commands.json >> $TARGET_COMPILE_FILE
