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

bool check_leap_year(unsigned int year)
{
    if ((year % 100) == 0 && (year % 400) != 0)
    {
        return false;
    }

    return (year % 4) == 0;
}

TEST(LeapYearCheck, check_division_by_four)
{
    EXPECT_TRUE(check_leap_year(2000));
}

TEST(LeapYearCheck, check_not_leap_year)
{
    EXPECT_FALSE(check_leap_year(1997));
}

TEST(LeapYearCheck, check_leap_year_division_100)
{
    EXPECT_FALSE(check_leap_year(1900));
}
