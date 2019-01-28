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

std::string FizzBuzz(int number)
{
    if(number % 3 == 0)
    {
        return "Fizz";
    }

    return "";
}

TEST(FizzBuzz, Any_number)
{
    EXPECT_EQ("", FizzBuzz(1));
}

TEST(FizzBuzz, Fizz_if_multiple_of_3)
{
    EXPECT_EQ("Fizz", FizzBuzz(3));
}

TEST(FizzBuzz, Buzz_if_multiple_of_5)
{
    EXPECT_EQ("Buzz", FizzBuzz(5));
}
