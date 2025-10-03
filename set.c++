# include <algorithm>

# include <set.h++>

static
std::vector<perm> P{
  {0,1,2,3},{0,2,1,3},{0,3,1,2},
};

static inline
int cross_corr(int j, seq const& s1, seq const& s2)
{
  int sum{0};
  int J{};
  for ( int i{0}; i < s1.size(); i++ ) {
    J = i - j;
    J = (J < 0 ? s1.size() + J : J);
    sum += s1[i] * s2[J];
  }
  return sum;
}

static inline
seq cross_corrs(seq const& s1, seq const& s2)
{
  seq corrs(s1.size());
  for ( int j{0}; j < s1.size(); j++ ) corrs[j] = cross_corr(j, s1, s2);
  return corrs;
}

static
seqs rotations(seq const& s)
{
  seqs S(s.size(), seq(s.size()));

  std::size_t i{}, j{}, J{};
  for ( i = 0; i < s.size(); i++ )
    for ( j = 0; j < s.size(); j++ ) {
      J = j + i;
      J = (J < s.size() ? J : J - s.size());
      S[i][j] = s[J];
    }

  seqs T(s.size(), seq(s.size() / 2));
  for ( i = 0; i < s.size(); i++ )
    for ( j = 1; j < T[i].size(); j++ )
      T[i][j] = S[i][j] - S[i][s.size() - j];

  return T;
}

static
bool _amicable(set_t& s, perm const& p)
{
  seqs corrs1{rotations(cross_corrs(s[p[0]], s[p[1]]))};
  seqs corrs2{rotations(cross_corrs(s[p[2]], s[p[3]]))};

  bool flag{}, neg{};
  std::size_t i1{}, i2{}, j{};
  for ( i1 = 0; i1 < corrs1.size(); i1++ )
    for ( i2 = 0; i2 < corrs2.size(); i2++ ) {
      flag = true;
      neg = true;
      for ( j = 0; j < corrs1[0].size(); j++ ) {
        if ( corrs1[i1][j] + corrs2[i2][j] != 0 ) flag = false;
        if ( -corrs1[i1][j] + corrs2[i2][j] != 0 ) neg = false;
        if ( !flag && !neg ) break;
      }
      if ( flag ) {
        s.apply_perm(p);
        std::rotate(s[1].rbegin(), s[1].rbegin() + i1, s[1].rend());
        std::rotate(s[3].rbegin(), s[3].rbegin() + i2, s[3].rend());
        std::cout << s << '\n';

        neg = false;
        return true;
      }
      if ( neg ) {
        s.apply_perm(p);
        s.negate();
        std::rotate(s[1].rbegin(), s[1].rbegin() + i1, s[1].rend());
        std::rotate(s[3].rbegin(), s[3].rbegin() + i2, s[3].rend());
        std::cout << s << '\n';

        return true;
      }
    }

  return false;
}

void set_t::amicable()
{
  // for ( auto const& p : P )
  //   if ( _amicable(*this, p) ) return;

  for ( auto const& p : P ) {
    seq tmp{s[p[3]]};
    std::reverse(s[p[3]].begin(), s[p[3]].end());
    if ( _amicable(*this, p) ) return;
    s[p[3]] = std::move(tmp);
  }

  for ( auto const& p : P ) {
    seq tmp{s[p[1]]};
    std::reverse(s[p[1]].begin(), s[p[1]].end());
    if ( _amicable(*this, p) ) return;
    s[p[1]] = std::move(tmp);
  }

  for ( auto const& p : P ) {
    seq tmp1{s[p[1]]};
    seq tmp2{s[p[3]]};
    std::reverse(s[p[1]].begin(), s[p[1]].end());
    std::reverse(s[p[3]].begin(), s[p[3]].end());
    if ( _amicable(*this, p) ) return;
    s[p[1]] = std::move(tmp1);
    s[p[3]] = std::move(tmp2);
  }

  return;
}
