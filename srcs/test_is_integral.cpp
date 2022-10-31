/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_integral.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:00:25 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/31 14:53:06 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.hpp"
#include "headers.hpp"
#include "iterator/restrictor/input_iterator_restrictor.tpp"
#include "tester.hpp"
#include "t_int.hpp"
#include IS_INTEGRAL_HEADER
#include <cstdlib>
#include <iostream>

inline static int	__test_bool(void)
{
	title(__func__);
	try
	{
		ft::is_integral<bool> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_char(void)
{
	title(__func__);
	try
	{
		ft::is_integral<char> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_wchar_t(void)
{
	title(__func__);
	try
	{
		ft::is_integral<wchar_t> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_signed_char(void)
{
	title(__func__);
	try
	{
		ft::is_integral<signed char> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_signed_short(void)
{
	title(__func__);
	try
	{
		ft::is_integral<signed short> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_signed_int(void)
{
	title(__func__);
	try
	{
		ft::is_integral<signed int> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_signed_long(void)
{
	title(__func__);
	try
	{
		ft::is_integral<signed long> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_unsigned_char(void)
{
	title(__func__);
	try
	{
		ft::is_integral<unsigned char> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_unsigned_short(void)
{
	title(__func__);
	try
	{
		ft::is_integral<unsigned short> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_unsigned_int(void)
{
	title(__func__);
	try
	{
		ft::is_integral<unsigned int> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_unsigned_long(void)
{
	title(__func__);
	try
	{
		ft::is_integral<unsigned long> const	ie;

		if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_void(void)
{
	title(__func__);
	try
	{
		ft::is_integral<void> const	ie;

		if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_pointer(void)
{
	title(__func__);
	try
	{
		ft::is_integral<void *> const	ie;

		if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_float(void)
{
	title(__func__);
	try
	{
		ft::is_integral<float> const	ie;

		if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_double(void)
{
	title(__func__);
	try
	{
		ft::is_integral<double> const	ie;

		if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_std_string(void)
{
	title(__func__);
	try
	{
		ft::is_integral<std::string> const	ie;

		if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_ft_input_iterator_restrictor(void)
{
	title(__func__);
	try
	{
		ft::is_integral<tester::input_iterator_restrictor<t_huint const *> > const	ie;

		if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false)
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int	test_is_integral(void)
{
	t_test const	tests[] = {
		__test_bool,
		__test_wchar_t,
		__test_char,
		__test_signed_char,
		__test_signed_short,
		__test_signed_int,
		__test_signed_long,
		__test_unsigned_char,
		__test_unsigned_short,
		__test_unsigned_int,
		__test_unsigned_long,
		__test_void,
		__test_pointer,
		__test_float,
		__test_double,
		__test_std_string,
		__test_ft_input_iterator_restrictor,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << LIGHT_BLUE_FG;
	std::cout << "###################################################" << '\n';
	std::cout << "##                  IS_INTEGRAL                  ##" << '\n';
	std::cout << "###################################################" << '\n';
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
		std::cout << '\n';
	}
	std::cout << '\n';
	return koCount;
}
