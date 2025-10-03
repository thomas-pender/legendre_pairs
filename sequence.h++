# ifndef INCLUDED_SEQUENCES_HPP
# define INCLUDED_SEQUENCES_HPP

# include <iostream>
# include <vector>

# define ERR 0.00005

using seq = std::vector<int>;
using psdseq = std::vector<double>;

struct sequence_t
{
  friend std::ostream& operator<<(std::ostream& os, sequence_t const& s)
  {
    for ( auto x : s.a ) os << x << " ";
    os << '\n';
    return os;
  }

  friend std::istream& operator>>(std::istream& is, sequence_t& s)
  {
    for ( auto& x : s.a ) is >> x;
    for ( auto& x : s.psd ) is >> x;
    return is;
  }

  friend auto operator<=>(sequence_t const& s1, sequence_t const& s2)
  {
    return s1.psd <=> s2.psd;
  }

  int& operator[](std::size_t i) & {return a[i];}
  int const& operator[](std::size_t i) const& {return a[i];}
  int operator[](std::size_t i) && {return std::move(a[i]);}

  sequence_t& operator=(sequence_t const&) & = default;
  sequence_t& operator=(sequence_t &&) & noexcept = default;

  sequence_t() = default;
  sequence_t(sequence_t const&) = default;
  sequence_t(sequence_t &&) noexcept = default;

  explicit sequence_t(unsigned _n)
    : n{_n}, bound{(_n << 2U) + 4U}, a(_n), psd(_n >> 1U)
  {}

  ~sequence_t() = default;

  unsigned n, bound;
  seq a{};
  psdseq psd{};
};

static inline
void pr(sequence_t const& s1, sequence_t const& s2,
        sequence_t const& s3, sequence_t const& s4)
{
  std::cout << s1 << s2 << s3 << s4 << '\n' << std::flush;
}

static inline
bool check_bound(sequence_t const& s1, sequence_t const& s2)
{
  for ( std::size_t i{0}; i < s1.psd.size(); i++ )
    if ( s1.psd[i] + s2.psd[i] > s1.bound + ERR ) return false;
  return true;
}

# endif
