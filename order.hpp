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
  bool operator() (const Edge& e1, const Edge& e2) const {
    if (e1.src != e2.src) return e1.src < e2.src;
    else return e1.dst < e2.dst;
  }
};
typedef struct SrcOrder SrcOrder;


struct DstOrder : OrderBase {
  bool operator()(const Edge& e1, const Edge& e2) const {
    if (e1.dst != e2.dst) return e1.dst < e2.dst;
    else return e1.src < e2.src;
  }
};
typedef struct DstOrder DstOrder;


struct HilbertOrder : OrderBase {
  // Rotate/flip a quadrant appropriately
  static void rot(VidType n, VidType *x, VidType *y, VidType rx, VidType ry) {
    if (ry == 0) {
      if (rx == 1) {
        *x = n-1 - *x;
        *y = n-1 - *y;
      }
      // Swap x and y
      VidType t  = *x;
      *x = *y;
      *y = t;
    }
  }

  // Convert the index (from, to) to Hilbert order
  VidType get_d(VidType from ,VidType to) const {
    VidType x = from, y = to, rx, ry, d = 0;
    for(VidType s = MAX_BIT; s > 0; s /= 2) {
      rx = (x & s) > 0;
      ry = (y & s) > 0;
      d += s * s * ((3 * rx) ^ ry);
      rot(s, &x, &y, rx, ry);
    }
    return d;
  }

  bool operator() (const Edge& e1, const Edge& e2) const {
    return get_d(e1.src, e1.dst) < get_d(e2.src, e2.dst);
  }
};
typedef struct HilbertOrder HilbertOrder;
