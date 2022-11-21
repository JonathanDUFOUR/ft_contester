/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:06:05 by jodufour          #+#    #+#             */
/*   Updated: 2022/11/13 19:11:02 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_type_traits.hpp"
#include "arrays.hpp"
#include "benchmark.hpp"
#include "colors.hpp"
#include "headers.hpp"
#include "iterator/requirements_check.tpp"
#include "iterator/restrictor/random_access_iterator_restrictor.tpp"
#include "tester.hpp"
#include "e_ret.hpp"
#include SET_HEADER
#include <algorithm>
#include <ctime>
#include <iostream>
#include <set>

inline static int	__test_constructor_default(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		g_start = clock();
		ft::set<int> const	ft_set;
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std::set<int> const	std_set;
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set)))
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_constructor_range(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Range of input_iterator_restrictor
		{
			tester::input_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
			tester::input_iterator_restrictor<t_huint const *> const	it1(&g_huint[0]);

			g_start = clock();
			ft::set<t_huint> const										ft_set(it0, it1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::set<t_huint> const										std_set(it0, it1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set)))
				ret = ISO_OK;
		}
		// Range of forward_iterator_restrictor
		{
			tester::forward_iterator_restrictor<void *const *> const	it;

			g_start = clock();
			ft::set<void *> const										ft_set(it, it);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::set<void *> const										std_set(it, it);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set)))
				ret = ISO_OK;
		}
		// Range of random_access_iterator
		{
			tester::random_access_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
			tester::random_access_iterator_restrictor<t_huint const *> const	it1(&g_huint[g_huint_size]);

			g_start = clock();
			ft::set<t_huint> const												ft_set(it0, it1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::set<t_huint> const												std_set(it0, it1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set)))
				ret = ISO_OK;
		}
		// Range of char const *
		{
			g_start = clock();
			ft::set<char> const		ft_set(&g_char[0], &g_char[g_char_size]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::set<char> const	std_set(&g_char[0], &g_char[g_char_size]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set)))
				ret = ISO_OK;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_constructor_copy(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Default set
		{
			ft::set<int> const	ft_set0;
			std::set<int> const	std_set0;

			g_start = clock();
			ft::set<int> const	ft_set1(ft_set0);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::set<int> const	std_set1(std_set0);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_set1) != sizeof(std_set1) || memcmp(&ft_set1, &std_set1, sizeof(ft_set1)))
				ret = ISO_OK;
		}
		// Filled set
		{
			ft::set<int> const	ft_set0(&g_int[0], &g_int[g_int_size]);
			std::set<int> const	std_set0(&g_int[0], &g_int[g_int_size]);

			g_start = clock();
			ft::set<int> const	ft_set1(ft_set0);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::set<int> const	std_set1(std_set0);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_set1) != sizeof(std_set1) || memcmp(&ft_set1, &std_set1, sizeof(ft_set1)))
				ret = ISO_OK;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_default_template_type_Compare(void)
{
	title(__func__);

	typedef ft::set<float>						set_type_0;
	typedef ft::set<float, std::less<float> >	set_type_1;

	if (!tester::is_same<set_type_0, set_type_1>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_default_template_type_Alloc(void)
{
	title(__func__);

	typedef ft::set<float>												set_type_0;
	typedef ft::set<float, std::less<float>, std::allocator<float> >	set_type_1;

	if (!tester::is_same<set_type_0, set_type_1>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_key_type(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint>	set_type;

		if (!tester::is_same<set_type::key_type, t_lint>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_value_type(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint>	set_type;

		if (!tester::is_same<set_type::value_type, t_lint>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_key_compare(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int> >	set_type;

		if (!tester::is_same<set_type::key_compare, std::less<int> >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_value_compare(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int> >	set_type;

		if (!tester::is_same<set_type::value_compare, std::less<int> >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_allocator_type(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int>, std::allocator<char> >	set_type;

		if (!tester::is_same<set_type::allocator_type, std::allocator<char> >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_reference(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int>, std::allocator<char> >	set_type;

		if (!tester::is_same<set_type::reference, std::allocator<char>::reference >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_const_reference(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int>, std::allocator<char> >	set_type;

		if (!tester::is_same<set_type::const_reference, std::allocator<char>::const_reference >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_pointer(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int>, std::allocator<char> >	set_type;

		if (!tester::is_same<set_type::pointer, std::allocator<char>::pointer >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_const_pointer(void)
{
	title(__func__);
	try
	{
		typedef ft::set<t_lint, std::less<int>, std::allocator<char> >	set_type;

		if (!tester::is_same<set_type::const_pointer, std::allocator<char>::const_pointer >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_max_size(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Set of unsigned char
		{
			ft::set<t_hhuint> const			ft_set;
			std::set<t_hhuint> const		std_set;
			ft::set<t_hhuint>::size_type	ft_ret;
			std::set<t_hhuint>::size_type	std_ret;

			g_start = clock();
			ft_ret = ft_set.max_size();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.max_size();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				ret = ISO_OK;
		}
		// Set of std::string
		{
			ft::set<std::string> const			ft_set;
			std::set<std::string> const			std_set;
			ft::set<std::string>::size_type		ft_ret;
			std::set<std::string>::size_type	std_ret;

			g_start = clock();
			ft_ret = ft_set.max_size();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.max_size();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				ret = ISO_OK;
		}
		// Set of long double
		{
			ft::set<long double> const			ft_set;
			std::set<long double> const			std_set;
			ft::set<long double>::size_type		ft_ret;
			std::set<long double>::size_type	std_ret;

			g_start = clock();
			ft_ret = ft_set.max_size();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.max_size();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				ret = ISO_OK;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_key_comp(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// std::less
		{
			ft::set<char, std::less<char> > const			ft_set;
			std::set<char, std::less<char> > const			std_set;
			ft::set<char, std::less<char> >::key_compare	ft_ret;
			std::set<char, std::less<char> >::key_compare	std_ret;

			g_start = clock();
			ft_ret = ft_set.key_comp();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.key_comp();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_ret(g_char[idx - 1], g_char[idx]) != std_ret(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::less_equal
		{
			ft::set<char, std::less_equal<char> > const			ft_set;
			std::set<char, std::less_equal<char> > const		std_set;
			ft::set<char, std::less_equal<char> >::key_compare	ft_ret;
			std::set<char, std::less_equal<char> >::key_compare	std_ret;

			g_start = clock();
			ft_ret = ft_set.key_comp();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.key_comp();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_ret(g_char[idx - 1], g_char[idx]) != std_ret(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::greater
		{
			ft::set<char, std::greater<char> > const			ft_set;
			std::set<char, std::greater<char> > const			std_set;
			ft::set<char, std::greater<char> >::key_compare		ft_ret;
			std::set<char, std::greater<char> >::key_compare	std_ret;

			g_start = clock();
			ft_ret = ft_set.key_comp();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.key_comp();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_ret(g_char[idx - 1], g_char[idx]) != std_ret(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::greater_equal
		{
			ft::set<char, std::greater_equal<char> > const			ft_set;
			std::set<char, std::greater_equal<char> > const			std_set;
			ft::set<char, std::greater_equal<char> >::key_compare	ft_ret;
			std::set<char, std::greater_equal<char> >::key_compare	std_ret;

			g_start = clock();
			ft_ret = ft_set.key_comp();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.key_comp();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_ret(g_char[idx - 1], g_char[idx]) != std_ret(g_char[idx - 1], g_char[idx]))
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

inline static int	__test_function_value_comp(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// std::less
		{
			ft::set<char, std::less<char> > const			ft_set;
			std::set<char, std::less<char> > const			std_set;
			ft::set<char, std::less<char> >::value_compare	ft_ret;
			std::set<char, std::less<char> >::value_compare	std_ret;

			g_start = clock();
			ft_ret = ft_set.value_comp();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.value_comp();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_ret(g_char[idx - 1], g_char[idx]) != std_ret(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::less_equal
		{
			ft::set<char, std::less_equal<char> > const				ft_set;
			std::set<char, std::less_equal<char> > const			std_set;
			ft::set<char, std::less_equal<char> >::value_compare	ft_ret;
			std::set<char, std::less_equal<char> >::value_compare	std_ret;

			g_start = clock();
			ft_ret = ft_set.value_comp();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.value_comp();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_ret(g_char[idx - 1], g_char[idx]) != std_ret(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::greater
		{
			ft::set<char, std::greater<char> > const			ft_set;
			std::set<char, std::greater<char> > const			std_set;
			ft::set<char, std::greater<char> >::value_compare	ft_ret;
			std::set<char, std::greater<char> >::value_compare	std_ret;

			g_start = clock();
			ft_ret = ft_set.value_comp();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.value_comp();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_ret(g_char[idx - 1], g_char[idx]) != std_ret(g_char[idx - 1], g_char[idx]))
					return KO;
		}
		// std::greater_equal
		{
			ft::set<char, std::greater_equal<char> > const				ft_set;
			std::set<char, std::greater_equal<char> > const				std_set;
			ft::set<char, std::greater_equal<char> >::value_compare		ft_ret;
			std::set<char, std::greater_equal<char> >::value_compare	std_ret;

			g_start = clock();
			ft_ret = ft_set.value_comp();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.value_comp();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			for (idx = 1U ; idx < g_char_size ; ++idx)
				if (ft_ret(g_char[idx - 1], g_char[idx]) != std_ret(g_char[idx - 1], g_char[idx]))
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

inline static int	__test_function_size(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_huint>::size_type		ft_ret;
		std::set<t_huint>::size_type	std_ret;

		for (idx = 0U ; idx < g_huint_size ; ++idx)
		{
			ft::set<t_huint> const	ft_set(&g_huint[idx], &g_huint[g_huint_size]);
			std::set<t_huint> const	std_set(&g_huint[idx], &g_huint[g_huint_size]);

			g_start = clock();
			ft_ret = ft_set.size();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.size();
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

inline static int	__test_function_empty(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		bool	ft_ret;
		bool	std_ret;

		for (idx = 0U ; idx < g_uint_size ; ++idx)
		{
			ft::set<t_uint> const	ft_set(&g_uint[idx * (idx % 2)], &g_uint[idx]);
			std::set<t_uint> const	std_set(&g_uint[idx * (idx % 2)], &g_uint[idx]);

			g_start = clock();
			ft_ret = ft_set.empty();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.empty();
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

inline static int	__test_function_begin_constant(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<char>::const_iterator	ft_ret;
		std::set<char>::const_iterator	std_ret;

		for (idx = 1U ; idx < g_char_size ; ++idx)
		{
			ft::set<char> const		ft_set(&g_char[idx - 1], &g_char[g_char_size]);
			std::set<char> const	std_set(&g_char[idx - 1], &g_char[g_char_size]);

			g_start = clock();
			ft_ret = ft_set.begin();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.begin();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (!!ft_ret.base() != !!std_ret._M_node)
				ret = ISO_OK;
			if (*ft_ret != *std_ret)
				return KO;
		}

		ft::set<char> const		ft_set;
		std::set<char> const	std_set;

		g_start = clock();
		ft_ret = ft_set.begin();
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std_ret = std_set.begin();
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (!!ft_ret.base() != !!std_ret._M_node)
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_begin_mutable(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<char>::iterator		ft_ret;
		std::set<char>::iterator	std_ret;

		for (idx = 1U ; idx < g_char_size ; ++idx)
		{
			ft::set<char>	ft_set(&g_char[idx - 1], &g_char[g_char_size]);
			std::set<char>	std_set(&g_char[idx - 1], &g_char[g_char_size]);

			g_start = clock();
			ft_ret = ft_set.begin();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.begin();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (!!ft_ret.base() != !!std_ret._M_node)
				ret = ISO_OK;
			if (*ft_ret != *std_ret)
				return KO;
		}

		ft::set<char>	ft_set;
		std::set<char>	std_set;

		g_start = clock();
		ft_ret = ft_set.begin();
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std_ret = std_set.begin();
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (!!ft_ret.base() != !!std_ret._M_node)
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_end_constant(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<char>::const_iterator	ft_ret;
		std::set<char>::const_iterator	std_ret;

		for (idx = 1U ; idx < g_char_size ; ++idx)
		{
			ft::set<char> const		ft_set(&g_char[0], &g_char[idx]);
			std::set<char> const	std_set(&g_char[0], &g_char[idx]);

			g_start = clock();
			ft_ret = ft_set.end();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.end();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (!!ft_ret.base() != !!std_ret._M_node)
				ret = ISO_OK;

			--ft_ret;
			--std_ret;

			if (*ft_ret != *std_ret)
				return KO;
		}

		ft::set<char> const		ft_set;
		std::set<char> const	std_set;

		g_start = clock();
		ft_ret = ft_set.end();
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std_ret = std_set.end();
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (!!ft_ret.base() != !!std_ret._M_node)
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_end_mutable(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<char>::iterator		ft_ret;
		std::set<char>::iterator	std_ret;

		for (idx = 1U ; idx < g_char_size ; ++idx)
		{
			ft::set<char>	ft_set(&g_char[0], &g_char[idx]);
			std::set<char>	std_set(&g_char[0], &g_char[idx]);

			g_start = clock();
			ft_ret = ft_set.end();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.end();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (!!ft_ret.base() != !!std_ret._M_node)
				ret = ISO_OK;

			--ft_ret;
			--std_ret;

			if (*ft_ret != *std_ret)
				return KO;
		}

		ft::set<char>	ft_set;
		std::set<char>	std_set;

		g_start = clock();
		ft_ret = ft_set.end();
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std_ret = std_set.end();
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (!!ft_ret.base() != !!std_ret._M_node)
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_rbegin_constant(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<char>::const_reverse_iterator	ft_ret;
		std::set<char>::const_reverse_iterator	std_ret;

		for (idx = 1U ; idx < g_char_size ; ++idx)
		{
			ft::set<char> const		ft_set(&g_char[idx - 1], &g_char[g_char_size]);
			std::set<char> const	std_set(&g_char[idx - 1], &g_char[g_char_size]);

			g_start = clock();
			ft_ret = ft_set.rbegin();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.rbegin();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (!!ft_ret.base().base() != !!std_ret.base()._M_node)
				ret = ISO_OK;
			if (*ft_ret != *std_ret)
				return KO;
		}

		ft::set<char> const		ft_set;
		std::set<char> const	std_set;

		g_start = clock();
		ft_ret = ft_set.rbegin();
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std_ret = std_set.rbegin();
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (!!ft_ret.base().base() != !!std_ret.base()._M_node)
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_rbegin_mutable(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<char>::reverse_iterator		ft_ret;
		std::set<char>::reverse_iterator	std_ret;

		for (idx = 1U ; idx < g_char_size ; ++idx)
		{
			ft::set<char>	ft_set(&g_char[idx - 1], &g_char[g_char_size]);
			std::set<char>	std_set(&g_char[idx - 1], &g_char[g_char_size]);

			g_start = clock();
			ft_ret = ft_set.rbegin();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.rbegin();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (!!ft_ret.base().base() != !!std_ret.base()._M_node)
				ret = ISO_OK;
			if (*ft_ret != *std_ret)
				return KO;
		}

		ft::set<char>	ft_set;
		std::set<char>	std_set;

		g_start = clock();
		ft_ret = ft_set.rbegin();
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std_ret = std_set.rbegin();
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (!!ft_ret.base().base() != !!std_ret.base()._M_node)
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_rend_constant(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<char>::const_reverse_iterator	ft_ret;
		std::set<char>::const_reverse_iterator	std_ret;

		for (idx = 1U ; idx < g_char_size ; ++idx)
		{
			ft::set<char> const		ft_set(&g_char[0], &g_char[idx]);
			std::set<char> const	std_set(&g_char[0], &g_char[idx]);

			g_start = clock();
			ft_ret = ft_set.rend();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.rend();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (!!ft_ret.base().base() != !!std_ret.base()._M_node)
				ret = ISO_OK;

			--ft_ret;
			--std_ret;

			if (*ft_ret != *std_ret)
				return KO;
		}

		ft::set<char> const		ft_set;
		std::set<char> const	std_set;

		g_start = clock();
		ft_ret = ft_set.rend();
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std_ret = std_set.rend();
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (!!ft_ret.base().base() != !!std_ret.base()._M_node)
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_rend_mutable(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<char>::reverse_iterator		ft_ret;
		std::set<char>::reverse_iterator	std_ret;

		for (idx = 1U ; idx < g_char_size ; ++idx)
		{
			ft::set<char>	ft_set(&g_char[0], &g_char[idx]);
			std::set<char>	std_set(&g_char[0], &g_char[idx]);

			g_start = clock();
			ft_ret = ft_set.rend();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.rend();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (!!ft_ret.base().base() != !!std_ret.base()._M_node)
				ret = ISO_OK;

			--ft_ret;
			--std_ret;

			if (*ft_ret != *std_ret)
				return KO;
		}

		ft::set<char>	ft_set;
		std::set<char>	std_set;

		g_start = clock();
		ft_ret = ft_set.rend();
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std_ret = std_set.rend();
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (!!ft_ret.base().base() != !!std_ret.base()._M_node)
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_type_iterator(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<float> const		ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float> const		std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::iterator	ft_it;
		std::set<float>::iterator	std_it;

		if (sizeof(ft_it) != sizeof(std_it))
			ret = ISO_OK;

		for (ft_it = ft_set.begin(), std_it = std_set.begin(), idx = 0U ;
			ft_it != ft_set.end() && std_it != std_set.end() ;
			++ft_it, ++std_it, ++idx)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_it);
				BidirectionalIteratorCheck(std_it);
			}

			if (*ft_it != *std_it)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_type_const_iterator(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<float> const			ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float> const			std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::const_iterator	ft_cit;
		std::set<float>::const_iterator	std_cit;

		if (sizeof(ft_cit) != sizeof(std_cit))
			ret = ISO_OK;

		for (ft_cit = ft_set.begin(), std_cit = std_set.begin(), idx = 0U ;
			ft_cit != ft_set.end() && std_cit != std_set.end() ;
			++ft_cit, ++std_cit)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_cit);
				BidirectionalIteratorCheck(std_cit);
			}

			if (*ft_cit != *std_cit)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_type_reverse_iterator(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<float>						ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float>						std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::reverse_iterator	ft_rit;
		std::set<float>::reverse_iterator	std_it;

		if (sizeof(ft_rit) != sizeof(std_it))
			ret = ISO_OK;

		for (ft_rit = ft_set.rbegin(), std_it = std_set.rbegin(), idx = 0U ;
			ft_rit != ft_set.rend() && std_it != std_set.rend() ;
			++ft_rit, ++std_it, ++idx)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_rit);
				BidirectionalIteratorCheck(std_it);
			}

			if (*ft_rit != *std_it)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_type_const_reverse_iterator(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::set<float> const					ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float> const					std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::const_reverse_iterator	ft_crit;
		std::set<float>::const_reverse_iterator	std_crit;

		if (sizeof(ft_crit) != sizeof(std_crit))
			ret = ISO_OK;

		for (ft_crit = ft_set.rbegin(), std_crit = std_set.rbegin(), idx = 0U ;
			ft_crit != ft_set.rend() && std_crit != std_set.rend() ;
			++ft_crit, ++std_crit)
		{
			if (idx)
			{
				BidirectionalIteratorCheck(ft_crit);
				BidirectionalIteratorCheck(std_crit);
			}

			if (*ft_crit != *std_crit)
				return KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_insert_range(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<std::string>	ft_set;
		std::set<std::string>	std_set;

		for (idx = 1U ; idx < g_string_size ; ++idx)
		{
			g_start = clock();
			ft_set.insert(&g_string[idx - 1], &g_string[idx + 1]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_set.insert(&g_string[idx - 1], &g_string[idx + 1]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_set.size() != std_set.size() || !std::equal(ft_set.begin(), ft_set.end(), std_set.begin()))
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

inline static int	__test_function_insert_single(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<std::string>								ft_set;
		std::set<std::string>								std_set;
		ft::pair<ft::set<std::string>::iterator, bool>		ft_ret;
		std::pair<std::set<std::string>::iterator, bool>	std_ret;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft_set.insert(g_string[idx]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.insert(g_string[idx]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (*ft_ret.first != *std_ret.first ||
				ft_ret.second != std_ret.second ||
				ft_set.size() != std_set.size() ||
				!std::equal(ft_set.begin(), ft_set.end(), std_set.begin()))
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

inline static int	__test_function_insert_single_hint(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<std::string>			ft_set;
		std::set<std::string>			std_set;
		ft::set<std::string>::iterator	ft_ret;
		std::set<std::string>::iterator	std_ret;

		ft_set.insert(ft_set.begin(), std::string("dedicated to lmartin"));
		std_set.insert(std_set.begin(), std::string("dedicated to lmartin"));
		ft_ret = ft_set.begin();
		std_ret = std_set.begin();
		for (idx = 0U ; idx < g_string_size * 3 ; ++idx)
		{
			switch (idx % 3)
			{
				case 0:
					g_start = clock();
					ft_ret = ft_set.insert(ft_ret, g_string[idx / 3]);
					g_ft_duration = clock() - g_start;
					g_ft_duration += !g_ft_duration;

					g_start = clock();
					std_ret = std_set.insert(std_ret, g_string[idx / 3]);
					g_std_duration = clock() - g_start;
					g_std_duration += !g_std_duration;
					break;
			
				case 1:
					g_start = clock();
					ft_ret = ft_set.insert(ft_set.begin(), *++ft_set.begin());
					g_ft_duration = clock() - g_start;
					g_ft_duration += !g_ft_duration;

					g_start = clock();
					std_ret = std_set.insert(std_set.begin(), *++std_set.begin());
					g_std_duration = clock() - g_start;
					g_std_duration += !g_std_duration;
					break;

				case 2:
					g_start = clock();
					ft_ret = ft_set.insert(ft_set.end(), *++ft_set.rbegin());
					g_ft_duration = clock() - g_start;
					g_ft_duration += !g_ft_duration;

					g_start = clock();
					std_ret = std_set.insert(std_set.end(), *++std_set.rbegin());
					g_std_duration = clock() - g_start;
					g_std_duration += !g_std_duration;
					break;
			}

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (*ft_ret != *std_ret ||
				ft_set.size() != std_set.size() ||
				!std::equal(ft_set.begin(), ft_set.end(), std_set.begin()))
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

inline static int	__test_function_erase_range(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<char>				ft_set(&g_char[0], &g_char[g_char_size]);
		std::set<char>				std_set(&g_char[0], &g_char[g_char_size]);
		ft::set<char>::iterator		ft_it0;
		ft::set<char>::iterator		ft_it1;
		std::set<char>::iterator	std_it0;
		std::set<char>::iterator	std_it1;
		
		for (idx = 0U ; idx < g_char_size && idx < g_lint_size ; idx += 2)
		{
			ft_it0 = ft_set.begin();
			std_it0 = std_set.begin();
			std::advance(ft_it0, ft_set.size() / 2 - 1);
			std::advance(std_it0, std_set.size() / 2 - 1);
			ft_it1 = ft_it0;
			std_it1 = std_it0;
			std::advance(ft_it1, 2U);
			std::advance(std_it1, 2U);

			g_start = clock();
			ft_set.erase(ft_it0, ft_it1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_set.erase(std_it0, std_it1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_set.size() != std_set.size() ||
				!std::equal(ft_set.begin(), ft_set.end(), std_set.begin()))
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

inline static int	__test_function_erase_single_position(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<char>	ft_set(&g_char[0], &g_char[g_char_size]);
		std::set<char>	std_set(&g_char[0], &g_char[g_char_size]);

		for (idx = 0U ; idx < g_char_size && idx < g_lint_size ; ++idx)
		{
			g_start = clock();
			ft_set.erase(ft_set.begin());
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_set.erase(std_set.begin());
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_set.size() != std_set.size() ||
				!std::equal(ft_set.begin(), ft_set.end(), std_set.begin()))
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

inline static int	__test_function_erase_single_key(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<char>				ft_set(&g_char[0], &g_char[g_char_size]);
		std::set<char>				std_set(&g_char[0], &g_char[g_char_size]);
		ft::set<char>::size_type	ft_ret;
		std::set<char>::size_type	std_ret;

		for (idx = 0U ; idx < g_char_size * 2 && idx < g_lint_size * 2 ; ++idx)
		{
			g_start = clock();
			ft_ret = ft_set.erase(g_char[idx / 2]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.erase(g_char[idx / 2]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret || ft_set.size() != std_set.size() ||
				!std::equal(ft_set.begin(), ft_set.end(), std_set.begin()))
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

inline static int	__test_function_clear(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			ft::set<int>	ft_set(&g_int[0], &g_int[idx]);
			std::set<int>	std_set(&g_int[0], &g_int[idx]);

			g_start = clock();
			ft_set.clear();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_set.clear();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_set.size() != std_set.size() || !std::equal(ft_set.begin(), ft_set.end(), std_set.begin()))
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

inline static int	__test_function_find_constant(void)
{
	t_uint	idx;
	float	nb;

	title(__func__);
	try
	{
		ft::set<float> const			ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float> const			std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::const_iterator	ft_ret;
		std::set<float>::const_iterator	std_ret;

		for (idx = 0U ; idx < g_float_size * 2 ; ++idx)
		{
			if (idx % 2)
			{
				nb = static_cast<float>(rand());
				while (std::find(&g_float[0], &g_float[g_float_size], nb) != &g_float[g_float_size])
					nb = static_cast<float>(rand());
			}
			else
				nb = g_float[idx / 2];

			g_start = clock();
			ft_ret = ft_set.find(nb);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.find(nb);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if ((ft_ret == ft_set.end()) != (std_ret == std_set.end()) ||
				(ft_ret != ft_set.end() && (*ft_ret != *std_ret)))
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

inline static int	__test_function_find_mutable(void)
{
	t_uint	idx;
	float	nb;

	title(__func__);
	try
	{
		ft::set<float>				ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float>				std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::iterator	ft_ret;
		std::set<float>::iterator	std_ret;

		for (idx = 0U ; idx < g_float_size * 2 ; ++idx)
		{
			if (idx % 2)
			{
				nb = static_cast<float>(rand());
				while (std::find(&g_float[0], &g_float[g_float_size], nb) != &g_float[g_float_size])
					nb = static_cast<float>(rand());
			}
			else
				nb = g_float[idx / 2];

			g_start = clock();
			ft_ret = ft_set.find(nb);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.find(nb);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if ((ft_ret == ft_set.end()) != (std_ret == std_set.end()) ||
				(ft_ret != ft_set.end() && (*ft_ret != *std_ret)))
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

inline static int	__test_function_count(void)
{
	t_uint	idx;
	float	nb;

	title(__func__);
	try
	{
		ft::set<float> const		ft_set(&g_float[0], &g_float[g_float_size]);
		std::set<float> const		std_set(&g_float[0], &g_float[g_float_size]);
		ft::set<float>::size_type	ft_ret;
		std::set<float>::size_type	std_ret;

		for (idx = 0U ; idx < g_float_size * 2 ; ++idx)
		{
			if (idx % 2)
			{
				nb = static_cast<float>(rand());
				while (std::find(&g_float[0], &g_float[g_float_size], nb) != &g_float[g_float_size])
					nb = static_cast<float>(rand());
			}
			else
				nb = g_float[idx / 2];

			g_start = clock();
			ft_ret = ft_set.count(nb);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.count(nb);
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

inline static int	__test_function_lower_bound_constant(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_lint> const				ft_set(&g_lint[0], &g_lint[g_lint_size]);
		std::set<t_lint> const				std_set(&g_lint[0], &g_lint[g_lint_size]);
		ft::set<t_lint>::const_iterator		ft_ret;
		std::set<t_lint>::const_iterator	std_ret;

		for (idx = 0U ; idx < g_lint_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft_set.lower_bound(g_lint[idx]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.lower_bound(g_lint[idx]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if ((ft_ret == ft_set.end()) != (std_ret == std_set.end()) ||
				(ft_ret != ft_set.end() && (*ft_ret != *std_ret)))
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

inline static int	__test_function_lower_bound_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_lint>				ft_set(&g_lint[0], &g_lint[g_lint_size]);
		std::set<t_lint>			std_set(&g_lint[0], &g_lint[g_lint_size]);
		ft::set<t_lint>::iterator	ft_ret;
		std::set<t_lint>::iterator	std_ret;

		for (idx = 0U ; idx < g_lint_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft_set.lower_bound(g_lint[idx]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.lower_bound(g_lint[idx]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if ((ft_ret == ft_set.end()) != (std_ret == std_set.end()) ||
				(ft_ret != ft_set.end() && (*ft_ret != *std_ret)))
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

inline static int	__test_function_upper_bound_constant(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_lint> const				ft_set(&g_lint[0], &g_lint[g_lint_size]);
		std::set<t_lint> const				std_set(&g_lint[0], &g_lint[g_lint_size]);
		ft::set<t_lint>::const_iterator		ft_ret;
		std::set<t_lint>::const_iterator	std_ret;

		for (idx = 0U ; idx < g_lint_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft_set.upper_bound(g_lint[idx]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.upper_bound(g_lint[idx]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if ((ft_ret == ft_set.end()) != (std_ret == std_set.end()) ||
				(ft_ret != ft_set.end() && (*ft_ret != *std_ret)))
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

inline static int	__test_function_upper_bound_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_lint>				ft_set(&g_lint[0], &g_lint[g_lint_size]);
		std::set<t_lint>			std_set(&g_lint[0], &g_lint[g_lint_size]);
		ft::set<t_lint>::iterator	ft_ret;
		std::set<t_lint>::iterator	std_ret;

		for (idx = 0U ; idx < g_lint_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft_set.upper_bound(g_lint[idx]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.upper_bound(g_lint[idx]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if ((ft_ret == ft_set.end()) != (std_ret == std_set.end()) ||
				(ft_ret != ft_set.end() && (*ft_ret != *std_ret)))
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

inline static int	__test_function_equal_range_constant(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_hint> const					ft_set(&g_hint[0], &g_hint[g_hint_size]);
		std::set<t_hint> const					std_set(&g_hint[0], &g_hint[g_hint_size]);
		ft::pair<
			ft::set<t_hint>::const_iterator,
			ft::set<t_hint>::const_iterator>	ft_ret;
		std::pair<
			std::set<t_hint>::const_iterator,
			std::set<t_hint>::const_iterator>	std_ret;

		for (idx = 0U ; idx < g_hint_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft_set.equal_range(g_hint[idx]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.equal_range(g_hint[idx]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if ((ft_ret.first == ft_set.end()) != (std_ret.first == std_set.end()) ||
				(ft_ret.first != ft_set.end() && !std::equal(ft_ret.first, ft_ret.second, std_ret.first)))
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

inline static int	__test_function_equal_range_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_hint>					ft_set(&g_hint[0], &g_hint[g_hint_size]);
		std::set<t_hint>				std_set(&g_hint[0], &g_hint[g_hint_size]);
		ft::pair<
			ft::set<t_hint>::iterator,
			ft::set<t_hint>::iterator>	ft_ret;
		std::pair<
			std::set<t_hint>::iterator,
			std::set<t_hint>::iterator>	std_ret;

		for (idx = 0U ; idx < g_hint_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft_set.equal_range(g_hint[idx]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_set.equal_range(g_hint[idx]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if ((ft_ret.first == ft_set.end()) != (std_ret.first == std_set.end()) ||
				(ft_ret.first != ft_set.end() && !std::equal(ft_ret.first, ft_ret.second, std_ret.first)))
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

inline static int	__test_function_swap(void)
{
	title(__func__);
	try
	{
		// Member function
		{
			// Swapping empty | empty
			{
				ft::set<char>					ft_set0;
				ft::set<char>					ft_set1;
				std::set<char>					std_set0;
				std::set<char>					std_set1;
				ft::set<char>::const_iterator	ft_cit0(ft_set0.begin());
				ft::set<char>::const_iterator	ft_cit1(ft_set1.begin());
				std::set<char>::const_iterator	std_cit0(std_set0.begin());
				std::set<char>::const_iterator	std_cit1(std_set1.begin());
				ft::set<char>::const_iterator	ft_cend0;
				ft::set<char>::const_iterator	ft_cend1;

				g_start = clock();
				ft_set0.swap(ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_set0.swap(std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				ft_cend0 = ft_set0.end();
				ft_cend1 = ft_set1.end();

				if (ft_set0.size() != std_set0.size() || ft_set1.size() != std_set1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0) || !std::equal(ft_cit1, ft_cend0, std_cit1))
					return KO;
			}
			// Swapping empty | non-empty
			{
				ft::set<char>					ft_set0;
				ft::set<char>					ft_set1(&g_char[g_char_size / 2], &g_char[g_char_size]);
				std::set<char>					std_set0;
				std::set<char>					std_set1(&g_char[g_char_size / 2], &g_char[g_char_size]);
				ft::set<char>::const_iterator	ft_cit0(ft_set0.begin());
				ft::set<char>::const_iterator	ft_cit1(ft_set1.begin());
				std::set<char>::const_iterator	std_cit0(std_set0.begin());
				std::set<char>::const_iterator	std_cit1(std_set1.begin());
				ft::set<char>::const_iterator	ft_cend0;
				ft::set<char>::const_iterator	ft_cend1;

				g_start = clock();
				ft_set0.swap(ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_set0.swap(std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				ft_cend0 = ft_set0.end();
				ft_cend1 = ft_set1.end();

				if (ft_set0.size() != std_set0.size() || ft_set1.size() != std_set1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0) || !std::equal(ft_cit1, ft_cend0, std_cit1))
					return KO;
			}
			// Swapping non-empty | empty
			{
				ft::set<char>					ft_set0(&g_char[0], &g_char[g_char_size / 2]);
				ft::set<char>					ft_set1;
				std::set<char>					std_set0(&g_char[0], &g_char[g_char_size / 2]);
				std::set<char>					std_set1;
				ft::set<char>::const_iterator	ft_cit0(ft_set0.begin());
				ft::set<char>::const_iterator	ft_cit1(ft_set1.begin());
				std::set<char>::const_iterator	std_cit0(std_set0.begin());
				std::set<char>::const_iterator	std_cit1(std_set1.begin());
				ft::set<char>::const_iterator	ft_cend0;
				ft::set<char>::const_iterator	ft_cend1;

				g_start = clock();
				ft_set0.swap(ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_set0.swap(std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				ft_cend0 = ft_set0.end();
				ft_cend1 = ft_set1.end();

				if (ft_set0.size() != std_set0.size() || ft_set1.size() != std_set1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0) || !std::equal(ft_cit1, ft_cend0, std_cit1))
					return KO;
			}
			// Swapping non-empty | non-empty
			{
				ft::set<char>					ft_set0(&g_char[0], &g_char[g_char_size / 2]);
				ft::set<char>					ft_set1(&g_char[g_char_size / 2], &g_char[g_char_size]);
				std::set<char>					std_set0(&g_char[0], &g_char[g_char_size / 2]);
				std::set<char>					std_set1(&g_char[g_char_size / 2], &g_char[g_char_size]);
				ft::set<char>::const_iterator	ft_cit0(ft_set0.begin());
				ft::set<char>::const_iterator	ft_cit1(ft_set1.begin());
				std::set<char>::const_iterator	std_cit0(std_set0.begin());
				std::set<char>::const_iterator	std_cit1(std_set1.begin());
				ft::set<char>::const_iterator	ft_cend0;
				ft::set<char>::const_iterator	ft_cend1;

				g_start = clock();
				ft_set0.swap(ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_set0.swap(std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				ft_cend0 = ft_set0.end();
				ft_cend1 = ft_set1.end();

				if (ft_set0.size() != std_set0.size() || ft_set1.size() != std_set1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0) || !std::equal(ft_cit1, ft_cend0, std_cit1))
					return KO;
			}
		}
		// Non-member function
		{
			// Swapping empty | empty
			{
				ft::set<char>					ft_set0;
				ft::set<char>					ft_set1;
				std::set<char>					std_set0;
				std::set<char>					std_set1;
				ft::set<char>::const_iterator	ft_cit0(ft_set0.begin());
				ft::set<char>::const_iterator	ft_cit1(ft_set1.begin());
				std::set<char>::const_iterator	std_cit0(std_set0.begin());
				std::set<char>::const_iterator	std_cit1(std_set1.begin());
				ft::set<char>::const_iterator	ft_cend0;
				ft::set<char>::const_iterator	ft_cend1;

				g_start = clock();
				ft::swap(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::swap(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				ft_cend0 = ft_set0.end();
				ft_cend1 = ft_set1.end();

				if (ft_set0.size() != std_set0.size() || ft_set1.size() != std_set1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0) || !std::equal(ft_cit1, ft_cend0, std_cit1))
					return KO;
			}
			// Swapping empty | non-empty
			{
				ft::set<char>					ft_set0;
				ft::set<char>					ft_set1(&g_char[g_char_size / 2], &g_char[g_char_size]);
				std::set<char>					std_set0;
				std::set<char>					std_set1(&g_char[g_char_size / 2], &g_char[g_char_size]);
				ft::set<char>::const_iterator	ft_cit0(ft_set0.begin());
				ft::set<char>::const_iterator	ft_cit1(ft_set1.begin());
				std::set<char>::const_iterator	std_cit0(std_set0.begin());
				std::set<char>::const_iterator	std_cit1(std_set1.begin());
				ft::set<char>::const_iterator	ft_cend0;
				ft::set<char>::const_iterator	ft_cend1;

				g_start = clock();
				ft::swap(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::swap(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				ft_cend0 = ft_set0.end();
				ft_cend1 = ft_set1.end();

				if (ft_set0.size() != std_set0.size() || ft_set1.size() != std_set1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0) || !std::equal(ft_cit1, ft_cend0, std_cit1))
					return KO;
			}
			// Swapping non-empty | empty
			{
				ft::set<char>					ft_set0(&g_char[0], &g_char[g_char_size / 2]);
				ft::set<char>					ft_set1;
				std::set<char>					std_set0(&g_char[0], &g_char[g_char_size / 2]);
				std::set<char>					std_set1;
				ft::set<char>::const_iterator	ft_cit0(ft_set0.begin());
				ft::set<char>::const_iterator	ft_cit1(ft_set1.begin());
				std::set<char>::const_iterator	std_cit0(std_set0.begin());
				std::set<char>::const_iterator	std_cit1(std_set1.begin());
				ft::set<char>::const_iterator	ft_cend0;
				ft::set<char>::const_iterator	ft_cend1;

				g_start = clock();
				ft::swap(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::swap(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				ft_cend0 = ft_set0.end();
				ft_cend1 = ft_set1.end();

				if (ft_set0.size() != std_set0.size() || ft_set1.size() != std_set1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0) || !std::equal(ft_cit1, ft_cend0, std_cit1))
					return KO;
			}
			// Swapping non-empty | non-empty
			{
				ft::set<char>					ft_set0(&g_char[0], &g_char[g_char_size / 2]);
				ft::set<char>					ft_set1(&g_char[g_char_size / 2], &g_char[g_char_size]);
				std::set<char>					std_set0(&g_char[0], &g_char[g_char_size / 2]);
				std::set<char>					std_set1(&g_char[g_char_size / 2], &g_char[g_char_size]);
				ft::set<char>::const_iterator	ft_cit0(ft_set0.begin());
				ft::set<char>::const_iterator	ft_cit1(ft_set1.begin());
				std::set<char>::const_iterator	std_cit0(std_set0.begin());
				std::set<char>::const_iterator	std_cit1(std_set1.begin());
				ft::set<char>::const_iterator	ft_cend0;
				ft::set<char>::const_iterator	ft_cend1;

				g_start = clock();
				ft::swap(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::swap(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				ft_cend0 = ft_set0.end();
				ft_cend1 = ft_set1.end();

				if (ft_set0.size() != std_set0.size() || ft_set1.size() != std_set1.size() ||
					!std::equal(ft_cit0, ft_cend1, std_cit0) || !std::equal(ft_cit1, ft_cend0, std_cit1))
					return KO;
			}
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
		// Assigning empty -> empty
		{
			ft::set<std::string>		ft_set0;
			ft::set<std::string> const	ft_set1;
			std::set<std::string>		std_set0;
			std::set<std::string> const	std_set1;

			g_start = clock();
			ft_set0 = ft_set1;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_set0 = std_set1;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_set0.size() != std_set0.size() || !std::equal(ft_set0.begin(), ft_set0.end(), std_set0.begin()))
				return KO;
		}
		// Assigning empty -> non-empty
		{
			ft::set<std::string>		ft_set0(&g_string[0], &g_string[g_string_size / 2]);
			ft::set<std::string> const	ft_set1;
			std::set<std::string>		std_set0(&g_string[0], &g_string[g_string_size / 2]);
			std::set<std::string> const	std_set1;

			g_start = clock();
			ft_set0 = ft_set1;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_set0 = std_set1;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_set0.size() != std_set0.size() || !std::equal(ft_set0.begin(), ft_set0.end(), std_set0.begin()))
				return KO;
		}
		// Assigning non-empty -> empty
		{
			ft::set<std::string>		ft_set0;
			ft::set<std::string> const	ft_set1(&g_string[g_string_size / 2], &g_string[g_string_size]);
			std::set<std::string>		std_set0;
			std::set<std::string> const	std_set1(&g_string[g_string_size / 2], &g_string[g_string_size]);

			g_start = clock();
			ft_set0 = ft_set1;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_set0 = std_set1;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_set0.size() != std_set0.size() || !std::equal(ft_set0.begin(), ft_set0.end(), std_set0.begin()))
				return KO;
		}
		// Assigning non-empty -> non-empty
		{
			ft::set<std::string>			ft_set0(&g_string[0], &g_string[g_string_size / 2]);
			ft::set<std::string> const	ft_set1(&g_string[g_string_size / 2], &g_string[g_string_size]);
			std::set<std::string>			std_set0(&g_string[0], &g_string[g_string_size / 2]);
			std::set<std::string> const	std_set1(&g_string[g_string_size / 2], &g_string[g_string_size]);

			g_start = clock();
			ft_set0 = ft_set1;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_set0 = std_set1;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_set0.size() != std_set0.size() || !std::equal(ft_set0.begin(), ft_set0.end(), std_set0.begin()))
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_hhint>	ft_set0;
		ft::set<t_hhint>	ft_set1;
		std::set<t_hhint>	std_set0;
		std::set<t_hhint>	std_set1;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_hhint_size ; ++idx)
		{
			// Key difference
			{
				ft_set0.insert(g_hhint[idx] + 1);
				ft_set1.insert(g_hhint[idx] - 1);
				std_set0.insert(g_hhint[idx] + 1);
				std_set1.insert(g_hhint[idx] - 1);

				g_start = clock();
				ft_ret = ft::operator==(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator==(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;

				ft_set0.erase(g_hhint[idx] + 1);
				ft_set1.erase(g_hhint[idx] - 1);
				std_set0.erase(g_hhint[idx] + 1);
				std_set1.erase(g_hhint[idx] - 1);
				
			}
			// Size difference
			{
				ft_set0.insert(g_hhint[idx]);
				std_set0.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator==(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator==(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Equivalence
			{
				ft_set1.insert(g_hhint[idx]);
				std_set1.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator==(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator==(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_hhint>	ft_set0;
		ft::set<t_hhint>	ft_set1;
		std::set<t_hhint>	std_set0;
		std::set<t_hhint>	std_set1;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_hhint_size ; ++idx)
		{
			// Key difference
			{
				ft_set0.insert(g_hhint[idx] + 1);
				ft_set1.insert(g_hhint[idx] - 1);
				std_set0.insert(g_hhint[idx] + 1);
				std_set1.insert(g_hhint[idx] - 1);

				g_start = clock();
				ft_ret = ft::operator!=(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator!=(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;

				ft_set0.erase(g_hhint[idx] + 1);
				ft_set1.erase(g_hhint[idx] - 1);
				std_set0.erase(g_hhint[idx] + 1);
				std_set1.erase(g_hhint[idx] - 1);
				
			}
			// Size difference
			{
				ft_set0.insert(g_hhint[idx]);
				std_set0.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator!=(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator!=(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Equivalence
			{
				ft_set1.insert(g_hhint[idx]);
				std_set1.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator!=(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator!=(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_hhint>	ft_set0;
		ft::set<t_hhint>	ft_set1;
		std::set<t_hhint>	std_set0;
		std::set<t_hhint>	std_set1;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_hhint_size ; ++idx)
		{
			// Key difference
			{
				ft_set0.insert(g_hhint[idx] + 1);
				ft_set1.insert(g_hhint[idx] - 1);
				std_set0.insert(g_hhint[idx] + 1);
				std_set1.insert(g_hhint[idx] - 1);

				g_start = clock();
				ft_ret = ft::operator<(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;

				ft_set0.erase(g_hhint[idx] + 1);
				ft_set1.erase(g_hhint[idx] - 1);
				std_set0.erase(g_hhint[idx] + 1);
				std_set1.erase(g_hhint[idx] - 1);
				
			}
			// Size difference
			{
				ft_set0.insert(g_hhint[idx]);
				std_set0.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator<(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Equivalence
			{
				ft_set1.insert(g_hhint[idx]);
				std_set1.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator<(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_hhint>	ft_set0;
		ft::set<t_hhint>	ft_set1;
		std::set<t_hhint>	std_set0;
		std::set<t_hhint>	std_set1;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_hhint_size ; ++idx)
		{
			// Key difference
			{
				ft_set0.insert(g_hhint[idx] + 1);
				ft_set1.insert(g_hhint[idx] - 1);
				std_set0.insert(g_hhint[idx] + 1);
				std_set1.insert(g_hhint[idx] - 1);

				g_start = clock();
				ft_ret = ft::operator>(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;

				ft_set0.erase(g_hhint[idx] + 1);
				ft_set1.erase(g_hhint[idx] - 1);
				std_set0.erase(g_hhint[idx] + 1);
				std_set1.erase(g_hhint[idx] - 1);
				
			}
			// Size difference
			{
				ft_set0.insert(g_hhint[idx]);
				std_set0.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator>(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Equivalence
			{
				ft_set1.insert(g_hhint[idx]);
				std_set1.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator>(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_hhint>	ft_set0;
		ft::set<t_hhint>	ft_set1;
		std::set<t_hhint>	std_set0;
		std::set<t_hhint>	std_set1;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_hhint_size ; ++idx)
		{
			// Key difference
			{
				ft_set0.insert(g_hhint[idx] + 1);
				ft_set1.insert(g_hhint[idx] - 1);
				std_set0.insert(g_hhint[idx] + 1);
				std_set1.insert(g_hhint[idx] - 1);

				g_start = clock();
				ft_ret = ft::operator<=(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<=(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;

				ft_set0.erase(g_hhint[idx] + 1);
				ft_set1.erase(g_hhint[idx] - 1);
				std_set0.erase(g_hhint[idx] + 1);
				std_set1.erase(g_hhint[idx] - 1);
				
			}
			// Size difference
			{
				ft_set0.insert(g_hhint[idx]);
				std_set0.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator<=(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<=(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Equivalence
			{
				ft_set1.insert(g_hhint[idx]);
				std_set1.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator<=(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<=(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
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
	t_uint	idx;

	title(__func__);
	try
	{
		ft::set<t_hhint>	ft_set0;
		ft::set<t_hhint>	ft_set1;
		std::set<t_hhint>	std_set0;
		std::set<t_hhint>	std_set1;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_hhint_size ; ++idx)
		{
			// Key difference
			{
				ft_set0.insert(g_hhint[idx] + 1);
				ft_set1.insert(g_hhint[idx] - 1);
				std_set0.insert(g_hhint[idx] + 1);
				std_set1.insert(g_hhint[idx] - 1);

				g_start = clock();
				ft_ret = ft::operator>=(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>=(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;

				ft_set0.erase(g_hhint[idx] + 1);
				ft_set1.erase(g_hhint[idx] - 1);
				std_set0.erase(g_hhint[idx] + 1);
				std_set1.erase(g_hhint[idx] - 1);
				
			}
			// Size difference
			{
				ft_set0.insert(g_hhint[idx]);
				std_set0.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator>=(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>=(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Equivalence
			{
				ft_set1.insert(g_hhint[idx]);
				std_set1.insert(g_hhint[idx]);

				g_start = clock();
				ft_ret = ft::operator>=(ft_set0, ft_set1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>=(std_set0, std_set1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

int	test_set(void)
{
	t_fct const				tests[] = {
		__test_constructor_default,
		__test_constructor_range,
		__test_constructor_copy,
		__test_default_template_type_Compare,
		__test_default_template_type_Alloc,
		__test_type_key_type,
		__test_type_value_type,
		__test_type_key_compare,
		__test_type_value_compare,
		__test_type_allocator_type,
		__test_type_reference,
		__test_type_const_reference,
		__test_type_pointer,
		__test_type_const_pointer,
		__test_function_max_size,
		__test_function_key_comp,
		__test_function_value_comp,
		__test_function_size,
		__test_function_empty,
		__test_function_begin_constant,
		__test_function_begin_mutable,
		__test_function_end_constant,
		__test_function_end_mutable,
		__test_function_rbegin_constant,
		__test_function_rbegin_mutable,
		__test_function_rend_constant,
		__test_function_rend_mutable,
		__test_type_iterator,
		__test_type_const_iterator,
		__test_type_reverse_iterator,
		__test_type_const_reverse_iterator,
		__test_function_insert_range,
		__test_function_insert_single,
		__test_function_insert_single_hint,
		__test_function_erase_range,
		__test_function_erase_single_position,
		__test_function_erase_single_key,
		__test_function_clear,
		__test_function_find_constant,
		__test_function_find_mutable,
		__test_function_count,
		__test_function_lower_bound_constant,
		__test_function_lower_bound_mutable,
		__test_function_upper_bound_constant,
		__test_function_upper_bound_mutable,
		__test_function_equal_range_constant,
		__test_function_equal_range_mutable,
		__test_function_swap,
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
	std::cout << "###################################################" << '\n';
	std::cout << "##                      SET                      ##" << '\n';
	std::cout << "###################################################" << '\n';
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
				std::cerr << MAGENTA_FG;
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
