/*
Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4
  except every year that is evenly divisible by 100
    unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

If your language provides a method in the standard library that does this look-up, pretend it doesn't exist and implement it yourself.
*/

#include <gtest/gtest.h>


const size_t g_four         = 4;
const size_t g_oneHundred   = 100;
const size_t g_fourHundred  = g_four * g_oneHundred;

bool isDivisible(size_t number, size_t divider)
{
    return number % divider == 0;
}

bool IsLeapYear(size_t year)
{
    if (isDivisible(year, g_fourHundred))
    {
        return true;
    }
    if (isDivisible(year, g_oneHundred))
    {
        return false;
    }
    if (isDivisible(year, g_four))
    {
        return true;
    }

    return false;
}

TEST(LeapYear, TestDivisible400)
{
    EXPECT_TRUE(IsLeapYear(g_fourHundred));
    EXPECT_TRUE(IsLeapYear(g_fourHundred * 2));
    EXPECT_TRUE(IsLeapYear(g_fourHundred * 3));
}

TEST(LeapYear, TestDivisible4AndNot100)
{
    EXPECT_TRUE(IsLeapYear(104));
    EXPECT_TRUE(IsLeapYear(404));
    EXPECT_TRUE(IsLeapYear(2008));
    EXPECT_TRUE(IsLeapYear(2012));
}

TEST(LeapYear, TestDivisible100)
{
    EXPECT_FALSE(IsLeapYear(g_oneHundred));
    EXPECT_FALSE(IsLeapYear(g_oneHundred * 5));
}

TEST(LeapYear, TestNotDivisible4_400_100)
{
    EXPECT_FALSE(IsLeapYear(333));
    EXPECT_FALSE(IsLeapYear(555));
}
