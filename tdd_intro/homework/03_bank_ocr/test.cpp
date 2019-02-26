/*### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices. The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification
#### User Story 1

The following format is created by the machine:
```
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
```
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

Example input and output
```
 _  _  _  _  _  _  _  _  _
| || || || || || || || || |
|_||_||_||_||_||_||_||_||_|

=> 000000000

  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 111111111

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
|_ |_ |_ |_ |_ |_ |_ |_ |_

=> 222222222

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
 _| _| _| _| _| _| _| _| _|

=> 333333333

|_||_||_||_||_||_||_||_||_|
  |  |  |  |  |  |  |  |  |

=> 444444444

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
 _| _| _| _| _| _| _| _| _|

=> 555555555

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
|_||_||_||_||_||_||_||_||_|

=> 666666666

 _  _  _  _  _  _  _  _  _
  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 777777777

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
|_||_||_||_||_||_||_||_||_|

=> 888888888

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
 _| _| _| _| _| _| _| _| _|

=> 999999999

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|

=> 123456789
```
*/
#include <gtest/gtest.h>
#include <string>

const unsigned short g_digitLen = 3;
const unsigned short g_linesInDigit = 3;
struct Digit
{
    std::string lines[g_linesInDigit];
    bool operator==(const Digit& d) const
    {
        return (lines[0] == d.lines[0] && lines[1] == d.lines[1] && lines[2] == d.lines[2]);
    }
};

const unsigned short g_digitsOnDisplay = 9;
struct Display
{
    std::string lines[g_linesInDigit];
};

const Digit s_digit0 = { " _ ",
                         "| |",
                         "|_|"
                       };//3 4 2
const Digit s_digit1 = { "   ",
                         "  |",
                         "  |"
                       };//7
const Digit s_digit2 = { " _ ",
                         " _|",
                         "|_ "
                       };//4 2 3
const Digit s_digit3 = { " _ ",
                         " _|",
                         " _|"
                       };//4 2 3
const Digit s_digit4 = { "   ",
                         "|_|",
                         "  |"
                       };//5
const Digit s_digit5 = { " _ ",
                         "|_ ",
                         " _|"
                       };//4 2 3
const Digit s_digit6 = { " _ ",
                         "|_ ",
                         "|_|"
                       };//3 3 3
const Digit s_digit7 = { " _ ",
                         "  |",
                         "  |"
                       };//6
const Digit s_digit8 = { " _ ",
                         "|_|",
                         "|_|"
                       };//2
const Digit s_digit9 = { " _ ",
                         "|_|",
                         " _|"
                       };//3 3 3

