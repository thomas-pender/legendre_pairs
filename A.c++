# include <sstream>

# include <args.h++>
# include <combinat.h>

int main(int argc, char *argv[])
{
  if ( argc < 2 ) {
    std::cerr << "USAGE -- ./A.out <N>\n" << std::flush;
    return 1;
  }

  unsigned n{};
  {
    std::stringstream ss{argv[1]};
    ss >> n;
  }

  if ( n & 1U ) {
    std::cerr << "ERROR -- parameter <N> must be even\n" << std::flush;
    return 1;
  }

  args_t args{n};
  combinat::neck_t<args_t> neck{n, 2U};
  neck.checkfunc = check_func;
  neck.encounterfunc = encounter_func;

  combinat::FCBraceletUnlabeled<args_t>(neck, args, NULL);

  return 0;
}
