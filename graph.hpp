#pragma once
#include <stdint.h>
#include <unordered_map>
#include <vector>

/*
 * simple graph structure storage
 */
typedef uint32_t VidType;

struct Edge {
  VidType src;
  VidType dst;
  Edge(){ }
  Edge(VidType _src, VidType _dst) : src(_src), dst(_dst) {}
};
typedef struct Edge Edge;



class Graph {
  public :
  std::vector<Edge> edges;
  std::unordered_map<VidType, VidType> Uid2id;
  std::vector<VidType> LUid2id;

  Graph() ;

  void load(std::string fname) ;
  size_t get_n_vertices() ;
  size_t get_n_edges() ;

  void sort_edges(std::string order) ;
  void dump_edges(std::string fname);
};
