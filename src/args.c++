/**
 * @file args.c++
 * @brief Implementation for arguments class used by the bracelet routines called
 * in files A.c++ and B.c++.
 *
 * Implementation for arguments class used by the bracelet routines called in
 * files A.c++ and B.c++. The construction of such an objects creates instances of
 * fftw3 objects used in the psd test for each bracelet generated.
 *
 * @author Thomas Pender
 * @date 10/2025
 * @copyright GNU Public License
 */
# include <args.h++>

# define ERR 0.00005

/**
 * @brief Power spectral density test of sequence.
 *
 * Power spectral density test of sequence.
 *
 * @pre The fftw3 input array is populated with given binary sequence.
 * @pre The fftw3 output array out is populated with the FT of the input array.
 * @pre the psd std::vector<double> is allocated.
 *
 * @post The psd std::vector<double> is populated with the power spectral
 * densities of the sequence. Actually, it is only completely filled in the
 * sequence passes the test; otherwise, it is filled up to the first entry which
 * fails the test.
 *
 * @param args Arguments used in the bracelet generating routines.
 * @return bool True if the sequences pass the psd test and false otherwise.
 */
static inline
bool psd_test(args_t& args)
{
  double val{};
  for ( std::size_t i{1}; i < (args.n >> 1U); i++ ) {
    val = (args.out[i] * args.out[i]) +
      (args.out[args.n - i] * args.out[args.n - i]);
    if ( val > args.bound + ERR ) return false;
    args.psd[i] = val;
  }

  val = args.out[args.n >> 1U] * args.out[args.n >> 1U];
  if ( val > args.bound + ERR ) return false;
  args.psd[args.n >> 1U] = val;

  return true;
}

bool check_func(seq const& a, args_t& args)
{
  args.assign(a);
  fftw_execute_r2r(args.plan, args.in, args.out);
  return psd_test(args);
}

void encounter_func(seq const& a, args_t& args)
{
  std::size_t i{};
  for ( i = 1; i <= args.n; i++ )
    std::cout << (a[i] == 1 ? -1 : 1) << " ";
  std::cout << "\t\t";
  for ( i = 1; i <= (args.n >> 1U); i++ ) std::cout << args.psd[i] << " ";
  std::cout << '\n' << std::flush;
}
