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

static const char* s_Fizz = "Fizz";
static const char* s_Buzz = "Buzz";
static const char* s_FizzBuzz = "FizzBuzz";

std::string FizzBuzz(int value)
{
    std::string result("");

    if(!(value % 3))
    {
        result = s_Fizz;
    }

    if(!(value % 5))
    {
        result += s_Buzz;
    }

    return result;
}

TEST(FizzBuzzTest, CheckAnyOtehrNubmer_ReturnNothing)
{
    EXPECT_EQ("", FizzBuzz(4));
}

TEST(FizzBuzzTest, CheckMultiplyOf_3_ReturnFizz)
{
    EXPECT_EQ(s_Fizz, FizzBuzz(6));
}

TEST(FizzBuzzTest, CheckMultiplyOf_5_ReturnBuzz)
{
    EXPECT_EQ(s_Buzz, FizzBuzz(5));
}

TEST(FizzBuzzTest, CheckMultiplyOf_15_ReturnFizzBuzz)
{
    EXPECT_EQ(s_FizzBuzz, FizzBuzz(15));
}
