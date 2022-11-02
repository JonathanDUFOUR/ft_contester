/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 06:00:18 by jodufour          #+#    #+#             */
/*   Updated: 2022/11/02 11:23:32 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "t_int.hpp"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <set>

clock_t					g_start;
time_t					g_ft_duration;
time_t					g_std_duration;
std::multiset<float>	g_ratio;

static void	__init(void) __attribute__((constructor));

static void	__init(void)
{
	std::cout << std::setprecision(2) << std::fixed;
	srand(time(NULL));
}

int	main(int const ac, char const *const *av)
{
	t_test const	tests[] = {
		{std::string("is_integral"), test_is_integral, true},
		{std::string("pair"), test_pair, true},
		{std::string("reverse_iterator"), test_reverse_iterator, true},
		{std::string("algorithm"), test_algorithm, true},
		// {std::string("rb_tree"), test_rb_tree, false},
		{std::string("vector"), test_vector, true},
		{std::string("stack"), test_stack, true},
		{std::string("map"), test_map, true},
		// {std::string("set"), test_set, false},
		{std::string(""), NULL, false}
	};
	std::string		test_name;
	t_uint			koCount;
	t_uint			idx;

	koCount = 0U;
	if (ac == 1)
	{
		for (idx = 0U ; tests[idx].function ; ++idx)
			if (tests[idx].run_as_default)
				koCount += tests[idx].function();
	}
	else
	{
		for (++av ; *av ; ++av)
		{
			for (test_name = *av, idx = 0U ; tests[idx].function && test_name != tests[idx].name ; ++idx);
			if (tests[idx].function)
				koCount += tests[idx].function();
			else
				std::cout << "Test '" << test_name << "' not found" << std::endl;
		}
	}
	return !!koCount;
}
