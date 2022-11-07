/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/11/07 08:57:58 by jodufour         ###   ########.fr       */
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
#include VECTOR_HEADER
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

inline static int	__test_constructor_default(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		g_start = clock();
		ft::vector<int> const	ft_vec;
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std::vector<int> const	std_vec;
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (sizeof(ft_vec) != sizeof(std_vec) || memcmp(&ft_vec, &std_vec, sizeof(ft_vec)))
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_constructor_fill(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			// Null size | default value
			{
				g_start = clock();
				ft::vector<char> const	ft_vec(0LU);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<char> const	std_vec(0LU);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec) || memcmp(&ft_vec, &std_vec, sizeof(ft_vec)))
					ret = ISO_OK;
			}
			// Null size | defined value
			{
				g_start = clock();
				ft::vector<char> const	ft_vec(0LU, 'A');
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<char> const	std_vec(0LU, 'A');
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Non-null size | default value
			{
				g_start = clock();
				ft::vector<char> const	ft_vec(21LU);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<char> const	std_vec(21LU);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Non-null size | defined value
			{
				g_start = clock();
				ft::vector<char> const	ft_vec(42LU, 42);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<char> const	std_vec(42LU, 42);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
		}
		// Trivially copyable
		// Ambiguous
		{
			// Null size | defined value
			{
				g_start = clock();
				ft::vector<char> const	ft_vec(static_cast<char>(0LU), 'A');
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<char> const	std_vec(static_cast<char>(0LU), 'A');
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Non-null size | defined value
			{
				g_start = clock();
				ft::vector<char> const	ft_vec(static_cast<char>(42LU), 42);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<char> const	std_vec(static_cast<char>(42LU), 42);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
		}
		// Non-trivial copy required
		{
			// Null size | default value
			{
				g_start = clock();
				ft::vector<std::string> const	ft_vec(0LU);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<std::string> const	std_vec(0LU);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec) || memcmp(&ft_vec, &std_vec, sizeof(ft_vec)))
					ret = ISO_OK;
			}
			// Non-null size | default value
			{
				g_start = clock();
				ft::vector<std::string> const	ft_vec(21LU);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<std::string> const	std_vec(21LU);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Null size | defined value
			{
				g_start = clock();
				ft::vector<std::string> const	ft_vec(0LU, std::string("pouic"));
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<std::string> const	std_vec(0LU, std::string("pouic"));
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Non-null size | defined value
			{
				g_start = clock();
				ft::vector<std::string> const	ft_vec(42LU, std::string("Hello World !"));
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<std::string> const	std_vec(42LU, std::string("Hello World !"));
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
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

inline static int	__test_constructor_range(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			// Range of input_iterator_restrictor
			{
				tester::input_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				tester::input_iterator_restrictor<t_huint const *> const	it1(&g_huint[0]);

				g_start = clock();
				ft::vector<t_huint> const									ft_vec(it0, it1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<t_huint> const									std_vec(it0, it1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of forward_iterator_restrictor
			{
				tester::forward_iterator_restrictor<void const *const *> const	it;

				g_start = clock();
				ft::vector<void const *> const									ft_vec(it, it);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<void const *> const									std_vec(it, it);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of random_access_iterator_restrictor
			{
				tester::random_access_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				tester::random_access_iterator_restrictor<t_huint const *> const	it1(&g_huint[g_huint_size]);

				g_start = clock();
				ft::vector<t_huint> const											ft_vec(it0, it1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<t_huint> const											std_vec(it0, it1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of char const *
			{
				g_start = clock();
				ft::vector<char> const	ft_vec(g_char, &g_char[g_char_size]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<char> const	std_vec(g_char, &g_char[g_char_size]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
		}
		// Non-trivial copy required
		{
			// Range of input_iterator_restrictor
			{
				tester::input_iterator_restrictor<std::string const *> const	it0(&g_string[0]);
				tester::input_iterator_restrictor<std::string const *> const	it1(&g_string[0]);

				g_start = clock();
				ft::vector<std::string> const									ft_vec(it0, it1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<std::string> const									std_vec(it0, it1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of forward_iterator_restrictor
			{
				tester::forward_iterator_restrictor<std::string const *> const	it0;
				tester::forward_iterator_restrictor<std::string const *> const	it1;

				g_start = clock();
				ft::vector<std::string> const									ft_vec(it0, it1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<std::string> const									std_vec(it0, it1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of random_access_iterator_restrictor
			{
				tester::random_access_iterator_restrictor<std::string const *> const	it0(&g_string[0]);
				tester::random_access_iterator_restrictor<std::string const *> const	it1(&g_string[g_string_size]);

				g_start = clock();
				ft::vector<std::string> const											ft_vec(it0, it1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<std::string> const											std_vec(it0, it1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
			// Range of std::string const *
			{
				g_start = clock();
				ft::vector<std::string> const	ft_vec(&g_string[0], &g_string[g_string_size]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<std::string> const	std_vec(&g_string[0], &g_string[g_string_size]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec) != sizeof(std_vec))
					ret = ISO_OK;
			}
		}
		// Trivially copyable
		// Force naive iteration along the range
		{
			std::ifstream						ifs0(g_file[g_file_size - 1]);
			std::ifstream						ifs1(g_file[g_file_size - 1]);
			std::istream_iterator<char> const	it0(ifs0);
			std::istream_iterator<char> const	it1(ifs1);
			std::istream_iterator<char> const	end_of_stream;

			g_start = clock();
			ft::vector<char> const				ft_vec(it0, end_of_stream);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::vector<char> const				std_vec(it1, end_of_stream);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_vec) != sizeof(std_vec))
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
		// Trivially copyable
		{
			// Default vector
			{
				ft::vector<t_huint> const	ft_vec0;
				std::vector<t_huint> const	std_vec0;

				g_start = clock();
				ft::vector<t_huint> const	ft_vec1(ft_vec0);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<t_huint> const	std_vec1(std_vec0);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec1) != sizeof(std_vec1))
					ret = ISO_OK;
			}
			// Filled vector
			{
				tester::forward_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				tester::forward_iterator_restrictor<t_huint const *> const	it1(&g_huint[g_huint_size]);
				ft::vector<t_huint> const									ft_vec0(it0, it1);
				std::vector<t_huint> const									std_vec0(it0, it1);

				g_start = clock();
				ft::vector<t_huint> const									ft_vec1(ft_vec0);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<t_huint> const									std_vec1(std_vec0);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec1) != sizeof(std_vec1))
					ret = ISO_OK;
			}
		}
		// Non-trivial copy required
		{
			// Default vector
			{
				ft::vector<std::string> const	ft_vec0;
				std::vector<std::string> const	std_vec0;

				g_start = clock();
				ft::vector<std::string> const	ft_vec1(ft_vec0);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<std::string> const	std_vec1(std_vec0);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec1) != sizeof(std_vec1))
					ret = ISO_OK;
			}
			// Filled vector
			{
				tester::forward_iterator_restrictor<std::string const *> const	it0(&g_string[0]);
				tester::forward_iterator_restrictor<std::string const *> const	it1(&g_string[g_string_size]);
				ft::vector<std::string> const									ft_vec0(it0, it1);
				std::vector<std::string> const									std_vec0(it0, it1);

				g_start = clock();
				ft::vector<std::string> const									ft_vec1(ft_vec0);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::vector<std::string> const									std_vec1(std_vec0);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_vec1) != sizeof(std_vec1))
					ret = ISO_OK;
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

inline static int	__test_default_template_type_Alloc(void)
{
	title(__func__);

	typedef ft::vector<float>							vec_type_0;
	typedef ft::vector<float, std::allocator<float> >	vec_type_1;

	if (!tester::is_same<vec_type_0, vec_type_1>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_value_type(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!tester::is_same<vec_type::value_type, t_lint>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_allocator_type(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!tester::is_same<vec_type::allocator_type, std::allocator<t_lint> >::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_reference(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!tester::is_same<vec_type::reference, std::allocator<t_lint>::reference>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_const_reference(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!tester::is_same<vec_type::const_reference, std::allocator<t_lint>::const_reference>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_pointer(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!tester::is_same<vec_type::pointer, std::allocator<t_lint>::pointer>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_const_pointer(void)
{
	title(__func__);

	typedef ft::vector<t_lint, std::allocator<t_lint> >	vec_type;

	if (!tester::is_same<vec_type::const_pointer, std::allocator<t_lint>::const_pointer>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_function_get_allocator(void)
{
	title(__func__);
	try
	{
		ft::vector<char> const				ft_vec;
		std::vector<char> const				std_vec;
		ft::vector<char>::allocator_type	ft_ret;
		std::vector<char>::allocator_type	std_ret;

		g_start = clock();
		ft_ret = ft_vec.get_allocator();
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std_ret = std_vec.get_allocator();
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (ft_ret != std_ret)
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
		// Vector of signed char
		{
			ft::vector<t_hhint> const		ft_vec;
			std::vector<t_hhint> const		std_vec;
			ft::vector<t_hhint>::size_type	ft_ret;
			std::vector<t_hhint>::size_type	std_ret;

			g_start = clock();
			ft_ret = ft_vec.max_size();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.max_size();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				ret = ISO_OK;
			if ((ft_ret == ft_vec.get_allocator().max_size()) != (std_ret == std_vec.get_allocator().max_size()))
				ret = KO;
		}
		// Vector of unsigned int
		{
			ft::vector<t_uint> const		ft_vec;
			std::vector<t_uint> const		std_vec;
			ft::vector<t_uint>::size_type	ft_ret;
			std::vector<t_uint>::size_type	std_ret;

			g_start = clock();
			ft_ret = ft_vec.max_size();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.max_size();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				ret = ISO_OK;
			if ((ft_ret == ft_vec.get_allocator().max_size()) != (std_ret == std_vec.get_allocator().max_size()))
				ret = KO;
		}
		// Vector of std::pair<long double, long int>
		{
			ft::vector<std::pair<long double, t_lint> > const		ft_vec;
			std::vector<std::pair<long double, t_lint> > const		std_vec;
			ft::vector<std::pair<long double, t_lint> >::size_type	ft_ret;
			std::vector<std::pair<long double, t_lint> >::size_type	std_ret;

			g_start = clock();
			ft_ret = ft_vec.max_size();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.max_size();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				ret = ISO_OK;
			if ((ft_ret == ft_vec.get_allocator().max_size()) != (std_ret == std_vec.get_allocator().max_size()))
				ret = KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_capacity(void)
{
	int		ret;
	size_t	n;

	title(__func__);
	ret = IMP_OK;
	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<float> const			ft_vec(n, 3.14f);
			std::vector<float> const		std_vec(n, 3.14f);
			ft::vector<float>::size_type	ft_ret;
			std::vector<float>::size_type	std_ret;

			g_start = clock();
			ft_ret = ft_vec.capacity();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.capacity();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				ret = ISO_OK;
			if (ft_ret < n)
				ret = KO;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_function_size(void)
{
	size_t	n;

	title(__func__);
	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<t_hhuint> const			ft_vec(n, 42U);
			std::vector<t_hhuint> const			std_vec(n, 42U);
			ft::vector<t_hhuint>::size_type		ft_ret;
			std::vector<t_hhuint>::size_type	std_ret;

			g_start = clock();
			ft_ret = ft_vec.size();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.size();
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
	size_t	n;

	title(__func__);
	try
	{
		for (n = 0LU ; n < 10LU ; ++n)
		{
			ft::vector<std::string> const	ft_vec(n * (n % 2), std::string("Hello World"));
			std::vector<std::string> const	std_vec(n * (n % 2), std::string("Hello World"));
			bool							ft_ret;
			bool							std_ret;

			g_start = clock();
			ft_ret = ft_vec.empty();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.empty();
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

	title(__func__);
	try
	{
		ft::vector<char>::const_iterator	ft_ret;
		std::vector<char>::const_iterator	std_ret;

		for (idx = 0U ; idx < g_file_size ; ++idx)
		{
			std::ifstream						ifs0(g_file[idx]);
			std::ifstream						ifs1(g_file[idx]);
			std::istream_iterator<char> const	it0(ifs0);
			std::istream_iterator<char> const	it1(ifs1);
			std::istream_iterator<char> const	end_of_stream;
			ft::vector<char> const				ft_vec(it0, end_of_stream);
			std::vector<char> const				std_vec(it1, end_of_stream);

			g_start = clock();
			ft_ret = ft_vec.begin();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.begin();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.size() && std_vec.size() && *ft_ret != *std_ret)
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

inline static int	__test_function_begin_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<char>::iterator	ft_ret;
		std::vector<char>::iterator	std_ret;

		for (idx = 0U ; idx < g_file_size ; ++idx)
		{
			std::ifstream						ifs0(g_file[idx]);
			std::ifstream						ifs1(g_file[idx]);
			std::istream_iterator<char> const	it0(ifs0);
			std::istream_iterator<char> const	it1(ifs1);
			std::istream_iterator<char> const	end_of_stream;
			ft::vector<char>					ft_vec(it0, end_of_stream);
			std::vector<char>					std_vec(it1, end_of_stream);

			g_start = clock();
			ft_ret = ft_vec.begin();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.begin();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.size() && std_vec.size() && *ft_ret != *std_ret)
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

inline static int	__test_function_end_constant(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<char>::const_iterator	ft_ret;
		std::vector<char>::const_iterator	std_ret;

		for (idx = 0U ; idx < g_file_size ; ++idx)
		{
			std::ifstream						ifs0(g_file[idx]);
			std::ifstream						ifs1(g_file[idx]);
			std::istream_iterator<char> const	it0(ifs0);
			std::istream_iterator<char> const	it1(ifs1);
			std::istream_iterator<char> const	end_of_stream;
			ft::vector<char> const				ft_vec(it0, end_of_stream);
			std::vector<char> const				std_vec(it1, end_of_stream);

			g_start = clock();
			ft_ret = ft_vec.end();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.end();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.size() && std_vec.size() && *--ft_ret != *--std_ret)
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

inline static int	__test_function_end_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<char>::iterator	ft_ret;
		std::vector<char>::iterator	std_ret;

		for (idx = 0U ; idx < g_file_size ; ++idx)
		{
			std::ifstream						ifs0(g_file[idx]);
			std::ifstream						ifs1(g_file[idx]);
			std::istream_iterator<char> const	it0(ifs0);
			std::istream_iterator<char> const	it1(ifs1);
			std::istream_iterator<char> const	end_of_stream;
			ft::vector<char>					ft_vec(it0, end_of_stream);
			std::vector<char>					std_vec(it1, end_of_stream);

			g_start = clock();
			ft_ret = ft_vec.end();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.end();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.size() && std_vec.size() && *--ft_ret != *--std_ret)
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

inline static int	__test_function_rbegin_constant(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<char>::const_reverse_iterator	ft_ret;
		std::vector<char>::const_reverse_iterator	std_ret;

		for (idx = 0U ; idx < g_file_size ; ++idx)
		{
			std::ifstream						ifs0(g_file[idx]);
			std::ifstream						ifs1(g_file[idx]);
			std::istream_iterator<char> const	it0(ifs0);
			std::istream_iterator<char> const	it1(ifs1);
			std::istream_iterator<char> const	end_of_stream;
			ft::vector<char> const				ft_vec(it0, end_of_stream);
			std::vector<char> const				std_vec(it1, end_of_stream);

			g_start = clock();
			ft_ret = ft_vec.rbegin();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.rbegin();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.size() && std_vec.size() && *ft_ret != *std_ret)
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

inline static int	__test_function_rbegin_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<char>::reverse_iterator	ft_ret;
		std::vector<char>::reverse_iterator	std_ret;

		for (idx = 0U ; idx < g_file_size ; ++idx)
		{
			std::ifstream						ifs0(g_file[idx]);
			std::ifstream						ifs1(g_file[idx]);
			std::istream_iterator<char> const	it0(ifs0);
			std::istream_iterator<char> const	it1(ifs1);
			std::istream_iterator<char> const	end_of_stream;
			ft::vector<char>					ft_vec(it0, end_of_stream);
			std::vector<char>					std_vec(it1, end_of_stream);

			g_start = clock();
			ft_ret = ft_vec.rbegin();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.rbegin();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.size() && std_vec.size() && *ft_ret != *std_ret)
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

inline static int	__test_function_rend_constant(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<char>::const_reverse_iterator	ft_ret;
		std::vector<char>::const_reverse_iterator	std_ret;

		for (idx = 0U ; idx < g_file_size ; ++idx)
		{
			std::ifstream						ifs0(g_file[idx]);
			std::ifstream						ifs1(g_file[idx]);
			std::istream_iterator<char> const	it0(ifs0);
			std::istream_iterator<char> const	it1(ifs1);
			std::istream_iterator<char> const	end_of_stream;
			ft::vector<char> const				ft_vec(it0, end_of_stream);
			std::vector<char> const				std_vec(it1, end_of_stream);

			g_start = clock();
			ft_ret = ft_vec.rend();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.rend();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.size() && std_vec.size() && *--ft_ret != *--std_ret)
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

inline static int	__test_function_rend_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<char>::reverse_iterator	ft_ret;
		std::vector<char>::reverse_iterator	std_ret;

		for (idx = 0U ; idx < g_file_size ; ++idx)
		{
			std::ifstream						ifs0(g_file[idx]);
			std::ifstream						ifs1(g_file[idx]);
			std::istream_iterator<char> const	it0(ifs0);
			std::istream_iterator<char> const	it1(ifs1);
			std::istream_iterator<char> const	end_of_stream;
			ft::vector<char>					ft_vec(it0, end_of_stream);
			std::vector<char>					std_vec(it1, end_of_stream);

			g_start = clock();
			ft_ret = ft_vec.rend();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.rend();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.size() && std_vec.size() && *--ft_ret != *--std_ret)
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

inline static int	__test_type_iterator(void)
{
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int>							ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int>						std_vec(&g_int[0], &g_int[g_int_size]);
		ft::vector<int>::iterator const			ft_mid(&ft_vec[ft_vec.size() / 2]);
		std::vector<int>::iterator const		std_mid(&std_vec[std_vec.size() / 2]);
		ft::vector<int>::const_iterator const	ft_cmid(ft_mid);
		std::vector<int>::const_iterator const	std_cmid(std_mid);
		ft::vector<int>::iterator				ft_it;
		std::vector<int>::iterator				std_it;

		if (sizeof(ft_it) != sizeof(std_it))
			ret = ISO_OK;

		for (ft_it = ft_vec.begin(), std_it = std_vec.begin() ;
			ft_it != ft_vec.end() && std_it != std_vec.end() ;
			++ft_it, ++std_it)
		{
			RandomAccessIteratorCheck(ft_it);
			RandomAccessIteratorCheck(std_it);

			if ((ft_it - ft_mid) != (std_it - std_mid) || (ft_it - ft_cmid) != (std_it - std_cmid) ||
				(ft_it < ft_mid) != (std_it < std_mid) || (ft_it < ft_cmid) != (std_it < std_cmid) ||
				(ft_it > ft_mid) != (std_it > std_mid) || (ft_it > ft_cmid) != (std_it > std_cmid) ||
				(ft_it <= ft_mid) != (std_it <= std_mid) || (ft_it <= ft_cmid) != (std_it <= std_cmid) ||
				(ft_it >= ft_mid) != (std_it >= std_mid) || (ft_it >= ft_cmid) != (std_it >= std_cmid) ||
				(*ft_it)++ != (*std_it)++ || ++(ft_it[0]) != ++(std_it[0]) ||
				(*ft_it)-- != (*std_it)-- || --(ft_it[0]) != --(std_it[0]))
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
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int>							ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int>						std_vec(&g_int[0], &g_int[g_int_size]);
		ft::vector<int>::iterator const			ft_mid(&ft_vec[ft_vec.size() / 2]);
		std::vector<int>::iterator const		std_mid(&std_vec[std_vec.size() / 2]);
		ft::vector<int>::const_iterator const	ft_cmid(ft_mid);
		std::vector<int>::const_iterator const	std_cmid(std_mid);
		ft::vector<int>::const_iterator			ft_cit;
		std::vector<int>::const_iterator		std_cit;

		if (sizeof(ft_cit) != sizeof(std_cit))
			ret = ISO_OK;

		for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin() ;
			ft_cit != ft_vec.end() && std_cit != std_vec.end() ;
			++ft_cit, ++std_cit)
		{
			RandomAccessIteratorCheck(ft_cit);
			RandomAccessIteratorCheck(std_cit);

			if ((ft_cit - ft_mid) != (std_cit - std_mid) || (ft_cit - ft_cmid) != (std_cit - std_cmid) ||
				(ft_cit < ft_mid) != (std_cit < std_mid) || (ft_cit < ft_cmid) != (std_cit < std_cmid) ||
				(ft_cit > ft_mid) != (std_cit > std_mid) || (ft_cit > ft_cmid) != (std_cit > std_cmid) ||
				(ft_cit <= ft_mid) != (std_cit <= std_mid) || (ft_cit <= ft_cmid) != (std_cit <= std_cmid) ||
				(ft_cit >= ft_mid) != (std_cit >= std_mid) || (ft_cit >= ft_cmid) != (std_cit >= std_cmid) ||
				*ft_cit != *std_cit || ft_cit[0] != std_cit[0])
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
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int>									ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int>								std_vec(&g_int[0], &g_int[g_int_size]);
		ft::vector<int>::reverse_iterator const			ft_rend(ft_vec.rend());
		std::vector<int>::reverse_iterator const		std_rend(std_vec.rend());
		ft::vector<int>::const_reverse_iterator const	ft_crend(ft_vec.rend());
		std::vector<int>::const_reverse_iterator const	std_crend(std_vec.rend());
		ft::vector<int>::reverse_iterator				ft_rit;
		std::vector<int>::reverse_iterator				std_rit;

		if (sizeof(ft_rit) != sizeof(std_rit))
			ret = ISO_OK;

		for (ft_rit = ft_vec.rbegin(), std_rit = std_vec.rbegin() ;
			ft_rit != ft_vec.rend() && std_rit != std_vec.rend() ;
			++ft_rit, ++std_rit)
		{
			RandomAccessIteratorCheck(ft_rit);
			RandomAccessIteratorCheck(std_rit);

			if ((ft_rit - ft_rend) != (std_rit - std_rend) || (ft_rit - ft_crend) != (std_rit - std_crend) ||
				(ft_rit < ft_rend) != (std_rit < std_rend) || (ft_rit < ft_crend) != (std_rit < std_crend) ||
				(ft_rit > ft_rend) != (std_rit > std_rend) || (ft_rit > ft_crend) != (std_rit > std_crend) ||
				(ft_rit <= ft_rend) != (std_rit <= std_rend) || (ft_rit <= ft_crend) != (std_rit <= std_crend) ||
				(ft_rit >= ft_rend) != (std_rit >= std_rend) || (ft_rit >= ft_crend) != (std_rit >= std_crend) ||
				(*ft_rit)++ != (*std_rit)++ || ++(ft_rit[0]) != ++(std_rit[0]) ||
				(*ft_rit)-- != (*std_rit)-- || --(ft_rit[0]) != --(std_rit[0]))
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
	int	ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int> const						ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int> const						std_vec(&g_int[0], &g_int[g_int_size]);
		ft::vector<int>::const_reverse_iterator		ft_crit;
		std::vector<int>::const_reverse_iterator	std_crit;

		if (sizeof(ft_crit) != sizeof(std_crit))
			ret = ISO_OK;

		for (ft_crit = ft_vec.rbegin(), std_crit = std_vec.rbegin() ;
			ft_crit != ft_vec.rend() && std_crit != std_vec.rend() ;
			++ft_crit, ++std_crit)
		{
			RandomAccessIteratorCheck(ft_crit);
			RandomAccessIteratorCheck(std_crit);

			if ((ft_crit - ft_vec.rend()) != (std_crit - std_vec.rend()) ||
				(ft_crit < ft_vec.rend()) != (std_crit < std_vec.rend()) ||
				(ft_crit > ft_vec.rend()) != (std_crit > std_vec.rend()) ||
				(ft_crit <= ft_vec.rend()) != (std_crit <= std_vec.rend()) ||
				(ft_crit >= ft_vec.rend()) != (std_crit >= std_vec.rend()) ||
				*ft_crit != *std_crit || ft_crit[0] != std_crit[0])
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

inline static int	__test_function_front_constant(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			ft::vector<int> const	ft_vec(&g_int[idx], &g_int[g_int_size]);
			std::vector<int> const	std_vec(&g_int[idx], &g_int[g_int_size]);

			g_start = clock();
			int const &ft_ret = ft_vec.front();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			int const &std_ret = std_vec.front();
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

inline static int	__test_function_front_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			ft::vector<int>		ft_vec(&g_int[idx], &g_int[g_int_size]);
			std::vector<int>	std_vec(&g_int[idx], &g_int[g_int_size]);

			g_start = clock();
			int &ft_ret = ft_vec.front();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			int &std_ret = std_vec.front();
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

inline static int	__test_function_back_constant(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 1U ; idx <= g_int_size ; ++idx)
		{
			ft::vector<int> const	ft_vec(&g_int[0], &g_int[idx]);
			std::vector<int> const	std_vec(&g_int[0], &g_int[idx]);

			g_start = clock();
			int const &ft_ret = ft_vec.back();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			int const &std_ret = std_vec.back();
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

inline static int	__test_function_back_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 1U ; idx <= g_int_size ; ++idx)
		{
			ft::vector<int>		ft_vec(&g_int[0], &g_int[idx]);
			std::vector<int>	std_vec(&g_int[0], &g_int[idx]);

			g_start = clock();
			int &ft_ret = ft_vec.back();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			int &std_ret = std_vec.back();
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

inline static int	__test_function_at_constant(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<int> const	ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int> const	std_vec(&g_int[0], &g_int[g_int_size]);

		// Normal usage
		{
			for (idx = 0U ; idx < g_int_size ; ++idx)
			{
				g_start = clock();
				int const &ft_ret = ft_vec.at(idx);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				int const &std_ret = std_vec.at(idx);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
		}
		// Overlimits usage
		{
			try
			{
				ft_vec.at(42LU);
			}
			catch (std::out_of_range const &e)
			{
				goto constant_at_overlimits_usage_ok;
			}
			return KO;
			constant_at_overlimits_usage_ok:;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_at_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<int>		ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int>	std_vec(&g_int[0], &g_int[g_int_size]);

		// Normal usage
		{
			for (idx = 0U ; idx < g_int_size ; ++idx)
			{
				g_start = clock();
				int &ft_ret = ft_vec.at(idx);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				int &std_ret = std_vec.at(idx);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
		}
		// Overlimits usage
		{
			try
			{
				++ft_vec.at(42LU);
			}
			catch (std::out_of_range const &e)
			{
				goto mutable_at_overlimits_usage_ok;
			}
			return KO;
			mutable_at_overlimits_usage_ok:;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_insert_fill(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			ft::vector<float>	ft_vec;
			std::vector<float>	std_vec;

			for (idx = 0U ; idx < g_float_size ; ++idx)
			{
				g_start = clock();
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_float_size - idx, g_float[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_float_size - idx, g_float[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Trivially copyable
		// Ambiguous
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			for (idx = 0U ; idx < g_int_size ; ++idx)
			{
				g_start = clock();
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, static_cast<int>(g_int_size - idx), g_int[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, static_cast<int>(g_int_size - idx), g_int[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec;
			std::vector<std::string>	std_vec;

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				g_start = clock();
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_string_size - idx, g_string[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_string_size - idx, g_string[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_insert_range(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			ft::vector<float>	ft_vec;
			std::vector<float>	std_vec;

			for (idx = 0U ; idx < g_float_size ; ++idx)
			{
				g_start = clock();
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_float, &g_float[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_float, &g_float[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Trivially copyable
		// Force naive iteration along th range
		{
			ft::vector<char>	ft_vec;
			std::vector<char>	std_vec;

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream				ifs0(g_file[idx]);
				std::ifstream				ifs1(g_file[idx]);
				std::istream_iterator<char>	it0(ifs0);
				std::istream_iterator<char>	it1(ifs1);
				std::istream_iterator<char>	end_of_stream;

				g_start = clock();
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, it0, end_of_stream);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, it1, end_of_stream);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec;
			std::vector<std::string>	std_vec;

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				g_start = clock();
				ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_string, &g_string[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_string, &g_string[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_insert_single(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Single insertion
		// Trivially copyable
		{
			ft::vector<float>					ft_vec;
			std::vector<float>					std_vec;
			ft::vector<float>::const_iterator	ft_ret;
			std::vector<float>::const_iterator	std_ret;

			for (idx = 0U ; idx < g_float_size ; ++idx)
			{
				g_start = clock();
				ft_ret = ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_float[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_float[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
					ft_ret - ft_vec.begin() != std_ret - std_vec.begin())
					return KO;
			}
		}
		// Single insertion
		// Non-trivial copy required
		{
			ft::vector<std::string>						ft_vec;
			std::vector<std::string>					std_vec;
			ft::vector<std::string>::const_iterator		ft_ret;
			std::vector<std::string>::const_iterator	std_ret;

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				g_start = clock();
				ft_ret = ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, g_string[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std_vec.insert(std_vec.begin() + std_vec.size() / 2, g_string[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
					ft_ret - ft_vec.begin() != std_ret - std_vec.begin())
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

inline static int	__test_function_erase_range(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<t_hhuint>					ft_vec;
		std::vector<t_hhuint>					std_vec;
		ft::vector<t_hhuint>::const_iterator	ft_ret;
		std::vector<t_hhuint>::const_iterator	std_ret;

		for (idx = 0U ; idx < g_hhuint_size ; ++idx)
		{
			ft_vec.insert(ft_vec.end(), &g_hhuint[idx], &g_hhuint[g_hhuint_size]);
			std_vec.insert(std_vec.end(), &g_hhuint[idx], &g_hhuint[g_hhuint_size]);

			g_start = clock();
			ft_ret = ft_vec.erase(ft_vec.begin() + idx, ft_vec.begin() + idx * 2);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.erase(std_vec.begin() + idx, std_vec.begin() + idx * 2);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.capacity() != std_vec.capacity())
				ret = ISO_OK;
			if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
				ft_ret - ft_vec.begin() != std_ret - std_vec.begin())
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

inline static int	__test_function_erase_single(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<t_hhuint>					ft_vec;
		std::vector<t_hhuint>					std_vec;
		ft::vector<t_hhuint>::const_iterator	ft_ret;
		std::vector<t_hhuint>::const_iterator	std_ret;

		for (idx = 0U ; idx < g_hhuint_size ; ++idx)
		{
			ft_vec.insert(ft_vec.end(), &g_hhuint[idx], &g_hhuint[g_hhuint_size]);
			std_vec.insert(std_vec.end(), &g_hhuint[idx], &g_hhuint[g_hhuint_size]);

			g_start = clock();
			ft_ret = ft_vec.erase(ft_vec.begin() + idx);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_vec.erase(std_vec.begin() + idx);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.capacity() != std_vec.capacity())
				ret = ISO_OK;
			if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()) ||
				ft_ret - ft_vec.begin() != std_ret - std_vec.begin())
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

inline static int	__test_function_push_back(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			ft::vector<long double>		ft_vec;
			std::vector<long double>	std_vec;

			for (idx = 0U ; idx < g_long_double_size ; ++idx)
			{
				g_start = clock();
				ft_vec.push_back(g_long_double[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.push_back(g_long_double[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec;
			std::vector<std::string>	std_vec;

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				g_start = clock();
				ft_vec.push_back(g_string[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.push_back(g_string[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_pop_back(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int>		ft_vec(&g_int[0], &g_int[g_int_size]);
		std::vector<int>	std_vec(&g_int[0], &g_int[g_int_size]);

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			g_start = clock();
			ft_vec.pop_back();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_vec.pop_back();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.capacity() != std_vec.capacity())
				return ISO_OK;
			if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_clear(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			ft::vector<std::string>		ft_vec(&g_string[0], &g_string[idx]);
			std::vector<std::string>	std_vec(&g_string[0], &g_string[idx]);

			g_start = clock();
			ft_vec.clear();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_vec.clear();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.capacity() != std_vec.capacity())
				return ISO_OK;
			if (ft_vec.size() != std_vec.size())
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

inline static int	__test_function_assign_fill(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			ft::vector<double>	ft_vec(7LU, NAN);
			std::vector<double>	std_vec(7LU, NAN);

			for (idx = 0U ; idx < g_double_size ; ++idx)
			{
				g_start = clock();
				ft_vec.assign(idx * idx, g_double[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.assign(idx * idx, g_double[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Trivially copyable
		// Ambiguous
		{
			ft::vector<t_lint>	ft_vec(7LU, 42L);
			std::vector<t_lint>	std_vec(7LU, 42L);

			for (idx = 0U ; idx < g_lint_size ; ++idx)
			{
				g_start = clock();
				ft_vec.assign(static_cast<t_lint>(idx * idx), g_lint[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.assign(static_cast<t_lint>(idx * idx), g_lint[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec(7LU, std::string("Koala"));
			std::vector<std::string>	std_vec(7LU, std::string("Koala"));

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				g_start = clock();
				ft_vec.assign(idx * idx, g_string[idx]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.assign(idx * idx, g_string[idx]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_assign_range(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			ft::vector<double>	ft_vec(7LU, NAN);
			std::vector<double>	std_vec(7LU, NAN);

			for (idx = 0U ; idx < g_double_size ; ++idx)
			{
				g_start = clock();
				ft_vec.assign(&g_double[idx / 2 + (idx % 2)], &g_double[g_double_size - idx / 2 - !(idx % 2)]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.assign(&g_double[idx / 2 + (idx % 2)], &g_double[g_double_size - idx / 2 - !(idx % 2)]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Trivially copyable
		// Force naive iteration along the range
		{
			ft::vector<char>	ft_vec(7LU, '+');
			std::vector<char>	std_vec(7LU, '+');

			for (idx = 0U ; idx < g_file_size ; ++idx)
			{
				std::ifstream				ifs0(g_file[idx]);
				std::ifstream				ifs1(g_file[idx]);
				std::istream_iterator<char>	it0(ifs0);
				std::istream_iterator<char>	it1(ifs1);
				std::istream_iterator<char>	end_of_stream;

				g_start = clock();
				ft_vec.assign(it0, end_of_stream);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.assign(it1, end_of_stream);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec(7LU, std::string("Koala"));
			std::vector<std::string>	std_vec(7LU, std::string("Koala"));

			for (idx = 0U ; idx < g_string_size ; ++idx)
			{
				g_start = clock();
				ft_vec.assign(&g_string[idx / 2 + (idx % 2)], &g_string[10 - idx / 2 - !(idx % 2)]);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.assign(&g_string[idx / 2 + (idx % 2)], &g_string[10 - idx / 2 - !(idx % 2)]);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
					ret = ISO_OK;
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_swap_member(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			ft::vector<t_uint>	ft_vec0(&g_uint[0], &g_uint[g_uint_size]);
			std::vector<t_uint>	std_vec0(&g_uint[0], &g_uint[g_uint_size]);
			ft::vector<t_uint>	ft_vec1;
			std::vector<t_uint>	std_vec1;

			for (idx = 0U ; idx < g_uint_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), g_uint[idx / 2]);
				std_vec1.insert(std_vec1.begin(), g_uint[idx / 2]);
			}

			g_start = clock();
			ft_vec0.swap(ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_vec0.swap(std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				ft_vec1.size() != std_vec1.size() || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
				return KO;
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec0(&g_string[0], &g_string[g_string_size]);
			std::vector<std::string>	std_vec0(&g_string[0], &g_string[g_string_size]);
			ft::vector<std::string>		ft_vec1;
			std::vector<std::string>	std_vec1;

			for (idx = 0U ; idx < g_string_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), g_string[idx / 2]);
				std_vec1.insert(std_vec1.begin(), g_string[idx / 2]);
			}

			g_start = clock();
			ft_vec0.swap(ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_vec0.swap(std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				ft_vec1.size() != std_vec1.size() || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
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

inline static int	__test_function_swap_non_member(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			ft::vector<t_uint>	ft_vec0(&g_uint[0], &g_uint[g_uint_size]);
			std::vector<t_uint>	std_vec0(&g_uint[0], &g_uint[g_uint_size]);
			ft::vector<t_uint>	ft_vec1;
			std::vector<t_uint>	std_vec1;

			for (idx = 0U ; idx < g_uint_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), g_uint[idx / 2]);
				std_vec1.insert(std_vec1.begin(), g_uint[idx / 2]);
			}

			g_start = clock();
			ft::swap(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::swap(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				ft_vec1.size() != std_vec1.size() || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
				return KO;
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec0(&g_string[0], &g_string[g_string_size]);
			std::vector<std::string>	std_vec0(&g_string[0], &g_string[g_string_size]);
			ft::vector<std::string>		ft_vec1;
			std::vector<std::string>	std_vec1;

			for (idx = 0U ; idx < g_string_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin(), g_string[idx / 2]);
				std_vec1.insert(std_vec1.begin(), g_string[idx / 2]);
			}

			g_start = clock();
			ft::swap(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::swap(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()) ||
				ft_vec1.size() != std_vec1.size() || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin()))
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

inline static int	__test_function_reserve(void)
{
	int		ret;
	size_t	n;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<t_huint>		ft_vec(&g_huint[0], &g_huint[g_huint_size]);
		std::vector<t_huint>	std_vec(&g_huint[0], &g_huint[g_huint_size]);

		// Normal usage
		{
			for (n = 0LU ; n < 100LU ; n += 10LU)
			{
				g_start = clock();
				ft_vec.reserve(n);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_vec.reserve(n);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_vec.capacity() != std_vec.capacity())
				{
					if (ft_vec.capacity() < n)
						return KO;
					ret = ISO_OK;
				}
				if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
					return KO;
			}
		}
		// Overlimits usage
		{
			try
			{
				ft_vec.reserve(ft_vec.max_size() + 42LU);
			}
			catch (std::length_error const &e)
			{
				goto reserve_overlimits_ok;
			}
			return KO;
			reserve_overlimits_ok:

			if (ft_vec.capacity() != std_vec.capacity())
			{
				if (ft_vec.capacity() < ft_vec.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_function_resize(void)
{
	int		ret;
	size_t	n;

	title(__func__);
	ret = IMP_OK;
	try
	{
		ft::vector<int>		ft_vec;
		std::vector<int>	std_vec;

		for (n = 0LU ; n < g_int_size ; ++n)
		{
			g_start = clock();
			ft_vec.resize(n * n, g_int[n]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_vec.resize(n * n, g_int[n]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.capacity() != std_vec.capacity())
			{
				if (ft_vec.capacity() < n * n)
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
				return KO;
		}
		for (--n ; n ; --n)
		{
			g_start = clock();
			ft_vec.resize(n * n);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_vec.resize(n * n);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec.capacity() != std_vec.capacity())
			{
				if (ft_vec.capacity() < n * n)
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec.size() != std_vec.size() || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()))
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

inline static int	__test_operator_assign(void)
{
	int		ret;
	t_uint	idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Trivially copyable
		{
			ft::vector<double>	ft_vec0(&g_double[0], &g_double[g_double_size]);
			std::vector<double>	std_vec0(&g_double[0], &g_double[g_double_size]);
			ft::vector<double>	ft_vec1;
			std::vector<double>	std_vec1;

			for (idx = 0U ; idx < g_double_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin() + idx / 2, g_double[idx / 2]);
				std_vec1.insert(std_vec1.begin() + idx / 2, g_double[idx / 2]);
			}

			g_start = clock();
			ft_vec0 = ft_vec1;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_vec0 = std_vec1;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()))
				return KO;
		}
		// Non-trivial copy required
		{
			ft::vector<std::string>		ft_vec0(&g_string[0], &g_string[g_string_size]);
			std::vector<std::string>	std_vec0(&g_string[0], &g_string[g_string_size]);
			ft::vector<std::string>		ft_vec1;
			std::vector<std::string>	std_vec1;

			for (idx = 0U ; idx < g_string_size * 2 ; ++idx)
			{
				ft_vec1.insert(ft_vec1.begin() + idx / 2, g_string[idx / 2]);
				std_vec1.insert(std_vec1.begin() + idx / 2, g_string[idx / 2]);
			}

			g_start = clock();
			ft_vec0 = ft_vec1;
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_vec0 = std_vec1;
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_vec0.capacity() != std_vec0.capacity())
			{
				if (ft_vec0.capacity() < ft_vec0.size())
					return KO;
				ret = ISO_OK;
			}
			if (ft_vec0.size() != std_vec0.size() || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin()))
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

inline static int	__test_operator_access_constant(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<t_lint> const	ft_vector(&g_lint[0], &g_lint[g_lint_size]);
		std::vector<t_lint> const	std_vector(&g_lint[0], &g_lint[g_lint_size]);

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			g_start = clock();
			t_lint const	&ft_ref = ft_vector[idx];
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			t_lint const	&std_ref = std_vector[idx];
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ref != std_ref)
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

inline static int	__test_operator_access_mutable(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::vector<t_lint>	ft_vector(&g_lint[0], &g_lint[g_lint_size]);
		std::vector<t_lint>	std_vector(&g_lint[0], &g_lint[g_lint_size]);

		for (idx = 0U ; idx < 10U ; ++idx)
		{
			g_start = clock();
			t_lint	&ft_ref = ft_vector[idx];
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			t_lint	&std_ref = std_vector[idx];
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ref != std_ref)
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;
		bool						ft_ret;
		bool						std_ret;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft::operator==(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator==(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);

			g_start = clock();
			ft_ret = ft::operator==(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator==(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;
		bool						ft_ret;
		bool						std_ret;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft::operator!=(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator!=(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);

			g_start = clock();
			ft_ret = ft::operator!=(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator!=(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;
		bool						ft_ret;
		bool						std_ret;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft::operator<(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);

			g_start = clock();
			ft_ret = ft::operator<(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;
		bool						ft_ret;
		bool						std_ret;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft::operator>(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);

			g_start = clock();
			ft_ret = ft::operator>(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;
		bool						ft_ret;
		bool						std_ret;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft::operator<=(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);

			g_start = clock();
			ft_ret = ft::operator<=(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator<=(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
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
		ft::vector<std::string>		ft_vec0;
		ft::vector<std::string>		ft_vec1;
		std::vector<std::string>	std_vec0;
		std::vector<std::string>	std_vec1;
		bool						ft_ret;
		bool						std_ret;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			g_start = clock();
			ft_ret = ft::operator>=(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec0.push_back(g_string[idx]);
			std_vec0.push_back(g_string[idx]);

			g_start = clock();
			ft_ret = ft::operator>=(ft_vec0, ft_vec1);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std::operator>=(std_vec0, std_vec1);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			ft_vec1.push_back(g_string[idx]);
			std_vec1.push_back(g_string[idx]);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

int	test_vector(void)
{
	t_fct const	tests[] = {
		__test_constructor_default,
		__test_constructor_fill,
		__test_constructor_range,
		__test_constructor_copy,
		__test_default_template_type_Alloc,
		__test_type_value_type,
		__test_type_allocator_type,
		__test_type_reference,
		__test_type_const_reference,
		__test_type_pointer,
		__test_type_const_pointer,
		__test_function_get_allocator,
		__test_function_max_size,
		__test_function_capacity,
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
		__test_function_front_constant,
		__test_function_front_mutable,
		__test_function_back_constant,
		__test_function_back_mutable,
		__test_function_at_constant,
		__test_function_at_mutable,
		__test_function_insert_fill,
		__test_function_insert_range,
		__test_function_insert_single,
		__test_function_erase_range,
		__test_function_erase_single,
		__test_function_push_back,
		__test_function_pop_back,
		__test_function_clear,
		__test_function_assign_fill,
		__test_function_assign_range,
		__test_function_swap_member,
		__test_function_swap_non_member,
		__test_function_reserve,
		__test_function_resize,
		__test_operator_assign,
		__test_operator_access_constant,
		__test_operator_access_mutable,
		__test_operator_equivalent,
		__test_operator_different,
		__test_operator_lower,
		__test_operator_greater,
		__test_operator_lower_or_equivalent,
		__test_operator_greater_or_equivalent,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << LIGHT_BLUE_FG;
	std::cout << "####################################################" << '\n';
	std::cout << "##                     VECTOR                     ##" << '\n';
	std::cout << "####################################################" << '\n';
	std::cerr << RESET;

	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
	{
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
