# ifndef INCLUDED_ARGS_HPP
# define INCLUDED_ARGS_HPP

# include <iostream>
# include <vector>

extern "C" {
# include <fftw3.h>
}

using seq = std::vector<unsigned>;
using psdseq = std::vector<double>;

struct args_t
{
  void destroy()
  {
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
  }

  void assign(seq const& a)
  {
    for ( std::size_t i{1}; i <= n; i++ ) in[i - 1] = (a[i] == 1 ? -1 : 1);
  }

  args_t& operator=(args_t const&) & = default;
  args_t& operator=(args_t &&) & noexcept = default;

  args_t() = default;
  args_t(args_t const&) = default;
  args_t(args_t &&) noexcept = default;

  explicit args_t(unsigned _n)
    : n{_n}, bound{(n << 2U) + 4U}, psd((n >> 1U) + 1),
      in{(double*)fftw_malloc(sizeof(double) * n)},
      out{(double*)fftw_malloc(sizeof(double) * n)},
      plan{fftw_plan_r2r_1d(n, in, out, FFTW_R2HC, FFTW_MEASURE)}
  {}

  ~args_t() = default;

  unsigned n, bound;
  psdseq psd;

  double *in, *out;
  fftw_plan plan;
};

bool check_func(seq const&, args_t&);
void encounter_func(seq const&, args_t&);

# endif
