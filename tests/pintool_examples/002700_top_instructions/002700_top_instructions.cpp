#include "pin.H"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>

typedef std::pair<std::string, int> mnemonic_counter;
std::vector<mnemonic_counter> mnemonic_histogram;

int mnemonicIdx(std::string &mnemonic) {
  for (int i = 0; i < mnemonic_histogram.size(); i++) {
    if (mnemonic_histogram[i].first == mnemonic) {
      return i;
    }
  }
  return -1;
}

VOID incrementMnemonicCount(int idx) {
  mnemonic_histogram[idx].second++;
}

VOID instrumentInstruction(INS ins, VOID *v) {
  std::string ins_disassembled = INS_Disassemble(ins);
  std::string mnemonic = ins_disassembled.substr(0, ins_disassembled.find(' '));
  int mnemonicIndex = mnemonicIdx(mnemonic);
  // Inserts mnemonic into histogram if it does not exists yet
  if (mnemonicIndex == -1) {
    // Pushing new mnemonic to the end of the mnemonic histogram
    mnemonicIndex = mnemonic_histogram.size();
    mnemonic_histogram.push_back(std::make_pair(mnemonic, 0));
  }

  INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)incrementMnemonicCount, IARG_UINT32, mnemonicIndex, IARG_END);
}

VOID fini(INT32 code, VOID *v) {
  std::sort(mnemonic_histogram.begin(), mnemonic_histogram.end(),
            [](const mnemonic_counter &l, const mnemonic_counter &r) {
              if (l.second != r.second)
                return l.second > r.second;

              return l.first > r.first;
            });

  // print the vector
  for (int i = 0; i < 30; i++) {
    std::cout << std::left << std::setw(10) << mnemonic_histogram[i].first << ": " << mnemonic_histogram[i].second << std::endl;
  }
}

int main(int argc, char *argv[]) {
  if (PIN_Init(argc, argv)) {
    return 1;
  }

  INS_AddInstrumentFunction(instrumentInstruction, 0);

  PIN_AddFiniFunction(fini, 0);

  PIN_StartProgram();

  return 0;
}
