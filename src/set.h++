/**
 * @file set.h++
 * @brief Interface of set_t class.
 *
 * Interface of set_t class. An object of set_t holds 4 complementary sequences and
 * their reversals.
 *
 * @author Thomas Pender
 * @date 10/2025
 * @copyright GNU Public License
 */
# ifndef INCLUDED_SET_HPP
# define INCLUDED_SET_HPP

# include <iostream>
# include <vector>

using seq = std::vector<int>;
using seqs = std::vector<seq>;
using perm = std::vector<unsigned>;

/**
 * @brief Reads in std::vector<int> from std::istream.
 *
 * Reads in std::vector<int> from std::istream.
 *
 * @pre The sequence object is assumed to be allocated and the appropriate size.
 *
 * @param is std::istream object.
 * @param s Sequence being read in.
 * @return std::istream object.
 */
static
std::istream& operator>>(std::istream& is, seq& s)
{
  for ( auto& x : s ) is >> x;
  return is;
}

/**
 * @brief Outputs std::vector<int> to ostream.
 *
 * Outputs std::vector<int> to ostream.
 *
 * @param os std::ostream object.
 * @param s Sequence object being written out.
 * @return std::ostream object.
 */
static
std::ostream& operator<<(std::ostream& os, seq const& s)
{
  for ( auto & x : s ) os << x << " ";
  return os;
}

/**
 * @brief Class to hold 4-set of complementary sequences and their reversals.
 *
 * Class to hold 4-set of complementary sequences and their reversals.
 */
struct set_t
{
  /**
   * @brief Reads set_t object from istream.
   *
   * Reads set_t object from istream.
   *
   * <strong>External Functions Called:</strong>
   * <ul>
   * <li>std::reverse</li>
   * </ul>
   *
   * @pre The set_t object is assumed to be allocated and the appropriate size.
   *
   * @param is std::istream object.
   * @param S set_t object being read in.
   * @return std::istream object.
   */
  friend
  std::istream& operator>>(std::istream& is, set_t& S)
  {
    for ( auto& x : S.s ) is >> x;

    S.r = S.s;
    for ( auto& x : S.r ) std::reverse(x.begin(), x.end());

    return is;
  }

  /**
   * @brief Outputs set_t object to ostream.
   *
   * Outputs set_t object to ostream.
   *
   * @param os std::ostream object.
   * @param Sset_t object being written out.
   * @return os std::ostream object.
   */
  friend
  std::ostream& operator<<(std::ostream& os, set_t const& S)
  {
    for ( auto const& x : S.s ) os << x << '\n';
    return os;
  }

  /**
   * @brief Permutes the elements of the set.
   *
   * Permutes the elements of the set.
   *
   * @pre The set_t object has space allocated to hold at least 4 sequences.
   *
   * @post The first 4 sequences in the set_t object are permuted according to
   * the given permutation.
   *
   * @param p Permutation object (std::vector<unsigned>).
   */
  void apply_perm(perm const& p)
  {
    seqs S(4);
    S[0] = std::move(s[p[0]]);
    S[1] = std::move(s[p[1]]);
    S[2] = std::move(s[p[2]]);
    S[3] = std::move(s[p[3]]);
    s = std::move(S);
  }

  /**
   * @brief Negates the first sequence of the set.
   *
   * Negates the first sequence of the set.
   *
   * @pre The set_t object has space enough allocated to hold at least 1 sequence.
   * @post The first sequence of the set_t object is negated.
   */
  void negate()
  {
    for ( auto& x : s[0] ) x = -x;
    for ( auto& x : r[0] ) x = -x;
  }

  /**
   * @brief Function to test if there exists equivalent amicable set.
   *
   * Function to test if there exists equivalent amicable set.
   *
   * <strong>External Functions Called:</strong>
   * <ul>
   * <li>_amicable</li>
   * <li>std::swap</li>
   * </ul>
   *
   * @pre set_t object has at least 4 sequences stored.
   * @post If there is an equivalent amicable set, the set is transformed to it;
   * otherwise, nothing is done.
   */
  void amicable();

  seq& operator[](std::size_t i) & {return s[i];}
  seq const& operator[](std::size_t i) const& {return s[i];}
  seq operator[](std::size_t i) && {return std::move(s[i]);}

  set_t& operator=(set_t const&) & = default;
  set_t& operator=(set_t &&) & noexcept = default;

  set_t() = default;
  set_t(set_t const&) = default;
  set_t(set_t &&) noexcept = default;

  /**
   * @brief Standard constructor for set_t object.
   *
   * Standard constructor for set_t object.
   *
   * @post length of the sequences assigned.
   * @post std::vector<std::vector<int> > allocated to hold 4 sequences of length
   * n.
   *
   * @param _n Length of sequences being read in.
   */
  explicit set_t(unsigned _n)
    : n{_n}, s(4, seq(n))
  {}

  ~set_t() = default;

  unsigned n{}; ///< sequence length
  seqs s{};     ///< std::vector<std::vector<int> > holding sequences
  seqs r{};     ///< std::vector<std::vector<int> > holding reversals
};

# endif
