/**
 * @file whiteman.c++
 * @brief File to generate executable that takes elements of two sequence types
 * and returns those 4-sets forming a summable set with out-of-phase periodic
 * autocorrelations summing to -4.
 *
 * File to generate executable that takes elements of two sequence types and
 * returns those 4-sets forming a summable set with out-of-phase periodic
 * autocorrelations summing to -4.
 *
 * <dl>
 * <dt><strong>Usage</strong></dt>
 * <dd>./whiteman N num1 num2 file1 file2</dd>
 * </dl>
 * <strong>Parameters</strong>
 * <ul>
 * <li><strong>N --</strong> length of sequences</li>
 * <li><strong>num1 --</strong> number of sequences in file1</li>
 * <li><strong>num2 --</strong> number of sequences in file2</li>
 * <li><strong>file1 --</strong> file containing sequences of first type and
 * their psds</li>
 * <li><strong>file2 --</strong> file containing sequences of second type and
 * their psds</li>
 * </ul>
 *
 * @author Thomas Pender
 * @date 10/2025
 * @copyright GNU Public License
 */
# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>

# include <sequence.h++>

int main(int argc, char *argv[])
{
  if ( argc < 6 ) {
    std::cerr << "USAGE -- ./set.out <N> <numA> <numB> <fileA> <fileB>\n"
              << std::flush;
    return 1;
  }

  unsigned n{}, numA{}, numB{};
  {
    std::stringstream ss{argv[1]};
    ss >> n;
    ss = std::stringstream{argv[2]};
    ss >> numA;
    ss = std::stringstream{argv[3]};
    ss >> numB;
  }

  long long i1{}, i2{}, j1{}, j2{}, k{};
  std::ifstream F1{argv[4]}, F2{argv[5]};

  std::vector<sequence_t> seqA(numA, sequence_t{n});
  for ( auto& x : seqA ) F1 >> x;
  std::sort(seqA.begin(), seqA.end());
  F1.close();

  std::vector<sequence_t> seqB(numB, sequence_t{n});
  for ( auto& x : seqB ) F2 >> x;
  std::sort(seqB.begin(), seqB.end());
  F2.close();

  for ( i1 = 0; i1 < numA; i1++ )
    for ( i2 = 0; i2 < numB; i2++ ) {
      if ( !check_bound(seqA[i1], seqB[i2]) ) continue;
      j1 = i1; j2 = numA - 1;
      while ( j1 < numA && j2 >= j1 ) {
        bool flag{true};

        for ( k = 0; k < seqA[i1].psd.size(); k++ ) {
          double val{seqA[i1].psd[k] + seqA[j1].psd[k] +
                     seqA[j2].psd[k] + seqB[i2].psd[k]};
          if ( val > seqA[i1].bound + ERR ) {
            flag = false;
            j2--;
            break;
          }
          if ( val < seqA[i1].bound - ERR ) {
            flag = false;
            j1++;
            break;
          }
        }

        if ( flag == true ) {
          pr(seqA[i1], seqA[j1], seqA[j2], seqB[i2]);
          j1++; j2--;
        }
      }
    }

  return 0;
}
