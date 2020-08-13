#include "pin.H"
#include <iostream>
#include <iomanip>      
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

//map<ADDRINT, string> addr2disassemble;

vector<uint>   ins_histogram;
vector<string> ins_names;

VOID build_histogram(UINT32 index){
	ins_histogram[index] ++;
}


VOID Instruction(INS ins, VOID *v)
{
  ADDRINT ins_addr = INS_Address(ins);
  string ins_str = INS_Disassemble(ins);
  string ins_name = ins_str.substr(0, ins_str.find(' '));
  int ins_index;

  auto iterator = std::find(ins_names.begin(), ins_names.end(), ins_name);
   if(iterator == ins_names.end()){
	ins_index = ins_names.size();
	ins_names.push_back(ins_name);	
	ins_histogram.push_back(0);
   } else {
        ins_index = std::distance(ins_names.begin(), iterator);    
   }

  INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)build_histogram, IARG_UINT32, ins_index, IARG_END);

}

VOID Fini(INT32 code, VOID *v)
{
  cout << "========================" << endl;
  vector<pair<string, int>> hist;

  for(int i = 0; i <  ins_names.size(); i++){
	  //cout << left << setw(6) << ins_names[i] << ":  " << ins_histogram[i]  << endl;
	  hist.push_back(pair<string, int>(ins_names[i], ins_histogram[i]));
  }
  std::sort(hist.begin(), hist.end(), [](auto &left, auto &right) { return left.second > right.second; });
  for(int i = 0; i <  ins_names.size(); i++){
	  cout << left << setw(6) << hist[i].first << ":  " << hist[i].second  << endl;
	  //hist.push_back(pair<string, int>(ins_names[i], ins_histogram[i]));
  }

}



int main(int argc, char *argv[])
{
    if( PIN_Init(argc,argv) )
    {
        cout << "initialization invalid" << endl;
    }

    INS_AddInstrumentFunction(Instruction, 0);

    PIN_AddFiniFunction(Fini, 0);


    PIN_StartProgram();

    return 0;
}

