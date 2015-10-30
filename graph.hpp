#pragma once

#include <glog/logging.h>
#include <gflags/gflags.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

/*
 * simple graph structure storage
 */
typedef uint32_t VidType;
typedef uint32_t VidType;

struct Edge {
  VidType src;
  VidType dst;
  Edge(VidType _src, VidType _dst) : src(_src), dst(_dst) {}
};
typedef struct Edge Edge;


#include "order.hpp"

class Graph {
  public :
  std::vector<Edge> edges;
  std::unordered_map<VidType, VidType> Uid2id;

  Graph() {
  }

  void load(std::string fname) {
    std::ifstream ifs(fname.c_str(), std::ios_base::in | std::ios_base::binary);
    std::string line;
    if (!ifs.good()) {
      LOG(FATAL) << "Error opning file " << fname << ".";
    }

    std::unordered_map<VidType, VidType>::iterator it;

    while(std::getline(ifs, line) ) {
      if (line[0] == '#') {
        LOG(INFO) << line;
        continue ;
      }
      std::stringstream ss(line);
      VidType src, dst;
      ss >> src >> dst;
      VidType tmp;
      /* convert to lvid */
      it = Uid2id.find(src);
      if (it == Uid2id.end() ) {
        tmp = Uid2id.size();
        Uid2id[src] = tmp;
        src = tmp;
      } else {
        src = it->second;
      }

      it = Uid2id.find(dst);
      if (it == Uid2id.end() ) {
        tmp = Uid2id.size();
        Uid2id[dst] = tmp;
        dst = tmp;
      } else {
        dst = it->second;
      }
      edges.emplace_back(src, dst);
    }
    LOG(INFO) << " Load graph fininshed. Number of edges : " << edges.size() << ".";
    ifs.close();
  }

  void sort_edges(std::string order) {

    if (order == HILBERT) {
      std::sort(edges.begin(), edges.end(), HilbertOrder());

    } else if (order == DST ) {
      std::sort(edges.begin(), edges.end(), DstOrder());

    } else if (order == SRC ){
      std::sort(edges.begin(), edges.end(), SrcOrder());

    } else {
      LOG(FATAL) << " Invalid order ." ;
    }
  }

  size_t get_n_vertices() {
    return Uid2id.size();
  }
};
