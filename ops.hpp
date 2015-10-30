#pragma once

#include <functional>
#include <glog/logging.h>
#include <fstream>
#include "graph.hpp"



template<typename VT>
void unary_apply(std::vector<VT> &vec, std::function<void(VT&)> app_op)
{
  for(auto &a : vec) {
    app_op(a);
  }
}

template<typename VT1, typename VT2>
void binary_apply(std::vector<VT1> &vec1, std::vector<VT2> &vec2, std::function<void(VT1&, VT2&)> app_op)
{
  CHECK_EQ(vec1.size(), vec2.size()) << " vec1 and vec2 should be equal size.";
  for(size_t i = 0;i < vec1.size();i ++) {
    app_op(vec1[i], vec2[i]);
  }
}

template<typename VT1, typename VT2, typename VT3>
void ternary_apply(std::vector<VT1> &vec1, std::vector<VT2> &vec2, std::vector<VT3> &vec3,
    std::function<void(VT1&, VT2&, VT3&)> app_op)
{
  CHECK_EQ(vec1.size(), vec2.size()) << " vec1 and vec2 should be equal size.";
  CHECK_EQ(vec1.size(), vec3.size()) << " vec1 and vec3 should be equal size.";
  for(size_t i = 0;i < vec1.size();i ++) {
    app_op(vec1[i], vec2[i], vec3[i]);
  }
}

template<typename VT>
void dump_vec(Graph &g, std::string fname, std::vector<VT> &vec) {
  std::ofstream ofs(fname.c_str(), std::ios_base::out | std::ios_base::binary);
  auto &lid2id = g.LUid2id;
  for(size_t i = 0;i < vec.size();i ++) {
    ofs  << lid2id[i] << "\t" << vec[i] << "\n";
  }
  ofs.close();
}




// --------------------------------------------------------------------/
// Graph ops
// --------------------------------------------------------------------/

template<typename VT>
void graph_reduce_src(Graph &g, std::vector<VT> &result, std::function<void(VT&)> red_op)
{
  for(auto &e : g.edges) {
    red_op(result[e.src]);
  }
}

template<typename VT>
void graph_reduce_dst(Graph &g, std::vector<VT> &result, std::function<void(VT&)> red_op)
{
  for(auto &e : g.edges) {
    red_op(result[e.dst]);
  }
}

template<typename SRCVT, typename DSTVT>
void graph_edge_apply(Graph &g, std::vector<SRCVT> &src_vec, std::vector<DSTVT> &dst_vec,
  std::function<void(SRCVT&, DSTVT&)> app_op)
{
  for(auto &e : g.edges) {
    app_op(src_vec[e.src], dst_vec[e.dst]);
  }
}
