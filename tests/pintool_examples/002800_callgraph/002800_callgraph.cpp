#include "pin.H"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <map>

FILE * fp;

struct GraphNode {
  std::string name;
  std::map<std::string, int> edges;
  bool visited;
};

class Graph {
  private:
    std::map<std::string, GraphNode> nodes;

    void ResetVisited(){
      for(std::map<std::string, GraphNode>::iterator it = nodes.begin(); it != nodes.end(); it++){
        it->second.visited = false;
      }
    }
    void CallgraphHelper(FILE* f, std::string nodeName){
      if(nodes[nodeName].visited) {
        return;
      }
      nodes[nodeName].visited = true;
      for(std::map<std::string, int>::iterator it = nodes[nodeName].edges.begin(); it != nodes[nodeName].edges.end(); it++){
        fprintf(fp, " \"%s\" -> \"%s\" [label=%u]\n", nodeName.c_str(), it->first.c_str(), it->second);
        CallgraphHelper(f, it->first);
      }
    }

    bool ValidName(string& name){
      if (name.size() > 0 && name[0] != '.'){
        return true;
      } else {
        return false;
      }
    }

  public:
    void AddNodeIfNecessary(std::string& name){
      if(nodes.find(name) == nodes.end()){
        GraphNode gn;
        gn.name = name;
        nodes.insert(std::make_pair(name, gn));
      }
    }
    
    void AddEdge(std::string& source, std::string& target){
      if( !ValidName(source) || !ValidName(target)) {
        return;
      }
      AddNodeIfNecessary(source);
      AddNodeIfNecessary(target);
      GraphNode &s = nodes[source];
      if(s.edges.find(target) == s.edges.end()){
        // create new edge
        s.edges.insert(std::make_pair(target, 1));
      } else {
        // increment existing edge;
        s.edges[target] ++;
      }
    }


    void GenerateCallgraph(FILE* f){
      fprintf(f, "digraph callgraph {\n");

      ResetVisited();
      CallgraphHelper(f, "main");

      fprintf(f, "}\n");

    }
};

Graph graph;


VOID createEdge(ADDRINT callerAddr, ADDRINT calleeAddr ){
  std::string callerName = RTN_FindNameByAddress(callerAddr);
  std::string calleeName = RTN_FindNameByAddress(calleeAddr);
  graph.AddEdge(callerName, calleeName);
}

VOID instrumentInstruction(INS ins, VOID *v) {

  if(INS_IsDirectBranchOrCall(ins)){
    ADDRINT ins_addr = INS_Address(ins);
    ADDRINT target_addr = INS_DirectBranchOrCallTargetAddress(ins);

    IMG ins_img = IMG_FindByAddress(ins_addr);
    IMG target_img = IMG_FindByAddress(target_addr);
    if(IMG_Valid(ins_img) && IMG_Valid(target_img) && IMG_IsMainExecutable(ins_img) && IMG_IsMainExecutable(target_img)){
      INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)createEdge, IARG_ADDRINT, ins_addr, IARG_ADDRINT, target_addr, IARG_END);
    }
  }
}

VOID fini(INT32 code, VOID *v) {
  fp = fopen ("./callgraph.dot","w");
  graph.GenerateCallgraph(fp);
  fclose (fp);
}

int main(int argc, char *argv[]) {
  if (PIN_Init(argc, argv)) {
    return 1;
  }


  PIN_InitSymbols();

  INS_AddInstrumentFunction(instrumentInstruction, 0);

  PIN_AddFiniFunction(fini, 0);

  PIN_StartProgram();

  return 0;
}
