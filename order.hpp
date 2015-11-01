#pragma once

#define HILBERT "hilbert"
#define DST  "dst"
#define SRC  "src"
#define MAX_BIT (1<<30)

#include "graph.hpp"


struct OrderBase {
  virtual bool operator() (const Edge& e1, const Edge& e2) const = 0;
};

struct SrcOrder : OrderBase {
  bool operator() (const Edge& e1, const Edge& e2) const ;
};
typedef struct SrcOrder SrcOrder;


struct DstOrder : OrderBase {
  bool operator()(const Edge& e1, const Edge& e2) const ;
};
typedef struct DstOrder DstOrder;


struct HilbertOrder : OrderBase {

  static VidType max_n ;

  static void set_maxn(VidType val) ;

  //rotate/flip a quadrant appropriately
  static void rot(int64_t n, VidType *x, VidType *y, VidType rx, VidType ry) ;

  // convert (x,y) to d
  static int64_t get_d (VidType x, VidType y) ;

  bool operator() (const Edge& e1, const Edge& e2) const ;
};
typedef struct HilbertOrder HilbertOrder;





