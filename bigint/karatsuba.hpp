#include "BasecaseMultiply.hpp"
#include "addition_and_subtraction.hpp"
#include "bigint.hpp"

inline size_t karatsuba_threshold = 10;

inline bigint mod_with_basePower_k(const bigint &a, size_t k) {
  bigint c(a.get_digits()[0]);
  for (int i = 1; i < k; i++) {
    c.get_digit().push_back(a.get_digits()[k]);
  }
  return c;
}

inline bigint div_with_basePower_k(const bigint &a, size_t k) {
  bigint c(a.get_digits()[k]);
  for (int i = k + 1; i < a.get_digits().size(); i++) {
    c.get_digit().push_back(a.get_digits()[k]);
  }
  return c;
}

inline bigint multiply_karatsuba(const bigint &a, const bigint &b) {
  size_t l = std::max(a.get_digits().size(), b.get_digits().size());
  if (l < karatsuba_threshold)
    return multiply_naive(a, b);

  size_t k = l / 2;

  bigint a0 = mod_with_basePower_k(a, k);
  bigint b0 = mod_with_basePower_k(b, k);

  bigint a1 = div_with_basePower_k(a, k);
  bigint b1 = div_with_basePower_k(b, k);

  bigint c0 = multiply_karatsuba(a0, b0);
  bigint c1 = multiply_karatsuba(a1, b1);
  bigint c2 = multiply_karatsuba(subtract(a1, a0), subtract(b1, b0));

  bigint c3 = add(c0, c1);
  c3 = subtract(c3, c2);
  c3 = shift(c3, k);

  bigint c4 = shift(c1, 2 * k);
  c4 = add(c3, c4);
  c4 = add(c4, c0);

  return c4;
}
