// 2.1
// Excercise 2.1
#include <iostream>

// this feels pretty neat
template <typename T> constexpr T multiply_by_10(T a) {
  auto b = a + a + a; // 3
  auto c = b + b;     // 6
  auto d = c + b + a; // 10
  return d;
}

static_assert(multiply_by_10(2) == 20);
static_assert(multiply_by_10(4) == 40);
static_assert(multiply_by_10(300.0f) == 3000.0f);

// no idea if this is optimal lol
template <typename T> constexpr T multiply_by_71(T a) {
  auto b = a + a + a; // 3
  auto c = b + b;     // 6
  auto d = c + c;     // 12
  auto e = d + d;     // 24
  auto f = e + e;     // 48
  auto g = f + d;     // 60
  auto h = g + c + b + a + a;
  return h;
}

static_assert(multiply_by_71(1) == 71);
static_assert(multiply_by_71(2) == 142);
static_assert(multiply_by_71(3) == 213);

// 2.2
template <typename T> constexpr auto half(T a) { return a >> 1; }
template <typename T> constexpr bool is_even(T a) { return (a & T{0x1}) == 0; }
template <typename T> constexpr bool is_odd(T a) { return !is_even(a); }

static_assert(half<int>(2) == 1);
static_assert(half<size_t>(4) == 2);
static_assert(half(3478) == 1739);

static_assert(is_odd<int>(9), "9 is odd");
static_assert(is_even<char>(8), "8 is even");
static_assert(is_odd(700000000000000001), "this big number is odd");

// This is an ancient egypitian multiplication algorithm

/*
 * r is the 'returning result'
 * we are calculating the product of n and a
 */
template <typename T> constexpr auto mult_acc1(T r, T n, T a) {
  if (n == 1) {
    return r + a;
  }
  if (is_odd(n)) {
    r = r + a;
  }
  return mult_acc1(r, half(n), a + a);
}

/*
 * r is the 'returning result'
 * we are calculating the product of n and a
 */
template <typename T> constexpr auto mult_acc2(T r, T n, T a) {
  if (is_odd(n)) {
    if (n == 1) {
      return r + a;
    }
    r = r + a;
  }
  return mult_acc2(r, half(n), a + a);
}

template <typename T> constexpr auto mult_acc3(T r, T n, T a) {
  if (is_odd(n)) {
    r = r + a;
    if (n == 1) {
      return r;
    }
  }
  n = half(n);
  a = a + a;
  return mult_acc3<T>(r, n, a);
}

template <typename T> constexpr auto mult_acc4(T r, T n, T a) {
  for (;;) {
    if (is_odd(n)) {
      r = r + a;
      if (n == 1) {
        return r;
      }
    }
    n = half(n);
    a = a + a;
  }
}
static_assert(mult_acc1(0, 3, 4) == 12);

template <typename T> constexpr T multiply(T n, T a) {
  return mult_acc1(0, n, a);
}

template <typename T> constexpr T exp_acc(T r, T a, T n) {
  for (;;) {
    if (is_odd(n)) {
      r = multiply(r, a);
      if (n == 1) {
        return r;
      }
    }
    n = half(n);
    a = multiply(a, a);
  }
}


static_assert(exp_acc(1, 4, 3) == 64);
static_assert(exp_acc(1, 4, 2) == 16);
static_assert(exp_acc(1, 3, 3) == 27);
static_assert(exp_acc(1, 4, 4) == 256);
static_assert(exp_acc(1, 5, 5) == 3125);

/**

  r = 2, n = 2, a = 1
  since n is is_odd
    r = 4          // r + a
  do not enter, n ==



*/

template <typename T> constexpr T mult_acc5(T r, T n, T a) {
  static_assert(std::is_integral<T>::value, "T must be integral");
  for (;;) {
    if (is_odd(n)) {
      r = r + a;
      if (n == 1) {
        return r;
      }
    }
    n = half(n);
    a = a + a;
  }
}

template <typename T> constexpr T multiply1(T n, T a) {
  if (n == 1) {
    return a;
  }
  return mult_acc5<T>(a, n - 1, a);
}

template <typename T> constexpr T multiply2(T n, T a) {
  while (is_even(n)) {
    a = a + a;
    n = half(n);
  }
  if (n == 1) {
    return a;
  }
  return mult_acc5<T>(a, n - 1, a);
}

// not sure i love this testing
template <typename Callback> constexpr bool mul_test(Callback fn) {
  static_assert(fn(2, 3) == 6);
  static_assert(fn(3, 3) == 9);
  static_assert(fn(7, 3) == 21);
  static_assert(fn(4, 3) == 12);
  static_assert(fn(5, 3) == 15);
  static_assert(fn(4, 7) == 28);
  static_assert(fn(5, 7) == 35);
  static_assert(fn(50001, 700) == 35000700);
  return true;
}
static_assert(mul_test([](auto n, auto a) { return mult_acc1(0, n, a); }));
static_assert(mul_test([](auto n, auto a) { return mult_acc2(0, n, a); }));
static_assert(mul_test([](auto n, auto a) { return mult_acc3(0, n, a); }));
static_assert(mul_test([](auto n, auto a) { return mult_acc4(0, n, a); }));
static_assert(mul_test([](auto n, auto a) { return mult_acc5(0, n, a); }));
static_assert(mul_test([](auto n, auto a) { return multiply1(n, a); }));
static_assert(mul_test([](auto n, auto a) { return multiply2(n, a); }));

// some fun, takes ~40 seconds on my machine to run
int main() {
  constexpr int N = 100;
  auto sum = 0;
  std::cout << "starting" << N << std::endl;
  for (int i = 1; i < N; ++i) {
    auto r = multiply1(i, i + 2);
    sum += r;
  }
  std::cout << "sum: " << sum << std::endl;
  return sum;
}
