/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _type_traits.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:38 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/31 14:51:47 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TYPE_TRAITS_HPP
# define _TYPE_TRAITS_HPP

namespace tester
{

template <typename T, T v>
struct integral_constant
{
	// Member types
	typedef T						value_type;
	typedef integral_constant<T, v>	type;

	// Attributes
	static value_type const	value = v;

	// Operators
	operator value_type(void) const
	{
		return value;
	}

}; // struct integral_constant

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;

template <typename T> class is_pointer : public false_type {};
template <typename T> class is_pointer<T *> : public true_type {};

template <typename T0, typename T1> class is_same : public false_type {};
template <typename T> class is_same<T, T> : public true_type {};
	
} // namespace tester

#endif
