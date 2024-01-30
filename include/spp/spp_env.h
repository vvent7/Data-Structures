#ifndef SPP_ENV_H
#define SPP_ENV_H

#include "env.h"

namespace spp{
  using namespace env;

  using vertex_t = data_t; //vertex==data inside the priority queue
  using edge_t = unsigned long long; //number of edges
  using weight_t = key_bit_t; //maximum edge weight (is indexable)
  using dist_t = key_real_t;

  static constexpr vertex_t NIL_VERTEX = -1;
  static constexpr edge_t NIL_EDGE = -1;
  static constexpr weight_t NIL_WEIGHT = -1;
  static constexpr dist_t NIL_DIST = -1;
  static constexpr dist_t oo = 1e18; //infinity (not reached)
}

#endif