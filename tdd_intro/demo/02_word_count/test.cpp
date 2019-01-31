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

struct Occurrences
{
    int cout;
    std::string word;
    constexpr bool operator == (const Occurrences &rhs) const
    {
        return cout == rhs.cout;
    }

};

std::vector<Occurrences> GetPhraseOccurrences(std::string phrase)
{
    std::vector<Occurrences> result;
    Occurrences result2;

    if(phrase.empty())
    {
        return result;
    }
    return result;
}

TEST(PhraseOccurrencesTest, Input_empty_str_return_empty_str)
{
    std::vector<Occurrences> result;
    EXPECT_EQ(result, (GetPhraseOccurrences("")));
}

TEST(PhraseOccurrencesTest, Input_2_word__return_1_occurrences)
{
    std::vector<Occurrences> result;
    Occurrences testData = {1, "test"};
    result.push_back(testData);

    EXPECT_EQ(result, GetPhraseOccurrences("test test"));
}
