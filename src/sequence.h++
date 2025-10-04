/**
 * @file sequence.h++
 * @brief Interface for seq_t class that holds a sequence and its out-of-phase
 * power spectral densities.
 *
 * Interface for seq_t class that holds a sequence and its out-of-phase power
 * spectral densities. The class is a helper class for the executable whiteman.
 *
 * @author Thomas Pender
 * @date 10/2025
 * @copyright GNU Public License
 */
# ifndef INCLUDED_SEQUENCES_HPP
# define INCLUDED_SEQUENCES_HPP

# include <iostream>
# include <vector>

# define ERR 0.00005

using seq = std::vector<int>;
using psdseq = std::vector<double>;

/**
 * @brief A class to hold a sequence and its psd sequence.
 *
 * A class to hold a sequence and its psd sequence.
 */
struct sequence_t
{
  /**
   * @brief Write out the sequence in the pair.
   *
   * Write out the sequence in the pair.
   *
   * @param os std::ostream object
   * @param s sequence_t object.
   * @return std::ostream object.
   */
  friend std::ostream& operator<<(std::ostream& os, sequence_t const& s)
  {
    for ( auto x : s.a ) os << x << " ";
    os << '\n';
    return os;
  }

  /**
   * @brief Read in sequence_t object.
   *
   * Read in sequence_t object.
   *
   * @param is std::istream object.
   * @param s sequence_t object be read in.
   * @return std::istream object.
   */
  friend std::istream& operator>>(std::istream& is, sequence_t& s)
  {
    for ( auto& x : s.a ) is >> x;
    for ( auto& x : s.psd ) is >> x;
    return is;
  }

  /**
   * @brief Ordering of sequence_t objects.
   *
   * Ordering of sequence_t objects.
   */
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

  /**
   * @brief Standard constructor.
   *
   * Standard constructor.
   *
   * @param _n Length of sequence to be constructed.
   */
  explicit sequence_t(unsigned _n)
    : n{_n}, bound{(_n << 2U) + 4U}, a(_n), psd(_n >> 1U)
  {}

  ~sequence_t() = default;

  unsigned n;     ///< length of sequences
  unsigned bound; ///< psd bound for sequence of given length
  seq a{};        ///< std::vector<int> holding sequence
  psdseq psd{};   ///< std::vector<double> holding power spectral densities
};

/**
 * @brief Print 4-set of sequences.
 *
 * Print 4-set of sequences.
 *
 * @param s1 First sequence.
 * @param s2 Second sequence.
 * @param s3 Third sequence.
 * @param s4 Fourth sequence.
 */
static inline
void pr(sequence_t const& s1, sequence_t const& s2,
        sequence_t const& s3, sequence_t const& s4)
{
  std::cout << s1 << s2 << s3 << s4 << '\n' << std::flush;
}

/**
 * @brief Psd test for a pair of sequences.
 *
 * Psd test for a pair of sequences.
 *
 * @param s1 First sequence.
 * @param s2 SEcond sequence.
 * @return True if the pair passes the test else false.
 */
static inline
bool check_bound(sequence_t const& s1, sequence_t const& s2)
{
  for ( std::size_t i{0}; i < s1.psd.size(); i++ )
    if ( s1.psd[i] + s2.psd[i] > s1.bound + ERR ) return false;
  return true;
}

# endif
