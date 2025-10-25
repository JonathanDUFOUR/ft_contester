#include "type/array.hh" // tester::array
#include "type/filename.hh" // tester::t_filename
#include "type/fundamentals.hh" // tester::t_{{i,u}{8,16,32,64},char}
#include "type/str.hh" // tester::t_str
#include <utility> // std::pair

namespace tester {

using std::pair;

template <>
t_filename array<t_filename>::s_inner[] = {
    "resource/alphabet",
    "resource/ascii",
    "resource/digits",
    "resource/empty",
    "resource/lorem_ipsum",
    "resource/only_z",
    "resource/reverse_ascii",
    "resource/reverse_digits",
    "resource/reverse_alphabet",
    "resource/reverse_lorem_ipsum"
};

template <>
t_char array<t_char>::s_inner[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'};

template <>
t_i8 array<t_i8>::s_inner[] = {-10, 11, -12, 13, -14, 15, -16, 17, -18, 19};

template <>
t_i16 array<t_i16>::s_inner[] = {210, -211, 212, -213, 214, -215, 216, -217, 218, -219};

template <>
t_i32 array<t_i32>::s_inner[] = {
    -1, -1234567890, -12, -123456789, -123, -12345678, -1234, -1234567, -12345, -123456
};

template <>
t_i64 array<t_i64>::s_inner[] = {
    1212121212121212,
    -2323232323232323,
    3434343434343434,
    -4545454545454545,
    5656456456456456,
    -6767676767676767,
    7878787878787878,
    -8989898989898989,
    9090909090909090,
    -0101010101010101
};

template <>
t_u8 array<t_u8>::s_inner[] = {255, 254, 253, 252, 251, 250, 249, 248, 247, 246};

template <>
t_u16 array<t_u16>::s_inner[] = {0, 42, 84, 126, 168, 210, 252, 294, 336, 378};

template <>
t_u32 array<t_u32>::s_inner[] = {
    4294967295,
    2147483647,
    1073741823,
    536870911,
    268435455,
    134217727,
    67108863,
    33554431,
    16777215,
    8388607
};

template <>
t_u64 array<t_u64>::s_inner[] = {
    424242424242420,
    424242424242421,
    424242424242422,
    424242424242423,
    424242424242424,
    424242424242425,
    424242424242426,
    424242424242427,
    424242424242428,
    424242424242429
};

template <>
t_float array<t_float>::s_inner[] = {9.9, 7.7, 8.8, 5.5, 6.6, 3.3, 4.4, 1.1, 2.2, -1.0};

template <>
t_double array<t_double>::s_inner[] = {0.0, 1.9, 2.8, 3.7, 4.6, 5.5, 6.4, 7.3, 8.2, 9.1};

template <>
t_long_double array<t_long_double>::s_inner[] = {
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

template <>
t_str array<t_str>::s_inner[] = {
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

template <>
pair<t_i32, t_char> const array<pair<t_i32, t_char> >::s_inner[] = {
    pair<t_i32, t_char>(0, 'Z'),
    pair<t_i32, t_char>(1, 'Y'),
    pair<t_i32, t_char>(2, 'X'),
    pair<t_i32, t_char>(3, 'W'),
    pair<t_i32, t_char>(4, 'V'),
    pair<t_i32, t_char>(5, 'U'),
    pair<t_i32, t_char>(6, 'T'),
    pair<t_i32, t_char>(7, 'S'),
    pair<t_i32, t_char>(8, 'R'),
    pair<t_i32, t_char>(9, 'Q')
};

} // namespace tester
