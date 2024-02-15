#include <longnumber.hpp>


using namespace LN;

void getPi(int digits) {
  LongNumber k8 = 0;
  k8.setExponent(digits+10);
  LongNumber pow16 = 1;
  pow16.setExponent(digits+10);
  LongNumber res = 0;
  res.setExponent(digits+10);
  LongNumber coefs[4] = {4, -2, -1, -1};
  for (int i = 0; i < 4; i++) {
    coefs[i].setExponent(digits+10);
  }

  for (int k = 0; k < digits; k++) {
    res += pow16 * (  coefs[0] / (k8 + 1)
                    + coefs[1] / (k8 + 4)
                    + coefs[2] / (k8 + 5)
                    + coefs[3] / (k8 + 6));
    res.setExponent(digits+10);
    pow16 *= 0.0625_LN; // div 16
    k8 += 8;
  }

  res.setExponent(digits);
  
  std::cout << res << std::endl;
}

int main() {
  std::cout << "Enter the precision of pi" << std::endl;

  int digits;
  std::cin >> digits; 

  getPi(digits);

  return 0;
}