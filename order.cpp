#include "order.hpp"
#include "graph.hpp"



bool SrcOrder::operator() (const Edge& e1, const Edge& e2) const {
  if (e1.src != e2.src) return e1.src < e2.src;
  else return e1.dst < e2.dst;
}



bool DstOrder::operator()(const Edge& e1, const Edge& e2) const {
  if (e1.dst != e2.dst) return e1.dst < e2.dst;
  else return e1.src < e2.src;
}


VidType HilbertOrder::max_n;

void HilbertOrder::set_maxn(VidType val) {
  max_n = val;
}

//rotate/flip a quadrant appropriately
void HilbertOrder::rot(int64_t n, VidType *x, VidType *y, VidType rx, VidType ry) {
  if (ry == 0) {
    if (rx == 1) {
      *x = n-1 - *x;
      *y = n-1 - *y;
    }
    // swap x and y
    VidType t  = *x;
    *x = *y;
    *y = t;
  }
}

// convert (x,y) to d
int64_t HilbertOrder::get_d (VidType x, VidType y) {
  VidType rx, ry;
  int64_t s, d=0;
  for (s= max_n/2; s>0; s/=2) {
    rx = (x & s) > 0;
    ry = (y & s) > 0;
    d += s * s * ((3 * rx) ^ ry);
    rot(s, &x, &y, rx, ry);
  }
  return d;
}

bool HilbertOrder::operator() (const Edge& e1, const Edge& e2) const {
  return get_d(e1.src, e1.dst) < get_d(e2.src, e2.dst);
}


