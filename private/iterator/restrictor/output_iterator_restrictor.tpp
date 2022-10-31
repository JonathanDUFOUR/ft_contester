/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_iterator_restrictor.tpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 06:26:53 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/31 14:43:15 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_ITERATOR_RESTRICTOR_TPP
# define OUTPUT_ITERATOR_RESTRICTOR_TPP

# include "iterator.hpp"

namespace tester
{
/**
 * @par		This class is the implementation of the output_iterator_restrictor.
 * 			It is designed to restrict any type of iterator to the Output Iterator requirements at most.
 * 			According to the C++98 standard, an Output Iterator must conform to the following requirements:
 * 			- copy constructible (it0(it1))
 * 			- copy assignable (it0 = it1)
 * 			- dereferenceable in write mode (*it = value)
 * 			- prefix incrementable (++it)
 * 			- postfix incrementable (it++)
 * 
 * @tparam	Iterator The type of the iterator to restrict.
 */
template <typename Iterator>
class output_iterator_restrictor
{
private:
	// Member types
	typedef output_iterator_restrictor<Iterator>						_self_type;

public:
	// Member types
	typedef Iterator													iterator_type;
	typedef typename std::output_iterator_tag							iterator_category;

	typedef typename iterator_traits<iterator_type>::value_type			value_type;
	typedef typename iterator_traits<iterator_type>::pointer			pointer;
	typedef typename iterator_traits<iterator_type>::reference			reference;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;

protected:
	// Attributes
	iterator_type	_it;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new output_iterator_restrictor object from an iterator. (wrap constructor)
	 * 
	 * @param	it The iterator to wrap.
	 */
	output_iterator_restrictor(iterator_type const &it) : _it(it) {}

	/**
	 * @brief	Construct a new output_iterator_restrictor object.
	 * 			Allow mutable to constant output_iterator_restrictor conversion. (copy constructor)
	 * 
	 * @tparam	_Iterator The type of the restricted iterator of the output_iterator_restrictor to copy.
	 * 
	 * @param	src The output_iterator_restrictor to copy.
	 */
	template <typename _Iterator>
	output_iterator_restrictor(output_iterator_restrictor<_Iterator> const &src) : _it(src.base()) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new iterator to the output_iterator_restrictor.
	 * 			Allow mutable to constant output_iterator_restrictor conversion. (copy assignment)
	 * 
	 * @tparam	_Iterator The type of the restricted iterator of the output_iterator_restrictor to copy.
	 * 
	 * @param	rhs The output_iterator_restrictor to copy the iterator from.
	 * 
	 * @return	A reference to the assigned output_iterator_restrictor.
	 */
	template <typename _Iterator>
	inline _self_type	&operator=(output_iterator_restrictor<_Iterator> const &rhs)
	{
		if (this != &rhs)
			this->_it = rhs.base();
		return *this;
	}

	/**
	 * @brief	Dereference the wrapped iterator.
	 * 
	 * @return 	The element pointed by the wrapped iterator.
	 */
	inline reference	operator*(void)
	{
		return *this->_it;
	}

	/**
	 * @brief	Increase the wrapped iterator value by 1. (prefix incrementation)
	 * 
	 * @return	A reference to the incremented output_iterator_restrictor.
	 */
	inline _self_type	&operator++(void)
	{
		++this->_it;
		return *this;
	}

	/**
	 * @brief	Increase the wrapped iterator value by 1. (postfix incrementation)
	 * 
	 * @return	A copy of the output_iterator_restrictor before the incrementation.
	 */
	inline _self_type	operator++(int)
	{
		return _self_type(this->_it++);
	}
};
} // namespace tester

#endif
