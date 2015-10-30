#include "graph.hpp"
#include "order.hpp"
#include "ops.hpp"
#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(input, "", "input file path.");
DEFINE_string(output, "", "output file path.");
DEFINE_int32(niters, 10, "num iterations.");



class PageRank {
  static constexpr double DAMPING_FACTOR = 0.85;

  public :
  // --------------/
  // Comp State
  // --------------/
  std::vector<double> rank_vec;
  std::vector<double> lab_vec;
  std::vector<double> update_vec;
  std::vector<size_t> odeg_vec;
  size_t nv;
  Graph &graph;

  // -------------/
  // UDF
  // -------------/
  static void reset_rank(double& r) {
    r = 0.0;
  }

  static void reset_update(double &r) {
    r = 0.0;
  }

  static void reset_odeg(size_t &d) {
    d = 0;
  }

  static void gen_deg(size_t &d) {
    d += 1;
  }

  static void gen_lab(double &lab, size_t &d) {
    if (d == 0) {
      lab = 0.0;
    } else {
      lab = 1.0 / (double)d;
    }
  }

  static void gen_update(double &update, double &rank, double &lab) {
    update = rank * lab;
  }

  /*
   * update : src
   * rank : dst
   */
  static void acc_update(double &update, double &rank) {
    rank += update;
  }

  static void update(double &rank) {
    rank = 1.0 - DAMPING_FACTOR + DAMPING_FACTOR * (rank);
  }


  // --------------/
  // For Benchmark
  // --------------/
  PageRank(Graph &g) : graph(g)
  {
    nv = graph.get_n_vertices();
    // init degree
    odeg_vec.resize(nv);
    lab_vec.resize(nv);
    unary_apply<size_t>(odeg_vec, reset_odeg);
    graph_reduce_src<size_t>(g, odeg_vec, gen_deg);
    binary_apply<double, size_t>(lab_vec, odeg_vec, gen_lab);
  }

  /*
   * reset computation State
   */
  void reset_state()
  {
    rank_vec.resize(nv);
    update_vec.resize(nv);
    // init vec
    unary_apply<double>(rank_vec, reset_rank);
    unary_apply<double>(update_vec, reset_update);
  }

  void do_pagerank()
  {
    for(size_t it = 0; it < FLAGS_niters; it ++) {
      // gen contrib
      ternary_apply<double, double, double>(update_vec, rank_vec, lab_vec, gen_update);

      // clean rank vec
      unary_apply<double>(rank_vec, reset_rank);

      // edge apply
      graph_edge_apply<double, double>(graph, update_vec, rank_vec, acc_update);

      // update rank
      unary_apply<double>(rank_vec, update);

      LOG(INFO) << " == iter " << it << "  ==";
    }

    dump_vec<double>(FLAGS_output, rank_vec);
  }

  /*
   * bench
   */
  void do_bench(std::string order) {
    LOG(INFO) << "========================================";
    LOG(INFO) << "\nPagerank::" << order << " bench Begin.\n";
    // resort graph
    graph.sort_edges(order);
    // reset state
    reset_state();
    // do PageRank
    do_pagerank();
    LOG(INFO) << "\nPagerank::" << order << " benced OK.\n";
  }


};



int main(int argc, char ** argv) {
  google::ParseCommandLineFlags(&argc, &argv, false);
  google::InitGoogleLogging(argv[0]);

  /* init graph */
  Graph *graph = new Graph();
  graph->load(FLAGS_input);

  /* bench order */
  PageRank pagerank(*graph);

  pagerank.do_bench(HILBERT);
  pagerank.do_bench(SRC);
  pagerank.do_bench(DST);

  delete graph;


  return 0;
}
