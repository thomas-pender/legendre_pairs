# include <args.h++>

# define ERR 0.00005

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
