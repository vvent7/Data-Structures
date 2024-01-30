#ifndef ENV_H
#define ENV_H

namespace env{
  using key_real_t = unsigned long long;
  using key_bit_t = unsigned int;
  using data_t = unsigned int;

  static constexpr key_real_t NIL_KEY_REAL = -1;
  static constexpr key_bit_t NIL_KEY_BIT = -1;
  static constexpr data_t NIL_DATA = -1;
}

#endif