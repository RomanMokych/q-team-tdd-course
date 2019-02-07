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

public:
    PhraseOccurrences(const std::string& phrase)
    {

    }

    PhraseOccurrences(const PhraseOccurrences& other)
    {

    }

//    bool operator==(const PhraseOccurrences& other)
//    {
//        return true;
//    }

private:
};
bool operator==(const PhraseOccurrences& lhs, const PhraseOccurrences& rhs)
{
    return false;
}

PhraseOccurrences GetPhraseOccurrences(const std::string& phrase)
{
    return PhraseOccurrences(phrase);
}

TEST(PhraseOccurrencesTest, Test_1_word)
{
    PhraseOccurrences result("");
    EXPECT_EQ(result, GetPhraseOccurrences("test"));
}
