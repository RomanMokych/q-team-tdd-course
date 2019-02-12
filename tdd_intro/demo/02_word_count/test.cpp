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
    PhraseOccurrences(const std::string& word, int cout)
    {
        m_occurrences[word] = cout;
    }

    PhraseOccurrences(const std::string& str)
        : m_Phrase(str)
    {
        Process();
    }


private:
    void Process()
    {
        std::istringstream stringStream(m_Phrase);
        std::string str;
        while(stringStream>>str)
        {
            m_occurrences[str]++;
        }
    }

private:

    std::string m_Phrase;
    std::map<std::string, int> m_occurrences;
};

bool operator==(const PhraseOccurrences& lhs, const PhraseOccurrences& rhs)
{
    return (lhs.m_occurrences == rhs.m_occurrences);
}

PhraseOccurrences GetPhraseOccurrences(const std::string& phrase)
{
    return PhraseOccurrences(phrase);
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

TEST(PhraseOccurrencesTest, Test_3_word_occurrences1)
{
    PhraseOccurrences result({"word1", 1}, {"word2", 1});
    EXPECT_EQ(result, GetPhraseOccurrences("word1 word2"));
}
