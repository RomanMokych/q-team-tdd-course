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
#include <iostream>
#include <string>

std::vector<std::string> get_words(const std::string& phrase)
{
    std::vector<std::string> words;
    std::stringstream stream(phrase);
    std::string word;
    while (std::getline(stream, word, ' '))
    {
        words.push_back(word);
    }

    return words;
}

std::map<const std::string, int> calc_duplicates(const std::string& phrase)
{
    std::map<const std::string, int> result;

    std::vector<std::string> words = get_words(phrase);
    for (auto current_word : words)
    {
        int occurances = 0;
        for (auto word : words)
        {
            if (current_word == word)
            {
                occurances++;
            }
        }
        result.insert(std::make_pair(current_word, occurances));
    }

    return result;
}


TEST(word_count, get_words_test)
{
    std::vector<std::string> words = {"olly", "olly", "in", "come", "free", "please", "please", "let", "it", "be", "in", "such", "manner", "olly"};

    EXPECT_EQ(words, get_words("olly olly in come free please please let it be in such manner olly"));
}

TEST(word_count, get_words_check_empty_strig)
{
    std::vector<std::string> words = {};

    EXPECT_EQ(words, get_words(""));
}

TEST(word_count, check_calc_duplicates)
{
    std::map<const std::string, int> result;
    result.insert(std::make_pair("olly", 3));
    result.insert(std::make_pair("in", 2));
    result.insert(std::make_pair("come", 1));
    result.insert(std::make_pair("free", 1));
    result.insert(std::make_pair("please", 2));
    result.insert(std::make_pair("let", 1));
    result.insert(std::make_pair("it", 1));
    result.insert(std::make_pair("be", 1));
    result.insert(std::make_pair("such", 1));
    result.insert(std::make_pair("manner", 1));

    EXPECT_EQ(result, calc_duplicates("olly olly in come free please please let it be in such manner olly"));
}

TEST(word_count, check_calc_duplicates_with_empty_string)
{
    std::map<const std::string, int> result;

    EXPECT_EQ(result, calc_duplicates(""));
}


