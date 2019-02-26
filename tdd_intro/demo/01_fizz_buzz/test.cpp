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

static const char* s_fizz = "Fizz";
static const char* s_buzz = "Buzz";
static const char* s_fizzbuzz = "FizzBuzz";

class Checker
{
public:
    const char* check (unsigned int num)
    {
        if ((num % 5) == 0 && (num % 3) == 0)
        {
            return s_fizzbuzz;
        }
        if ((num % 5) == 0)
        {
            return s_buzz;
        }
        if ((num % 3) == 0)
        {
            return s_fizz;
        }

        return nullptr;
    }
};


TEST(Checker, check_multiply_three)
{
    Checker c;
    EXPECT_EQ(c.check(9), s_fizz);
}

TEST(Checker, check_multiply_five)
{
    Checker c;
    EXPECT_EQ(c.check(5), s_buzz);
}

TEST(Checker, check_multiply_three_and_five)
{
    Checker c;
    EXPECT_EQ(c.check(15), s_fizzbuzz);
}

TEST(Checker, check_no_multiply)
{
    Checker c;
    EXPECT_EQ(c.check(14), nullptr);
}
