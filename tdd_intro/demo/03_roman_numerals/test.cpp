/*
Write a function to convert from normal numbers to Roman Numerals.

The Romans wrote numbers using letters - I, V, X, L, C, D, M. (converter http://www.novaroma.org/via_romana/numbers.html)

There is no need to be able to convert numbers larger than about 3000. (The Romans themselves didn't tend to go any higher)

Wikipedia says: Modern Roman numerals ... are written by expressing each digit separately starting with the left most digit and skipping any digit with a value of zero.

To see this in practice, consider the example of 1990.
In Roman numerals 1990 is MCMXC:
1000=M 900=CM 90=XC

2008 is written as MMVIII:
2000=MM 8=VIII

1998 is written as MCMXCVIII.
*/

#include <gtest/gtest.h>

static std::map<char, int> g_RomanToDecTable = {
    {'I', 1},
    {'V', 5},
    {'X', 10},
};

int RemanToDec(std::string romanStr)
{
    int result = 0;
    while(romanStr.size())
    {
        int val = g_RomanToDecTable[romanStr.front()];
        romanStr.erase(romanStr.begin(),romanStr.begin() + 1);
        if(romanStr.empty())
        {
            result += val;
            break;
        }
        result += val * (g_RomanToDecTable[*romanStr.begin()] > val ? -1 : 1);
    }
    return result;
}

TEST(RomanToDecTest, I_is_1)
{
    EXPECT_EQ(1, RemanToDec("I"));
}

TEST(RomanToDecTest, II_is_2)
{
    EXPECT_EQ(2, RemanToDec("II"));
}

TEST(RomanToDecTest, VII_is_7)
{
    EXPECT_EQ(7, RemanToDec("VII"));
}

TEST(RomanToDecTest, IV_is_4)
{
    EXPECT_EQ(4, RemanToDec("IV"));
}
