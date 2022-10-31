/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_iterator_restrictor.tpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 06:06:43 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/31 14:37:22 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_ITERATOR_RESTRICTOR_TPP
# define INPUT_ITERATOR_RESTRICTOR_TPP

# include "_type_traits.hpp"
# include <iterator>

namespace tester
{
/**
 * @par		This class is the implementation of the input_iterator_restrictor.
 * 			It is designed to restrict any type of iterator to the Input Iterator requirements at most.
 * 			According to the C++98 standard, an Input Iterator must conform to the following requirements:
 * 			- copy constructible (it0(it1))
 * 			- copy assignable (it0 = it1)
 * 			- equivalent comparable with another iterator of the same type (it0 == it1)
 * 			- different comparable with another iterator of the same type (it0 != it1)
 * 			- dereferenceable in read mode, and in write mode if the value type is mutable (*it)
 * 			- if `(*it).m` is a valid expression, then so is `it->m` (it->m)
 * 			- prefix incrementable (++it)
 * 			- postfix incrementable (it++)
 * 
 * @tparam	Iterator The type of the iterator to restrict.
 */
template <typename Iterator>
class input_iterator_restrictor
{
private:
	// Member types
	typedef input_iterator_restrictor<Iterator>								_self_type;

public:
	// Member types
	typedef Iterator														iterator_type;
	typedef typename std::input_iterator_tag								iterator_category;

	typedef typename std::iterator_traits<iterator_type>::value_type		value_type;
	typedef typename std::iterator_traits<iterator_type>::pointer			pointer;
	typedef typename std::iterator_traits<iterator_type>::reference			reference;
	typedef typename std::iterator_traits<iterator_type>::difference_type	difference_type;

protected:
	// Attributes
	iterator_type	_it;

private:
// ****************************************************************************************************************** //
//                                              Private Member Functions                                              //
// ****************************************************************************************************************** //

	/**
	 * @return	The wrapped pointer value.
	 */
	inline pointer	_maddressDispatch(tester::true_type const) const
	{
		return this->_it;
	}

	/**
	 * @return	The wrapped pointer value.
	 */
	inline pointer	_maddressDispatch(false_type const) const
	{
		return this->_it.operator->();
	}

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new input_iterator_restrictor object from an iterator. (wrap constructor)
	 * 
	 * @param	it The iterator to wrap.
	 */
	input_iterator_restrictor(iterator_type const &it) : _it(it) {}

	/**
	 * @brief	Construct a new input_iterator_restrictor object from another one.
	 * 			Allow mutable to constant input_iterator_restrictor conversion. (copy constructor)
	 * 
	 * @tparam	_Iterator The type of the restricted iterator of the input_iterator_restrictor to copy.
	 * 
	 * @param	src The input_iterator_restrictor to copy.
	 */
	template <typename _Iterator>
	input_iterator_restrictor(input_iterator_restrictor<_Iterator> const &src) : _it(src.base()) {}

// ***************************************************************************************************************** //
//                                                     Accessors                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Return the wrapped iterator.
	 * 
	 * @return	iterator_type const & The wrapped iterator.
	 */
	iterator_type const &base() const
	{
		return this->_it;
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Check if two input_iterator_restrictor are equivalent.
	 * 			Allow comparison between mutable and constant input_iterator_restrictor.
	 * 
	 * @tparam	_Iterator The type of the restricted iterator of the input_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The input_iterator_restrictor to compare with.
	 * 
	 * @return 	Either true if the two input_iterator_restrictor are equivalent, or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator==(input_iterator_restrictor<_Iterator> const &rhs) const
	{
		return this->_it == rhs.base();
	}

	/**
	 * @brief	Check if two input_iterator_restrictor are different.
	 * 			Allow comparison between mutable and constant input_iterator_restrictor.
	 * 
	 * @tparam	_Iterator The type of the restricted iterator of the input_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The input_iterator_restrictor to compare with.
	 * 
	 * @return	Either true if the two input_iterator_restrictor are different, or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator!=(input_iterator_restrictor<_Iterator> const &rhs) const
	{
		return this->_it != rhs.base();
	}

	/**
	 * @return 	The element pointed by the wrapped iterator.
	 */
	inline reference	operator*(void) const
	{
		return *this->_it;
	}

	/**
	 * @return 	The wrapped pointer value.
	 */
	inline pointer	operator->(void) const
	{
		return this->_maddressDispatch(is_pointer<pointer>());
	}

	/**
	 * @brief	Assign a new iterator to the input_iterator_restrictor.
	 * 			Allow mutable to constant input_iterator_restrictor conversion.
	 * 
	 * @tparam	_Iterator The type of the restricted iterator of the input_iterator_restrictor to copy.
	 * 
	 * @param	rhs The input_iterator_restrictor to copy the iterator from.
	 * 
	 * @return 	A reference to the assigned input_iterator_restrictor.
	 */
	template <typename _Iterator>
	inline _self_type	&operator=(input_iterator_restrictor<_Iterator> const &rhs)
	{
		if (this != &rhs)
			this->_it = rhs.base();
		return *this;
	}

	/**
	 * @brief	Increment the wrapped iterator value by 1. (prefix incrementation)
	 * 
	 * @return 	A reference to the incremented input_iterator_restrictor.
	 */
	inline _self_type	&operator++(void)
	{
		++this->_it;
		return *this;
	}

	/**
	 * @brief	Increment the wrapped iterator value by 1. (postfix incrementation)
	 * 
	 * @return 	A copy of the input_iterator_restrictor before the incrementation.
	 */
	inline _self_type	operator++(int)
	{
		return _self_type(this->_it++);
	}
};
} // namespace tester

#endif
