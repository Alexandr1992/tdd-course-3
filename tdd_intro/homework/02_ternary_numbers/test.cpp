#include <gtest/gtest.h>
#include <cmath>
#include <string>

/*
Convert a ternary number, represented as a string (e.g. '102012'), to its decimal equivalent using first principles.

The program should consider strings specifying an invalid ternary as the value 0.

Ternary numbers contain three symbols: 0, 1, and 2.

The last place in a ternary number is the 1's place. The second to last is the 3's place, the third to last is the 9's place, etc.

# "102012"
    1       0       2       0       1       2    # the number
1*3^5   + 0*3^4 + 2*3^3 + 0*3^2 + 1*3^1 + 2*3^0    # the value
  243   +   0 +    54 +     0 +     3 +     2 =  302

If your language provides a method in the standard library to perform the conversion, pretend it doesn't exist and implement it yourself.
*/

size_t ConvertTernaryToDecimal(size_t numerical, size_t position)
{
    if(numerical > 2)
    {
        return 0;
    }

    double ternaryPow = std::pow(3, position);
    return static_cast<size_t>(ternaryPow) * numerical;
}

size_t ConvertTernaryToDecimal(const std::string& ternary)
{
    size_t result = 0;
    size_t position = ternary.size();
    for (const char ternarySymbChar: ternary)
    {
        int ternaryNumb = std::atoi(&ternarySymbChar);
        result += ConvertTernaryToDecimal(static_cast<size_t>(ternaryNumb), --position);
    }

    return result;
}

TEST(TernaryNumber, TestConvertTernaryNum_Pos0_ToDecimal)
{
    EXPECT_EQ(0, ConvertTernaryToDecimal(0, 0));
    EXPECT_EQ(1, ConvertTernaryToDecimal(1, 0));
    EXPECT_EQ(2, ConvertTernaryToDecimal(2, 0));
}

TEST(TernaryNumber, TestConvertTernaryNum_Larger0_ToDecimal)
{
    EXPECT_EQ(3, ConvertTernaryToDecimal(1, 1));
    EXPECT_EQ(0, ConvertTernaryToDecimal(0, 2));
    EXPECT_EQ(54, ConvertTernaryToDecimal(2, 3));
}

TEST(TernaryNumber, TestConvertInvalidTernary)
{
    EXPECT_EQ(0, ConvertTernaryToDecimal(4, 0));
    EXPECT_EQ(0, ConvertTernaryToDecimal(5, 0));
    EXPECT_EQ(0, ConvertTernaryToDecimal(20, 0));
}

TEST(TernaryNumber, TestConvertOneTernaryNumericalStrToDecimal)
{
    EXPECT_EQ(0, ConvertTernaryToDecimal("0"));
    EXPECT_EQ(1, ConvertTernaryToDecimal("1"));
    EXPECT_EQ(2, ConvertTernaryToDecimal("2"));
    EXPECT_EQ(0, ConvertTernaryToDecimal("3"));
}

TEST(TernaryNumber, TestConvertTernaryStrToDecimal)
{
    EXPECT_EQ(302, ConvertTernaryToDecimal("102012"));
}

TEST(TernaryNumber, TestEmptyTernaryString)
{
    EXPECT_EQ(0, ConvertTernaryToDecimal(""));
}

TEST(TernaryNumber, TestIncorrectTernaryNumberInString)
{
    EXPECT_EQ(302, ConvertTernaryToDecimal("192612"));
    EXPECT_EQ(302, ConvertTernaryToDecimal("1*2%12"));
}
