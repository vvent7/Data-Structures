#ifndef PQUEUES_H
#define PQUEUES_H

#include "container/kdc_vector_unordered.h"
#include "pred_list/pred_list_data.h"
#include "veb/veb_data/veb_data.h"
#include "pred_bitset/pred_bitset_data.h"
#include "pred_bintree/pred_bintree_data.h"
#include "circular.h"

namespace spp{
  
  using pqueue_bintree_t = pred_bintree::Data;
  using pqueue_pred_list_t = pred_list::Data<kdc_vector_unordered>;
  using pqueue_pred_bitset_t = Circular<pred_bitset::Data<kdc_vector_unordered>>;
  using pqueue_veb_t = Circular<veb::Data<kdc_vector_unordered>>;

}

#endif