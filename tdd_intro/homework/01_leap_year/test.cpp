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

/* Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4 except every year that is evenly divisible by 100 unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

If your language provides a method in the standard library that does this look-up, pretend it doesn't exist and implement it yourself. */

bool IsLeapYear(unsigned int year)
{
    if(year == 0)
    {
        return false;
    }

    if(year % 4 == 0)
    {
        return true;
    }

    return false;
}

TEST(LeapYear, Not_a_leap_year)
{
    EXPECT_FALSE(IsLeapYear(1997));
    EXPECT_FALSE(IsLeapYear(2019));
    EXPECT_FALSE(IsLeapYear(1));
    EXPECT_FALSE(IsLeapYear(0));
}

TEST(LeapYear, Is_Leap_Year)
{
    EXPECT_TRUE(IsLeapYear(4));
}
