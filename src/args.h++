/**
 * @file args.h++
 * @brief Interface for arguments class used by the bracelet routines called in
 * files A.c++ abd B.c++.
 *
 * Interface for arguments class used by the bracelet routines called in
 * files A.c++ abd B.c++. The construction of such an objects creates instances of
 * fftw3 objects used in the psd test for each bracelet generated.
 *
 * @author Thomas Pender
 * @date 10/2025
 * @copyright GNU Public License
 */
# ifndef INCLUDED_ARGS_HPP
# define INCLUDED_ARGS_HPP

# include <iostream>
# include <vector>

extern "C" {
# include <fftw3.h>
}

using seq = std::vector<unsigned>;
using psdseq = std::vector<double>;

/**
 * @brief Argument class used by bracelet generation routines.
 *
 * Argument class used by bracelet generation routines. The construction of such
 * an objects creates instances of fftw3 objects used in the psd test for each
 * bracelet generated.
 */
struct args_t
{
  /**
   * @brief Frees memory allocated for the fftw3 objects.
   *
   * Frees memory allocated for the fftw3 objects.
   *
   * <strong>External Called Functions:</strong>
   * <ul>
   * <li>fftw_destroy_plan</li>
   * <li>fftw_free</li>
   * </ul>
   *
   * @pre Memory allocated by fftw3 objects: plan, in, out. This is done at
   * construction.
   *
   * @post Memory allocated for fftw3 objects is deallocated.
   */
  void destroy()
  {
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
  }

  /**
   * @brief Maps the contents from the std::vector<unsigned> holding the completed
   * string into the fftw3 array in used
   * @brief Assigns contents of fftw3 input array in.
   *
   * Maps the contents from the std::vector<unsigned> holding the completed string
   * into the fftw3 input array in. The FFT routine will run on this array and the
   * output is assigned to the fftw3 ouput array out. The output array is used for
   * the psd test.
   *
   * @pre Memory needs to be allocated for fftw3 input array in.
   * @pre The completed vector has intial element 0 and remaining elements +1 and
   * -1.
   *
   * @post Contents of vector are mapped into fftw3 input array in.
   *
   * @param a vector containing string.
   */
  void assign(seq const& a)
  {
    for ( std::size_t i{1}; i <= n; i++ ) in[i - 1] = (a[i] == 1 ? -1 : 1);
  }

  args_t& operator=(args_t const&) & = default;
  args_t& operator=(args_t &&) & noexcept = default;

  args_t() = default;
  args_t(args_t const&) = default;
  args_t(args_t &&) noexcept = default;

  /**
   * @brief Standard constructor.
   *
   * Standard constructor. This constructor allocates the memory required for the
   * fftw3 objects used in the psd test.
   *
   * <strong>External Called Functions:</strong>
   * <ul>
   * <li>fftw_malloc</li>
   * <li>fftw_plan_r2r_1d</li>
   * </ul>
   *
   * @post Length n is assigned.
   * @post The psd bound 2n+2 is assigned.
   * @post Memory is allocated for the fftw3 input and output arrays.
   * @post The fftw3 plan is allocated and constructed.
   * @post The vector used to house the important psd values is allocated.
   *
   * @param _n The length of the bracelets being constructed.
   */
  explicit args_t(unsigned _n)
    : n{_n}, bound{(n << 2U) + 4U}, psd((n >> 1U) + 1),
      in{(double*)fftw_malloc(sizeof(double) * n)},
      out{(double*)fftw_malloc(sizeof(double) * n)},
      plan{fftw_plan_r2r_1d(n, in, out, FFTW_R2HC, FFTW_MEASURE)}
  {}

  ~args_t() = default;

  unsigned n{};     ///< length of sequences
  unsigned bound{}; ///< psd bound 2n+2
  psdseq   psd{};   ///< relevant psd values of sequence

  double    *in{};   ///< fftw3 input array
  double    *out{};  ///< fftw3 output array
  fftw_plan  plan{}; ///< fftw3 plan used
};

/**
 * @brief Function used to implement the psd test.
 *
 * Function used to implement the psd test.
 *
 * <strong>External Called Functions:</strong>
 * <ul>
 * <li>fftw_execute_r2r -- runs FFT algorithm, output written to fftw3 output
 * array out.</li>
 * </ul>
 * <strong>Internal Called Functions:</strong>
 * <ul>
 * <li>args_t::assign -- maps sequence to fftw3 input array</li>
 * <li>psd_test -- uses outout of fftw_execute_r2r to do psd test</li>
 * </ul>
 *
 * @pre Sequence a has first element 0 and remaining elements +1 or -1.
 * @pre args_t object created, and internal fftw3 objects are allocated.
 *
 * @post Contents of a are mapped to fftw3 input array in.
 * @post The fftw3 ouput array out is populated with the FT of the input array in.
 * @post The psd std::vector is populated witht he power spectral densities of
 * the sequence.
 *
 * @param a Sequence constructed from bracelet routine.
 * @param args Arguments used in bracelet generating routines.
 * @return bool True if passes psd test; false otherwise (value of function
 * psd_test).
 */
bool check_func(seq const& a, args_t& args);

/**
 * @brief Prints sequence if it passes the psd test.
 *
 * Prints sequence if it passes the psd test.
 *
 * @pre Sequence a has first element 0 and remaining elements +1 or -1.
 * @pre args_t object created, and internal fftw3 objects are allocated.
 *
 * @post Sequence is mapped to stdout.
 *
 * @param a Sequence constructed from bracelet routine.
 * @param args Arguments used in bracelet generating routines.
 */
void encounter_func(seq const& a, args_t& args);

# endif
