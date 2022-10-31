/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:16 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/31 15:20:12 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arrays.hpp"
#include "benchmark.hpp"
#include "colors.hpp"
#include "headers.hpp"
#include "tester.hpp"
#include "e_ret.hpp"
#include STACK_HEADER
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

inline static int	__test_constructor_default(void)
{
	int					ret;
	std::vector<t_uint>	vec;

	title(__func__);
	ret = IMP_OK;
	try
	{
		g_start = clock();
		ft::stack<int, std::vector<int> >	ft_sta;
		g_ft_duration = clock() - g_start;
		g_ft_duration += !g_ft_duration;

		g_start = clock();
		std::stack<int, std::vector<int> >	std_sta;
		g_std_duration = clock() - g_start;
		g_std_duration += !g_std_duration;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (sizeof(ft_sta) != sizeof(std_sta) || memcmp(&ft_sta, &std_sta, sizeof(ft_sta)))
			ret = ISO_OK;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return ret;
}

inline static int	__test_constructor_wrapper(void)
{
	int					ret;
	std::vector<t_uint>	vec;
	t_uint				idx;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Empty underlying container
		{
			g_start = clock();
			ft::stack<t_uint, std::vector<t_uint> >		ft_sta(vec);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std::stack<t_uint, std::vector<t_uint> >	std_sta(vec);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (sizeof(ft_sta) != sizeof(std_sta) || memcmp(&ft_sta, &std_sta, sizeof(ft_sta)))
				ret = ISO_OK;
		}
		// Non-empty underlying container
		{
			for (idx = 0U ; idx < g_uint_size ; ++idx)
			{
				vec.push_back(g_uint[idx]);

				g_start = clock();
				ft::stack<t_uint, std::vector<t_uint> >		ft_sta(vec);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std::stack<t_uint, std::vector<t_uint> >	std_sta(vec);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (sizeof(ft_sta) != sizeof(std_sta))
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

inline static int	__test_default_template_type_Container(void)
{
	title(__func__);

	typedef ft::stack<float>						sta_type_0;
	typedef ft::stack<float, ft::vector<float> >	sta_type_1;

	if (!is_same<sta_type_0, sta_type_1>::value)
		return KO;

	return IMP_OK;
}

inline static int	__test_type_value_type(void)
{
	title(__func__);
	try
	{
		typedef ft::stack<t_lint, std::vector<t_lint> >	sta_type;

		if (!is_same<sta_type::value_type, t_lint>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_size_type(void)
{
	title(__func__);
	try
	{
		typedef ft::stack<t_lint, std::vector<t_lint> >	sta_type;

		if (!is_same<sta_type::size_type, std::vector<t_lint>::size_type>::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_type_container_type(void)
{
	title(__func__);
	try
	{
		typedef ft::stack<t_lint, std::vector<t_lint> >	sta_type;

		if (!is_same<sta_type::container_type, std::vector<t_lint> >::value)
			return KO;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return KO;
	}
	return IMP_OK;
}

inline static int	__test_function_top_constant(void)
{
	std::vector<char>	vec;
	t_uint				idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_char_size ; ++idx)
		{
			vec.push_back(g_char[idx]);

			ft::stack<char, std::vector<char> > const	ft_sta(vec);
			std::stack<char, std::vector<char> > const	std_sta(vec);

			g_start = clock();
			char const	&ft_ret = ft_sta.top();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			char const	&std_ret = std_sta.top();
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

inline static int	__test_function_top_mutable(void)
{
	std::vector<char>	vec;
	t_uint				idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_char_size ; ++idx)
		{
			vec.push_back(g_char[idx]);

			ft::stack<char, std::vector<char> >		ft_sta(vec);
			std::stack<char, std::vector<char> >	std_sta(vec);

			g_start = clock();
			char	&ft_ret = ft_sta.top();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			char	&std_ret = std_sta.top();
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

inline static int	__test_function_push(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<std::string, std::vector<std::string> >	ft_sta;
		std::stack<std::string, std::vector<std::string> >	std_sta;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			g_start = clock();
			ft_sta.push(g_string[idx]);
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_sta.push(g_string[idx]);
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_sta.top() != std_sta.top())
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

inline static int	__test_function_pop(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::stack<float, std::vector<float> >	ft_sta;
		std::stack<float, std::vector<float> >	std_sta;

		for (idx = 0U ; idx < g_float_size ; ++idx)
		{
			ft_sta.push(g_float[idx]);
			std_sta.push(g_float[idx]);
		}
		for (idx = 0U ; idx < g_float_size ; ++idx)
		{
			if (ft_sta.top() != std_sta.top())
				return KO;
			g_start = clock();
			ft_sta.pop();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_sta.pop();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));
		}
		for (idx = 0U ; idx < g_float_size ; ++idx)
		{
			g_start = clock();
			ft_sta.pop();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_sta.pop();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));
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
		std::vector<t_lint>	vec;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_lint_size ; ++idx)
		{
			ft::stack<t_lint, std::vector<t_lint> > const	ft_sta(vec);
			std::stack<t_lint, std::vector<t_lint> > const	std_sta(vec);

			g_start = clock();
			ft_ret = ft_sta.empty();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_sta.empty();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			vec.push_back(g_lint[idx]);
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
		std::vector<t_uint>									vec;
		ft::stack<t_uint, std::vector<t_uint> >::size_type	ft_ret;
		std::stack<t_uint, std::vector<t_uint> >::size_type	std_ret;

		for (idx = 0U ; idx < g_uint_size ; ++idx)
		{
			ft::stack<t_uint, std::vector<t_uint> > const	ft_sta(vec);
			std::stack<t_uint, std::vector<t_uint> > const	std_sta(vec);

			g_start = clock();
			ft_ret = ft_sta.size();
			g_ft_duration = clock() - g_start;
			g_ft_duration += !g_ft_duration;

			g_start = clock();
			std_ret = std_sta.size();
			g_std_duration = clock() - g_start;
			g_std_duration += !g_std_duration;

			g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

			if (ft_ret != std_ret)
				return KO;

			vec.push_back(g_uint[idx]);
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
		std::vector<int>	vec;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			// Equivalence
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator==(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator==(std_sta0, std_sta1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Difference
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);

				vec.push_back(g_int[idx]);

				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator==(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator==(std_sta0, std_sta1);
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
		std::vector<int>	vec;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			// Equivalence
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator!=(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator!=(std_sta0, std_sta1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Difference
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);

				vec.push_back(g_int[idx]);

				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator!=(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator!=(std_sta0, std_sta1);
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
		std::vector<int>	vec;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			// Equivalence
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator<(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<(std_sta0, std_sta1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Difference
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);

				vec.push_back(g_int[idx]);

				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator<(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<(std_sta0, std_sta1);
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
		std::vector<int>	vec;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			// Equivalence
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator>(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>(std_sta0, std_sta1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Difference
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);

				vec.push_back(g_int[idx]);

				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator>(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>(std_sta0, std_sta1);
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
		std::vector<int>	vec;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			// Equivalence
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator<=(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<=(std_sta0, std_sta1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Difference
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);

				vec.push_back(g_int[idx]);

				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator<=(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator<=(std_sta0, std_sta1);
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
		std::vector<int>	vec;
		bool				ft_ret;
		bool				std_ret;

		for (idx = 0U ; idx < g_int_size ; ++idx)
		{
			// Equivalence
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator>=(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>=(std_sta0, std_sta1);
				g_std_duration = clock() - g_start;
				g_std_duration += !g_std_duration;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return KO;
			}
			// Difference
			{
				ft::stack<int, std::vector<int> > const		ft_sta0(vec);
				std::stack<int, std::vector<int> > const	std_sta0(vec);

				vec.push_back(g_int[idx]);

				ft::stack<int, std::vector<int> > const		ft_sta1(vec);
				std::stack<int, std::vector<int> > const	std_sta1(vec);

				g_start = clock();
				ft_ret = ft::operator>=(ft_sta0, ft_sta1);
				g_ft_duration = clock() - g_start;
				g_ft_duration += !g_ft_duration;

				g_start = clock();
				std_ret = std::operator>=(std_sta0, std_sta1);
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

int	test_stack(void)
{
	t_test const	tests[] = {
		__test_constructor_default,
		__test_constructor_wrapper,
		__test_default_template_type_Container,
		__test_type_value_type,
		__test_type_size_type,
		__test_type_container_type,
		__test_function_top_constant,
		__test_function_top_mutable,
		__test_function_push,
		__test_function_pop,
		__test_function_empty,
		__test_function_size,
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
	std::cout << "###################################################" << '\n';
	std::cout << "##                     STACK                     ##" << '\n';
	std::cout << "###################################################" << '\n';
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
