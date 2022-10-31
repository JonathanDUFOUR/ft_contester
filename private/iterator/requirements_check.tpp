/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requirements_check.tpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:10:52 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/31 14:33:02 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUIREMENTS_CHECK_TPP
# define REQUIREMENTS_CHECK_TPP

/**
 * @brief	Apply several assignation and move tests to an input iterator.
 * 			Leave the given iterator in the same state as it was before the test.
 * 
 * @tparam	InputIterator The type of the input iterator to test.
 * 			(it must conform to the standard input iterator requirements)
 * 
 * @param	it The input iterator to test.
 */
template <typename InputIterator>
void	InputIteratorCheck(InputIterator &it)
{
	InputIterator const	it0(it);
	InputIterator const	it1(it++);
	InputIterator const	it2(++it);
	InputIterator		it3(it);
	bool				cmp;

	cmp = (it0 == it1 && *it0 == *it1);
	cmp = (it0 != it1 && *it0 != *it1);
	it = (it3 = it0);

	(void)it0;
	(void)it1;
	(void)it2;
	(void)cmp;
}

/**
 * @brief	Apply several assignation and move tests to an output iterator.
 * 			Leave the given iterator in the same state as it was before the test.
 * 
 * @tparam	OutputIterator The type of the output iterator to test.
 * 			(it must conform to the standard output iterator requirements)
 * 
 * @param	it The output iterator to test.
 */
template<typename OutputIterator>
void	OutputIteratorCheck(OutputIterator &it)
{
	OutputIterator const	it0(it);
	OutputIterator const	it1(it++);
	OutputIterator const	it2(++it);

	it = (it1 = it0);
	*it = *it0;

	(void)it0;
	(void)it1;
	(void)it2;
}

/**
 * @brief	Apply several assignation and move tests to a forward iterator.
 * 			Leave the given iterator in the same state as it was before the test.
 * 
 * @tparam	ForwardIterator The type of the forward iterator to test.
 * 			(it must conform to the standard forward iterator requirements)
 * 
 * @param	it The forward iterator to test.
 */
template<typename ForwardIterator>
void	ForwardIteratorCheck(ForwardIterator &it)
{
	ForwardIterator const	it0;

	InputIteratorCheck(it);

	(void)it0;
}

/**
 * @brief	Apply several assignation and move tests to a bidirectional iterator.
 * 			Leave the given iterator in the same state as it was before the test.
 * 
 * @tparam	BidirectionalIterator The type of the bidirectional iterator to test.
 * 			(it must conform to the standard bidirectional iterator requirements)
 * 
 * @param	it The bidirectional iterator to test.
 */
template <typename BidirectionalIterator>
void	BidirectionalIteratorCheck(BidirectionalIterator &it)
{
	BidirectionalIterator const	it0(it);
	BidirectionalIterator const	it1(it--++);
	BidirectionalIterator const	it2(--it++);

	ForwardIteratorCheck(it);

	(void)it0;
	(void)it1;
	(void)it2;
}

/**
 * @brief	Apply several assignation and move tests to a random access iterator.
 * 			Leave the given iterator in the same state as it was before the test.
 * 
 * @tparam	RandomAccessIterator The type of the random access iterator to test.
 * 			(it must conform to the standard random access iterator requirements)
 * 
 * @param	it The random access iterator to test.
 */
template <typename RandomAccessIterator>
void	RandomAccessIteratorCheck(RandomAccessIterator &it)
{
	RandomAccessIterator const	it0(it);
	RandomAccessIterator const	it1(it += 2);
	RandomAccessIterator const	it2(it -= 2);
	RandomAccessIterator const	it3(it + 3);
	RandomAccessIterator const	it4(it - 3);
	RandomAccessIterator const	it5(4 + it);
	std::ptrdiff_t				dist;
	bool						cmp;

	dist = (it0 - it5);
	cmp = (it0 < it1);
	cmp = (it0 > it1);
	cmp = (it0 <= it1);
	cmp = (it0 >= it1);
	cmp = (it[0] == it0[0]);

	BidirectionalIteratorCheck(it);

	(void)it0;
	(void)it1;
	(void)it2;
	(void)it3;
	(void)it4;
	(void)it5;
	(void)dist;
	(void)cmp;
}

#endif
