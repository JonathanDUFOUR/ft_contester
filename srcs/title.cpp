/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:02:43 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/06 13:25:45 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "tester.hpp"

/**
 * @brief	Display a title for a test function
 * 
 * @param	funcName The name of the running test function.
 * 			It is assumed to be formatted like this: __test_<explicit_name>.
 */
void	title(char const *const funcName)
{
	std::string	str(funcName + 7);

	if (str.length() < PADDING)
		str.append(PADDING - str.length(), ' ');
	std::cout << str << " : ";
}
