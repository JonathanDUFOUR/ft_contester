/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rb_tree.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:13:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/11/13 19:07:36 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arrays.hpp"
#include "colors.hpp"
#include "iterator/requirements_check.tpp"
#include "iterator/restrictor/random_access_iterator_restrictor.tpp"
#include "rb_tree.tpp"
#include "tester.hpp"
#include "t_int.hpp"
#include "utility.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <set>

template <typename T>
inline static void	__blackSteps(
	ft::rb_node<T> const *const node,
	ft::rb_node<T> const *const nil,
	std::list<t_uint> &lst,
	t_uint const steps)
{
	if (node != nil)
		return lst.push_back(steps);
	__blackSteps(node->child[ft::RB_LEFT], nil, lst, steps + (node->color == ft::RB_BLACK));
	__blackSteps(node->child[ft::RB_RIGHT], nil, lst, steps + (node->color == ft::RB_BLACK));
}

template <typename T, typename Compare>
inline static int	__propertiesCheck(
	ft::rb_node<T> const *const node,
	ft::rb_node<T> const *const nil,
	Compare const cmp)
{
	std::list<t_uint>					lst;
	std::list<t_uint>::const_iterator	it;

	if (node == nil)
	{
		if (node->color != ft::RB_BLACK)
			return EXIT_FAILURE;
		return EXIT_SUCCESS;
	}
	// Color check
	{
		if (node->color != ft::RB_RED && node->color != ft::RB_BLACK)
			return EXIT_FAILURE;
	}
	// Order check
	{
		if ((node->child[ft::RB_LEFT] != nil && !cmp(node->child[ft::RB_LEFT]->val, node->val)) ||
			(node->child[ft::RB_RIGHT] != nil && !cmp(node->val, node->child[ft::RB_RIGHT]->val)))
			return EXIT_FAILURE;
	}
	// Red violation check
	{
		if (node->color == ft::RB_RED &&
			((node->child[ft::RB_LEFT] != nil && node->child[ft::RB_LEFT]->color == ft::RB_RED) ||
			(node->child[ft::RB_RIGHT] != nil && node->child[ft::RB_RIGHT]->color == ft::RB_RED)))
			return EXIT_FAILURE;
	}
	// Black violation check
	{
		__blackSteps(node, nil, lst, 0U);
		for (it = lst.begin() ; it != lst.end() ; ++it)
			if (*it != *lst.begin())
				return EXIT_FAILURE;
	}
	return __propertiesCheck(node->child[ft::RB_LEFT], nil, cmp) || __propertiesCheck(node->child[ft::RB_RIGHT], nil, cmp);
}

template <typename T>
inline static int	__integrityCheck(ft::rb_node<T> const *const node, ft::rb_node<T> const *const nil)
{
	if (node == nil)
		return EXIT_SUCCESS;
	if (node->child[ft::RB_LEFT] != nil && node->child[ft::RB_LEFT]->parent != node)
		return EXIT_FAILURE;
	if (node->child[ft::RB_RIGHT] != nil && node->child[ft::RB_RIGHT]->parent != node)
		return EXIT_FAILURE;
	return __integrityCheck(node->child[ft::RB_LEFT], nil) || __integrityCheck(node->child[ft::RB_RIGHT], nil);
}

