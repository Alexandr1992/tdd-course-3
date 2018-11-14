/*### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices. The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification
#### User Story 1

The following format is created by the machine:
```
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
```
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

Example input and output
```
 _  _  _  _  _  _  _  _  _
| || || || || || || || || |
|_||_||_||_||_||_||_||_||_|

=> 000000000

  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 111111111

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
|_ |_ |_ |_ |_ |_ |_ |_ |_

=> 222222222

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
 _| _| _| _| _| _| _| _| _|

=> 333333333

|_||_||_||_||_||_||_||_||_|
  |  |  |  |  |  |  |  |  |

=> 444444444

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
 _| _| _| _| _| _| _| _| _|

=> 555555555

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
|_||_||_||_||_||_||_||_||_|

=> 666666666

 _  _  _  _  _  _  _  _  _
  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 777777777

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
|_||_||_||_||_||_||_||_||_|

=> 888888888

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
 _| _| _| _| _| _| _| _| _|

=> 999999999

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|

=> 123456789
```
*/
#include <gtest/gtest.h>
#include <string>

const unsigned short g_digitLen = 3;
const unsigned short g_linesInDigit = 3;
struct Digit
{
    std::string lines[g_linesInDigit];
};

const unsigned short g_digitsOnDisplay = 9;
struct Display
{
    std::string lines[g_linesInDigit];
};

std::map<std::string, char> g_digitsMap{
    { " _ | ||_|", '0'},
    { "     |  |", '1'},
    { " _  _||_ ", '2'},
    { " _  _| _|", '3'},
    { "   |_|  |", '4'},
    { " _ |_  _|", '5'},
    { " _ |_ |_|", '6'},
    { " _   |  |", '7'},
    { " _ |_||_|", '8'},
    { " _ |_| _|", '9'}
};

const Digit s_digit0 = { " _ ",
                         "| |",
                         "|_|"
                       };
const Digit s_digit1 = { "   ",
                         "  |",
                         "  |"
                       };
const Digit s_digit2 = { " _ ",
                         " _|",
                         "|_ "
                       };
const Digit s_digit3 = { " _ ",
                         " _|",
                         " _|"
                       };
const Digit s_digit4 = { "   ",
                         "|_|",
                         "  |"
                       };
const Digit s_digit5 = { " _ ",
                         "|_ ",
                         " _|"
                       };
const Digit s_digit6 = { " _ ",
                         "|_ ",
                         "|_|"
                       };
const Digit s_digit7 = { " _ ",
                         "  |",
                         "  |"
                       };
const Digit s_digit8 = { " _ ",
                         "|_|",
                         "|_|"
                       };
const Digit s_digit9 = { " _ ",
                         "|_|",
                         " _|"
                       };

const Display s_displayAll0 = { " _  _  _  _  _  _  _  _  _ ",
                                "| || || || || || || || || |",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll1 = { "                           ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll2 = {  " _  _  _  _  _  _  _  _  _ ",
                                 " _| _| _| _| _| _| _| _| _|",
                                 "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
};

const Display s_displayAll3 = { " _  _  _  _  _  _  _  _  _ ",
                                " _| _| _| _| _| _| _| _| _|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll4 = { "                           ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll5 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll6 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll7 = { " _  _  _  _  _  _  _  _  _ ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll8 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll9 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_display123456789 = { "    _  _     _  _  _  _  _ ",
                                     "  | _| _||_||_ |_   ||_||_|",
                                     "  ||_  _|  | _||_|  ||_| _|"
};

char DetectDigit(const Digit& digit)
{
    const std::string digitHash = digit.lines[0] + digit.lines[1] + digit.lines[2];

    const auto& value = g_digitsMap.find(digitHash);
    if (value != g_digitsMap.end())
    {
        return g_digitsMap[digitHash];
    }

    throw std::runtime_error("Invalid digit format");
}

std::string ParseDigits(const Display& display)
{
    return "0";
}

Digit ParseDigitFromDisplay(const Display& display, size_t pos)
{
    Digit digit;
    const size_t offset = pos * g_digitLen;
    for(size_t i = 0; i < g_linesInDigit; ++i)
    {
        digit.lines[i] = display.lines[i].substr(offset, g_digitLen);
    }

    return digit;
}

TEST(BankOcr, TestDetectValidDigits)
{
    EXPECT_EQ('0', DetectDigit(s_digit0));
    EXPECT_EQ('1', DetectDigit(s_digit1));
    EXPECT_EQ('2', DetectDigit(s_digit2));
    EXPECT_EQ('3', DetectDigit(s_digit3));
    EXPECT_EQ('4', DetectDigit(s_digit4));
    EXPECT_EQ('5', DetectDigit(s_digit5));
    EXPECT_EQ('6', DetectDigit(s_digit6));
    EXPECT_EQ('7', DetectDigit(s_digit7));
    EXPECT_EQ('8', DetectDigit(s_digit8));
    EXPECT_EQ('9', DetectDigit(s_digit9));
}

TEST(BankOcr, TestThrowExceptionWhenDetectInvalidDigits)
{
    const static Digit invalidDigit = { " _ ",
                                        "| |",
                                        "| |"};

    EXPECT_THROW(DetectDigit(invalidDigit), std::runtime_error);
}

TEST(BankOcr, DISABLED_TestParseFirstDigitFromDisplay0)
{
    EXPECT_EQ('0', ParseDigits(s_displayAll0)[0]);
}

TEST(BankOcr, TestParseDigit1FromDisplayNumber0)
{
    const Digit digit = ParseDigitFromDisplay(s_display123456789, 0);

    EXPECT_EQ(s_digit1.lines[0], digit.lines[0]);
    EXPECT_EQ(s_digit1.lines[1], digit.lines[1]);
    EXPECT_EQ(s_digit1.lines[2], digit.lines[2]);
}

TEST(BankOcr, TestExceptionWhenParseUnknownDisplayOffset)
{
    EXPECT_THROW(ParseDigitFromDisplay(s_display123456789, 10), std::runtime_error);
}
