/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:00:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/08 16:05:02 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "benchmark.hpp"
#include "colors.hpp"
#include <iomanip>
#include <iostream>

static inline float	__average(void)
{
	float							sum;
	std::set<float>::const_iterator	cit;

	for (sum = 0.0f, cit = g_ratio.begin() ; cit != g_ratio.end() ; ++cit)
		sum += *cit;
	return sum / g_ratio.size();
}

void	benchmark_best_case(void)
{
	float const	best = *g_ratio.begin();

	std::cout << "(best case: ";
	if (best < 1.0f)
	{
		std::cerr << GREEN_FG << BOLD << BLINK << PURPLE_BG;
		std::cout << 1.0f / best << "x faster";
		std::cerr << RESET;
	}
	else
	{
		if (best < 10.0f)
			std::cerr << GREEN_FG;
		else if (best < 20.0f)
			std::cerr << YELLOW_FG;
		else
			std::cerr << RED_FG;
		std::cout << best << "x slower";
		std::cerr << RESET;
	}
	std::cout << ')';
}

void	benchmark_worst_case(void)
{
	float const	worst = *g_ratio.rbegin();

	std::cout << "(worst case: ";
	if (worst < 1.0f)
	{
		std::cerr << GREEN_FG << BOLD << BLINK << PURPLE_BG;
		std::cout << 1.0f / worst << "x faster";
		std::cerr << RESET;
	}
	else
	{
		if (worst < 10.0f)
			std::cerr << GREEN_FG;
		else if (worst < 20.0f)
			std::cerr << YELLOW_FG;
		else
			std::cerr << RED_FG;
		std::cout << worst << "x slower";
		std::cerr << RESET;
	}
	std::cout << ')';
}

void	benchmark_average_case(void)
{
	float const	average = __average();

	std::cout << "(average case: ";
	if (average < 1.0f)
	{
		std::cerr << GREEN_FG << BOLD << BLINK << PURPLE_BG;
		std::cout << 1.0f / average << "x faster";
		std::cerr << RESET;
	}
	else
	{
		if (average < 10.0f)
			std::cerr << GREEN_FG;
		else if (average < 20.0f)
			std::cerr << YELLOW_FG;
		else
			std::cerr << RED_FG;
		std::cout << average << "x slower";
		std::cerr << RESET;
	}
	std::cout << ')';
}
