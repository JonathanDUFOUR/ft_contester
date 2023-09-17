/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:15:58 by jodufour          #+#    #+#             */
/*   Updated: 2023/09/17 21:08:06 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
# define TESTER_HPP

# include <cstddef>
# include <string>

# define PADDING			33
# define SLEEP_TIME_SEC		0
# define SLEEP_TIME_NANOSEC	0

typedef int	(*				t_fct)(void);
typedef struct s_test		t_test;

struct s_test
{
	std::string const	name;
	t_fct const			function;
	bool				run_as_default;
};

int	test_algorithm(void);
int	test_is_integral(void);
int	test_map(void);
int	test_pair(void);
int	test_rb_tree(void);
int	test_reverse_iterator(void);
int	test_set(void);
int	test_stack(void);
int	test_vector(void);

void	title(char const *const funcName);

#endif
