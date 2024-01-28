#ifndef ENV_H
#define ENV_H

namespace env{
  using key_real_t = unsigned long long;
  using key_bit_t = unsigned int;
  using data_t = unsigned int;

  extern const key_real_t NIL_KEY_REAL;
  extern const key_bit_t NIL_KEY_BIT;
  extern const data_t NIL_DATA; 
}

#endif