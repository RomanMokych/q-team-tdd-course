/*### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices.
The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification
#### User Story 1

The following format is created by the machine:
```
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
```
Each entry is 3 lines long, and each line has 27 characters.
3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9.
A normal file contains around 500 entries.

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

const std::string s_string0 = { " _ "
                                "| |"
                                "|_|"
                              };
const std::string s_string1 = { "   "
                                "  |"
                                "  |"
                              };
const std::string s_string2 = { " _ "
                                " _|"
                                "|_ "
                              };
const std::string s_string3 = { " _ "
                                " _|"
                                " _|"
                              };
const std::string s_string4 = { "   "
                                "|_|"
                                "  |"
                              };
const std::string s_string5 = { " _ "
                                "|_ "
                                " _|"
                              };
const std::string s_string6 = { " _ "
                                "|_ "
                                "|_|"
                              };
const std::string s_string7 = { " _ "
                                "  |"
                                "  |"
                              };
const std::string s_string8 = { " _ "
                                "|_|"
                                "|_|"
                              };
const std::string s_string9 = { " _ "
                                "|_|"
                                " _|"
                              };

const std::string s_stringAll0 = { " _  _  _  _  _  _  _  _  _ "
                                   "| || || || || || || || || |"
                                   "|_||_||_||_||_||_||_||_||_|"
                                 };

const std::string s_stringAll1 = { "                           "
                                   "  |  |  |  |  |  |  |  |  |"
                                   "  |  |  |  |  |  |  |  |  |"
                                 };

const std::string s_stringAll2 = {  " _  _  _  _  _  _  _  _  _ "
                                    " _| _| _| _| _| _| _| _| _|"
                                    "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
                                 };

const std::string s_stringAll3 = { " _  _  _  _  _  _  _  _  _ "
                                   " _| _| _| _| _| _| _| _| _|"
                                   " _| _| _| _| _| _| _| _| _|"
                                 };

const std::string s_stringAll4 = { "                           "
                                   "|_||_||_||_||_||_||_||_||_|"
                                   "  |  |  |  |  |  |  |  |  |"
                                 };

const std::string s_stringAll5 = { " _  _  _  _  _  _  _  _  _ "
                                   "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
                                   " _| _| _| _| _| _| _| _| _|"
                                 };

const std::string s_stringAll6 = { " _  _  _  _  _  _  _  _  _ "
                                   "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
                                   "|_||_||_||_||_||_||_||_||_|"
                                 };

const std::string s_stringAll7 = { " _  _  _  _  _  _  _  _  _ "
                                   "  |  |  |  |  |  |  |  |  |"
                                   "  |  |  |  |  |  |  |  |  |"
                                 };

const std::string s_stringAll8 = { " _  _  _  _  _  _  _  _  _ "
                                   "|_||_||_||_||_||_||_||_||_|"
                                   "|_||_||_||_||_||_||_||_||_|"
                                 };

const std::string s_stringAll9 = { " _  _  _  _  _  _  _  _  _ "
                                   "|_||_||_||_||_||_||_||_||_|"
                                   " _| _| _| _| _| _| _| _| _|"
                                 };

const std::string s_string123456789 = { "    _  _     _  _  _  _  _ "
                                        "  | _| _||_||_ |_   ||_||_|"
                                        "  ||_  _|  | _||_|  ||_| _|"
                                      };

std::vector<std::string> split_to_3_strings(std::string str)
{
    std::vector<std::string> result;
    int substring_size = str.length() / 3;
    result.push_back(str.substr(0, substring_size));
    result.push_back(str.substr(substring_size, substring_size));
    result.push_back(str.substr(2 * substring_size, substring_size));
    return result;
}

std::string merge_strings(std::vector<std::string> strings)
{
    std::string result;
    for(const auto str : strings)
    {
        result.append(str);
    }
    return result;
}

int parse(std::string str)
{
    if(str == s_string1)
    {
        return 1;
    }
    else if(str == s_string2)
    {
        return 2;
    }

    return 0;
}

TEST(Split, abc_splitted_to_a_b_c)
{
    std::vector<std::string> result = {"a", "b", "c"};
    EXPECT_EQ(result, split_to_3_strings("abc"));
}

TEST(Split, abcabc_splitted_to_ab_ca_bc)
{
    std::vector<std::string> result = {"ab", "ca", "bc"};
    EXPECT_EQ(result, split_to_3_strings("abcabc"));
}

TEST(Merge, a_b_c_merged_into_abc)
{
    std::string result = "abc";
    EXPECT_EQ(result, merge_strings({"a", "b", "c"}));
}

TEST(Parse, parse1)
{
    EXPECT_EQ(1, parse(s_string1));
}

TEST(Parse, parse2)
{
    EXPECT_EQ(2, parse(s_string2));
}
