/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pair.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:56:47 by jodufour          #+#    #+#             */
/*   Updated: 2022/11/13 19:05:26 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_type_traits.hpp"
#include "arrays.hpp"
#include "benchmark.hpp"
#include "colors.hpp"
#include "headers.hpp"
#include "tester.hpp"
#include "e_ret.hpp"
#include PAIR_HEADER
#include MAKE_PAIR_HEADER
#include <cstring>
#include <ctime>
#include <iostream>

inline static int	__test_constructor(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Default constructor
		{
			g_start = clock();
			ft::pair<int, t_uint> const		ft_pair;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::pair<int, t_uint> const	std_pair;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_pair) != sizeof(std_pair) || memcmp(&ft_pair, &std_pair, sizeof(ft_pair)))
				ret = ISO_OK;
			if (ft_pair.first != std_pair.first || ft_pair.second != std_pair.second)
				return KO;
		}
		// Parameters constructor
		{
			g_start = clock();
			ft::pair<t_uint, int> const		ft_pair(42U, -42);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::pair<t_uint, int> const	std_pair(42U, -42);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_pair) != sizeof(std_pair) || memcmp(&ft_pair, &std_pair, sizeof(ft_pair)))
				ret = ISO_OK;
			if (ft_pair.first != std_pair.first || ft_pair.second != std_pair.second)
				return KO;
		}
		// Copy constructor
		{
			// Default pair
			{
				ft::pair<char const, char const> const	ft_pair0;
				std::pair<char const, char const> const	std_pair0;

				g_start = clock();
				ft::pair<char const, char const> const	ft_pair1(ft_pair0);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::pair<char const, char const> const	std_pair1(std_pair0);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_pair1) != sizeof(std_pair1) || memcmp(&ft_pair1, &std_pair1, sizeof(ft_pair1)))
					ret = ISO_OK;
				if (ft_pair1.first != std_pair1.first || ft_pair1.second != std_pair1.second)
					return KO;
			}
			// Filled pair
			{
				ft::pair<char const, char const> const	ft_pair0('!', '?');
				std::pair<char const, char const> const	std_pair0('!', '?');

				g_start = clock();
				ft::pair<char, char> const				ft_pair1(ft_pair0);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::pair<char, char> const				std_pair1(std_pair0);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_pair1) != sizeof(std_pair1) || memcmp(&ft_pair1, &std_pair1, sizeof(ft_pair1)))
					ret = ISO_OK;
				if (ft_pair1.first != std_pair1.first || ft_pair1.second != std_pair1.second)
					return KO;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_type_first_type(void)
{
	title(__func__);
	try
	{
		typedef ft::pair<long double, char>	pair_type;

		if (!tester::is_same<pair_type::first_type, long double>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_second_type(void)
{
	title(__func__);
	try
	{
		typedef ft::pair<long double, char>	pair_type;

		if (!tester::is_same<pair_type::second_type, char>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_make_pair(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::pair<t_luint, std::string>	ft_pair;
		std::pair<t_luint, std::string>	std_pair;

		for (idx = 0U ; idx < g_luint_size && idx < g_string_size ; ++idx)
		{
			g_start = clock();
			ft_pair = ft::make_pair(g_luint[idx], g_string[idx]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_pair = std::make_pair(g_luint[idx], g_string[idx]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_pair.first != std_pair.first || ft_pair.second != std_pair.second)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_assign(void)
{
	title(__func__);
	try
	{
		// Assigning mutable -> mutable
		{
			ft::pair<t_hhint, std::string>			ft_pair0(-1, "Hello World");
			ft::pair<t_hhint, std::string> const	ft_pair1(55, "How are you today ?");
			std::pair<t_hhint, std::string>			std_pair0(-1, "Hello World");
			std::pair<t_hhint, std::string> const	std_pair1(55, "How are you today ?");

			g_start = clock();
			ft_pair0 = ft_pair1;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_pair0 = std_pair1;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_pair0.first != std_pair0.first || ft_pair0.second != std_pair0.second)
				return KO;
		}
		// Assigning constant -> mutable
		{
			ft::pair<t_hhint, std::string>						ft_pair0(-1, "Hello World");
			ft::pair<t_hhint const, std::string const> const	ft_pair1(55, "How are you today ?");
			std::pair<t_hhint, std::string>						std_pair0(-1, "Hello World");
			std::pair<t_hhint const, std::string const> const	std_pair1(55, "How are you today ?");

			g_start = clock();
			ft_pair0 = ft_pair1;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_pair0 = std_pair1;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_pair0.first != std_pair0.first || ft_pair0.second != std_pair0.second)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_equivalent(void)
{
	title(__func__);
	try
	{
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator==(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator==(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second != second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 209U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 209U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator==(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator==(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first != first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.22f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.22f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator==(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator==(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first != first | second != second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.22f, 209U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.22f, 209U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator==(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator==(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_different(void)
{
	title(__func__);
	try
	{
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator!=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator!=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second != second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 209U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 209U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator!=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator!=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first != first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.22f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.22f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator!=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator!=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first != first | second != second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.22f, 209U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.22f, 209U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator!=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator!=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_lower(void)
{
	title(__func__);
	try
	{
		// first < first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first < first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first < first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_greater(void)
{
	title(__func__);
	try
	{
		// first < first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first < first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first < first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_lower_or_equivalent(void)
{
	title(__func__);
	try
	{
		// first < first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first < first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first < first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator<=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_operator_greater_or_equivalent(void)
{
	title(__func__);
	try
	{
		// first < first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first < first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first < first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(21.12f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first > first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(21.12f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(21.12f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second < second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 201U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second > second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 201U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 201U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
		// first == first | second == second
		{
			ft::pair<float, t_hhuint> const		ft_pair0(12.21f, 210U);
			ft::pair<float, t_hhuint> const		ft_pair1(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair0(12.21f, 210U);
			std::pair<float, t_hhuint> const	std_pair1(12.21f, 210U);
			bool								ft_ret;
			bool								std_ret;

			g_start = clock();
			ft_ret = ft::operator>=(ft_pair0, ft_pair1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_pair0, std_pair1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

int	test_pair(void)
{
	t_fct const				tests[] = {
		__test_constructor,
		__test_type_first_type,
		__test_type_second_type,
		__test_function_make_pair,
		__test_operator_assign,
		__test_operator_equivalent,
		__test_operator_different,
		__test_operator_lower,
		__test_operator_greater,
		__test_operator_lower_or_equivalent,
		__test_operator_greater_or_equivalent,
		NULL
	};
	t_uint					koCount;
	t_uint					idx;
	struct timespec const	delay = {SLEEP_TIME_SEC, SLEEP_TIME_NANOSEC};

	nanosleep(&delay, NULL);

	std::cerr << LIGHT_BLUE_FG;
	std::cout << "####################################################" << '\n';
	std::cout << "##                      PAIR                      ##" << '\n';
	std::cout << "####################################################" << '\n';
	std::cerr << RESET;

	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
	{
		nanosleep(&delay, NULL);

		switch (tests[idx]())
		{
			case IMP_OK:
				std::cerr << GREEN_FG;
				std::cout << "[OK]";
				std::cerr << RESET;
				break;

			case ISO_OK:
				std::cerr << YELLOW_FG;
				std::cout << "[OK]";
				std::cerr << RESET;
				break;

			case KO:
				std::cerr << RED_FG;
				std::cout << "[KO]";
				std::cerr << RESET;
				++koCount;
				break;
		}
		if (!g_ratio.empty())
		{
			std::cout << ' ';
			benchmark_best_case();
			std::cout << ' ';
			benchmark_worst_case();
			std::cout << ' ';
			benchmark_average_case();
			g_ratio.clear();
		}
		std::cout << '\n';
	}
	std::cout << '\n';
	return koCount;
}
