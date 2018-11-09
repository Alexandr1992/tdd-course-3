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

words_mt SeparateWords(const std::string& phrase)
{
    const size_t index = phrase.find_first_of(wordSeparator);

    if (index != std::string::npos)
    {
        return {{phrase.substr(0, index), 1}};
    }
    return {{phrase, 1}};
}

TEST(WordsCount, TestSeparateFirstWord)
{
    words_mt words = SeparateWords("hello");
    EXPECT_EQ(1, words.size());
    EXPECT_TRUE(words.find("hello") != words.end());
    EXPECT_EQ(1, words["hello"]);
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
