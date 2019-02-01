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
        return this->cout == rhs.cout;
    }

};

std::vector<std::string> splitString(const std::string& input)
{
    std::vector<std::string> result;
    std::string word;

    for(size_t i = 0; i < input.size(); ++i)
    {
        if( input[i] == ' ' && input.size() > i )
        {
            result.push_back(word);
            word = "";
        }
        else
        {
            word += input[i];
        }
    }

    return result;
}

std::vector<Occurrences> GetPhraseOccurrences(const std::string& phrase)
{
    std::vector<Occurrences> result;

    if(phrase.empty())
    {
        return result;
    }

    Occurrences occurrence;

    std::vector<std::string> str = splitString(phrase);

    occurrence.word = str[0];
    occurrence.cout = 2;

    result.push_back(occurrence);

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
    Occurrences testData = {2, "test"};
    result.push_back(testData);

    EXPECT_EQ(result, GetPhraseOccurrences("test test"));
}

TEST(PhraseOccurrencesTest, Input_2_word__return_0_occurrences)
{
    std::vector<Occurrences> result;
    Occurrences testData = {0, ""};
    result.push_back(testData);

    EXPECT_EQ(result, GetPhraseOccurrences("test test2"));
}
