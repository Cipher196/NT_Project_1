// multiplication.hpp
#pragma once

#include "addition_and_subtraction.hpp"

inline bigint shift(const bigint &a, size_t i) {
  bigint c(vector<uint64_t>(a.get_digits().size() + i, 0), true);
  for (int j = 0; j < a.get_digits().size(); j++) {
    c.at(i + j, a.get_digits()[j]);
  }
  return c;
}

inline bigint scalar_multiply(const bigint &a, unsigned __int128 b) {
  unsigned __int128 d = 0;
  bigint c(a.get_digits(), true);
  for (int i = 0; i < a.get_digits().size(); i++) {
    d += a.get_digits()[i] * b;
    c.at(i, (uint64_t)d);
    d = d >> 64;
  }
  if (d > 0)
    c.get_digit().push_back(d);
  return c;
}

inline bigint shift_add(const bigint &c, const bigint &a, size_t i,
                        uint64_t bi) {
  bigint b = scalar_multiply(a, bi);
  bigint d = shift(b,i);
  bigint e = add(c,d);
  return e;
}

inline bigint multiply_naive(const bigint &a, const bigint &b) {
  bigint c(0);
  c = scalar_multiply(a, b.get_digits()[0]);
  for (int i = 1; i < b.get_digits().size(); i++) {
    c = shift_add(c, a, i, b.get_digits()[i]);
  }
  if(a.ip()^b.ip()) c.flipSign();
  return c;
}
