/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 06:00:18 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/08 16:11:09 by jodufour         ###   ########.fr       */
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

int	main(void)
{
	t_test const	tests[] = {
		test_pair,
		test_reverse_iterator,
		test_is_integral,
		test_algorithm,
		test_rb_tree,
		test_vector,
		test_stack,
		test_map,
		test_set,
		NULL
	};
	t_uint	koCount;
	t_uint	idx;

	for (koCount = 0, idx = 0 ; tests[idx] ; ++idx)
		koCount += tests[idx]();
	return !!koCount;
}
