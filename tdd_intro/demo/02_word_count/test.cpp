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
#include <algorithm>

class PhraseOccurrences
{
    friend bool operator==(const PhraseOccurrences& lhs, const PhraseOccurrences& rhs);

public:
    PhraseOccurrences(const std::string& word, int count)
        : m_word(word), m_count(count)
    {

    }

    PhraseOccurrences(const PhraseOccurrences& other)
    {

    }

private:

    std::string phrase;
    std::string m_word;
    int m_count;
};

bool operator==(const PhraseOccurrences& lhs, const PhraseOccurrences& rhs)
{
    return (lhs.m_word == rhs.m_word)
            &&
            (lhs.m_count == rhs.m_count);
}

PhraseOccurrences GetPhraseOccurrences(const std::string& phrase)
{
    return PhraseOccurrences(phrase, 1);
}

TEST(PhraseOccurrencesTest, Test_1_word)
{
    PhraseOccurrences result("word", 1);
    EXPECT_EQ(result, GetPhraseOccurrences("word"));
}

TEST(PhraseOccurrencesTest, Test_2_word2)
{
    PhraseOccurrences result("word", 2);
    EXPECT_EQ(result, GetPhraseOccurrences("word word"));
}

