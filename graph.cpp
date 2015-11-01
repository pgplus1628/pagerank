#include <glog/logging.h>
#include <gflags/gflags.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

#include "graph.hpp"
#include "order.hpp"

Graph::Graph() {}

void Graph::load(std::string fname) {
  LOG(INFO) << "Graph::loading graph : " << fname;
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


  // construct Luid2id
  LUid2id.resize(Uid2id.size());
  for(auto kv : Uid2id) {
    LUid2id[kv.second] = kv.first;
  }
  ifs.close();
}

size_t Graph::get_n_vertices() {
  return Uid2id.size();
}

size_t Graph::get_n_edges() {
  return edges.size();
}

void Graph::sort_edges(std::string order) {

  if (order == HILBERT) {
    VidType nv = (VidType)get_n_vertices();
    LOG(INFO) << " Graph::nv = " << nv;
    VidType max_n = 2;
    while ( nv >>=1 ) {
      max_n <<= 1;
    }

    LOG(INFO) << " HilbertOrder::max_n = " << max_n;
    HilbertOrder::set_maxn(max_n);
    //HilbertOrder::set_maxn(MAX_BIT);

    //std::sort(edges.begin(), edges.end(), HilbertOrder());
    // get permutation
    
    size_t ne = edges.size();
    std::vector<int64_t> d(ne);
    for(size_t i = 0;i < ne;i ++) {
      d[i] = HilbertOrder::get_d(edges[i].src, edges[i].dst);
    }

    std::vector<size_t> perm(ne);
    for(size_t i = 0;i < ne;i ++) {
      perm[i] = i;
    }

    std::sort(perm.begin(), perm.end(), 
              [&](const size_t & A, const size_t &B) {
                return d[A] < d[B];
              });

    d.resize(0);
    // sort
    size_t flag = 0;
    size_t cnt = 0;

    std::vector<Edge> edge_copy(edges);
    for(size_t i = 0;i < ne;i ++) {
      edges[i] = edge_copy[perm[i]];  
    }
    edge_copy.resize(0);

  } else if (order == DST ) {
    std::sort(edges.begin(), edges.end(), DstOrder());

  } else if (order == SRC ){
    std::sort(edges.begin(), edges.end(), SrcOrder());

  } else {
    LOG(FATAL) << " Invalid order ." ;
  }
}

void Graph::dump_edges(std::string fname)
{
  std::ofstream ofs(fname.c_str(), std::ios_base::out | std::ios_base::binary);

  for( auto & e : edges) {
    ofs << e.src << "\t" << e.dst <<"\n";
  }

  ofs.close();
  LOG(INFO) << "Graph::dump edges to file " << fname << " OK.";
}
