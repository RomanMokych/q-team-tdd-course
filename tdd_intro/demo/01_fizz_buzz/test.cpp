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
    if(number % 3 == 0)
    {
        return g_Fizz;
    }

    if(number % 5 == 0)
    {
        return g_Buzz;
    }

    return "";
}

TEST(FizzBuzz, Any_number)
{
    EXPECT_EQ("", FizzBuzz(1));
}

TEST(FizzBuzz, Fizz_if_multiple_of_3)
{
    EXPECT_EQ(g_Fizz, FizzBuzz(3));
}

TEST(FizzBuzz, Buzz_if_multiple_of_5)
{
    EXPECT_EQ(g_Buzz, FizzBuzz(5));
}

TEST(FizzBuzz, FizzBuzz_if_multiple_of_15)
{
    EXPECT_EQ(g_FizzBuzz, FizzBuzz(15));
}
