#if 0

# include "type/filename.hh"
# include <stdint.h>
# include <string>

namespace tester {

using std::make_pair;
using std::pair;
using std::string;

t_filename const FILENAME_ARRAY[] = {
    "resource/alphabet",
    "resource/ascii",
    "resource/digits",
    "resource/empty",
    "resource/lorem_ipsum",
    "resource/only_z",
    "resource/reverse_ascii",
    "resource/reverse_digits",
    "resource/reverse_alphabet",
    "resource/reverse_lorem_ipsum",
};

char const CHAR_ARRAY[] = {
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
};

int8_t const INT8_ARRAY[] = {
    -10,
    11,
    -12,
    13,
    -14,
    15,
    -16,
    17,
    -18,
    19,
};

int16_t const INT16_ARRAY[] = {
    210,
    -211,
    212,
    -213,
    214,
    -215,
    216,
    -217,
    218,
    -219,
};

int32_t const INT32_ARRAY[] = {
    -1,
    -1234567890,
    -12,
    -123456789,
    -123,
    -12345678,
    -1234,
    -1234567,
    -12345,
    -123456,
};

int64_t const INT64_ARRAY[] = {
    1212121212121212,
    -2323232323232323,
    3434343434343434,
    -4545454545454545,
    5656456456456456,
    -6767676767676767,
    7878787878787878,
    -8989898989898989,
    9090909090909090,
    -0101010101010101,
};

uint8_t const UINT8_ARRAY[] = {
    255,
    254,
    253,
    252,
    251,
    250,
    249,
    248,
    247,
    246,
};

uint16_t const UINT16_ARRAY[] = {
    0,
    42,
    84,
    126,
    168,
    210,
    252,
    294,
    336,
    378,
};

uint32_t const UINT32_ARRAY[] = {
    4294967295,
    2147483647,
    1073741823,
    536870911,
    268435455,
    134217727,
    67108863,
    33554431,
    16777215,
    8388607,
};

uint64_t const UINT64_ARRAY[] = {
    424242424242420,
    424242424242421,
    424242424242422,
    424242424242423,
    424242424242424,
    424242424242425,
    424242424242426,
    424242424242427,
    424242424242428,
    424242424242429,
};

float const FLOAT_ARRAY[] = {
    9.9,
    7.7,
    8.8,
    5.5,
    6.6,
    3.3,
    4.4,
    1.1,
    2.2,
    -1.0,
};

double const DOUBLE_ARRAY[] = {
    0.0,
    1.9,
    2.8,
    3.7,
    4.6,
    5.5,
    6.4,
    7.3,
    8.2,
    9.1,
};

long double const LONG_DOUBLE_ARRAY[] = {
    987654321.0,
    98765432.10,
    9876543.210,
    987654.3210,
    98765.43210,
    9876.543210,
    987.6543210,
    98.75643210,
    9.876543210,
    .9876543210
};

string const STRING_ARRAY[] = {
    "Where is the moment we needed the most?",
    "You kick up the leaves, and the magic is lost.",
    "They tell me your blue sky's faded to grey.",
    "They tell me your passion's gone away.",
    "And I don't need to carrying on.",
    "You stand in the line just to hit a new low.",
    "You're faking a smile with the coffee to go.",
    "You tell me your life's been way off line.",
    "You're falling to pieces every time.",
    "And I don't need to carrying on!"
};

pair<int32_t const, char const> const PAIR_ARRAY[] = {
    make_pair(0, 'Z'),
    make_pair(1, 'Y'),
    make_pair(2, 'X'),
    make_pair(3, 'W'),
    make_pair(4, 'V'),
    make_pair(5, 'U'),
    make_pair(6, 'T'),
    make_pair(7, 'S'),
    make_pair(8, 'R'),
    make_pair(9, 'Q')
};

} // namespace tester

#endif
