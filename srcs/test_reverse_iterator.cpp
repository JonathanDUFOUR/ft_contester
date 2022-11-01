/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reverse_iterator.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:40:33 by jodufour          #+#    #+#             */
/*   Updated: 2022/11/01 14:41:55 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arrays.hpp"
#include "benchmark.hpp"
#include "colors.hpp"
#include "headers.hpp"
#include "iterator/restrictor/random_access_iterator_restrictor.tpp"
#include "tester.hpp"
#include REVERSE_ITERATOR_HEADER
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

inline static int	__test_constructor(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Default constructor
		{
			g_start = clock();
			ft::reverse_iterator<tester::random_access_iterator_restrictor<std::ostream const *> > const	ft_rit;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::reverse_iterator<tester::random_access_iterator_restrictor<std::ostream const *> > const	std_rit;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_rit) != sizeof(std_rit) ||
				memcmp(&ft_rit, &std_rit, sizeof(ft_rit)))
				return EXIT_FAILURE;
		}
		// Wrap constructor
		{
			for (idx = 0U ; idx < g_int_size ; ++idx)
			{
				tester::random_access_iterator_restrictor<int const *> const							it(&g_int[idx]);

				g_start = clock();
				ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> > const		ft_rit(it);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> > const	std_rit(it);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_rit) != sizeof(std_rit) || memcmp(&ft_rit, &std_rit, sizeof(ft_rit)))
					return EXIT_FAILURE;
			}
		}
		// Copy constructor
		{
			// Default position
			{
				ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> > const		ft_rit0;
				std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> > const	std_rit0;

				g_start = clock();
				ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> > const		ft_rit1(ft_rit0);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> > const	std_rit1(std_rit0);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_rit1) != sizeof(std_rit1) ||
					memcmp(&ft_rit1, &std_rit1, sizeof(ft_rit1)))
					return EXIT_FAILURE;
			}
			// Defined position
			{
				for (idx = 0U ; idx < g_int_size ; ++idx)
				{
					tester::random_access_iterator_restrictor<int const *> const								it(&g_int[idx]);

					g_start = clock();
					ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> > const			ft_rit0(it);
					g_ft_duration = clock() - g_start;
					g_ft_duration += !g_ft_duration;

					g_start = clock();
					std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> > const		std_rit0(it);
					g_std_duration = clock() - g_start;
					g_std_duration += !g_std_duration;

					g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

					g_start = clock();
					ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> > const			ft_rit1(ft_rit0);
					g_ft_duration = clock() - g_start;
					g_ft_duration += !g_ft_duration;

					g_start = clock();
					std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> > const		std_rit1(std_rit0);
					g_std_duration = clock() - g_start;
					g_std_duration += !g_std_duration;

					g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

					g_start = clock();
					ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	ft_rit2(ft_rit1);
					g_ft_duration = clock() - g_start;
					g_ft_duration += !g_ft_duration;

					g_start = clock();
					std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	std_rit2(std_rit1);
					g_std_duration = clock() - g_start;
					g_std_duration += !g_std_duration;

					g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

					if ((sizeof (ft_rit1) != sizeof (std_rit1)) || sizeof(ft_rit2) != sizeof(std_rit2) ||
						(memcmp(&ft_rit0, &ft_rit1, sizeof(ft_rit0)) != memcmp(&std_rit0, &std_rit1, sizeof(std_rit0))) ||
						(memcmp(&ft_rit1, &ft_rit2, sizeof(ft_rit1)) != memcmp(&std_rit1, &std_rit2, sizeof(std_rit1))))
						return EXIT_FAILURE;
				}
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_base(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_double_size ; ++idx)
		{
			tester::random_access_iterator_restrictor<double const *> const							it(&g_double[idx]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<double const *> > const	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<double const *> > const	std_rit(it);
			tester::random_access_iterator_restrictor<double const *>								ft_ret;
			tester::random_access_iterator_restrictor<double const *>								std_ret;

			g_start = clock();
			ft_ret = ft_rit.base();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_rit.base();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_assign(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::reverse_iterator<tester::random_access_iterator_restrictor<std::string const *> >	ft_rit0;
		std::reverse_iterator<tester::random_access_iterator_restrictor<std::string const *> >	std_rit0;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			tester::random_access_iterator_restrictor<std::string *> const									it0(&g_string[idx]);
			tester::random_access_iterator_restrictor<std::string const *> const							it1(&g_string[idx]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> > const			ft_rit1(it0);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<std::string const *> > const		ft_rit2(it1);
			std::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> > const			std_rit1(it0);
			std::reverse_iterator<tester::random_access_iterator_restrictor<std::string const *> > const	std_rit2(it1);

			g_start = clock();
			ft_rit0 = ft_rit1;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_rit0 = std_rit1;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (memcmp(&ft_rit0, &ft_rit1, sizeof(ft_rit0)) != memcmp(&std_rit0, &std_rit1, sizeof(std_rit0)))
				return EXIT_FAILURE;

			g_start = clock();
			ft_rit0 = ft_rit2;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_rit0 = std_rit2;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (memcmp(&ft_rit0, &ft_rit2, sizeof(ft_rit0)) != memcmp(&std_rit0, &std_rit2, sizeof(std_rit0)))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_dereference(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 1U ; idx <= g_hint_size ; ++idx)
			{
				tester::random_access_iterator_restrictor<t_hint *> const							it(&g_hint[idx]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<t_hint *> > const	ft_rit(it);
				std::reverse_iterator<tester::random_access_iterator_restrictor<t_hint *> > const	std_rit(it);

				g_start = clock();
				t_hint &ft_nb = *ft_rit;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				t_hint &std_nb = *std_rit;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_nb != std_nb)
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 1U ; idx <= g_hint_size ; ++idx)
			{
				tester::random_access_iterator_restrictor<t_hint const *> const							it(&g_hint[idx]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<t_hint const *> > const	ft_rit(it);
				std::reverse_iterator<tester::random_access_iterator_restrictor<t_hint const *> > const	std_rit(it);

				g_start = clock();
				t_hint const &ft_nb = *ft_rit;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				t_hint const &std_nb = *std_rit;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				if (ft_nb != std_nb)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_maddress(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 1U ; idx <= g_pair_size ; ++idx)
			{
				tester::random_access_iterator_restrictor<std::pair<int, char> *> const							it(&g_pair[idx]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<std::pair<int, char> *> > const	ft_rit(it);
				std::reverse_iterator<tester::random_access_iterator_restrictor<std::pair<int, char> *> > const	std_rit(it);

				g_start = clock();
				int	&ft_first = ft_rit->first;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				int	&std_first = std_rit->first;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_first != std_first)
					return EXIT_FAILURE;

				g_start = clock();
				char	&ft_second = ft_rit->second;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				char	&std_second = std_rit->second;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_second != std_second)
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 1U ; idx <= g_pair_size ; ++idx)
			{
				tester::random_access_iterator_restrictor<std::pair<int, char> const *> const							it(&g_pair[idx]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<std::pair<int, char> const *> > const	ft_rit(it);
				std::reverse_iterator<tester::random_access_iterator_restrictor<std::pair<int, char> const *> > const	std_rit(it);

				g_start = clock();
				int const	&ft_first = ft_rit->first;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				int const	&std_first = std_rit->first;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_first != std_first)
					return EXIT_FAILURE;

				g_start = clock();
				char const	&ft_second = ft_rit->second;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				char const	&std_second = std_rit->second;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_second != std_second)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_increment(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Prefix incrementation
		{
			tester::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[g_luint_size]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);

			for (idx = 1U ; idx < g_luint_size ; ++idx)
			{
				g_start = clock();
				ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	&ft_ret = ++ft_rit;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	&std_ret = ++std_rit;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base())
					return EXIT_FAILURE;
			}
		}
		// Postfix incrementation
		{
			tester::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[g_luint_size]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	ft_ret;
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	std_ret;

			for (idx = 1U ; idx > g_luint_size ; ++idx)
			{
				g_start = clock();
				ft_ret = ft_rit++;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std_rit++;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base())
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_decrement(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Prefix decrementation
		{
			tester::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[0]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);

			for (idx = 1U ; idx < g_luint_size ; ++idx)
			{
				g_start = clock();
				ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	&ft_ret = --ft_rit;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	&std_ret = --std_rit;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base())
					return EXIT_FAILURE;
			}
		}
		// Postfix decrementation
		{
			tester::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[0]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	ft_ret;
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	std_ret;

			for (idx = 1U ; idx < g_luint_size ; ++idx)
			{
				g_start = clock();
				ft_ret = ft_rit--;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std_rit--;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base())
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_add_assign(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_luint_size ; ++idx)
		{
			tester::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[g_luint_size - 1]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);

			g_start = clock();
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	&ft_ret = ft_rit += idx;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	&std_ret = std_rit += idx;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base())
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_sub_assign(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_luint_size ; ++idx)
		{
			tester::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[0]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);

			g_start = clock();
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	&ft_ret = ft_rit -= idx;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_luint const *> >	&std_ret = std_rit -= idx;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base())
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_add(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Member operator
		{
			tester::random_access_iterator_restrictor<float const *> const							it(&g_float[g_float_size - 1]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const	std_rit(it);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> >			ft_ret;
			std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> >		std_ret;

			for (idx = 0U ; idx < g_float_size ; ++idx)
			{
				g_start = clock();
				ft_ret = ft_rit + idx;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std_rit + idx;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret.base() != std_ret.base())
					return EXIT_FAILURE;
			}
		}
		// Non-member operator
		{
			tester::random_access_iterator_restrictor<float const *> const							it(&g_float[g_float_size - 1]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const	std_rit(it);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> >			ft_ret;
			std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> >		std_ret;

			for (idx = 0U ; idx < g_float_size ; ++idx)
			{
				g_start = clock();
				ft_ret = idx + ft_rit;
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = idx + std_rit;
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret.base() != std_ret.base())
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_sub(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		tester::random_access_iterator_restrictor<float const *> const							it(&g_float[0]);
		ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const	ft_rit(it);
		std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const	std_rit(it);
		ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> >			ft_ret;
		std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> >		std_ret;

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			g_start = clock();
			ft_ret = ft_rit - idx;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_rit - idx;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret.base() != std_ret.base())
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_access(void)
{
	t_uint		idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			tester::random_access_iterator_restrictor<t_hhuint *> const							it(&g_hhuint[g_hhuint_size]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_hhuint *> > const	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_hhuint *> > const	std_rit(it);

			for (idx = 0U ; idx < g_hhuint_size ; ++idx)
			{
				g_start = clock();
				t_hhuint	&ft_ret = ft_rit[idx];
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				t_hhuint	&std_ret = std_rit[idx];
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			tester::random_access_iterator_restrictor<t_hhuint const *> const							it(&g_hhuint[g_hhuint_size]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<t_hhuint const *> > const	ft_rit(it);
			std::reverse_iterator<tester::random_access_iterator_restrictor<t_hhuint const *> > const	std_rit(it);

			for (idx = 0U ; idx < g_hhuint_size ; ++idx)
			{
				g_start = clock();
				t_hhuint const	&ft_ret = ft_rit[idx];
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				t_hhuint const	&std_ret = std_rit[idx];
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_distance(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		ft::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> >::difference_type	ft_ret;
		std::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> >::difference_type	std_ret;

		for (idx0 = 0U ; idx0 < g_string_size ; ++idx0)
		{
			tester::random_access_iterator_restrictor<std::string *> const							it0(&g_string[idx0]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> > const	ft_rit0(it0);
			std::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_string_size ; ++idx1)
			{
				tester::random_access_iterator_restrictor<std::string const *> const								it1(&g_string[idx1]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<std::string const *> const> const	ft_rit1(it1);
				std::reverse_iterator<tester::random_access_iterator_restrictor<std::string const *> const> const	std_rit1(it1);

				g_start = clock();
				ft_ret = ft::operator-(ft_rit0 , ft_rit1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator-(std_rit0 , std_rit1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_equivalent(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		bool	ft_ret;
		bool	std_ret;

		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			tester::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				tester::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				g_start = clock();
				ft_ret = ft::operator==(ft_rit0 , ft_rit1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator==(std_rit0 , std_rit1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_different(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		bool	ft_ret;
		bool	std_ret;

		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			tester::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				tester::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				g_start = clock();
				ft_ret = ft::operator!=(ft_rit0 , ft_rit1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator!=(std_rit0 , std_rit1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_lower(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		bool	ft_ret;
		bool	std_ret;

		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			tester::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				tester::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				g_start = clock();
				ft_ret = ft::operator<(ft_rit0 , ft_rit1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<(std_rit0 , std_rit1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_greater(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		bool	ft_ret;
		bool	std_ret;

		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			tester::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				tester::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				g_start = clock();
				ft_ret = ft::operator>(ft_rit0 , ft_rit1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>(std_rit0 , std_rit1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_lower_or_equivalent(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		bool	ft_ret;
		bool	std_ret;

		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			tester::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				tester::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				g_start = clock();
				ft_ret = ft::operator<=(ft_rit0 , ft_rit1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<=(std_rit0 , std_rit1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_greater_or_equivalent(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		bool	ft_ret;
		bool	std_ret;

		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			tester::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<tester::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				tester::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<tester::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				g_start = clock();
				ft_ret = ft::operator>=(ft_rit0 , ft_rit1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>=(std_rit0 , std_rit1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int	test_reverse_iterator(void)
{
	t_fct const	tests[] = {
		__test_constructor,
		__test_function_base,
		__test_operator_assign,
		__test_operator_dereference,
		__test_operator_maddress,
		__test_operator_increment,
		__test_operator_decrement,
		__test_operator_add_assign,
		__test_operator_sub_assign,
		__test_operator_add,
		__test_operator_sub,
		__test_operator_access,
		__test_operator_distance,
		__test_operator_equivalent,
		__test_operator_different,
		__test_operator_lower,
		__test_operator_greater,
		__test_operator_lower_or_equivalent,
		__test_operator_greater_or_equivalent,
		NULL,
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << LIGHT_BLUE_FG;
	std::cout << "####################################################" << '\n';
	std::cout << "##                REVERSE ITERATOR                ##" << '\n';
	std::cout << "####################################################" << '\n';
	std::cerr << RESET;

	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
	{
		switch (tests[idx]())
		{
			case EXIT_SUCCESS:
				std::cerr << GREEN_FG;
				std::cout << "[OK]";
				std::cerr << RESET;
				break;

			case EXIT_FAILURE:
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
