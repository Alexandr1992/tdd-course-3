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

using words_mt = std::map<std::string, size_t>;
const static char wordSeparator = ' ';

std::string TrimWord(std::string& phrase, const char seperator)
{
    size_t index = phrase.find_first_of(seperator);
    std::string word;

    if (index == std::string::npos || index == phrase.size())
    {
        word = phrase;
        phrase.clear();
    }
    else
    {
        word = phrase.substr(0, index);
        phrase = phrase.substr(index + 1, phrase.size() - index);
    }

    return word;
}

words_mt SeparateWords(const std::string& phrase)
{
    std::string separatedPhrase = phrase;
    words_mt words;
    size_t wordEndIndex = 0;

    do
    {
        separatedPhrase = phrase.substr(wordEndIndex, phrase.size() - wordEndIndex);
        wordEndIndex = separatedPhrase.find_first_of(wordSeparator);
        if (wordEndIndex == std::string::npos)
        {
            wordEndIndex = phrase.size();
        }

        std::string word = separatedPhrase.substr(0, wordEndIndex);
        ++words[word];
        ++wordEndIndex;
    }
    while(wordEndIndex < phrase.size());

    return words;
}

TEST(WordsCount, TestSeparateFirstWord)
{
    words_mt words = SeparateWords("hello");
    EXPECT_EQ(1, words.size());
    EXPECT_TRUE(words.find("hello") != words.end());
    EXPECT_EQ(1, words["hello"]);
}

TEST(WordsCount, TestTrimWord)
{
    std::string phrase = "tdd course";

    EXPECT_EQ("tdd", TrimWord(phrase, ' '));
    EXPECT_EQ("course", phrase);

    EXPECT_EQ("course", TrimWord(phrase, ' '));
    EXPECT_EQ("", phrase);
}

TEST(WordsCount, TestSeparateSeveralWords)
{
    words_mt words = SeparateWords("hello bro");
    EXPECT_EQ(2, words.size());

    EXPECT_TRUE(words.find("hello") != words.end());
    EXPECT_EQ(1, words["hello"]);

    EXPECT_TRUE(words.find("bro") != words.end());
    EXPECT_EQ(1, words["bro"]);
}
