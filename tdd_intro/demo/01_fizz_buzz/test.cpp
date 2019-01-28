#include <gtest/gtest.h>
#include <string>

/*
 * The program should answer "Fizz" if the input number is multiple of 3, Buzz - if you specify a number which is multiple of 5,
 * and FizzBuzz - if the number is a multiple of 3 and 5. In other cases the program should not answer. So, the conditions are:
 * a multiple of 3 = Fizz
 * a multiple of 5 = Buzz
 * a multiple of 15 = FizzBuzz
 * any other number = <nothing>
*/

static const char* g_Fizz = "Fizz";
static const char* g_Buzz = "Buzz";
static const char* g_FizzBuzz = "FizzBuzz";

std::string FizzBuzz(int number)
{
    std::string result;

    if(number % 3 == 0)
    {
        result += g_Fizz;
    }

    if(number % 5 == 0)
    {
        result += g_Buzz;
    }

    return result;
}

TEST(FizzBuzz, Any_number)
{
    EXPECT_EQ("", FizzBuzz(1));
    EXPECT_EQ("", FizzBuzz(2));
    EXPECT_EQ("", FizzBuzz(13));
}

TEST(FizzBuzz, Fizz_if_multiple_of_3)
{
    EXPECT_EQ(g_Fizz, FizzBuzz(3));
    EXPECT_EQ(g_Fizz, FizzBuzz(6));
    EXPECT_EQ(g_Fizz, FizzBuzz(12));
}

TEST(FizzBuzz, Buzz_if_multiple_of_5)
{
    EXPECT_EQ(g_Buzz, FizzBuzz(5));
    EXPECT_EQ(g_Buzz, FizzBuzz(10));
    EXPECT_EQ(g_Buzz, FizzBuzz(100));
}

TEST(FizzBuzz, FizzBuzz_if_multiple_of_15)
{
    EXPECT_EQ(g_FizzBuzz, FizzBuzz(0));
    EXPECT_EQ(g_FizzBuzz, FizzBuzz(15));
    EXPECT_EQ(g_FizzBuzz, FizzBuzz(30));
    EXPECT_EQ(g_FizzBuzz, FizzBuzz(120));
}
