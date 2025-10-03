# include <iostream>
# include <sstream>
# include <vector>

# include <set.h++>

static inline
int cross_corr(int j, seq const& s1, seq const& s2)
{
  int sum{0};
  int J{};
  for ( std::size_t i{0}; i < s1.size(); i++ ) {
    J = i -j;
    J = (J < 0 ? s1.size() + J : J);
    sum += s1[i] * s2[J];
  }
  return sum;
}

int main(int argc, char *argv[])
{
  if ( argc < 2 ) {
    std::cerr << "USAGE -- ./amicable.out <N>\n" << std::flush;
    return 1;
  }

  unsigned n{};
  {
    std::stringstream ss{argv[1]};
    ss >> n;
  }
  if ( n & 1U ) {
    std::cerr << "ERROR -- <N> must be even\n" << std::flush;
    return 1;
  }

  set_t s{n};
  while ( std::cin >> s ) {
    s.amicable();
  }

  return 0;
}
