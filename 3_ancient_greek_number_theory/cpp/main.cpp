template <typename NaturalNumber>
constexpr static auto triangle_number_dumb(NaturalNumber index) {
  NaturalNumber sum = 0;
  for (auto i = index; i > 0; i--) {
    sum += i;
  }
  return sum;
}

template <typename NaturalNumber>
constexpr static auto triangle_number_normal(NaturalNumber index) {
  return (index * (index + 1)) >> 1;
}

static_assert(triangle_number_dumb(1) == 1);
static_assert(triangle_number_dumb(2) == 3);
static_assert(triangle_number_dumb(3) == 6);
static_assert(triangle_number_dumb(6) == 21);

// not sure i love this testing
template <typename Callback> constexpr bool test(Callback fn) {
  static_assert(fn(1) == 1);
  static_assert(fn(2) == 3);
  static_assert(fn(3) == 6);
  static_assert(fn(6) == 21);
  return true;
}

static_assert(test([](auto i) { return triangle_number_dumb(i); }));
static_assert(test([](auto i) { return triangle_number_normal(i); }));

template <typename NaturalNumber>
constexpr static auto oblong_number(NaturalNumber index) {
  return 2 * triangle_number_normal(index);
}

template <typename NaturalNumber>
constexpr static auto gnomon(NaturalNumber index) {
  return index + (index - 1);
}

static_assert(gnomon(1) == 1);
static_assert(gnomon(6) == 11);

static_assert(oblong_number(1) == 2);
static_assert(oblong_number(6) == 42);

int main() {
  return 0;
}
