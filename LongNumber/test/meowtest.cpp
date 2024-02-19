#include <gtest/gtest.h>
#include <longnumber.hpp>


using namespace LN;

TEST(LongNumber, CompareTest) {
  // Expect equality.
  EXPECT_EQ(0.1_LN  <= 0.11e1_LNE, true);
  EXPECT_EQ(0.1_LN  > 0.11e1_LNE, false);
  EXPECT_EQ(2.2e99_LNE == 0.11e100_LNE * 2, true);
  EXPECT_EQ(0.1_LN  != -0.1_LN, true);
}


TEST(LongNumber, Arithmetic) {
  // Expect equality.
  EXPECT_EQ(1._LN + 0.1_LN, 0.11e1_LNE);
  EXPECT_EQ(1._LN - 0.1_LN, 0.009e2_LNE);
  EXPECT_EQ(0.123_LN * 0.654_LN, 8.0442e-2_LNE);
  LongNumber a = 123456789, b = 987654321;
  a.setExponent(20);
  a /= b;
  a.setExponent(7);
  EXPECT_EQ(a, 0.1249999_LN);
}

TEST(LongNumber, String) {
  // Expect string equality.
  LongNumber a = 3.14_LN;
  std::string b = a.toString();
  EXPECT_EQ(b, "3.14");
}

TEST(LongNumber, DivisionByZero) {
  // Expect string equality.
  LongNumber a = 3.14_LN;
  EXPECT_DEATH(a /= 0, "");
}

TEST(LongNumber, Computation) {
  // Solve equation x^2 = 2 (positive root)

  LongNumber l = 0, r = 2;
  l.setExponent(100);
  r.setExponent(100);
  LongNumber eps = 1e-100_LNE;

  while (r - l > eps)
  {
    LongNumber m = (r + l) * 0.5_LN;

    if (m * m > 2)
    {
      r = m;
    } else {
      l = m;
    }
  }

  LongNumber ans = (l+r)*0.5_LN;
  
  ans.setExponent(100);

  EXPECT_EQ(ans*ans - 2 <= 1e-50_LNE, true);
  EXPECT_EQ(ans*ans - 2 >= -1e-50_LNE, true);
}