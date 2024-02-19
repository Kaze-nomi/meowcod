#include <cstring>
#include <iostream>
#include <vector>

#include "longnumber.hpp"

namespace LN {

LongNumber::LongNumber(const int val) {
  int val1 = val;
  if (val1 < 0) {
    sign = -1;
    val1 = -val1;
  } else if (val1 == 0) {
    sign = 0;
  } else {
    sign = 1;
  }

  digits.resize(exponent, 0); // Заполняем нули в дробной части

  if (val1 == 0) {
    digits.push_back(0);
  } else {
    while (val1 != 0) {
      digits.push_back(val1 % base);
      val1 /= base;
    }
  }
}

void LongNumber::setExponent(int exp) {
  if (exp == exponent) {
    return;
  }
  if (exp > exponent) {
    int dIdx = exp - exponent;
    int oldSize = (int)digits.size();
    digits.resize(digits.size() + dIdx);
    for (int i = oldSize - 1; i >= 0; i--) {
      digits[i + dIdx] = digits[i];
    }
    for (int i = 0; i < dIdx; i++) {
      digits[i] = 0;
    }

    exponent = exp;
    return;
  } else {
    int dIdx = exponent - exp;
    if (dIdx < (int)digits.size()) {
      for (int i = dIdx; i < digits.size(); i++) {
        digits[i - dIdx] = digits[i];
      }
      digits.resize(digits.size() - dIdx);
    } else {
      digits.clear();
      digits.push_back(0);
      sign = 0;
    }

    exponent = exp;
  }
  return;
}

std::string LongNumber::toString() const {
  if (sign == 0) {
    return "0";
  }

  std::string res = "";
  if (sign == -1) {
    res.push_back('-');
  }

  if (digits.size() > exponent) {
    for (int i = (int)digits.size() - 1; i >= exponent; i--) {
      res.push_back(digits[i] + '0');
    }
  } else {
    res.push_back('0');
  }
  res.push_back('.');

  for (int i = exponent - 1; i >= (int)digits.size(); i--) {
    res.push_back('0');
  }

  for (int i = std::min((int)digits.size(), exponent) - 1; i >= 0; i--) {
    res.push_back(digits[i] + '0');
  }

  if (res[res.size() - 1] == '.') {
    res.push_back('0');
  }

  return res;
}

LongNumber &LongNumber::operator+=(const LongNumber &value) {
  int maxExp = std::max(exponent, value.exponent);
  setExponent(maxExp);
  LongNumber val = value;
  val.setExponent(maxExp);
  if (val.sign == 0) {
    return *this;
  }

  if (sign == 0) {
    sign = val.sign;

    digits = val.digits;
    return *this;
  }

  if (sign == val.sign) {
    int over = 0;
    int idx = 0;
    while (idx < std::max((int)digits.size(), (int)val.digits.size()) ||
           over != 0) {
      if (idx == (int)digits.size()) {
        digits.push_back(0);
      }

      digits[idx] += over;

      if (idx < (int)val.digits.size()) {
        digits[idx] += val.digits[idx];
      }

      if (digits[idx] >= base) {
        digits[idx] -= base;
        over = 1;
      } else {
        over = 0;
      }

      ++idx;
    }
  } else {
    (*this) -= (-val);
  }

  return *this;
}

bool LongNumber::cmp_abs(const LongNumber &bi1, const LongNumber &bi2) {
  if ((int)bi1.digits.size() - bi1.exponent !=
      (int)bi2.digits.size() - bi2.exponent) {
    return (int)bi1.digits.size() - bi1.exponent >
           (int)bi2.digits.size() - bi2.exponent;
  }

  LongNumber a1 = bi1;
  LongNumber a2 = bi2;
  int maxExp = std::max(bi1.exponent, bi2.exponent);
  a1.setExponent(maxExp);
  a2.setExponent(maxExp);
  int idx = (int)a1.digits.size() - 1;
  while (idx >= 0 && a1.digits[idx] == a2.digits[idx]) {
    idx--;
  }

  return (idx == -1 || a1.digits[idx] > a2.digits[idx]);
}

LongNumber &LongNumber::operator-=(const LongNumber &value) {
  int maxExp = std::max(exponent, value.exponent);
  setExponent(maxExp);
  LongNumber val = value;
  val.setExponent(maxExp);

  if (val.sign == 0) {
    return *this;
  }

  if (sign == 0) {
    digits = val.digits;
    sign = -val.sign;

    return *this;
  }

  if (sign == val.sign) {
    if (cmp_abs(*this, val)) {
      int over = 0;

      int idx = 0;

      while (idx < (int)val.digits.size() || over != 0) {
        digits[idx] += over;

        if (idx < (int)val.digits.size()) {
          digits[idx] -= val.digits[idx];
        }
        if (digits[idx] < 0) {
          digits[idx] += base;
          over = -1;
        } else {
          over = 0;
        }

        ++idx;
      }

      while ((int)digits.size() > 1 && digits[(int)digits.size() - 1] == 0) {
        digits.pop_back();
      }

      if (digits.size() == 1 && digits[0] == 0) {
        sign = 0;
      }
    } else {
      *this = -(val - *this);
    }
  } else {
    (*this) += (-val);
  }

  return *this;
}

LongNumber &LongNumber::operator*=(const LongNumber &val) {
  if (sign == 0 || val.sign == 0) {
    sign = 0;

    digits.clear();

    digits.push_back(0);

    return *this;
  }

  std::vector<int> res((int)digits.size() + (int)val.digits.size(), 0);

  int over = 0;
  for (int i = 0; i < (int)digits.size(); i++) {
    int idx = 0;

    while (idx < (int)val.digits.size() || over != 0) {
      int tec = res[i + idx] + over;

      if (idx < (int)val.digits.size()) {
        tec += digits[i] * val.digits[idx];
      }

      res[i + idx] = int(tec % base);
      over = int(tec / base);

      ++idx;
    }

    res[i + (int)val.digits.size()] += over;
  }

  while ((int)res.size() > 1 && res.back() == 0) {
    res.pop_back();
  }

  digits = res;

  sign *= val.sign;

  exponent += val.exponent;

  return *this;
}

LongNumber &LongNumber::operator/=(const LongNumber &value) {
  if (value.sign == 0) {
    std::cerr << "Division by zero!" << std::endl;
    
    exit(1);
  }
  
  int oldExp = exponent;
  setExponent(exponent + value.exponent);

  exponent = 0;
  LongNumber val = value;
  val.exponent = 0;

  if (sign == 0) {
    exponent = oldExp;
    return *this;
  }

  std::vector<int> res;

  digits.push_back(0);
  for (int i = (int)digits.size() - 2; i >= (int)val.digits.size() - 1; i--) {
    int l = 0, r = base;

    while (r - l > 1) {
      int m = (l + r) / 2;
      LongNumber tec = val;
      tec.exponent = 0;
      LongNumber mm = m;
      mm.setExponent(0);
      tec *= mm;

      if ((int)tec.digits.size() == (int)val.digits.size()) {
        tec.digits.push_back(0);
      }

      int kol = 0;
      while (kol < (int)tec.digits.size() &&
             digits[i + 1 - kol] ==
                 tec.digits[(int)tec.digits.size() - 1 - kol]) {
        kol++;
      }

      if (kol == (int)tec.digits.size() ||
          digits[i + 1 - kol] > tec.digits[(int)tec.digits.size() - 1 - kol]) {
        l = m;
      } else {
        r = m;
      }
    }

    res.push_back(l);

    LongNumber um = val;
    um.exponent = 0;

    LongNumber ll = l;
    ll.setExponent(0);
    um *= ll;

    if ((int)um.digits.size() == (int)val.digits.size()) {
      um.digits.push_back(0);
    }

    int over = 0;

    int idx = 0;
    while (idx < (int)um.digits.size() || over != 0) {
      int k = i + 2 - (int)um.digits.size() + idx;
      digits[k] += over;

      if (idx < (int)um.digits.size()) {
        digits[k] -= um.digits[idx];
      }

      if (digits[k] < 0) {
        digits[k] += base;
        over = -1;
      } else {
        over = 0;
      }
      ++idx;
    }
  }

  digits = res;

  for (int i = 0; i < (int)digits.size() / 2; i++) {
    std::swap(digits[i], digits[(int)digits.size() - 1 - i]);
  }

  while (digits.size() > 1 && digits.back() == 0) {
    digits.pop_back();
  }

  sign *= val.sign;

  exponent = oldExp;

  return *this;
}

LongNumber::operator bool() { return (sign != 0); }

LongNumber operator-(const LongNumber &val) {
  LongNumber new_val = val;

  new_val.sign *= (-1);

  return new_val;
}

LongNumber operator+(const LongNumber &val1, const LongNumber &val2) {
  LongNumber val = val1;
  val += val2;
  return val;
}

LongNumber operator-(const LongNumber &val1, const LongNumber &val2) {
  LongNumber val = val1;
  val -= val2;
  return val;
}

LongNumber operator*(const LongNumber &val1, const LongNumber &val2) {
  LongNumber new_val = val1;

  new_val *= val2;

  return new_val;
}

LongNumber operator/(const LongNumber &val1, const LongNumber &val2) {
  LongNumber new_val = val1;

  new_val /= val2;

  return new_val;
}

bool operator==(const LongNumber &value1, const LongNumber &value2) {
  if (value1.sign == value2.sign && value1.sign == 0) {
    return true;
  }
  int maxExp = std::max(value1.exponent, value2.exponent);
  LongNumber val1 = value1;
  LongNumber val2 = value2;
  val1.setExponent(maxExp);
  val2.setExponent(maxExp);
  if ((int)val1.digits.size() != (int)val2.digits.size() ||
      val1.sign != val2.sign) {
    return false;
  }

  bool flag = true;
  for (int i = (int)val1.digits.size() - 1; i >= 0; i--) {
    if (val1.digits[i] != val2.digits[i]) {
      flag = false;
      break;
    }
  }

  return flag;
}

bool operator!=(const LongNumber &val1, const LongNumber &val2) {
  return !(val1 == val2);
}

bool operator<(const LongNumber &value1, const LongNumber &value2) {

  if (value1.sign == 0) {
    return (value2.sign == 1);
  }

  if (value2.sign == 0) {
    return (value1.sign == -1);
  }

  if (value1.sign != value2.sign) {
    return (value1.sign < value2.sign);
  }

  int maxExp = std::max(value1.exponent, value2.exponent);
  LongNumber val1 = value1;
  LongNumber val2 = value2;
  val1.setExponent(maxExp);
  val2.setExponent(maxExp);

  if ((int)val1.digits.size() < (int)val2.digits.size()) {
    return (val1.sign == 1);
  }

  if ((int)val1.digits.size() > (int)val2.digits.size()) {
    return (val1.sign == -1);
  }

  int flag = 0;
  for (int i = (int)val1.digits.size() - 1; i >= 0; i--) {
    if (val1.digits[i] < val2.digits[i]) {
      flag = 1;
      break;
    }

    if (val1.digits[i] > val2.digits[i]) {
      flag = -1;
      break;
    }
  }

  return (flag == val1.sign);
}

bool operator>(const LongNumber &val1, const LongNumber &val2) {
  return (val2 < val1);
}

bool operator<=(const LongNumber &val1, const LongNumber &val2) {
  return !(val1 > val2);
}

bool operator>=(const LongNumber &val1, const LongNumber &val2) {
  return !(val1 < val2);
}

std::ostream &operator<<(std::ostream &out, const LongNumber &val) {
  out << val.toString();
  return out;
}

LongNumber operator"" _LN(const char *lit) {
  LongNumber res;

  int idx = 0;
  if (lit[0] == '-') {
    res.sign = -1;
    idx = 1;
  } else {
    res.sign = 1;
  }

  int len = strlen(lit);

  res.exponent = 0;

  for (int i = len - 1; i >= idx; i--) {
    if (lit[i] == '.') {
      res.exponent = len - i - 1;
    } else {
      res.digits.push_back(lit[i] - '0');
    }
  }

  while (res.digits.size() > 1 && res.digits.back() == 0) {
    res.digits.pop_back();
  }

  if ((int)res.digits.size() == 1 && res.digits[0] == 0) {
    res.sign = 0;
  }

  return res;
}

LongNumber operator"" _LNE(const char *lit) {
  LongNumber res;

  int idx = 0;
  if (lit[0] == '-') {
    res.sign = -1;
    idx = 1;
  } else {
    res.sign = 1;
  }

  int len = strlen(lit);

  int e_idx = len - 1;

  while (e_idx > 0 && lit[e_idx] != 'e' && lit[e_idx] != 'E') {
    e_idx--;
  }

  int exp = atoi(lit + e_idx + 1);

  res.exponent = 0;

  for (int i = e_idx - 1; i >= idx; i--) {
    if (lit[i] == '.') {
      res.exponent = e_idx - i - 1;
    } else {
      res.digits.push_back(lit[i] - '0');
    }
  }

  while (res.digits.size() > 1 && res.digits.back() == 0) {
    res.digits.pop_back();
  }

  if ((int)res.digits.size() == 1 && res.digits[0] == 0) {
    res.sign = 0;
    return res;
  }

  if (exp <= 0) {
    res.exponent -= exp;
  } else {
    int oldExp = res.exponent;
    res.setExponent(oldExp + exp);
    res.exponent -= exp;
  }

  return res;
}
} // namespace LN