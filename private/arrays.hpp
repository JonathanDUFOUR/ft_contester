/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:27:44 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/10 18:50:06 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYS_HPP
# define ARRAYS_HPP

# include "t_int.hpp"
# include <string>

static char const *const	g_file[] = {
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

static char					g_char[] = {
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

static t_hhint				g_hhint[] = {
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

static t_hint				g_hint[] = {
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

static t_int				g_int[] = {
	-1,
	-1234567890
	-12,
	-123456789,
	-123,
	-12345678,
	-1234,
	-1234567,
	-12345,
	-123456,
};

static t_lint				g_lint[] = {
	1212121212121212L,
	-2323232323232323L,
	3434343434343434L,
	-4545454545454545L,
	5656456456456456L,
	-6767676767676767L,
	7878787878787878L,
	-8989898989898989L,
	9090909090909090L,
	-0101010101010101L,
};

static t_hhuint				g_hhuint[] = {
	255U,
	254U,
	253U,
	252U,
	251U,
	250U,
	249U,
	248U,
	247U,
	246U,
};

static t_huint				g_huint[] = {
	0U,
	42U,
	84U,
	126U,
	168U,
	210U,
	252U,
	294U,
	336U,
	378U,
};

static t_uint				g_uint[] = {
	4294967295U,
	2147483647U,
	1073741823U,
	536870911U,
	268435455U,
	134217727U,
	67108863U,
	33554431U,
	16777215U,
	8388607U,
};

static t_luint				g_luint[] = {
	424242424242420LU,
	424242424242421LU,
	424242424242422LU,
	424242424242423LU,
	424242424242424LU,
	424242424242425LU,
	424242424242426LU,
	424242424242427LU,
	424242424242428LU,
	424242424242429LU,
};

static float				g_float[] = {
	9.9f,
	7.7f,
	8.8f,
	5.5f,
	6.6f,
	3.3f,
	4.4f,
	1.1f,
	2.2f,
	-1.0f,
};

static double				g_double[] = {
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

static long double			g_long_double[] = {
	987654321.0,
	98765432.10,
	9876543.210,
	987654.3210,
	98765.43210,
	9876.543210,
	987.6543210,
	98.75643210,
	9.876543210,
	.9876543210,
};

static std::string			g_string[] = {
	std::string("Where is the moment we needed the most?"),
	std::string("You kick up the leaves, and the magic is lost."),
	std::string("They tell me your blue sky's faded to grey."),
	std::string("They tell me your passion's gone away."),
	std::string("And I don't need to carrying on."),
	std::string("You stand in the line just to hit a new low."),
	std::string("You're faking a smile with the coffee to go."),
	std::string("You tell me your life's been way off line."),
	std::string("You're falling to pieces every time."),
	std::string("And I don't need to carrying on!"),
};

static std::pair<int, char>	g_pair[] = {
	std::pair<int, char>(0, 'Z'),
	std::pair<int, char>(1, 'Y'),
	std::pair<int, char>(2, 'X'),
	std::pair<int, char>(3, 'W'),
	std::pair<int, char>(4, 'V'),
	std::pair<int, char>(5, 'U'),
	std::pair<int, char>(6, 'T'),
	std::pair<int, char>(7, 'S'),
	std::pair<int, char>(8, 'R'),
	std::pair<int, char>(9, 'Q'),
};

static size_t const			g_file_size = sizeof(g_file) / sizeof(*g_file);
static size_t const			g_char_size = sizeof(g_char) / sizeof(*g_char);
static size_t const			g_hhint_size = sizeof(g_hhint) / sizeof(*g_hhint);
static size_t const			g_hint_size = sizeof(g_hint) / sizeof(*g_hint);
static size_t const			g_int_size = sizeof(g_int) / sizeof(*g_int);
static size_t const			g_lint_size = sizeof(g_lint) / sizeof(*g_lint);
static size_t const			g_hhuint_size = sizeof(g_hhuint) / sizeof(*g_hhuint);
static size_t const			g_huint_size = sizeof(g_huint) / sizeof(*g_huint);
static size_t const			g_uint_size = sizeof(g_uint) / sizeof(*g_uint);
static size_t const			g_luint_size = sizeof(g_luint) / sizeof(*g_luint);
static size_t const			g_float_size = sizeof(g_float) / sizeof(*g_float);
static size_t const			g_double_size = sizeof(g_double) / sizeof(*g_double);
static size_t const			g_long_double_size = sizeof(g_long_double) / sizeof(*g_long_double);
static size_t const			g_string_size = sizeof(g_string) / sizeof(*g_string);
static size_t const			g_pair_size = sizeof(g_pair) / sizeof(*g_pair);

#endif
