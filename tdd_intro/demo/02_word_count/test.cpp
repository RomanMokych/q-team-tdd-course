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
#include <regex>

using namespace std;

map<string, int> count_words(const string &str)
{
    map<string, int> result;

    regex rgx("\\b\\w+\\b", regex::ECMAScript);

    smatch word;

    string::const_iterator searchStart(str.cbegin());
    while(regex_search(searchStart, str.cend(), word, rgx))
    {
        auto it = result.emplace(word[0], 0);
        it.first->second++;
        searchStart = word.suffix().first;
    }

    return result;
}

TEST(word_count, one_foo)
{
    auto result = count_words("foo");
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(1, result.at("foo"));
}

TEST(word_count, one_bar)
{
    auto result = count_words("bar");
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(1, result.at("bar"));
}

TEST(word_count, two_foo_devided_by_space)
{
    auto result = count_words("foo foo");
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(2, result.at("foo"));
}

TEST(word_count, foo_and_bar_devided_by_space)
{
    auto result = count_words("foo bar");
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(1, result.at("foo"));
    EXPECT_EQ(1, result.at("bar"));
}

TEST(word_count, foo_and_bar_devided_by_comma)
{
    auto result = count_words("foo,bar");
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(1, result.at("foo"));
    EXPECT_EQ(1, result.at("bar"));
}

TEST(word_count, a_lot_of_words_different_deviders)
{
    auto result = count_words("olly olly in:come free please.please  let ..it be? in such,:?! manner olly");
    ASSERT_EQ(10, result.size());
    EXPECT_EQ(3, result.at("olly"));
    EXPECT_EQ(2, result.at("in"));
    EXPECT_EQ(1, result.at("come"));
    EXPECT_EQ(1, result.at("free"));
    EXPECT_EQ(2, result.at("please"));
    EXPECT_EQ(1, result.at("let"));
    EXPECT_EQ(1, result.at("it"));
    EXPECT_EQ(1, result.at("be"));
    EXPECT_EQ(1, result.at("manner"));
    EXPECT_EQ(1, result.at("such"));
}

TEST(word_count, empty_string)
{
    auto result = count_words("");
    ASSERT_EQ(0, result.size());
}