inline static int	__test_constructor(void)
{
	title(__func__);
	try
	{
		// Default constructor
		{
			ft::rb_tree<int> const	tree;
		}
		// Range constructor
		{
			// Range of input_iterator_restrictor
			{
				tester::input_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				tester::input_iterator_restrictor<t_huint const *> const	it1(&g_huint[0]);
				ft::rb_tree<t_huint> const									tree(it0, it1);
			}
			// Range of forward_iterator_restrictor
			{
				tester::forward_iterator_restrictor<void *const *> const	it;
				ft::rb_tree<void *> const									tree(it, it);
			}
			// Range of random_access_iterator
			{
				tester::random_access_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				tester::random_access_iterator_restrictor<t_huint const *> const	it1(&g_huint[g_huint_size]);
				ft::rb_tree<t_huint> const											tree(it0, it1);
			}
			// Range of char const *
			{
				ft::rb_tree<char> const	tree(&g_char[0], &g_char[g_char_size]);
			}
		}
		// Copy constructor
		{
			// Default tree
			{
				ft::rb_tree<int> const	tree0;
				ft::rb_tree<int> const	tree1(tree0);
			}
			// Filled tree
			{
				ft::rb_tree<int> const	tree0(&g_int[0], &g_int[g_int_size]);
				ft::rb_tree<int> const	tree1(tree0);
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_accessor_getNil(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Empty tree
		{
			ft::rb_tree<long double> const			tree;
			ft::rb_node<long double> const *const	nil = tree.getNil();

			if (!nil || nil->color != ft::RB_BLACK || nil->parent ||
				nil->child[ft::RB_MIN] != nil ||
				nil->child[ft::RB_MAX] != nil)
				return EXIT_FAILURE;
		}
		// Non-empty tree
		{
			for (idx = 1U ; idx <= g_long_double_size ; ++idx)
			{
				ft::rb_tree<long double> const			tree(&g_long_double[0], &g_long_double[idx]);
				ft::rb_node<long double> const *const	nil = tree.getNil();

				if (!nil || nil->color != ft::RB_BLACK || nil->parent ||
					!nil->child[ft::RB_MIN] || nil->child[ft::RB_MIN] == nil ||
					!nil->child[ft::RB_MAX] || nil->child[ft::RB_MAX] == nil)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_accessor_getRoot(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Empty tree
		{
			ft::rb_tree<int> const	tree;

			if (tree.getRoot() != tree.getNil())
				return EXIT_FAILURE;
		}
		// Non-empty tree
		{
			for (idx = 1U ; idx <= g_int_size ; ++idx)
			{
				ft::rb_tree<int> const			tree(&g_int[0], &g_int[idx]);
				ft::rb_node<int> const *const	root = tree.getRoot();
				ft::rb_node<int> const *const	nil = tree.getNil();

				if (!root || root == nil || root->parent != nil ||
					std::find(&g_int[0], &g_int[idx], root->val) == &g_int[idx])
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_accessor_getSize(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Empty tree
		{
			ft::rb_tree<std::string> const	tree;

			if (tree.getSize())
				return EXIT_FAILURE;
		}
		// Non-empty tree
		{
			for (idx = 1U ; idx <= g_string_size ; ++idx)
			{
				ft::rb_tree<std::string> const	tree(&g_string[0], &g_string[idx]);

				if (tree.getSize() != idx)
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_max_size(void)
{
	title(__func__);
	try
	{
		ft::rb_tree<t_hhuint> const		tree0;
		ft::rb_tree<std::string> const	tree1;
		ft::rb_tree<long double> const	tree2;
		std::set<t_hhuint> const		ref0;
		std::set<std::string> const		ref1;
		std::set<long double> const		ref2;

		if ((tree0.max_size() < tree1.max_size()) != (ref0.max_size() < ref1.max_size()) ||
			(tree0.max_size() < tree2.max_size()) != (ref0.max_size() < ref2.max_size()) ||
			(tree1.max_size() < tree2.max_size()) != (ref1.max_size() < ref2.max_size()))
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_max(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Empty tree
		{
			ft::rb_tree<char> const	tree;

			if (tree.min() != tree.getNil())
				return EXIT_FAILURE;
		}
		// Non-empty tree
		{
			for (idx = 1U ; idx < g_char_size ; ++idx)
			{
				ft::rb_tree<char> const	tree(&g_char[0], &g_char[idx]);

				if (!tree.max() || tree.max() == tree.getNil() ||
					tree.max()->val != *std::max_element(&g_char[0], &g_char[idx]))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_min(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Empty tree
		{
			ft::rb_tree<char> const	tree;

			if (tree.min() != tree.getNil())
				return EXIT_FAILURE;
		}
		// Non-empty tree
		{
			for (idx = 1U ; idx < g_char_size ; ++idx)
			{
				ft::rb_tree<char> const	tree(&g_char[0], &g_char[idx]);

				if (!tree.min() || tree.min() == tree.getNil() ||
					tree.min()->val != *std::min_element(&g_char[0], &g_char[idx]))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_begin(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::rb_tree<t_luint>::iterator	it;

			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>	tree(&g_luint[0], &g_luint[idx]);

				it = tree.begin();
				if (it.base() != tree.min())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			ft::rb_tree<t_luint>::const_iterator	cit;

			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint> const	tree(&g_luint[0], &g_luint[idx]);

				cit = tree.begin();
				if (cit.base() != tree.min())
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_end(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>					tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::iterator const	it(--tree.end());

				if (it.base() != tree.max())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint> const					tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::const_iterator const	cit(--tree.end());

				if (cit.base() != tree.max())
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_rbegin(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>							tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::reverse_iterator const	rit(tree.rbegin());

				if (rit.base() != tree.end())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>								tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::const_reverse_iterator const	crit(tree.rbegin());

				if (crit.base() != tree.end())
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_rend(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>							tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::reverse_iterator const	rit(tree.rend());

				if (rit.base() != tree.begin())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>								tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::const_reverse_iterator const	crit(tree.rend());

				if (crit.base() != tree.begin())
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_type_iterator(void)
{
	title(__func__);
	try
	{
		ft::rb_tree<float>				tree(&g_float[0], &g_float[g_float_size]);
		ft::rb_tree<float>::iterator	it;

		it = tree.begin();
		BidirectionalIteratorCheck(it);
		*it /= 7;

		if (it != tree.begin() || it.base() != tree.min() || *it != tree.min()->val)
			return EXIT_FAILURE;

		it = --tree.end();
		BidirectionalIteratorCheck(it);
		*it /= 7;

		if (it != --tree.end() || it.base() != tree.max() || *it != tree.max()->val)
			return EXIT_FAILURE;

		it = tree.end();
		++it;
		--it;
		it--;
		it++;

		if (it != tree.end() || it.base() != tree.getNil())
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_type_const_iterator(void)
{
	title(__func__);
	try
	{
		ft::rb_tree<float> const			tree(&g_float[0], &g_float[g_float_size]);
		ft::rb_tree<float>::const_iterator	cit;

		cit = tree.begin();
		BidirectionalIteratorCheck(cit);

		if (cit != tree.begin() || cit.base() != tree.min() || *cit != tree.min()->val)
			return EXIT_FAILURE;

		cit = --tree.end();
		BidirectionalIteratorCheck(cit);

		if (cit != --tree.end() || cit.base() != tree.max() || *cit != tree.max()->val)
			return EXIT_FAILURE;

		cit = tree.end();
		++cit;
		--cit;
		cit--;
		cit++;

		if (cit != tree.end() || cit.base() != tree.getNil())
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_type_reverse_iterator(void)
{
	title(__func__);
	try
	{
		ft::rb_tree<float>						tree(&g_float[0], &g_float[g_float_size]);
		ft::rb_tree<float>::reverse_iterator	rit;

		rit = tree.rbegin();
		BidirectionalIteratorCheck(rit);

		if (rit.base() != tree.end())
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_type_const_reverse_iterator(void)
{
	title(__func__);
	try
	{
		ft::rb_tree<float> const					tree(&g_float[0], &g_float[g_float_size]);
		ft::rb_tree<float>::const_reverse_iterator	crit;

		crit = tree.rbegin();
		BidirectionalIteratorCheck(crit);

		if (crit.base() != tree.end())
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_insert(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Single insertion
		{
			ft::rb_tree<std::string>							tree;
			std::set<std::string>								ref;
			ft::pair<ft::rb_tree<std::string>::iterator, bool>	ft_ret;
			std::pair<std::set<std::string>::iterator, bool>	std_ret;

			for (idx = 0U ; idx < g_string_size * 2 ; ++idx)
			{
				ft_ret = tree.insert(g_string[idx / 2]);
				std_ret = ref.insert(g_string[idx / 2]);

				if (tree.getSize() != ref.size() ||
					*ft_ret.first != *std_ret.first || ft_ret.second != std_ret.second ||
					__integrityCheck(tree.getRoot(), tree.getNil()) ||
					__propertiesCheck(tree.getRoot(), tree.getNil(), ft::rb_tree<std::string>::compare_type()) ||
					!std::equal(tree.begin(), tree.end(), ref.begin()))
					return EXIT_FAILURE;
			}
		}
		// Single insertion with hint
		{
			ft::rb_tree<std::string>			tree;
			std::set<std::string>				ref;
			ft::rb_tree<std::string>::iterator	ft_it;
			std::set<std::string>::iterator		std_it;

			tree.insert(tree.begin().base(), std::string("dedicated to lmartin"));
			ref.insert(ref.begin(), std::string("dedicated to lmartin"));
			ft_it = tree.begin();
			std_it = ref.begin();
			for (idx = 0U ; idx < g_string_size * 3 ; ++idx)
			{
				switch (idx % 3)
				{
					case 0:
						ft_it = tree.insert(ft_it.base(), g_string[idx / 3]);
						std_it = ref.insert(std_it, g_string[idx / 3]);
						break;
				
					case 1:
						ft_it = tree.insert(tree.begin().base(), *++tree.begin());
						std_it = ref.insert(ref.begin(), *++ref.begin());
						break;

					case 2:
						ft_it = tree.insert(tree.end().base(), *++tree.rbegin());
						std_it = ref.insert(ref.end(), *++ref.rbegin());
						break;
				}

				if (*ft_it != *std_it ||
					tree.getSize() != ref.size() ||
					!std::equal(tree.begin(), tree.end(), ref.begin()))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_erase(void)
{
	t_uint idx;

	title(__func__);
	try
	{
		// Position erase
		{
			ft::rb_tree<long double>	tree(&g_long_double[0], &g_long_double[g_long_double_size]);
			std::set<long double>		ref(&g_long_double[0], &g_long_double[g_long_double_size]);

			for (idx = 0U ; idx < g_long_double_size ; ++idx)
			{
				if (idx % 2)
				{
					tree.erase(tree.begin().base());
					ref.erase(ref.begin());
				}
				else
				{
					tree.erase((--tree.end()).base());
					ref.erase(--ref.end());
				}

				if (tree.getSize() != ref.size() ||
					__integrityCheck(tree.getRoot(), tree.getNil()) ||
					__propertiesCheck(tree.getRoot(), tree.getNil(), ft::rb_tree<long double>::compare_type()) ||
					!std::equal(tree.begin(), tree.end(), ref.begin()))
					return EXIT_FAILURE;
			}
		}
		// Value erase
		{
			ft::rb_tree<char>	tree(&g_char[0], &g_char[g_char_size]);
			std::set<char>		ref(&g_char[0], &g_char[g_char_size]);
			size_t				ft_ret;
			size_t				std_ret;

			for (idx = 0U ; idx < g_char_size * 2 ; ++idx)
			{
				ft_ret = tree.erase(g_char[idx / 2]);
				std_ret = ref.erase(g_char[idx / 2]);

				if (tree.getSize() != ref.size() || ft_ret != std_ret ||
					__integrityCheck(tree.getRoot(), tree.getNil()) ||
					__propertiesCheck(tree.getRoot(), tree.getNil(), ft::rb_tree<char>::compare_type()) ||
					!std::equal(tree.begin(), tree.end(), ref.begin()))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_clear(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_char_size ; ++idx)
		{
			ft::rb_tree<char>	tree(&g_char[0], &g_char[idx]);

			tree.clear();
			if (tree.getSize() ||
				tree.max() != tree.getNil() ||
				tree.min() != tree.getNil() ||
				tree.getRoot() != tree.getNil())
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_find(void)
{
	t_uint	idx;
	t_lint	nb;

	title(__func__);
	try
	{
		ft::rb_tree<t_lint> const	tree(&g_lint[0], &g_lint[g_lint_size]);
		std::set<t_lint> const		ref(&g_lint[0], &g_lint[g_lint_size]);

		for (idx = 0U ; idx < g_lint_size * 2 ; ++idx)
		{
			if (idx % 2)
			{
				nb = rand();
				while (std::find(&g_lint[0], &g_lint[g_lint_size], nb) != &g_lint[g_lint_size])
					nb = rand();
				if (tree.find(nb) != tree.getNil())
					return EXIT_FAILURE;
			}
			else if (tree.find(g_lint[idx / 2])->val != *ref.find(g_lint[idx / 2]))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_lower_bound(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::rb_tree<t_lint>				tree(&g_lint[0], &g_lint[g_lint_size]);
			std::set<t_lint>				ref(&g_lint[0], &g_lint[g_lint_size]);
			ft::rb_tree<t_lint>::iterator	ft_it;
			std::set<t_lint>::iterator		std_it;

			for (idx = 0U ; idx < g_lint_size ; ++idx)
			{
				ft_it = tree.lower_bound(g_lint[idx]);
				std_it = ref.lower_bound(g_lint[idx]);

				if ((ft_it == tree.end()) != (std_it == ref.end()) ||
					(ft_it != tree.end() && (*ft_it != *std_it)))
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			ft::rb_tree<t_lint> const			tree(&g_lint[0], &g_lint[g_lint_size]);
			std::set<t_lint> const				ref(&g_lint[0], &g_lint[g_lint_size]);
			ft::rb_tree<t_lint>::const_iterator	ft_cit;
			std::set<t_lint>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_lint_size ; ++idx)
			{
				ft_cit = tree.lower_bound(g_lint[idx]);
				std_cit = ref.lower_bound(g_lint[idx]);

				if ((ft_cit == tree.end()) != (std_cit == ref.end()) ||
					(ft_cit != tree.end() && (*ft_cit != *std_cit)))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_upper_bound(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::rb_tree<t_lint>				tree(&g_lint[0], &g_lint[g_lint_size]);
			std::set<t_lint>				ref(&g_lint[0], &g_lint[g_lint_size]);
			ft::rb_tree<t_lint>::iterator	ft_it;
			std::set<t_lint>::iterator		std_it;

			for (idx = 0U ; idx < g_lint_size ; ++idx)
			{
				ft_it = tree.upper_bound(g_lint[idx]);
				std_it = ref.upper_bound(g_lint[idx]);


				if ((ft_it == tree.end()) != (std_it == ref.end()) ||
					(ft_it != tree.end() && (*ft_it != *std_it)))
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			ft::rb_tree<t_lint> const			tree(&g_lint[0], &g_lint[g_lint_size]);
			std::set<t_lint> const				ref(&g_lint[0], &g_lint[g_lint_size]);
			ft::rb_tree<t_lint>::const_iterator	ft_cit;
			std::set<t_lint>::const_iterator	std_cit;

			for (idx = 0U ; idx < g_lint_size ; ++idx)
			{
				ft_cit = tree.upper_bound(g_lint[idx]);
				std_cit = ref.upper_bound(g_lint[idx]);

				if ((ft_cit == tree.end()) != (std_cit == ref.end()) ||
					(ft_cit != tree.end() && (*ft_cit != *std_cit)))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_equal_range(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::rb_tree<t_hint>					tree(&g_hint[0], &g_hint[g_hint_size]);
			std::set<t_hint>					ref(&g_hint[0], &g_hint[g_hint_size]);
			ft::pair<
				ft::rb_tree<t_hint>::iterator,
				ft::rb_tree<t_hint>::iterator>	ft_ret;
			std::pair<
				std::set<t_hint>::iterator,
				std::set<t_hint>::iterator>		std_ret;

			for (idx = 0U ; idx < g_hint_size && idx < g_uint_size ; ++idx)
			{
				ft_ret = tree.equal_range(g_hint[idx]);
				std_ret = ref.equal_range(g_hint[idx]);

				if ((ft_ret.first == tree.end()) != (std_ret.first == ref.end()) ||
					(ft_ret.first != tree.end() && (
						*ft_ret.first != *std_ret.first ||
						!std::equal(ft_ret.first, ft_ret.second, std_ret.first))))
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			ft::rb_tree<t_hint> const					tree(&g_hint[0], &g_hint[g_hint_size]);
			std::set<t_hint> const						ref(&g_hint[0], &g_hint[g_hint_size]);
			ft::pair<
				ft::rb_tree<t_hint>::const_iterator,
				ft::rb_tree<t_hint>::const_iterator>	ft_ret;
			std::pair<
				std::set<t_hint>::const_iterator,
				std::set<t_hint>::const_iterator>		std_ret;

			for (idx = 0U ; idx < g_hint_size && idx < g_uint_size ; ++idx)
			{
				ft_ret = tree.equal_range(g_hint[idx]);
				std_ret = ref.equal_range(g_hint[idx]);

				if ((ft_ret.first == tree.end()) != (std_ret.first == ref.end()) ||
					(ft_ret.first != tree.end() && (
						*ft_ret.first != *std_ret.first ||
						!std::equal(ft_ret.first, ft_ret.second, std_ret.first))))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_swap(void)
{
	title(__func__);
	try
	{
		// Swapping empty | empty
		{
			ft::rb_tree<float>	tree0;
			ft::rb_tree<float>	tree1;
			std::set<float>		ref0;
			std::set<float>		ref1;

			tree0.swap(tree1);
			ref0.swap(ref1);

			if (tree0.getSize() != ref0.size() || tree1.getSize() != ref1.size() ||
				__integrityCheck(tree0.getRoot(), tree0.getNil()) ||
				__integrityCheck(tree1.getRoot(), tree1.getNil()) ||
				__propertiesCheck(tree0.getRoot(), tree0.getNil(), ft::rb_tree<float>::compare_type()) ||
				__propertiesCheck(tree1.getRoot(), tree1.getNil(), ft::rb_tree<float>::compare_type()) ||
				!std::equal(tree0.begin(), tree0.end(), ref0.begin()) ||
				!std::equal(tree1.begin(), tree1.end(), ref1.begin()))
				return EXIT_FAILURE;
		}
		// Swapping empty | non-empty
		{
			ft::rb_tree<float>	tree0;
			ft::rb_tree<float>	tree1(&g_float[g_float_size / 2], &g_float[g_float_size]);
			std::set<float>		ref0;
			std::set<float>		ref1(&g_float[g_float_size / 2], &g_float[g_float_size]);

			tree0.swap(tree1);
			ref0.swap(ref1);

			if (tree0.getSize() != ref0.size() || tree1.getSize() != ref1.size() ||
				__integrityCheck(tree0.getRoot(), tree0.getNil()) ||
				__integrityCheck(tree1.getRoot(), tree1.getNil()) ||
				__propertiesCheck(tree0.getRoot(), tree0.getNil(), ft::rb_tree<float>::compare_type()) ||
				__propertiesCheck(tree1.getRoot(), tree1.getNil(), ft::rb_tree<float>::compare_type()) ||
				!std::equal(tree0.begin(), tree0.end(), ref0.begin()) ||
				!std::equal(tree1.begin(), tree1.end(), ref1.begin()))
				return EXIT_FAILURE;
		}
		// Swapping non-empty | empty
		{
			ft::rb_tree<float>	tree0(&g_float[0], &g_float[g_float_size / 2]);
			ft::rb_tree<float>	tree1;
			std::set<float>		ref0(&g_float[0], &g_float[g_float_size / 2]);
			std::set<float>		ref1;

			tree0.swap(tree1);
			ref0.swap(ref1);

			if (tree0.getSize() != ref0.size() || tree1.getSize() != ref1.size() ||
				__integrityCheck(tree0.getRoot(), tree0.getNil()) ||
				__integrityCheck(tree1.getRoot(), tree1.getNil()) ||
				__propertiesCheck(tree0.getRoot(), tree0.getNil(), ft::rb_tree<float>::compare_type()) ||
				__propertiesCheck(tree1.getRoot(), tree1.getNil(), ft::rb_tree<float>::compare_type()) ||
				!std::equal(tree0.begin(), tree0.end(), ref0.begin()) ||
				!std::equal(tree1.begin(), tree1.end(), ref1.begin()))
				return EXIT_FAILURE;
		}
		// Swapping non-empty | non-empty
		{
			ft::rb_tree<float>	tree0(&g_float[0], &g_float[g_float_size / 2]);
			ft::rb_tree<float>	tree1(&g_float[g_float_size / 2], &g_float[g_float_size]);
			std::set<float>		ref0(&g_float[0], &g_float[g_float_size / 2]);
			std::set<float>		ref1(&g_float[g_float_size / 2], &g_float[g_float_size]);

			tree0.swap(tree1);
			ref0.swap(ref1);

			if (tree0.getSize() != ref0.size() || tree1.getSize() != ref1.size() ||
				__integrityCheck(tree0.getRoot(), tree0.getNil()) ||
				__integrityCheck(tree1.getRoot(), tree1.getNil()) ||
				__propertiesCheck(tree0.getRoot(), tree0.getNil(), ft::rb_tree<float>::compare_type()) ||
				__propertiesCheck(tree1.getRoot(), tree1.getNil(), ft::rb_tree<float>::compare_type()) ||
				!std::equal(tree0.begin(), tree0.end(), ref0.begin()) ||
				!std::equal(tree1.begin(), tree1.end(), ref1.begin()))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_assign(void)
{
	title(__func__);
	try
	{
		// Assigning empty -> empty
		{
			ft::rb_tree<std::string>		tree0;
			ft::rb_tree<std::string> const	tree1;
			std::set<std::string>			ref0;
			std::set<std::string> const		ref1;

			tree0 = tree1;
			ref0 = ref1;

			if (tree0.getSize() != ref0.size() ||
				__integrityCheck(tree0.getRoot(), tree0.getNil()) ||
				__propertiesCheck(tree0.getRoot(), tree0.getNil(), ft::rb_tree<std::string>::compare_type()) ||
				!std::equal(tree0.begin(), tree0.end(), ref0.begin()))
				return EXIT_FAILURE;
		}
		// Assigning empty -> non-empty
		{
			ft::rb_tree<std::string>		tree0(&g_string[0], &g_string[g_string_size / 2]);
			ft::rb_tree<std::string> const	tree1;
			std::set<std::string>			ref0(&g_string[0], &g_string[g_string_size / 2]);
			std::set<std::string> const		ref1;

			tree0 = tree1;
			ref0 = ref1;

			if (tree0.getSize() != ref0.size() ||
				__integrityCheck(tree0.getRoot(), tree0.getNil()) ||
				__propertiesCheck(tree0.getRoot(), tree0.getNil(), ft::rb_tree<std::string>::compare_type()) ||
				!std::equal(tree0.begin(), tree0.end(), ref0.begin()))
				return EXIT_FAILURE;
		}
		// Assigning non-empty -> empty
		{
			ft::rb_tree<std::string>		tree0;
			ft::rb_tree<std::string> const	tree1(&g_string[g_string_size / 2], &g_string[g_string_size]);
			std::set<std::string>			ref0;
			std::set<std::string> const		ref1(&g_string[g_string_size / 2], &g_string[g_string_size]);

			tree0 = tree1;
			ref0 = ref1;

			if (tree0.getSize() != ref0.size() ||
				__integrityCheck(tree0.getRoot(), tree0.getNil()) ||
				__propertiesCheck(tree0.getRoot(), tree0.getNil(), ft::rb_tree<std::string>::compare_type()) ||
				!std::equal(tree0.begin(), tree0.end(), ref0.begin()))
				return EXIT_FAILURE;
		}
		// Assigning non-empty -> non-empty
		{
			ft::rb_tree<std::string>		tree0(&g_string[0], &g_string[g_string_size / 2]);
			ft::rb_tree<std::string> const	tree1(&g_string[g_string_size / 2], &g_string[g_string_size]);
			std::set<std::string>			ref0(&g_string[0], &g_string[g_string_size / 2]);
			std::set<std::string> const		ref1(&g_string[g_string_size / 2], &g_string[g_string_size]);

			tree0 = tree1;
			ref0 = ref1;

			if (tree0.getSize() != ref0.size() ||
				__integrityCheck(tree0.getRoot(), tree0.getNil()) ||
				__propertiesCheck(tree0.getRoot(), tree0.getNil(), ft::rb_tree<std::string>::compare_type()) ||
				!std::equal(tree0.begin(), tree0.end(), ref0.begin()))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int	test_rb_tree(void)
{
	t_fct const				tests[] = {
		__test_constructor,
		__test_accessor_getNil,
		__test_accessor_getRoot,
		__test_accessor_getSize,
		__test_function_max_size,
		__test_function_max,
		__test_function_min,
		__test_function_begin,
		__test_function_end,
		__test_function_rbegin,
		__test_function_rend,
		__test_type_iterator,
		__test_type_const_iterator,
		__test_type_reverse_iterator,
		__test_type_const_reverse_iterator,
		__test_function_insert,
		__test_function_erase,
		__test_function_clear,
		__test_function_find,
		__test_function_lower_bound,
		__test_function_upper_bound,
		__test_function_equal_range,
		__test_function_swap,
		__test_operator_assign,
		NULL
	};
	t_uint					koCount;
	t_uint					idx;
	struct timespec const	delay = {SLEEP_TIME_SEC, SLEEP_TIME_NANOSEC};

	nanosleep(&delay, NULL);

	std::cerr << LIGHT_BLUE_FG;
	std::cout << "###################################################" << '\n';
	std::cout << "##                    RB_TREE                    ##" << '\n';
	std::cout << "###################################################" << '\n';
	std::cerr << RESET;

	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
	{
		nanosleep(&delay, NULL);

		switch (tests[idx]())
		{
			case EXIT_SUCCESS:
				std::cerr << GREEN_FG;
				std::cout << "[OK]";
				std::cerr << RESET;
				break;

			case EXIT_FAILURE:
				std::cerr << RED_FG;
				std::cout << "[KO]";
				std::cerr << RESET;
				++koCount;
				break;
		}
		std::cout << '\n';
	}
	std::cout << '\n';
	return koCount;
}
