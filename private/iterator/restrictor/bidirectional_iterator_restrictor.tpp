/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator_restrictor.tpp              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 07:30:16 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/31 14:20:50 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_RESTRICTOR_TPP
# define BIDIRECTIONAL_ITERATOR_RESTRICTOR_TPP

# include "forward_iterator_restrictor.tpp"

namespace tester
{
/**
 * @par		This class is the implementation of the bidirectional_iterator_restrictor.
 * 			It is designed to restrict any type of iterator to the Bidirectional Iterator requirements at most.
 * 			According to the C++98 standard, a Bidirectional Iterator must conform to the following requirements:
 * 			- conform to the Forward Iterator requirements
 * 			- prefix decrementable (--it)
 * 			- postfix decrementable (it--)
 * 
 * @tparam	Iterator The type of the iterator to restrict.
 */
template <typename Iterator>
class bidirectional_iterator_restrictor : public forward_iterator_restrictor<Iterator>
{
private:
	// Member types
	typedef bidirectional_iterator_restrictor<Iterator>	_self_type;
	typedef forward_iterator_restrictor<Iterator>		_base_type;

public:
	// Member types
	typedef Iterator									iterator_type;
	typedef std::bidirectional_iterator_tag				iterator_category;

	using typename _base_type::							value_type;
	using typename _base_type::							pointer;
	using typename _base_type::							reference;
	using typename _base_type::							difference_type;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new bidirectional_iterator_restrictor object. (default constructor)
	 * 
	 * @param	it The iterator to wrap.
	 */
	bidirectional_iterator_restrictor(iterator_type const &it = iterator_type()) :
		_base_type(it) {}

	/**
	 * @brief	Construct a new bidirectional_iterator_restrictor object.
	 * 			Allow mutable to constant bidirectional_iterator_restrictor conversion. (copy constructor)
	 * 
	 * @tparam	_Iterator The type of the restricted iterator of the bidirectional_iterator_restrictor to copy.
	 * 
	 * @param	src The bidirectional_iterator_restrictor to copy.
	 */
	template <typename _Iterator>
	bidirectional_iterator_restrictor(bidirectional_iterator_restrictor<_Iterator> const &src) :
		_base_type(src) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new iterator to the bidirectional_iterator_restrictor.
	 * 			Allow mutable to constant bidirectional_iterator_restrictor conversion.
	 * 
	 * @tparam	_Iterator The type of the restricted iterator of the bidirectional_iterator_restrictor to copy.
	 * 
	 * @param	rhs The bidirectional_iterator_restrictor to copy the iterator from.
	 * 
	 * @return 	A reference to the assigned bidirectional_iterator_restrictor.
	 */
	template <typename _Iterator>
	inline _self_type	&operator=(bidirectional_iterator_restrictor<_Iterator> const &rhs)
	{
		if (this != &rhs)
			this->_it = rhs.base();
		return *this;
	}

	/**
	 * @brief	Check if two bidirectional_iterator_restrictor are equivalent.
	 * 			Allow comparison between mutable and constant bidirectional_iterator_restrictor.
	 * 
	 * @tparam	_Iterator The type of the restricted iterator of the bidirectional_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The bidirectional_iterator_restrictor to compare with.
	 * 
	 * @return 	Either true if the two bidirectional_iterator_restrictor are equivalent, or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator==(bidirectional_iterator_restrictor<_Iterator> const &rhs) const
	{
		return this->_it == rhs.base();
	}

	/**
	 * @brief	Check if two bidirectional_iterator_restrictor are different.
	 * 			Allow comparison between mutable and constant bidirectional_iterator_restrictor.
	 * 
	 * @tparam	_Iterator The type of the restricted iterator of the bidirectional_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The bidirectional_iterator_restrictor to compare with.
	 * 
	 * @return	Either true if the two bidirectional_iterator_restrictor are different, or false if not.
	 */
	template <typename _Iterator>
	inline bool	operator!=(bidirectional_iterator_restrictor<_Iterator> const &rhs) const
	{
		return this->_it != rhs.base();
	}

	/**
	 * @brief	Increment the wrapped iterator value by 1. (prefix incrementation)
	 * 
	 * @return 	A reference to the incremented bidirectional_iterator_restrictor.
	 */
	inline _self_type	&operator++(void)
	{
		++this->_it;
		return *this;
	}

	/**
	 * @brief	Increment the wrapped iterator value by 1. (postfix incrementation)
	 * 
	 * @return 	A copy of the bidirectional_iterator_restrictor before the incrementation.
	 */
	inline _self_type	operator++(int)
	{
		return _self_type(this->_it++);
	}

	/**
	 * @brief	Decrement the wrapped pointer value by 1. (prefix decrementation)
	 * 
	 * @return	A reference to the decremented bidirectional_iterator_restrictor.
	 */
	inline _self_type	&operator--(void)
	{
		--this->_it;
		return *this;
	}

	/**
	 * @brief	Decrement the wrapped pointer value by 1. (postfix decrementation)
	 * 
	 * @return	A copy of the bidirectional_iterator_restrictor before the decrementation.
	 */
	inline _self_type	operator--(int)
	{
		return _self_type(this->_it--);
	}
};
} // namespace tester

#endif