const Display s_displayAll0 = { " _  _  _  _  _  _  _  _  _ ",
                                "| || || || || || || || || |",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll1 = { "                           ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll2 = {  " _  _  _  _  _  _  _  _  _ ",
                                 " _| _| _| _| _| _| _| _| _|",
                                 "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
};

const Display s_displayAll3 = { " _  _  _  _  _  _  _  _  _ ",
                                " _| _| _| _| _| _| _| _| _|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll4 = { "                           ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll5 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll6 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll7 = { " _  _  _  _  _  _  _  _  _ ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll8 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll9 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_display123456789 = { "    _  _     _  _  _  _  _ ",
                                     "  | _| _||_||_ |_   ||_||_|",
                                     "  ||_  _|  | _||_|  ||_| _|"
};

short calc_specific_symbol(const std::string& line, char symbol)
{
    auto number_of_symbols = 0;

    for (size_t i = 0; i < line.size(); ++i)
    {
        if (line[i] == symbol)
        {
            ++number_of_symbols;
        }
    }

    return number_of_symbols;
}

short get_digit_from_struct(const Digit& digit)
{
    auto spaces = 0;
    auto pipes = 0;
    for(auto &line : digit.lines)
    {
        spaces += calc_specific_symbol(line, ' ');
        pipes += calc_specific_symbol(line, '|');
    }

    auto result = 10; // some incorrect number to detect failure
    switch(spaces)
    {
        case 7:
            result = 1;
            break;

        case 6:
            result = 7;
            break;

        case 5:
            result = 4;
            break;

        case 2:
            result = 8;
            break;

        case 3:
            if (4 == pipes)
            {
                result = 0;
            }
            else if (2 == calc_specific_symbol(digit.lines[1], '|'))
            {
                result = 9;
            }
            else
            {
                result = 6;
            }
            break;

        case 4:
            if(digit.lines[1].at(0) == '|')
            {
                result = 5;
            }
            else if(digit.lines[2].at(0) == '|')
            {
                result = 2;
            }
            else
            {
                result = 3;
            }
            break;
    }

    return result;
}

Digit get_digit_from_display(const Display& display, int num)
{
    Digit result;
    auto i = 0;
    for (auto line : display.lines)
    {
        result.lines[i] = line.substr(num * 3, 3);
        i++;
    }

    return result;
}

int get_sequence_from_display(const Display& display)
{
    auto result = 0;
    for (auto i = 0; i < 9; i++)
    {
        Digit digit = get_digit_from_display(display, i);
        auto value = get_digit_from_struct(digit);
        result *= 10;
        result += value;
    }

    return result;
}

TEST(test_get_sequence_from_display, all_digits_sequence)
{
    EXPECT_EQ(get_sequence_from_display(s_display123456789), 123456789);
}

TEST(test_get_sequence_from_display, nine_sequence)
{
    EXPECT_EQ(get_sequence_from_display(s_displayAll9), 999999999);
}

TEST(test_get_sequence_from_display, two_sequence)
{
    EXPECT_EQ(get_sequence_from_display(s_displayAll2), 222222222);
}

TEST(test_get_sequence_from_display, one_sequence)
{
    EXPECT_EQ(get_sequence_from_display(s_displayAll1), 111111111);
}

TEST(test_get_digit_from_display, first_digit)
{
    EXPECT_EQ(get_digit_from_display(s_displayAll1, 0), s_digit1);
}

TEST(test_get_digit_from_display, fifth_digit)
{
    EXPECT_EQ(get_digit_from_display(s_displayAll8, 5), s_digit8);
}

TEST(test_calc_specific_symbol, two_non_spaces)
{
    EXPECT_EQ(2, calc_specific_symbol(" _ ", ' '));
}

TEST(test_calc_specific_symbol, one_underline)
{
    EXPECT_EQ(1, calc_specific_symbol(" _ ", '_'));
}

TEST(test_calc_specific_symbol, three_spaces)
{
    EXPECT_EQ(3, calc_specific_symbol("   ", ' '));
}

TEST(test_calc_specific_symbol, none_search_symbols)
{
    EXPECT_EQ(0, calc_specific_symbol("   ", '|'));
}

TEST(test_get_digit_from_struct, digit_one)
{
    EXPECT_EQ(1, get_digit_from_struct(s_digit1));
}

TEST(test_get_digit_from_struct, digit_seven)
{
    EXPECT_EQ(7, get_digit_from_struct(s_digit7));
}

TEST(test_get_digit_from_struct, digit_four)
{
    EXPECT_EQ(4, get_digit_from_struct(s_digit4));
}

TEST(test_get_digit_from_struct, digit_eight)
{
    EXPECT_EQ(8, get_digit_from_struct(s_digit8));
}

TEST(test_get_digit_from_struct, digit_zero)
{
    EXPECT_EQ(0, get_digit_from_struct(s_digit0));
}

TEST(test_get_digit_from_struct, digit_nine)
{
    EXPECT_EQ(9, get_digit_from_struct(s_digit9));
}

TEST(test_get_digit_from_struct, digit_six)
{
    EXPECT_EQ(6, get_digit_from_struct(s_digit6));
}

TEST(test_get_digit_from_struct, digit_five)
{
    EXPECT_EQ(5, get_digit_from_struct(s_digit5));
}

TEST(test_get_digit_from_struct, digit_two)
{
    EXPECT_EQ(2, get_digit_from_struct(s_digit2));
}

TEST(test_get_digit_from_struct, digit_three)
{
    EXPECT_EQ(3, get_digit_from_struct(s_digit3));
}
