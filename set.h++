# ifndef INCLUDED_SET_HPP
# define INCLUDED_SET_HPP

# include <iostream>
# include <vector>

using seq = std::vector<int>;
using seqs = std::vector<seq>;
using perm = std::vector<unsigned>;

static
std::istream& operator>>(std::istream& is, seq& s)
{
  for ( auto& x : s ) is >> x;
  return is;
}

static
std::ostream& operator<<(std::ostream& os, seq const& s)
{
  for ( auto & x : s ) os << x << " ";
  return os;
}

struct set_t
{
  friend
  std::istream& operator>>(std::istream& is, set_t& S)
  {
    for ( auto& x : S.s ) is >> x;

    S.r = S.s;
    for ( auto& x : S.r ) std::reverse(x.begin(), x.end());

    return is;
  }

  friend
  std::ostream& operator<<(std::ostream& os, set_t const& S)
  {
    for ( auto const& x : S.s ) os << x << '\n';
    return os;
  }

  void apply_perm(perm const& p)
  {
    seqs S(4);
    S[0] = std::move(s[p[0]]);
    S[1] = std::move(s[p[1]]);
    S[2] = std::move(s[p[2]]);
    S[3] = std::move(s[p[3]]);
    s = std::move(S);
  }

  void negate()
  {
    for ( auto& x : s[0] ) x = -x;
    for ( auto& x : r[0] ) x = -x;
  }

  void rev01()
  {
    s[3] = std::move(r[2]);
  }

  void rev10()
  {
    s[1] = std::move(r[0]);
  }

  void rev11()
  {
    s[1] = std::move(r[0]);
    s[3] = std::move(r[2]);
  }

  void amicable();

  seq& operator[](std::size_t i) & {return s[i];}
  seq const& operator[](std::size_t i) const& {return s[i];}
  seq operator[](std::size_t i) && {return std::move(s[i]);}

  set_t& operator=(set_t const&) & = default;
  set_t& operator=(set_t &&) & noexcept = default;

  set_t() = default;
  set_t(set_t const&) = default;
  set_t(set_t &&) noexcept = default;

  explicit set_t(unsigned _n)
    : n{_n}, s(4, seq(n))
  {}

  ~set_t() = default;

  unsigned n{};
  seqs s{}, r{};
};

# endif
