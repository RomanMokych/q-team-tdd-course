/*
Given a phrase, count the occurrences of each word in that phrase. Ignore whitespaces and punctual symbols
For example for the input "olly olly in come free please please let it be in such manner olly"
olly: 3
in: 2
come: 1
free: 1
please: 2
let: 1
it: 1
be: 1
manner: 1
such: 1
*/

#include <gtest/gtest.h>
#include <string>
#include <map>

using namespace std;

map<string, int> count_words(const string &str)
{
    map<string, int> result;
    result.insert({str, 1});
    return result;
}

TEST(word_count, one_word_in_string)
{
    auto result = count_words("one");
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(1, result.at("one"));
}

TEST(word_count, another_one_word_in_string)
{
    auto result = count_words("another");
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(1, result.at("another"));
}
