#ifndef LONG_NUMBER_H
#define LONG_NUMBER_H

#include <iostream>
#include <vector>
#include <string>

namespace LN {

  class LongNumber {
  private:
    const static int base = 10;

    std::vector<int> digits;

    int sign;
    int exponent = 10;

  public:
    LongNumber() = default;

    LongNumber(const int val);

    void setExponent(int exp);

    std::string toString() const;

    LongNumber& operator+=(const LongNumber& value);

    static bool cmp_abs(const LongNumber& bi1, const LongNumber& bi2);

    LongNumber& operator-=(const LongNumber& value);

    LongNumber& operator*=(const LongNumber& val);

    LongNumber& operator/=(const LongNumber& value);

    explicit operator bool();

    friend LongNumber operator-(const LongNumber& val);
    friend LongNumber operator+(const LongNumber& val1, const LongNumber& val2);
    friend LongNumber operator-(const LongNumber& val1, const LongNumber& val2);
    friend LongNumber operator*(const LongNumber& val1, const LongNumber& val2);
    friend LongNumber operator/(const LongNumber& val1, const LongNumber& val2);
    friend bool operator==(const LongNumber& val1, const LongNumber& val2);
    friend bool operator!=(const LongNumber& val1, const LongNumber& val2);
    friend bool operator<(const LongNumber& val1, const LongNumber& val2);
    friend bool operator<=(const LongNumber& val1, const LongNumber& val2);
    friend bool operator>(const LongNumber& val1, const LongNumber& val2);
    friend bool operator>=(const LongNumber& val1, const LongNumber& val2);
    friend std::ostream& operator<<(std::ostream& out, const LongNumber& val);
    friend LongNumber operator"" _LN(const char* lit);
    friend LongNumber operator"" _LNE(const char* lit);
  };

  LongNumber operator-(const LongNumber& val);
  LongNumber operator+(const LongNumber& val1, const LongNumber& val2);
  LongNumber operator-(const LongNumber& val1, const LongNumber& val2);
  LongNumber operator*(const LongNumber& val1, const LongNumber& val2);
  LongNumber operator/(const LongNumber& val1, const LongNumber& val2);

  bool operator==(const LongNumber& value1, const LongNumber& value2);
  bool operator!=(const LongNumber& val1, const LongNumber& val2);
  bool operator<(const LongNumber& value1, const LongNumber& value2);
  bool operator>(const LongNumber& val1, const LongNumber& val2);
  bool operator<=(const LongNumber& val1, const LongNumber& val2);
  bool operator>=(const LongNumber& val1, const LongNumber& val2);

  std::ostream& operator<<(std::ostream& out, const LongNumber& val);

  LongNumber operator"" _LN(const char* lit);
  LongNumber operator"" _LNE(const char* lit);
}

#endif // LONG_NUMBER_H