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

bool IsLeapYear(int year)
{
    if(!(year % 4))
    {
        if(!(year % 100))
        {
            return false;
        }

    }

    return true;

}

TEST(LeapYearTest, Check_IsLeapYear_2000_Return_true)
{
    EXPECT_TRUE(IsLeapYear(2020));
}

TEST(LeapYearTest, Check_IsLeapYear_Exclude_Every_100_years)
{
    EXPECT_FALSE(IsLeapYear(1900));
}

TEST(LeapYearTest, Check_IsLeapYear_Include_Every_400_years)
{
    EXPECT_TRUE(IsLeapYear(2000));
}
