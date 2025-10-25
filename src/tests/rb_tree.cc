#define DISABLE
#ifndef DISABLE

# include "colors.hh"
# include "iterator/requirements_check.hh"
# include "iterator/restrictor/random_access_iterator_restrictor.hh"
# include "red_black_tree.hh"
# include "tester.hh"
# include "types/array.hh"
# include "types/numerics.hh"
# include "utility.hh"
# include <algorithm>
# include <cstdlib>
# include <ctime>
# include <iostream>
# include <list>
# include <set>

template <typename T>
inline static void __blackSteps(
    ft::RedBlackTreeNode<T> const *const node,
    ft::RedBlackTreeNode<T> const *const nil,
    std::list<u32>                      &lst,
    u32 const                            steps
)
{
    if (node != nil) {
        return lst.push_back(steps);
    }
    __blackSteps(node->childs[ft::LCHILD], nil, lst, steps + (node->color == ft::BLACK));
    __blackSteps(node->childs[ft::RCHILD], nil, lst, steps + (node->color == ft::BLACK));
}

template <typename T, typename Compare>
inline static i32 __propertiesCheck(
    ft::RedBlackTreeNode<T> const *const node,
    ft::RedBlackTreeNode<T> const *const nil,
    Compare const                        cmp
)
{
    std::list<u32>                 lst;
    std::list<u32>::const_iterator it;

    if (node == nil) {
        if (node->color != ft::BLACK) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    // Color check
    {
        if (node->color != ft::RED && node->color != ft::BLACK) {
            return EXIT_FAILURE;
        }
    }
    // Order check
    {
        if ((node->childs[ft::LCHILD] != nil && !cmp(node->childs[ft::LCHILD]->inner, node->inner))
            || (node->childs[ft::RCHILD] != nil
                && !cmp(node->inner, node->childs[ft::RCHILD]->inner))) {
            return EXIT_FAILURE;
        }
    }
    // Red violation check
    {
        if (node->color == ft::RED
            && ((node->childs[ft::LCHILD] != nil && node->childs[ft::LCHILD]->color == ft::RED)
                || (node->childs[ft::RCHILD] != nil
                    && node->childs[ft::RCHILD]->color == ft::RED))) {
            return EXIT_FAILURE;
        }
    }
    // Black violation check
    {
        __blackSteps(node, nil, lst, 0U);
        for (it = lst.begin(); it != lst.end(); ++it) {
            if (*it != *lst.begin()) {
                return EXIT_FAILURE;
            }
        }
    }
    return __propertiesCheck(node->childs[ft::LCHILD], nil, cmp)
        || __propertiesCheck(node->childs[ft::RCHILD], nil, cmp);
}

template <typename T>
inline static i32 __integrityCheck(
    ft::RedBlackTreeNode<T> const *const node, ft::RedBlackTreeNode<T> const *const nil
)
{
    if (node == nil) {
        return EXIT_SUCCESS;
    }
    if (node->childs[ft::LCHILD] != nil && node->childs[ft::LCHILD]->parent != node) {
        return EXIT_FAILURE;
    }
    if (node->childs[ft::RCHILD] != nil && node->childs[ft::RCHILD]->parent != node) {
        return EXIT_FAILURE;
    }
    return __integrityCheck(node->childs[ft::LCHILD], nil)
        || __integrityCheck(node->childs[ft::RCHILD], nil);
}

inline static u8 __test_constructor()
{
    title(__func__);
    try {
        // Default constructor
        {
            ft::rb_tree<i32> const tree;
        }
        // Range constructor
        {
            // Range of input_iterator_restrictor
            {
                tester::input_iterator_restrictor<u16 const *> const it0(&Array<u16>::at(0));
                tester::input_iterator_restrictor<u16 const *> const it1(&Array<u16>::at(0));
                ft::rb_tree<u16> const                               tree(it0, it1);
            }
            // Range of forward_iterator_restrictor
            {
                tester::forward_iterator_restrictor<void *const *> const it;
                ft::rb_tree<void *> const                                tree(it, it);
            }
            // Range of random_access_iterator
            {
                tester::random_access_iterator_restrictor<u16 const *> const it0(
                    &Array<u16>::at(0)
                );
                tester::random_access_iterator_restrictor<u16 const *> const it1(
                    &Array<u16>::at(Array<u16>::len)
                );
                ft::rb_tree<u16> const tree(it0, it1);
            }
            // Range of char const *
            {
                ft::rb_tree<char> const tree(
                    &Array<char>::at(0), &Array<char>::at(Array<char>::len)
                );
            }
        }
        // Copy constructor
        {
            // Default tree
            {
                ft::rb_tree<i32> const tree0;
                ft::rb_tree<i32> const tree1(tree0);
            }
            // Filled tree
            {
                ft::rb_tree<i32> const tree0(&Array<i32>::at(0), &Array<i32>::at(Array<i32>::len));
                ft::rb_tree<i32> const tree1(tree0);
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_accessor_getNil()
{
    u32 idx;

    title(__func__);
    try {
        // Empty tree
        {
            ft::rb_tree<f128> const                 tree;
            ft::RedBlackTreeNode<f128> const *const nil = tree.getNil();

            if (!nil
                || nil->color != ft::BLACK
                || nil->parent
                || nil->childs[ft::LCHILD] != nil
                || nil->childs[ft::RCHILD] != nil) {
                return EXIT_FAILURE;
            }
        }
        // Non-empty tree
        {
            for (idx = 1U; idx <= Array<f128>::len; ++idx) {
                ft::rb_tree<f128> const tree(&Array<f128>::at(0), &Array<f128>::at(idx));
                ft::RedBlackTreeNode<f128> const *const nil = tree.getNil();

                if (!nil
                    || nil->color != ft::BLACK
                    || nil->parent
                    || !nil->childs[ft::LCHILD]
                    || nil->childs[ft::RB_MIN] == nil
                    || !nil->childs[ft::RCHILD]
                    || nil->childs[ft::RB_MAX] == nil) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_accessor_getRoot()
{
    u32 idx;

    title(__func__);
    try {
        // Empty tree
        {
            ft::rb_tree<i32> const tree;

            if (tree.getRoot() != tree.getNil()) {
                return EXIT_FAILURE;
            }
        }
        // Non-empty tree
        {
            for (idx = 1U; idx <= Array<i32>::len; ++idx) {
                ft::rb_tree<i32> const tree(&Array<i32>::at(0), &Array<i32>::at(idx));
                ft::RedBlackTreeNode<i32> const *const root = tree.getRoot();
                ft::RedBlackTreeNode<i32> const *const nil  = tree.getNil();

                if (!root
                    || root == nil
                    || root->parent != nil
                    || std::find(&Array<i32>::at(0), &Array<i32>::at(idx), root->inner)
                           == &Array<i32>::at(idx)) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_accessor_getSize()
{
    u32 idx;

    title(__func__);
    try {
        // Empty tree
        {
            ft::rb_tree<std::string> const tree;

            if (tree.getSize()) {
                return EXIT_FAILURE;
            }
        }
        // Non-empty tree
        {
            for (idx = 1U; idx <= Array<std::string>::len; ++idx) {
                ft::rb_tree<std::string> const tree(
                    &Array<std::string>::at(0), &Array<std::string>::at(idx)
                );

                if (tree.getSize() != idx) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_max_size()
{
    title(__func__);
    try {
        ft::rb_tree<u8> const          tree0;
        ft::rb_tree<std::string> const tree1;
        ft::rb_tree<f128> const        tree2;
        std::set<u8> const             ref0;
        std::set<std::string> const    ref1;
        std::set<f128> const           ref2;

        if ((tree0.max_size() < tree1.max_size()) != (ref0.max_size() < ref1.max_size())
            || (tree0.max_size() < tree2.max_size()) != (ref0.max_size() < ref2.max_size())
            || (tree1.max_size() < tree2.max_size()) != (ref1.max_size() < ref2.max_size())) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_max()
{
    u32 idx;

    title(__func__);
    try {
        // Empty tree
        {
            ft::rb_tree<char> const tree;

            if (tree.min() != tree.getNil()) {
                return EXIT_FAILURE;
            }
        }
        // Non-empty tree
        {
            for (idx = 1U; idx < Array<char>::len; ++idx) {
                ft::rb_tree<char> const tree(&Array<char>::at(0), &Array<char>::at(idx));

                if (!tree.max()
                    || tree.max() == tree.getNil()
                    || tree.max()->inner
                           != *std::max_element(&Array<char>::at(0), &Array<char>::at(idx))) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_min()
{
    u32 idx;

    title(__func__);
    try {
        // Empty tree
        {
            ft::rb_tree<char> const tree;

            if (tree.min() != tree.getNil()) {
                return EXIT_FAILURE;
            }
        }
        // Non-empty tree
        {
            for (idx = 1U; idx < Array<char>::len; ++idx) {
                ft::rb_tree<char> const tree(&Array<char>::at(0), &Array<char>::at(idx));

                if (!tree.min()
                    || tree.min() == tree.getNil()
                    || tree.min()->inner
                           != *std::min_element(&Array<char>::at(0), &Array<char>::at(idx))) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_begin()
{
    u32 idx;

    title(__func__);
    try {
        // Mutable access
        {
            ft::rb_tree<u64>::iterator it;

            for (idx = 0U; idx <= Array<u64>::len; ++idx) {
                ft::rb_tree<u64> tree(&Array<u64>::at(0), &Array<u64>::at(idx));

                it = tree.begin();
                if (it.base() != tree.min()) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Constant access
        {
            ft::rb_tree<u64>::const_iterator cit;

            for (idx = 0U; idx <= Array<u64>::len; ++idx) {
                ft::rb_tree<u64> const tree(&Array<u64>::at(0), &Array<u64>::at(idx));

                cit = tree.begin();
                if (cit.base() != tree.min()) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_end()
{
    u32 idx;

    title(__func__);
    try {
        // Mutable access
        {
            for (idx = 0U; idx <= Array<u64>::len; ++idx) {
                ft::rb_tree<u64>                 tree(&Array<u64>::at(0), &Array<u64>::at(idx));
                ft::rb_tree<u64>::iterator const it(--tree.end());

                if (it.base() != tree.max()) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Constant access
        {
            for (idx = 0U; idx <= Array<u64>::len; ++idx) {
                ft::rb_tree<u64> const tree(&Array<u64>::at(0), &Array<u64>::at(idx));
                ft::rb_tree<u64>::const_iterator const cit(--tree.end());

                if (cit.base() != tree.max()) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_rbegin()
{
    u32 idx;

    title(__func__);
    try {
        // Mutable access
        {
            for (idx = 0U; idx <= Array<u64>::len; ++idx) {
                ft::rb_tree<u64> tree(&Array<u64>::at(0), &Array<u64>::at(idx));
                ft::rb_tree<u64>::reverse_iterator const rit(tree.rbegin());

                if (rit.base() != tree.end()) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Constant access
        {
            for (idx = 0U; idx <= Array<u64>::len; ++idx) {
                ft::rb_tree<u64> tree(&Array<u64>::at(0), &Array<u64>::at(idx));
                ft::rb_tree<u64>::const_reverse_iterator const crit(tree.rbegin());

                if (crit.base() != tree.end()) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_rend()
{
    u32 idx;

    title(__func__);
    try {
        // Mutable access
        {
            for (idx = 0U; idx <= Array<u64>::len; ++idx) {
                ft::rb_tree<u64> tree(&Array<u64>::at(0), &Array<u64>::at(idx));
                ft::rb_tree<u64>::reverse_iterator const rit(tree.rend());

                if (rit.base() != tree.begin()) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Constant access
        {
            for (idx = 0U; idx <= Array<u64>::len; ++idx) {
                ft::rb_tree<u64> tree(&Array<u64>::at(0), &Array<u64>::at(idx));
                ft::rb_tree<u64>::const_reverse_iterator const crit(tree.rend());

                if (crit.base() != tree.begin()) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_type_iterator()
{
    title(__func__);
    try {
        ft::rb_tree<f32>           tree(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len));
        ft::rb_tree<f32>::iterator it;

        it = tree.begin();
        BidirectionalIteratorCheck(it);
        *it /= 7;

        if (it != tree.begin() || it.base() != tree.min() || *it != tree.min()->inner) {
            return EXIT_FAILURE;
        }

        it = --tree.end();
        BidirectionalIteratorCheck(it);
        *it /= 7;

        if (it != --tree.end() || it.base() != tree.max() || *it != tree.max()->inner) {
            return EXIT_FAILURE;
        }

        it = tree.end();
        ++it;
        --it;
        it--;
        it++;

        if (it != tree.end() || it.base() != tree.getNil()) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_type_const_iterator()
{
    title(__func__);
    try {
        ft::rb_tree<f32> const           tree(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len));
        ft::rb_tree<f32>::const_iterator cit;

        cit = tree.begin();
        BidirectionalIteratorCheck(cit);

        if (cit != tree.begin() || cit.base() != tree.min() || *cit != tree.min()->inner) {
            return EXIT_FAILURE;
        }

        cit = --tree.end();
        BidirectionalIteratorCheck(cit);

        if (cit != --tree.end() || cit.base() != tree.max() || *cit != tree.max()->inner) {
            return EXIT_FAILURE;
        }

        cit = tree.end();
        ++cit;
        --cit;
        cit--;
        cit++;

        if (cit != tree.end() || cit.base() != tree.getNil()) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_type_reverse_iterator()
{
    title(__func__);
    try {
        ft::rb_tree<f32> tree(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len));
        ft::rb_tree<f32>::reverse_iterator rit;

        rit = tree.rbegin();
        BidirectionalIteratorCheck(rit);

        if (rit.base() != tree.end()) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_type_const_reverse_iterator()
{
    title(__func__);
    try {
        ft::rb_tree<f32> const tree(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len));
        ft::rb_tree<f32>::const_reverse_iterator crit;

        crit = tree.rbegin();
        BidirectionalIteratorCheck(crit);

        if (crit.base() != tree.end()) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_insert()
{
    u32 idx;

    title(__func__);
    try {
        // Single insertion
        {
            ft::rb_tree<std::string>                           tree;
            std::set<std::string>                              ref;
            ft::Pair<ft::rb_tree<std::string>::iterator, bool> ft_ret;
            std::pair<std::set<std::string>::iterator, bool>   std_ret;

            for (idx = 0U; idx < Array<std::string>::len * 2; ++idx) {
                ft_ret  = tree.insert(Array<std::string>::at(idx / 2));
                std_ret = ref.insert(Array<std::string>::at(idx / 2));

                if (tree.getSize() != ref.size()
                    || *ft_ret.first != *std_ret.first
                    || ft_ret.second != std_ret.second
                    || __integrityCheck(tree.getRoot(), tree.getNil())
                    || __propertiesCheck(
                        tree.getRoot(), tree.getNil(), ft::rb_tree<std::string>::compare_type()
                    )
                    || !std::equal(tree.begin(), tree.end(), ref.begin())) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Single insertion with hint
        {
            ft::rb_tree<std::string>           tree;
            std::set<std::string>              ref;
            ft::rb_tree<std::string>::iterator ft_it;
            std::set<std::string>::iterator    std_it;

            tree.insert(tree.begin().base(), std::string("dedicated to lmartin"));
            ref.insert(ref.begin(), std::string("dedicated to lmartin"));
            ft_it  = tree.begin();
            std_it = ref.begin();
            for (idx = 0U; idx < Array<std::string>::len * 3; ++idx) {
                switch (idx % 3) {
                case 0:
                    ft_it  = tree.insert(ft_it.base(), Array<std::string>::at(idx / 3));
                    std_it = ref.insert(std_it, Array<std::string>::at(idx / 3));
                    break;

                case 1:
                    ft_it  = tree.insert(tree.begin().base(), *++tree.begin());
                    std_it = ref.insert(ref.begin(), *++ref.begin());
                    break;

                case 2:
                    ft_it  = tree.insert(tree.end().base(), *++tree.rbegin());
                    std_it = ref.insert(ref.end(), *++ref.rbegin());
                    break;
                }

                if (*ft_it != *std_it
                    || tree.getSize() != ref.size()
                    || !std::equal(tree.begin(), tree.end(), ref.begin())) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_erase()
{
    u32 idx;

    title(__func__);
    try {
        // Position erase
        {
            ft::rb_tree<f128> tree(&Array<f128>::at(0), &Array<f128>::at(Array<f128>::len));
            std::set<f128>    ref(&Array<f128>::at(0), &Array<f128>::at(Array<f128>::len));

            for (idx = 0U; idx < Array<f128>::len; ++idx) {
                if (idx % 2) {
                    tree.erase(tree.begin().base());
                    ref.erase(ref.begin());
                }
                else {
                    tree.erase((--tree.end()).base());
                    ref.erase(--ref.end());
                }

                if (tree.getSize() != ref.size()
                    || __integrityCheck(tree.getRoot(), tree.getNil())
                    || __propertiesCheck(
                        tree.getRoot(), tree.getNil(), ft::rb_tree<f128>::compare_type()
                    )
                    || !std::equal(tree.begin(), tree.end(), ref.begin())) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Value erase
        {
            ft::rb_tree<char> tree(&Array<char>::at(0), &Array<char>::at(Array<char>::len));
            std::set<char>    ref(&Array<char>::at(0), &Array<char>::at(Array<char>::len));
            size_t            ft_ret;
            size_t            std_ret;

            for (idx = 0U; idx < Array<char>::len * 2; ++idx) {
                ft_ret  = tree.erase(Array<char>::at(idx / 2));
                std_ret = ref.erase(Array<char>::at(idx / 2));

                if (tree.getSize() != ref.size()
                    || ft_ret != std_ret
                    || __integrityCheck(tree.getRoot(), tree.getNil())
                    || __propertiesCheck(
                        tree.getRoot(), tree.getNil(), ft::rb_tree<char>::compare_type()
                    )
                    || !std::equal(tree.begin(), tree.end(), ref.begin())) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_clear()
{
    u32 idx;

    title(__func__);
    try {
        for (idx = 0U; idx < Array<char>::len; ++idx) {
            ft::rb_tree<char> tree(&Array<char>::at(0), &Array<char>::at(idx));

            tree.clear();
            if (tree.getSize()
                || tree.max() != tree.getNil()
                || tree.min() != tree.getNil()
                || tree.getRoot() != tree.getNil()) {
                return EXIT_FAILURE;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_find()
{
    u32 idx;
    i64 nb;

    title(__func__);
    try {
        ft::rb_tree<i64> const tree(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
        std::set<i64> const    ref(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));

        for (idx = 0U; idx < Array<i64>::len * 2; ++idx) {
            if (idx % 2) {
                nb = rand();
                while (std::find(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len), nb)
                       != &Array<i64>::at(Array<i64>::len)) {
                    nb = rand();
                }
                if (tree.find(nb) != tree.getNil()) {
                    return EXIT_FAILURE;
                }
            }
            else if (tree.find(Array<i64>::at(idx / 2))->inner
                     != *ref.find(Array<i64>::at(idx / 2))) {
                return EXIT_FAILURE;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_lower_bound()
{
    u32 idx;

    title(__func__);
    try {
        // Mutable access
        {
            ft::rb_tree<i64>           tree(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
            std::set<i64>              ref(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
            ft::rb_tree<i64>::iterator ft_it;
            std::set<i64>::iterator    std_it;

            for (idx = 0U; idx < Array<i64>::len; ++idx) {
                ft_it  = tree.lower_bound(Array<i64>::at(idx));
                std_it = ref.lower_bound(Array<i64>::at(idx));

                if ((ft_it == tree.end()) != (std_it == ref.end())
                    || (ft_it != tree.end() && (*ft_it != *std_it))) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Constant access
        {
            ft::rb_tree<i64> const tree(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
            std::set<i64> const    ref(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
            ft::rb_tree<i64>::const_iterator ft_cit;
            std::set<i64>::const_iterator    std_cit;

            for (idx = 0U; idx < Array<i64>::len; ++idx) {
                ft_cit  = tree.lower_bound(Array<i64>::at(idx));
                std_cit = ref.lower_bound(Array<i64>::at(idx));

                if ((ft_cit == tree.end()) != (std_cit == ref.end())
                    || (ft_cit != tree.end() && (*ft_cit != *std_cit))) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_upper_bound()
{
    u32 idx;

    title(__func__);
    try {
        // Mutable access
        {
            ft::rb_tree<i64>           tree(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
            std::set<i64>              ref(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
            ft::rb_tree<i64>::iterator ft_it;
            std::set<i64>::iterator    std_it;

            for (idx = 0U; idx < Array<i64>::len; ++idx) {
                ft_it  = tree.upper_bound(Array<i64>::at(idx));
                std_it = ref.upper_bound(Array<i64>::at(idx));

                if ((ft_it == tree.end()) != (std_it == ref.end())
                    || (ft_it != tree.end() && (*ft_it != *std_it))) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Constant access
        {
            ft::rb_tree<i64> const tree(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
            std::set<i64> const    ref(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
            ft::rb_tree<i64>::const_iterator ft_cit;
            std::set<i64>::const_iterator    std_cit;

            for (idx = 0U; idx < Array<i64>::len; ++idx) {
                ft_cit  = tree.upper_bound(Array<i64>::at(idx));
                std_cit = ref.upper_bound(Array<i64>::at(idx));

                if ((ft_cit == tree.end()) != (std_cit == ref.end())
                    || (ft_cit != tree.end() && (*ft_cit != *std_cit))) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_equal_range()
{
    u32 idx;

    title(__func__);
    try {
        // Mutable access
        {
            ft::rb_tree<i16> tree(&Array<i16>::at(0), &Array<i16>::at(Array<i16>::len));
            std::set<i16>    ref(&Array<i16>::at(0), &Array<i16>::at(Array<i16>::len));
            ft::Pair<ft::rb_tree<i16>::iterator, ft::rb_tree<i16>::iterator> ft_ret;
            std::pair<std::set<i16>::iterator, std::set<i16>::iterator>      std_ret;

            for (idx = 0U; idx < Array<i16>::len && idx < Array<u32>::len; ++idx) {
                ft_ret  = tree.equal_range(Array<i16>::at(idx));
                std_ret = ref.equal_range(Array<i16>::at(idx));

                if ((ft_ret.first == tree.end()) != (std_ret.first == ref.end())
                    || (ft_ret.first != tree.end()
                        && (*ft_ret.first != *std_ret.first
                            || !std::equal(ft_ret.first, ft_ret.second, std_ret.first)))) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Constant access
        {
            ft::rb_tree<i16> const tree(&Array<i16>::at(0), &Array<i16>::at(Array<i16>::len));
            std::set<i16> const    ref(&Array<i16>::at(0), &Array<i16>::at(Array<i16>::len));
            ft::Pair<ft::rb_tree<i16>::const_iterator, ft::rb_tree<i16>::const_iterator> ft_ret;
            std::pair<std::set<i16>::const_iterator, std::set<i16>::const_iterator>      std_ret;

            for (idx = 0U; idx < Array<i16>::len && idx < Array<u32>::len; ++idx) {
                ft_ret  = tree.equal_range(Array<i16>::at(idx));
                std_ret = ref.equal_range(Array<i16>::at(idx));

                if ((ft_ret.first == tree.end()) != (std_ret.first == ref.end())
                    || (ft_ret.first != tree.end()
                        && (*ft_ret.first != *std_ret.first
                            || !std::equal(ft_ret.first, ft_ret.second, std_ret.first)))) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_function_swap()
{
    title(__func__);
    try {
        // Swapping empty | empty
        {
            ft::rb_tree<f32> tree0;
            ft::rb_tree<f32> tree1;
            std::set<f32>    ref0;
            std::set<f32>    ref1;

            tree0.swap(tree1);
            ref0.swap(ref1);

            if (tree0.getSize() != ref0.size()
                || tree1.getSize() != ref1.size()
                || __integrityCheck(tree0.getRoot(), tree0.getNil())
                || __integrityCheck(tree1.getRoot(), tree1.getNil())
                || __propertiesCheck(
                    tree0.getRoot(), tree0.getNil(), ft::rb_tree<f32>::compare_type()
                )
                || __propertiesCheck(
                    tree1.getRoot(), tree1.getNil(), ft::rb_tree<f32>::compare_type()
                )
                || !std::equal(tree0.begin(), tree0.end(), ref0.begin())
                || !std::equal(tree1.begin(), tree1.end(), ref1.begin())) {
                return EXIT_FAILURE;
            }
        }
        // Swapping empty | non-empty
        {
            ft::rb_tree<f32> tree0;
            ft::rb_tree<f32> tree1(
                &Array<f32>::at(Array<f32>::len / 2), &Array<f32>::at(Array<f32>::len)
            );
            std::set<f32> ref0;
            std::set<f32> ref1(
                &Array<f32>::at(Array<f32>::len / 2), &Array<f32>::at(Array<f32>::len)
            );

            tree0.swap(tree1);
            ref0.swap(ref1);

            if (tree0.getSize() != ref0.size()
                || tree1.getSize() != ref1.size()
                || __integrityCheck(tree0.getRoot(), tree0.getNil())
                || __integrityCheck(tree1.getRoot(), tree1.getNil())
                || __propertiesCheck(
                    tree0.getRoot(), tree0.getNil(), ft::rb_tree<f32>::compare_type()
                )
                || __propertiesCheck(
                    tree1.getRoot(), tree1.getNil(), ft::rb_tree<f32>::compare_type()
                )
                || !std::equal(tree0.begin(), tree0.end(), ref0.begin())
                || !std::equal(tree1.begin(), tree1.end(), ref1.begin())) {
                return EXIT_FAILURE;
            }
        }
        // Swapping non-empty | empty
        {
            ft::rb_tree<f32> tree0(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len / 2));
            ft::rb_tree<f32> tree1;
            std::set<f32>    ref0(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len / 2));
            std::set<f32>    ref1;

            tree0.swap(tree1);
            ref0.swap(ref1);

            if (tree0.getSize() != ref0.size()
                || tree1.getSize() != ref1.size()
                || __integrityCheck(tree0.getRoot(), tree0.getNil())
                || __integrityCheck(tree1.getRoot(), tree1.getNil())
                || __propertiesCheck(
                    tree0.getRoot(), tree0.getNil(), ft::rb_tree<f32>::compare_type()
                )
                || __propertiesCheck(
                    tree1.getRoot(), tree1.getNil(), ft::rb_tree<f32>::compare_type()
                )
                || !std::equal(tree0.begin(), tree0.end(), ref0.begin())
                || !std::equal(tree1.begin(), tree1.end(), ref1.begin())) {
                return EXIT_FAILURE;
            }
        }
        // Swapping non-empty | non-empty
        {
            ft::rb_tree<f32> tree0(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len / 2));
            ft::rb_tree<f32> tree1(
                &Array<f32>::at(Array<f32>::len / 2), &Array<f32>::at(Array<f32>::len)
            );
            std::set<f32> ref0(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len / 2));
            std::set<f32> ref1(
                &Array<f32>::at(Array<f32>::len / 2), &Array<f32>::at(Array<f32>::len)
            );

            tree0.swap(tree1);
            ref0.swap(ref1);

            if (tree0.getSize() != ref0.size()
                || tree1.getSize() != ref1.size()
                || __integrityCheck(tree0.getRoot(), tree0.getNil())
                || __integrityCheck(tree1.getRoot(), tree1.getNil())
                || __propertiesCheck(
                    tree0.getRoot(), tree0.getNil(), ft::rb_tree<f32>::compare_type()
                )
                || __propertiesCheck(
                    tree1.getRoot(), tree1.getNil(), ft::rb_tree<f32>::compare_type()
                )
                || !std::equal(tree0.begin(), tree0.end(), ref0.begin())
                || !std::equal(tree1.begin(), tree1.end(), ref1.begin())) {
                return EXIT_FAILURE;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_operator_assign()
{
    title(__func__);
    try {
        // Assigning empty -> empty
        {
            ft::rb_tree<std::string>       tree0;
            ft::rb_tree<std::string> const tree1;
            std::set<std::string>          ref0;
            std::set<std::string> const    ref1;

            tree0 = tree1;
            ref0  = ref1;

            if (tree0.getSize() != ref0.size()
                || __integrityCheck(tree0.getRoot(), tree0.getNil())
                || __propertiesCheck(
                    tree0.getRoot(), tree0.getNil(), ft::rb_tree<std::string>::compare_type()
                )
                || !std::equal(tree0.begin(), tree0.end(), ref0.begin())) {
                return EXIT_FAILURE;
            }
        }
        // Assigning empty -> non-empty
        {
            ft::rb_tree<std::string> tree0(
                &Array<std::string>::at(0), &Array<std::string>::at(Array<std::string>::len / 2)
            );
            ft::rb_tree<std::string> const tree1;
            std::set<std::string>          ref0(
                &Array<std::string>::at(0), &Array<std::string>::at(Array<std::string>::len / 2)
            );
            std::set<std::string> const ref1;

            tree0 = tree1;
            ref0  = ref1;

            if (tree0.getSize() != ref0.size()
                || __integrityCheck(tree0.getRoot(), tree0.getNil())
                || __propertiesCheck(
                    tree0.getRoot(), tree0.getNil(), ft::rb_tree<std::string>::compare_type()
                )
                || !std::equal(tree0.begin(), tree0.end(), ref0.begin())) {
                return EXIT_FAILURE;
            }
        }
        // Assigning non-empty -> empty
        {
            ft::rb_tree<std::string>       tree0;
            ft::rb_tree<std::string> const tree1(
                &Array<std::string>::at(Array<std::string>::len / 2),
                &Array<std::string>::at(Array<std::string>::len)
            );
            std::set<std::string>       ref0;
            std::set<std::string> const ref1(
                &Array<std::string>::at(Array<std::string>::len / 2),
                &Array<std::string>::at(Array<std::string>::len)
            );

            tree0 = tree1;
            ref0  = ref1;

            if (tree0.getSize() != ref0.size()
                || __integrityCheck(tree0.getRoot(), tree0.getNil())
                || __propertiesCheck(
                    tree0.getRoot(), tree0.getNil(), ft::rb_tree<std::string>::compare_type()
                )
                || !std::equal(tree0.begin(), tree0.end(), ref0.begin())) {
                return EXIT_FAILURE;
            }
        }
        // Assigning non-empty -> non-empty
        {
            ft::rb_tree<std::string> tree0(
                &Array<std::string>::at(0), &Array<std::string>::at(Array<std::string>::len / 2)
            );
            ft::rb_tree<std::string> const tree1(
                &Array<std::string>::at(Array<std::string>::len / 2),
                &Array<std::string>::at(Array<std::string>::len)
            );
            std::set<std::string> ref0(
                &Array<std::string>::at(0), &Array<std::string>::at(Array<std::string>::len / 2)
            );
            std::set<std::string> const ref1(
                &Array<std::string>::at(Array<std::string>::len / 2),
                &Array<std::string>::at(Array<std::string>::len)
            );

            tree0 = tree1;
            ref0  = ref1;

            if (tree0.getSize() != ref0.size()
                || __integrityCheck(tree0.getRoot(), tree0.getNil())
                || __propertiesCheck(
                    tree0.getRoot(), tree0.getNil(), ft::rb_tree<std::string>::compare_type()
                )
                || !std::equal(tree0.begin(), tree0.end(), ref0.begin())) {
                return EXIT_FAILURE;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

u8 test_rb_tree()
{
    TestFn const tests[] = {
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
    u32                   koCount;
    u32                   idx;
    struct timespec const delay = {SLEEP_TIME_SEC, SLEEP_TIME_NANOSEC};

    nanosleep(&delay, NULL);

    std::cerr << LIGHT_BLUE_FG;
    std::cout << "###################################################" << '\n';
    std::cout << "##                    RB_TREE                    ##" << '\n';
    std::cout << "###################################################" << '\n';
    std::cerr << RESET;

    for (koCount = 0U, idx = 0U; tests[idx]; ++idx) {
        nanosleep(&delay, NULL);

        switch (tests[idx]()) {
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

#endif
