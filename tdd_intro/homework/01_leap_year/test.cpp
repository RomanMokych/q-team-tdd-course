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
    if(year <= 0)
    {
        throw std::invalid_argument("Year value must be greater than 0");
    }

    if(!(year % 4))
    {
        if(!(year % 400))
        {
            return true;
        }

        if(!(year % 100))
        {
            return false;
        }

        return true;
    }

    return false;

}

TEST(LeapYearTest, Check_IsLeapYear_2020_Return_true)
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

TEST(LeapYearTest, Check_IsLeapYear_1997_Return_false)
{
    EXPECT_FALSE(IsLeapYear(1997));
}

TEST(LeapYearTest, Check_IsLeapYear_1996_Return_true)
{
    EXPECT_TRUE(IsLeapYear(1996));
}

TEST(LeapYearTest, Throw_invalid_argument_exception_if_year_less_0)
{
    EXPECT_THROW(IsLeapYear(-1), std::invalid_argument);
}

TEST(LeapYearTest, Throw_invalid_argument_exception_if_year_eq_0)
{
    EXPECT_THROW(IsLeapYear(0), std::invalid_argument);
}
