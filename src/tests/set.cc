#define DISABLE
#ifndef DISABLE

# include "set.hpp" // ft::set
# include "type/array.hh" // tester::array
# include "type/range.hh" // tester::range
# include "type/test/benchmark/ratio_multiset.hh" // tester::test::benchmark::t_ratio_multiset_mut
# include "type/test/status.hh" // tester::test::t_status
# include <ctime> // {clock,time}_t,clock
# include <exception> // std::exception
# include <functional> // std::{{,not_}equal_to,greater{,_equal},less{,_equal}}
# include <iostream> // std::c{err,out}
# include <set> // std::set

namespace tester { namespace test {

using benchmark::t_ratio_multiset_mut;
using std::cerr;
using std::cout;
using std::equal_to;
using std::exception;
using std::greater;
using std::greater_equal;
using std::less;
using std::less_equal;
using std::not_equal_to;

namespace constructor {

template <typename Set>
inline static Set test_variant(
    time_t &duration
)
{
    clock_t const start = clock();
    Set const     ret;

    duration  = clock() - start;
    duration += !duration;
    return ret;
}

template <typename Set>
inline static Set test_variant(
    time_t &duration, Set const &other
)
{
    clock_t const start = clock();
    Set const     ret(other);

    duration  = clock() - start;
    duration += !duration;
    return ret;
}

template <typename Set, typename Compare>
inline static Set test_variant(
    time_t &duration, Compare const &cmp
)
{
    clock_t const start = clock();
    Set const     ret(cmp);

    duration  = clock() - start;
    duration += !duration;
    return ret;
}

template <typename Set, typename InputIterator>
inline static Set test_variant(
    time_t &duration, range<InputIterator> const &range
)
{
    clock_t const start = clock();
    Set const     ret(range.first, range.ptend);

    duration  = clock() - start;
    duration += !duration;
    return ret;
}

template <typename Set, typename InputIterator, typename Compare>
inline static Set test_variant(
    time_t &duration, range<InputIterator> const &range, Compare const &cmp
)
{
    clock_t const start = clock();
    Set const     ret(range.first, range.ptend, cmp);

    duration  = clock() - start;
    duration += !duration;
    return ret;
}

template <typename Set, typename Compare, typename Allocator>
inline static Set test_variant(
    time_t &duration, Compare const &cmp, Allocator const &alloc
)
{
    clock_t const start = clock();
    Set const     ret(cmp, alloc);

    duration  = clock() - start;
    duration += !duration;
    return ret;
}

template <typename Set, typename InputIterator, typename Compare, typename Allocator>
inline static Set test_variant(
    time_t &duration, range<InputIterator> const &range, Compare const &cmp, Allocator const &alloc
)
{
    clock_t const start = clock();
    Set const     ret(range.first, range.ptend, cmp, alloc);

    duration  = clock() - start;
    duration += !duration;
    return ret;
}

template <typename Compare, typename InputIterator, typename Allocator>
inline static t_status test_each_variant(
    t_ratio_multiset_mut       &ratios,
    Compare const              &cmp,
    range<InputIterator> const &range,
    Allocator const            &alloc
)
{}

} // namespace constructor

}} // namespace tester::test

inline static u8 __test_constructor_default()
{
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        START = clock();
        ft::set<i32> const ft_set;
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START = clock();
        std::set<i32> const std_set;
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set))) {
            ret = ISO_OK;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_constructor_range()
{
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        // Range of input_iterator_restrictor
        {
            tester::input_iterator_restrictor<u16 const *> const mut_iter0(&array<u16>::at(0));
            tester::input_iterator_restrictor<u16 const *> const mut_iter1(&array<u16>::at(0));

            START = clock();
            ft::set<u16> const ft_set(mut_iter0, mut_iter1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::set<u16> const std_set(mut_iter0, mut_iter1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set))) {
                ret = ISO_OK;
            }
        }
        // Range of forward_iterator_restrictor
        {
            tester::forward_iterator_restrictor<void *const *> const it;

            START = clock();
            ft::set<void *> const ft_set(it, it);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::set<void *> const std_set(it, it);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set))) {
                ret = ISO_OK;
            }
        }
        // Range of random_access_iterator
        {
            tester::random_access_iterator_restrictor<u16 const *> const mut_iter0(
                &array<u16>::at(0)
            );
            tester::random_access_iterator_restrictor<u16 const *> const mut_iter1(
                &array<u16>::at(array<u16>::len)
            );

            START = clock();
            ft::set<u16> const ft_set(mut_iter0, mut_iter1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::set<u16> const std_set(mut_iter0, mut_iter1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set))) {
                ret = ISO_OK;
            }
        }
        // Range of char const *
        {
            START = clock();
            ft::set<char> const ft_set(&Array<char>::at(0), &Array<char>::at(Array<char>::len));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::set<char> const std_set(&Array<char>::at(0), &Array<char>::at(Array<char>::len));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_set) != sizeof(std_set) || memcmp(&ft_set, &std_set, sizeof(ft_set))) {
                ret = ISO_OK;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_constructor_copy()
{
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        // Default set
        {
            ft::set<i32> const  ft_set0;
            std::set<i32> const std_set0;

            START = clock();
            ft::set<i32> const ft_set1(ft_set0);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::set<i32> const std_set1(std_set0);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_set1) != sizeof(std_set1)
                || memcmp(&ft_set1, &std_set1, sizeof(ft_set1))) {
                ret = ISO_OK;
            }
        }
        // Filled set
        {
            ft::set<i32> const  ft_set0(&Array<i32>::at(0), &Array<i32>::at(Array<i32>::len));
            std::set<i32> const std_set0(&Array<i32>::at(0), &Array<i32>::at(Array<i32>::len));

            START = clock();
            ft::set<i32> const ft_set1(ft_set0);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::set<i32> const std_set1(std_set0);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_set1) != sizeof(std_set1)
                || memcmp(&ft_set1, &std_set1, sizeof(ft_set1))) {
                ret = ISO_OK;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_default_template_type_Compare()
{
    title(__func__);

    typedef ft::set<float>                    set_type_0;
    typedef ft::set<float, std::less<float> > set_type_1;

    if (!tester::is_same<set_type_0, set_type_1>::s_value) {
        return KO;
    }

    return IMPL_OK;
}

inline static u8 __test_default_template_type_Alloc()
{
    title(__func__);

    typedef ft::set<float>                                           set_type_0;
    typedef ft::set<float, std::less<float>, std::allocator<float> > set_type_1;

    if (!tester::is_same<set_type_0, set_type_1>::s_value) {
        return KO;
    }

    return IMPL_OK;
}

inline static u8 __test_type_key_type()
{
    title(__func__);
    try {
        typedef ft::set<i64> set_type;

        if (!tester::is_same<set_type::key_type, i64>::s_value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_value_type()
{
    title(__func__);
    try {
        typedef ft::set<i64> set_type;

        if (!tester::is_same<set_type::value_type, i64>::s_value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_key_compare()
{
    title(__func__);
    try {
        typedef ft::set<i64, std::less<i32> > set_type;

        if (!tester::is_same<set_type::key_compare, std::less<i32> >::s_value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_value_compare()
{
    title(__func__);
    try {
        typedef ft::set<i64, std::less<i32> > set_type;

        if (!tester::is_same<set_type::value_compare, std::less<i32> >::s_value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_allocator_type()
{
    title(__func__);
    try {
        typedef ft::set<i64, std::less<i32>, std::allocator<char> > set_type;

        if (!tester::is_same<set_type::allocator_type, std::allocator<char> >::s_value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_reference()
{
    title(__func__);
    try {
        typedef ft::set<i64, std::less<i32>, std::allocator<char> > set_type;

        if (!tester::is_same<set_type::reference, std::allocator<char>::reference>::s_value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_const_reference()
{
    title(__func__);
    try {
        typedef ft::set<i64, std::less<i32>, std::allocator<char> > set_type;

        if (!tester::is_same<set_type::const_reference, std::allocator<char>::const_reference>::
                s_value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_pointer()
{
    title(__func__);
    try {
        typedef ft::set<i64, std::less<i32>, std::allocator<char> > set_type;

        if (!tester::is_same<set_type::pointer, std::allocator<char>::pointer>::s_value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_const_pointer()
{
    title(__func__);
    try {
        typedef ft::set<i64, std::less<i32>, std::allocator<char> > set_type;

        if (!tester::is_same<set_type::const_pointer, std::allocator<char>::const_pointer>::
                s_value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_max_size()
{
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        // Set of unsigned char
        {
            ft::set<u8> const       ft_set;
            std::set<u8> const      std_set;
            ft::set<u8>::size_type  ft_ret;
            std::set<u8>::size_type std_ret;

            START        = clock();
            ft_ret       = ft_set.max_size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.max_size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                ret = ISO_OK;
            }
        }
        // Set of std::string
        {
            ft::set<std::string> const       ft_set;
            std::set<std::string> const      std_set;
            ft::set<std::string>::size_type  ft_ret;
            std::set<std::string>::size_type std_ret;

            START        = clock();
            ft_ret       = ft_set.max_size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.max_size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                ret = ISO_OK;
            }
        }
        // Set of long double
        {
            ft::set<long double> const       ft_set;
            std::set<long double> const      std_set;
            ft::set<long double>::size_type  ft_ret;
            std::set<long double>::size_type std_ret;

            START        = clock();
            ft_ret       = ft_set.max_size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.max_size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                ret = ISO_OK;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_function_key_comp()
{
    u32 idx;

    title(__func__);
    try {
        // std::less
        {
            ft::set<char, std::less<char> > const         ft_set;
            std::set<char, std::less<char> > const        std_set;
            ft::set<char, std::less<char> >::key_compare  ft_ret;
            std::set<char, std::less<char> >::key_compare std_ret;

            START        = clock();
            ft_ret       = ft_set.key_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.key_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (idx = 1; idx < Array<char>::len; ++idx) {
                if (ft_ret(Array<char>::at(idx - 1), Array<char>::at(idx))
                    != std_ret(Array<char>::at(idx - 1), Array<char>::at(idx))) {
                    return KO;
                }
            }
        }
        // std::less_equal
        {
            ft::set<char, std::less_equal<char> > const         ft_set;
            std::set<char, std::less_equal<char> > const        std_set;
            ft::set<char, std::less_equal<char> >::key_compare  ft_ret;
            std::set<char, std::less_equal<char> >::key_compare std_ret;

            START        = clock();
            ft_ret       = ft_set.key_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.key_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (idx = 1; idx < Array<char>::len; ++idx) {
                if (ft_ret(Array<char>::at(idx - 1), Array<char>::at(idx))
                    != std_ret(Array<char>::at(idx - 1), Array<char>::at(idx))) {
                    return KO;
                }
            }
        }
        // std::greater
        {
            ft::set<char, std::greater<char> > const         ft_set;
            std::set<char, std::greater<char> > const        std_set;
            ft::set<char, std::greater<char> >::key_compare  ft_ret;
            std::set<char, std::greater<char> >::key_compare std_ret;

            START        = clock();
            ft_ret       = ft_set.key_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.key_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (idx = 1; idx < Array<char>::len; ++idx) {
                if (ft_ret(Array<char>::at(idx - 1), Array<char>::at(idx))
                    != std_ret(Array<char>::at(idx - 1), Array<char>::at(idx))) {
                    return KO;
                }
            }
        }
        // std::greater_equal
        {
            ft::set<char, std::greater_equal<char> > const         ft_set;
            std::set<char, std::greater_equal<char> > const        std_set;
            ft::set<char, std::greater_equal<char> >::key_compare  ft_ret;
            std::set<char, std::greater_equal<char> >::key_compare std_ret;

            START        = clock();
            ft_ret       = ft_set.key_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.key_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (idx = 1; idx < Array<char>::len; ++idx) {
                if (ft_ret(Array<char>::at(idx - 1), Array<char>::at(idx))
                    != std_ret(Array<char>::at(idx - 1), Array<char>::at(idx))) {
                    return KO;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_value_comp()
{
    u32 idx;

    title(__func__);
    try {
        // std::less
        {
            ft::set<char, std::less<char> > const           ft_set;
            std::set<char, std::less<char> > const          std_set;
            ft::set<char, std::less<char> >::value_compare  ft_ret;
            std::set<char, std::less<char> >::value_compare std_ret;

            START        = clock();
            ft_ret       = ft_set.value_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.value_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (idx = 1; idx < Array<char>::len; ++idx) {
                if (ft_ret(Array<char>::at(idx - 1), Array<char>::at(idx))
                    != std_ret(Array<char>::at(idx - 1), Array<char>::at(idx))) {
                    return KO;
                }
            }
        }
        // std::less_equal
        {
            ft::set<char, std::less_equal<char> > const           ft_set;
            std::set<char, std::less_equal<char> > const          std_set;
            ft::set<char, std::less_equal<char> >::value_compare  ft_ret;
            std::set<char, std::less_equal<char> >::value_compare std_ret;

            START        = clock();
            ft_ret       = ft_set.value_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.value_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (idx = 1; idx < Array<char>::len; ++idx) {
                if (ft_ret(Array<char>::at(idx - 1), Array<char>::at(idx))
                    != std_ret(Array<char>::at(idx - 1), Array<char>::at(idx))) {
                    return KO;
                }
            }
        }
        // std::greater
        {
            ft::set<char, std::greater<char> > const           ft_set;
            std::set<char, std::greater<char> > const          std_set;
            ft::set<char, std::greater<char> >::value_compare  ft_ret;
            std::set<char, std::greater<char> >::value_compare std_ret;

            START        = clock();
            ft_ret       = ft_set.value_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.value_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (idx = 1; idx < Array<char>::len; ++idx) {
                if (ft_ret(Array<char>::at(idx - 1), Array<char>::at(idx))
                    != std_ret(Array<char>::at(idx - 1), Array<char>::at(idx))) {
                    return KO;
                }
            }
        }
        // std::greater_equal
        {
            ft::set<char, std::greater_equal<char> > const           ft_set;
            std::set<char, std::greater_equal<char> > const          std_set;
            ft::set<char, std::greater_equal<char> >::value_compare  ft_ret;
            std::set<char, std::greater_equal<char> >::value_compare std_ret;

            START        = clock();
            ft_ret       = ft_set.value_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.value_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (idx = 1; idx < Array<char>::len; ++idx) {
                if (ft_ret(Array<char>::at(idx - 1), Array<char>::at(idx))
                    != std_ret(Array<char>::at(idx - 1), Array<char>::at(idx))) {
                    return KO;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_size()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<u16>::size_type  ft_ret;
        std::set<u16>::size_type std_ret;

        for (idx = 0; idx < array<u16>::len; ++idx) {
            ft::set<u16> const  ft_set(&Array<u16>::at(idx), &Array<u16>::at(Array<u16>::len));
            std::set<u16> const std_set(&array<u16>::at(idx), &array<u16>::at(array<u16>::len));

            START        = clock();
            ft_ret       = ft_set.size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_empty()
{
    u32 idx;

    title(__func__);
    try {
        bool ft_ret;
        bool std_ret;

        for (idx = 0; idx < Array<u32>::len; ++idx) {
            ft::set<u32> const  ft_set(&Array<u32>::at(idx * (idx % 2)), &Array<u32>::at(idx));
            std::set<u32> const std_set(&Array<u32>::at(idx * (idx % 2)), &Array<u32>::at(idx));

            START        = clock();
            ft_ret       = ft_set.empty();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.empty();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_begin_constant()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<char>::const_iterator  ft_ret;
        std::set<char>::const_iterator std_ret;

        for (idx = 1; idx < Array<char>::len; ++idx) {
            ft::set<char> const ft_set(
                &Array<char>::at(idx - 1), &Array<char>::at(Array<char>::len)
            );
            std::set<char> const std_set(
                &Array<char>::at(idx - 1), &Array<char>::at(Array<char>::len)
            );

            START        = clock();
            ft_ret       = ft_set.begin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.begin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (!!ft_ret.base() != !!std_ret._M_node) {
                ret = ISO_OK;
            }
            if (*ft_ret != *std_ret) {
                return KO;
            }
        }

        ft::set<char> const  ft_set;
        std::set<char> const std_set;

        START        = clock();
        ft_ret       = ft_set.begin();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_set.begin();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (!!ft_ret.base() != !!std_ret._M_node) {
            ret = ISO_OK;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_function_begin_mutable()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<char>::iterator  ft_ret;
        std::set<char>::iterator std_ret;

        for (idx = 1; idx < Array<char>::len; ++idx) {
            ft::set<char>  ft_set(&Array<char>::at(idx - 1), &Array<char>::at(Array<char>::len));
            std::set<char> std_set(&Array<char>::at(idx - 1), &Array<char>::at(Array<char>::len));

            START        = clock();
            ft_ret       = ft_set.begin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.begin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (!!ft_ret.base() != !!std_ret._M_node) {
                ret = ISO_OK;
            }
            if (*ft_ret != *std_ret) {
                return KO;
            }
        }

        ft::set<char>  ft_set;
        std::set<char> std_set;

        START        = clock();
        ft_ret       = ft_set.begin();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_set.begin();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (!!ft_ret.base() != !!std_ret._M_node) {
            ret = ISO_OK;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_function_end_constant()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<char>::const_iterator  ft_ret;
        std::set<char>::const_iterator std_ret;

        for (idx = 1; idx < Array<char>::len; ++idx) {
            ft::set<char> const  ft_set(&Array<char>::at(0), &Array<char>::at(idx));
            std::set<char> const std_set(&Array<char>::at(0), &Array<char>::at(idx));

            START        = clock();
            ft_ret       = ft_set.end();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.end();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (!!ft_ret.base() != !!std_ret._M_node) {
                ret = ISO_OK;
            }

            --ft_ret;
            --std_ret;

            if (*ft_ret != *std_ret) {
                return KO;
            }
        }

        ft::set<char> const  ft_set;
        std::set<char> const std_set;

        START        = clock();
        ft_ret       = ft_set.end();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_set.end();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (!!ft_ret.base() != !!std_ret._M_node) {
            ret = ISO_OK;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_function_end_mutable()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<char>::iterator  ft_ret;
        std::set<char>::iterator std_ret;

        for (idx = 1; idx < Array<char>::len; ++idx) {
            ft::set<char>  ft_set(&Array<char>::at(0), &Array<char>::at(idx));
            std::set<char> std_set(&Array<char>::at(0), &Array<char>::at(idx));

            START        = clock();
            ft_ret       = ft_set.end();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.end();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (!!ft_ret.base() != !!std_ret._M_node) {
                ret = ISO_OK;
            }

            --ft_ret;
            --std_ret;

            if (*ft_ret != *std_ret) {
                return KO;
            }
        }

        ft::set<char>  ft_set;
        std::set<char> std_set;

        START        = clock();
        ft_ret       = ft_set.end();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_set.end();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (!!ft_ret.base() != !!std_ret._M_node) {
            ret = ISO_OK;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_function_rbegin_constant()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<char>::const_reverse_iterator  ft_ret;
        std::set<char>::const_reverse_iterator std_ret;

        for (idx = 1; idx < Array<char>::len; ++idx) {
            ft::set<char> const ft_set(
                &Array<char>::at(idx - 1), &Array<char>::at(Array<char>::len)
            );
            std::set<char> const std_set(
                &Array<char>::at(idx - 1), &Array<char>::at(Array<char>::len)
            );

            START        = clock();
            ft_ret       = ft_set.rbegin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.rbegin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (!!ft_ret.base().base() != !!std_ret.base()._M_node) {
                ret = ISO_OK;
            }
            if (*ft_ret != *std_ret) {
                return KO;
            }
        }

        ft::set<char> const  ft_set;
        std::set<char> const std_set;

        START        = clock();
        ft_ret       = ft_set.rbegin();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_set.rbegin();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (!!ft_ret.base().base() != !!std_ret.base()._M_node) {
            ret = ISO_OK;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_function_rbegin_mutable()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<char>::reverse_iterator  ft_ret;
        std::set<char>::reverse_iterator std_ret;

        for (idx = 1; idx < Array<char>::len; ++idx) {
            ft::set<char>  ft_set(&Array<char>::at(idx - 1), &Array<char>::at(Array<char>::len));
            std::set<char> std_set(&Array<char>::at(idx - 1), &Array<char>::at(Array<char>::len));

            START        = clock();
            ft_ret       = ft_set.rbegin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.rbegin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (!!ft_ret.base().base() != !!std_ret.base()._M_node) {
                ret = ISO_OK;
            }
            if (*ft_ret != *std_ret) {
                return KO;
            }
        }

        ft::set<char>  ft_set;
        std::set<char> std_set;

        START        = clock();
        ft_ret       = ft_set.rbegin();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_set.rbegin();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (!!ft_ret.base().base() != !!std_ret.base()._M_node) {
            ret = ISO_OK;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_function_rend_constant()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<char>::const_reverse_iterator  ft_ret;
        std::set<char>::const_reverse_iterator std_ret;

        for (idx = 1; idx < Array<char>::len; ++idx) {
            ft::set<char> const  ft_set(&Array<char>::at(0), &Array<char>::at(idx));
            std::set<char> const std_set(&Array<char>::at(0), &Array<char>::at(idx));

            START        = clock();
            ft_ret       = ft_set.rend();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.rend();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (!!ft_ret.base().base() != !!std_ret.base()._M_node) {
                ret = ISO_OK;
            }

            --ft_ret;
            --std_ret;

            if (*ft_ret != *std_ret) {
                return KO;
            }
        }

        ft::set<char> const  ft_set;
        std::set<char> const std_set;

        START        = clock();
        ft_ret       = ft_set.rend();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_set.rend();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (!!ft_ret.base().base() != !!std_ret.base()._M_node) {
            ret = ISO_OK;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_function_rend_mutable()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<char>::reverse_iterator  ft_ret;
        std::set<char>::reverse_iterator std_ret;

        for (idx = 1; idx < Array<char>::len; ++idx) {
            ft::set<char>  ft_set(&Array<char>::at(0), &Array<char>::at(idx));
            std::set<char> std_set(&Array<char>::at(0), &Array<char>::at(idx));

            START        = clock();
            ft_ret       = ft_set.rend();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.rend();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (!!ft_ret.base().base() != !!std_ret.base()._M_node) {
                ret = ISO_OK;
            }

            --ft_ret;
            --std_ret;

            if (*ft_ret != *std_ret) {
                return KO;
            }
        }

        ft::set<char>  ft_set;
        std::set<char> std_set;

        START        = clock();
        ft_ret       = ft_set.rend();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_set.rend();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (!!ft_ret.base().base() != !!std_ret.base()._M_node) {
            ret = ISO_OK;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_type_iterator()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<float> const  ft_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        std::set<float> const std_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        ft::set<float>::iterator  ft_it;
        std::set<float>::iterator std_it;

        if (sizeof(ft_it) != sizeof(std_it)) {
            ret = ISO_OK;
        }

        for (ft_it = ft_set.begin(), std_it = std_set.begin(), idx = 0;
             ft_it != ft_set.end() && std_it != std_set.end();
             ++ft_it, ++std_it, ++idx) {
            if (idx) {
                BidirectionalIteratorCheck(ft_it);
                BidirectionalIteratorCheck(std_it);
            }

            if (*ft_it != *std_it) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_type_const_iterator()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<float> const  ft_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        std::set<float> const std_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        ft::set<float>::const_iterator  ft_cit;
        std::set<float>::const_iterator std_cit;

        if (sizeof(ft_cit) != sizeof(std_cit)) {
            ret = ISO_OK;
        }

        for (ft_cit = ft_set.begin(), std_cit = std_set.begin(), idx = 0;
             ft_cit != ft_set.end() && std_cit != std_set.end();
             ++ft_cit, ++std_cit) {
            if (idx) {
                BidirectionalIteratorCheck(ft_cit);
                BidirectionalIteratorCheck(std_cit);
            }

            if (*ft_cit != *std_cit) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_type_reverse_iterator()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<float>  ft_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        std::set<float> std_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        ft::set<float>::reverse_iterator  ft_rit;
        std::set<float>::reverse_iterator std_it;

        if (sizeof(ft_rit) != sizeof(std_it)) {
            ret = ISO_OK;
        }

        for (ft_rit = ft_set.rbegin(), std_it = std_set.rbegin(), idx = 0;
             ft_rit != ft_set.rend() && std_it != std_set.rend();
             ++ft_rit, ++std_it, ++idx) {
            if (idx) {
                BidirectionalIteratorCheck(ft_rit);
                BidirectionalIteratorCheck(std_it);
            }

            if (*ft_rit != *std_it) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_type_const_reverse_iterator()
{
    u32 idx;
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::set<float> const  ft_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        std::set<float> const std_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        ft::set<float>::const_reverse_iterator  ft_crit;
        std::set<float>::const_reverse_iterator std_crit;

        if (sizeof(ft_crit) != sizeof(std_crit)) {
            ret = ISO_OK;
        }

        for (ft_crit = ft_set.rbegin(), std_crit = std_set.rbegin(), idx = 0;
             ft_crit != ft_set.rend() && std_crit != std_set.rend();
             ++ft_crit, ++std_crit) {
            if (idx) {
                BidirectionalIteratorCheck(ft_crit);
                BidirectionalIteratorCheck(std_crit);
            }

            if (*ft_crit != *std_crit) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_function_insert_range()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<std::string>  ft_set;
        std::set<std::string> std_set;

        for (idx = 1; idx < Array<std::string>::len; ++idx) {
            START = clock();
            ft_set.insert(&Array<std::string>::at(idx - 1), &Array<std::string>::at(idx + 1));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_set.insert(&Array<std::string>::at(idx - 1), &Array<std::string>::at(idx + 1));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_set.size() != std_set.size()
                || !std::equal(ft_set.begin(), ft_set.end(), std_set.begin())) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_insert_single()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<std::string>                             ft_set;
        std::set<std::string>                            std_set;
        ft::Pair<ft::set<std::string>::iterator, bool>   ft_ret;
        std::pair<std::set<std::string>::iterator, bool> std_ret;

        for (idx = 0; idx < Array<std::string>::len; ++idx) {
            START        = clock();
            ft_ret       = ft_set.insert(Array<std::string>::at(idx));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.insert(Array<std::string>::at(idx));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (*ft_ret.first != *std_ret.first
                || ft_ret.second != std_ret.second
                || ft_set.size() != std_set.size()
                || !std::equal(ft_set.begin(), ft_set.end(), std_set.begin())) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_insert_single_hint()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<std::string>            ft_set;
        std::set<std::string>           std_set;
        ft::set<std::string>::iterator  ft_ret;
        std::set<std::string>::iterator std_ret;

        ft_set.insert(ft_set.begin(), std::string("dedicated to lmartin"));
        std_set.insert(std_set.begin(), std::string("dedicated to lmartin"));
        ft_ret  = ft_set.begin();
        std_ret = std_set.begin();
        for (idx = 0; idx < Array<std::string>::len * 3; ++idx) {
            switch (idx % 3) {
            case 0:
                START        = clock();
                ft_ret       = ft_set.insert(ft_ret, Array<std::string>::at(idx / 3));
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std_set.insert(std_ret, Array<std::string>::at(idx / 3));
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;
                break;

            case 1:
                START        = clock();
                ft_ret       = ft_set.insert(ft_set.begin(), *++ft_set.begin());
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std_set.insert(std_set.begin(), *++std_set.begin());
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;
                break;

            case 2:
                START        = clock();
                ft_ret       = ft_set.insert(ft_set.end(), *++ft_set.rbegin());
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std_set.insert(std_set.end(), *++std_set.rbegin());
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;
                break;
            }

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (*ft_ret != *std_ret
                || ft_set.size() != std_set.size()
                || !std::equal(ft_set.begin(), ft_set.end(), std_set.begin())) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_erase_range()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<char>            ft_set(&Array<char>::at(0), &Array<char>::at(Array<char>::len));
        std::set<char>           std_set(&Array<char>::at(0), &Array<char>::at(Array<char>::len));
        ft::set<char>::iterator  ft_mut_iter0;
        ft::set<char>::iterator  ft_mut_iter1;
        std::set<char>::iterator std_mut_iter0;
        std::set<char>::iterator std_mut_iter1;

        for (idx = 0; idx < Array<char>::len && idx < Array<i64>::len; idx += 2) {
            ft_mut_iter0  = ft_set.begin();
            std_mut_iter0 = std_set.begin();
            std::advance(ft_mut_iter0, ft_set.size() / 2 - 1);
            std::advance(std_mut_iter0, std_set.size() / 2 - 1);
            ft_mut_iter1  = ft_mut_iter0;
            std_mut_iter1 = std_mut_iter0;
            std::advance(ft_mut_iter1, 2);
            std::advance(std_mut_iter1, 2);

            START = clock();
            ft_set.erase(ft_mut_iter0, ft_mut_iter1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_set.erase(std_mut_iter0, std_mut_iter1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_set.size() != std_set.size()
                || !std::equal(ft_set.begin(), ft_set.end(), std_set.begin())) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_erase_single_position()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<char>  ft_set(&Array<char>::at(0), &Array<char>::at(Array<char>::len));
        std::set<char> std_set(&Array<char>::at(0), &Array<char>::at(Array<char>::len));

        for (idx = 0; idx < Array<char>::len && idx < Array<i64>::len; ++idx) {
            START = clock();
            ft_set.erase(ft_set.begin());
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_set.erase(std_set.begin());
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_set.size() != std_set.size()
                || !std::equal(ft_set.begin(), ft_set.end(), std_set.begin())) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_erase_single_key()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<char>             ft_set(&Array<char>::at(0), &Array<char>::at(Array<char>::len));
        std::set<char>            std_set(&Array<char>::at(0), &Array<char>::at(Array<char>::len));
        ft::set<char>::size_type  ft_ret;
        std::set<char>::size_type std_ret;

        for (idx = 0; idx < Array<char>::len * 2 && idx < Array<i64>::len * 2; ++idx) {
            START        = clock();
            ft_ret       = ft_set.erase(Array<char>::at(idx / 2));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.erase(Array<char>::at(idx / 2));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret
                || ft_set.size() != std_set.size()
                || !std::equal(ft_set.begin(), ft_set.end(), std_set.begin())) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_clear()
{
    u32 idx;

    title(__func__);
    try {
        for (idx = 0; idx < Array<i32>::len; ++idx) {
            ft::set<i32>  ft_set(&Array<i32>::at(0), &Array<i32>::at(idx));
            std::set<i32> std_set(&Array<i32>::at(0), &Array<i32>::at(idx));

            START = clock();
            ft_set.clear();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_set.clear();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_set.size() != std_set.size()
                || !std::equal(ft_set.begin(), ft_set.end(), std_set.begin())) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_find_constant()
{
    u32   idx;
    float nb;

    title(__func__);
    try {
        ft::set<float> const  ft_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        std::set<float> const std_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        ft::set<float>::const_iterator  ft_ret;
        std::set<float>::const_iterator std_ret;

        for (idx = 0; idx < Array<float>::len * 2; ++idx) {
            if (idx % 2) {
                nb = static_cast<float>(rand());
                while (std::find(&Array<float>::at(0), &Array<float>::at(Array<float>::len), nb)
                       != &Array<float>::at(Array<float>::len)) {
                    nb = static_cast<float>(rand());
                }
            }
            else {
                nb = Array<float>::at(idx / 2);
            }

            START        = clock();
            ft_ret       = ft_set.find(nb);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.find(nb);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_set.end()) != (std_ret == std_set.end())
                || (ft_ret != ft_set.end() && (*ft_ret != *std_ret))) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_find_mutable()
{
    u32   idx;
    float nb;

    title(__func__);
    try {
        ft::set<float>  ft_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        std::set<float> std_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        ft::set<float>::iterator  ft_ret;
        std::set<float>::iterator std_ret;

        for (idx = 0; idx < Array<float>::len * 2; ++idx) {
            if (idx % 2) {
                nb = static_cast<float>(rand());
                while (std::find(&Array<float>::at(0), &Array<float>::at(Array<float>::len), nb)
                       != &Array<float>::at(Array<float>::len)) {
                    nb = static_cast<float>(rand());
                }
            }
            else {
                nb = Array<float>::at(idx / 2);
            }

            START        = clock();
            ft_ret       = ft_set.find(nb);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.find(nb);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_set.end()) != (std_ret == std_set.end())
                || (ft_ret != ft_set.end() && (*ft_ret != *std_ret))) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_count()
{
    u32   idx;
    float nb;

    title(__func__);
    try {
        ft::set<float> const  ft_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        std::set<float> const std_set(&Array<float>::at(0), &Array<float>::at(Array<float>::len));
        ft::set<float>::size_type  ft_ret;
        std::set<float>::size_type std_ret;

        for (idx = 0; idx < Array<float>::len * 2; ++idx) {
            if (idx % 2) {
                nb = static_cast<float>(rand());
                while (std::find(&Array<float>::at(0), &Array<float>::at(Array<float>::len), nb)
                       != &Array<float>::at(Array<float>::len)) {
                    nb = static_cast<float>(rand());
                }
            }
            else {
                nb = Array<float>::at(idx / 2);
            }

            START        = clock();
            ft_ret       = ft_set.count(nb);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.count(nb);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_lower_bound_constant()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i64> const            ft_set(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
        std::set<i64> const           std_set(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
        ft::set<i64>::const_iterator  ft_ret;
        std::set<i64>::const_iterator std_ret;

        for (idx = 0; idx < Array<i64>::len; ++idx) {
            START        = clock();
            ft_ret       = ft_set.lower_bound(Array<i64>::at(idx));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.lower_bound(Array<i64>::at(idx));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_set.end()) != (std_ret == std_set.end())
                || (ft_ret != ft_set.end() && (*ft_ret != *std_ret))) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_lower_bound_mutable()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i64>            ft_set(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
        std::set<i64>           std_set(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
        ft::set<i64>::iterator  ft_ret;
        std::set<i64>::iterator std_ret;

        for (idx = 0; idx < Array<i64>::len; ++idx) {
            START        = clock();
            ft_ret       = ft_set.lower_bound(Array<i64>::at(idx));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.lower_bound(Array<i64>::at(idx));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_set.end()) != (std_ret == std_set.end())
                || (ft_ret != ft_set.end() && (*ft_ret != *std_ret))) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_upper_bound_constant()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i64> const            ft_set(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
        std::set<i64> const           std_set(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
        ft::set<i64>::const_iterator  ft_ret;
        std::set<i64>::const_iterator std_ret;

        for (idx = 0; idx < Array<i64>::len; ++idx) {
            START        = clock();
            ft_ret       = ft_set.upper_bound(Array<i64>::at(idx));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.upper_bound(Array<i64>::at(idx));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_set.end()) != (std_ret == std_set.end())
                || (ft_ret != ft_set.end() && (*ft_ret != *std_ret))) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_upper_bound_mutable()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i64>            ft_set(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
        std::set<i64>           std_set(&Array<i64>::at(0), &Array<i64>::at(Array<i64>::len));
        ft::set<i64>::iterator  ft_ret;
        std::set<i64>::iterator std_ret;

        for (idx = 0; idx < Array<i64>::len; ++idx) {
            START        = clock();
            ft_ret       = ft_set.upper_bound(Array<i64>::at(idx));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.upper_bound(Array<i64>::at(idx));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_set.end()) != (std_ret == std_set.end())
                || (ft_ret != ft_set.end() && (*ft_ret != *std_ret))) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_equal_range_constant()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i16> const  ft_set(&Array<i16>::at(0), &Array<i16>::at(Array<i16>::len));
        std::set<i16> const std_set(&Array<i16>::at(0), &Array<i16>::at(Array<i16>::len));
        ft::Pair<ft::set<i16>::const_iterator, ft::set<i16>::const_iterator>    ft_ret;
        std::pair<std::set<i16>::const_iterator, std::set<i16>::const_iterator> std_ret;

        for (idx = 0; idx < Array<i16>::len; ++idx) {
            START        = clock();
            ft_ret       = ft_set.equal_range(Array<i16>::at(idx));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.equal_range(Array<i16>::at(idx));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret.first == ft_set.end()) != (std_ret.first == std_set.end())
                || (ft_ret.first != ft_set.end()
                    && !std::equal(ft_ret.first, ft_ret.second, std_ret.first))) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_equal_range_mutable()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i16>  ft_set(&Array<i16>::at(0), &Array<i16>::at(Array<i16>::len));
        std::set<i16> std_set(&Array<i16>::at(0), &Array<i16>::at(Array<i16>::len));
        ft::Pair<ft::set<i16>::iterator, ft::set<i16>::iterator>    ft_ret;
        std::pair<std::set<i16>::iterator, std::set<i16>::iterator> std_ret;

        for (idx = 0; idx < Array<i16>::len; ++idx) {
            START        = clock();
            ft_ret       = ft_set.equal_range(Array<i16>::at(idx));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_set.equal_range(Array<i16>::at(idx));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret.first == ft_set.end()) != (std_ret.first == std_set.end())
                || (ft_ret.first != ft_set.end()
                    && !std::equal(ft_ret.first, ft_ret.second, std_ret.first))) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_swap()
{
    title(__func__);
    try {
        // Member function
        {
            // Swapping empty | empty
            {
                ft::set<char>                  ft_set0;
                ft::set<char>                  ft_set1;
                ft::set<char>::const_iterator  ft_const_iter0(ft_set0.begin());
                ft::set<char>::const_iterator  ft_const_iter1(ft_set1.begin());
                ft::set<char>::const_iterator  ft_const_end0;
                ft::set<char>::const_iterator  ft_const_end1;
                std::set<char>                 std_set0;
                std::set<char>                 std_set1;
                std::set<char>::const_iterator std_const_iter0(std_set0.begin());
                std::set<char>::const_iterator std_const_iter1(std_set1.begin());

                START = clock();
                ft_set0.swap(ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_set0.swap(std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                ft_const_end0 = ft_set0.end();
                ft_const_end1 = ft_set1.end();

                if (ft_set0.size() != std_set0.size()
                    || ft_set1.size() != std_set1.size()
                    || !std::equal(ft_const_iter0, ft_const_end1, std_const_iter0)
                    || !std::equal(ft_const_iter1, ft_const_end0, std_const_iter1)) {
                    return KO;
                }
            }
            // Swapping empty | non-empty
            {
                ft::set<char> ft_set0;
                ft::set<char> ft_set1(
                    &Array<char>::at(Array<char>::len / 2), &Array<char>::at(Array<char>::len)
                );
                std::set<char> std_set0;
                std::set<char> std_set1(
                    &Array<char>::at(Array<char>::len / 2), &Array<char>::at(Array<char>::len)
                );
                ft::set<char>::const_iterator  ft_const_iter0(ft_set0.begin());
                ft::set<char>::const_iterator  ft_const_iter1(ft_set1.begin());
                std::set<char>::const_iterator std_const_iter0(std_set0.begin());
                std::set<char>::const_iterator std_const_iter1(std_set1.begin());
                ft::set<char>::const_iterator  ft_const_end0;
                ft::set<char>::const_iterator  ft_const_end1;

                START = clock();
                ft_set0.swap(ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_set0.swap(std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                ft_const_end0 = ft_set0.end();
                ft_const_end1 = ft_set1.end();

                if (ft_set0.size() != std_set0.size()
                    || ft_set1.size() != std_set1.size()
                    || !std::equal(ft_const_iter0, ft_const_end1, std_const_iter0)
                    || !std::equal(ft_const_iter1, ft_const_end0, std_const_iter1)) {
                    return KO;
                }
            }
            // Swapping non-empty | empty
            {
                ft::set<char>  ft_set0(&Array<char>::at(0), &Array<char>::at(Array<char>::len / 2));
                ft::set<char>  ft_set1;
                std::set<char> std_set0(
                    &Array<char>::at(0), &Array<char>::at(Array<char>::len / 2)
                );
                std::set<char>                 std_set1;
                ft::set<char>::const_iterator  ft_const_iter0(ft_set0.begin());
                ft::set<char>::const_iterator  ft_const_iter1(ft_set1.begin());
                std::set<char>::const_iterator std_const_iter0(std_set0.begin());
                std::set<char>::const_iterator std_const_iter1(std_set1.begin());
                ft::set<char>::const_iterator  ft_const_end0;
                ft::set<char>::const_iterator  ft_const_end1;

                START = clock();
                ft_set0.swap(ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_set0.swap(std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                ft_const_end0 = ft_set0.end();
                ft_const_end1 = ft_set1.end();

                if (ft_set0.size() != std_set0.size()
                    || ft_set1.size() != std_set1.size()
                    || !std::equal(ft_const_iter0, ft_const_end1, std_const_iter0)
                    || !std::equal(ft_const_iter1, ft_const_end0, std_const_iter1)) {
                    return KO;
                }
            }
            // Swapping non-empty | non-empty
            {
                ft::set<char> ft_set0(&Array<char>::at(0), &Array<char>::at(Array<char>::len / 2));
                ft::set<char> ft_set1(
                    &Array<char>::at(Array<char>::len / 2), &Array<char>::at(Array<char>::len)
                );
                std::set<char> std_set0(
                    &Array<char>::at(0), &Array<char>::at(Array<char>::len / 2)
                );
                std::set<char> std_set1(
                    &Array<char>::at(Array<char>::len / 2), &Array<char>::at(Array<char>::len)
                );
                ft::set<char>::const_iterator  ft_const_iter0(ft_set0.begin());
                ft::set<char>::const_iterator  ft_const_iter1(ft_set1.begin());
                std::set<char>::const_iterator std_const_iter0(std_set0.begin());
                std::set<char>::const_iterator std_const_iter1(std_set1.begin());
                ft::set<char>::const_iterator  ft_const_end0;
                ft::set<char>::const_iterator  ft_const_end1;

                START = clock();
                ft_set0.swap(ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_set0.swap(std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                ft_const_end0 = ft_set0.end();
                ft_const_end1 = ft_set1.end();

                if (ft_set0.size() != std_set0.size()
                    || ft_set1.size() != std_set1.size()
                    || !std::equal(ft_const_iter0, ft_const_end1, std_const_iter0)
                    || !std::equal(ft_const_iter1, ft_const_end0, std_const_iter1)) {
                    return KO;
                }
            }
        }
        // Non-member function
        {
            // Swapping empty | empty
            {
                ft::set<char>                  ft_set0;
                ft::set<char>                  ft_set1;
                std::set<char>                 std_set0;
                std::set<char>                 std_set1;
                ft::set<char>::const_iterator  ft_const_iter0(ft_set0.begin());
                ft::set<char>::const_iterator  ft_const_iter1(ft_set1.begin());
                std::set<char>::const_iterator std_const_iter0(std_set0.begin());
                std::set<char>::const_iterator std_const_iter1(std_set1.begin());
                ft::set<char>::const_iterator  ft_const_end0;
                ft::set<char>::const_iterator  ft_const_end1;

                START = clock();
                ft::swap(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::swap(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                ft_const_end0 = ft_set0.end();
                ft_const_end1 = ft_set1.end();

                if (ft_set0.size() != std_set0.size()
                    || ft_set1.size() != std_set1.size()
                    || !std::equal(ft_const_iter0, ft_const_end1, std_const_iter0)
                    || !std::equal(ft_const_iter1, ft_const_end0, std_const_iter1)) {
                    return KO;
                }
            }
            // Swapping empty | non-empty
            {
                ft::set<char> ft_set0;
                ft::set<char> ft_set1(
                    &Array<char>::at(Array<char>::len / 2), &Array<char>::at(Array<char>::len)
                );
                std::set<char> std_set0;
                std::set<char> std_set1(
                    &Array<char>::at(Array<char>::len / 2), &Array<char>::at(Array<char>::len)
                );
                ft::set<char>::const_iterator  ft_const_iter0(ft_set0.begin());
                ft::set<char>::const_iterator  ft_const_iter1(ft_set1.begin());
                std::set<char>::const_iterator std_const_iter0(std_set0.begin());
                std::set<char>::const_iterator std_const_iter1(std_set1.begin());
                ft::set<char>::const_iterator  ft_const_end0;
                ft::set<char>::const_iterator  ft_const_end1;

                START = clock();
                ft::swap(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::swap(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                ft_const_end0 = ft_set0.end();
                ft_const_end1 = ft_set1.end();

                if (ft_set0.size() != std_set0.size()
                    || ft_set1.size() != std_set1.size()
                    || !std::equal(ft_const_iter0, ft_const_end1, std_const_iter0)
                    || !std::equal(ft_const_iter1, ft_const_end0, std_const_iter1)) {
                    return KO;
                }
            }
            // Swapping non-empty | empty
            {
                ft::set<char>  ft_set0(&Array<char>::at(0), &Array<char>::at(Array<char>::len / 2));
                ft::set<char>  ft_set1;
                std::set<char> std_set0(
                    &Array<char>::at(0), &Array<char>::at(Array<char>::len / 2)
                );
                std::set<char>                 std_set1;
                ft::set<char>::const_iterator  ft_const_iter0(ft_set0.begin());
                ft::set<char>::const_iterator  ft_const_iter1(ft_set1.begin());
                std::set<char>::const_iterator std_const_iter0(std_set0.begin());
                std::set<char>::const_iterator std_const_iter1(std_set1.begin());
                ft::set<char>::const_iterator  ft_const_end0;
                ft::set<char>::const_iterator  ft_const_end1;

                START = clock();
                ft::swap(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::swap(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                ft_const_end0 = ft_set0.end();
                ft_const_end1 = ft_set1.end();

                if (ft_set0.size() != std_set0.size()
                    || ft_set1.size() != std_set1.size()
                    || !std::equal(ft_const_iter0, ft_const_end1, std_const_iter0)
                    || !std::equal(ft_const_iter1, ft_const_end0, std_const_iter1)) {
                    return KO;
                }
            }
            // Swapping non-empty | non-empty
            {
                ft::set<char> ft_set0(&Array<char>::at(0), &Array<char>::at(Array<char>::len / 2));
                ft::set<char> ft_set1(
                    &Array<char>::at(Array<char>::len / 2), &Array<char>::at(Array<char>::len)
                );
                std::set<char> std_set0(
                    &Array<char>::at(0), &Array<char>::at(Array<char>::len / 2)
                );
                std::set<char> std_set1(
                    &Array<char>::at(Array<char>::len / 2), &Array<char>::at(Array<char>::len)
                );
                ft::set<char>::const_iterator  ft_const_iter0(ft_set0.begin());
                ft::set<char>::const_iterator  ft_const_iter1(ft_set1.begin());
                std::set<char>::const_iterator std_const_iter0(std_set0.begin());
                std::set<char>::const_iterator std_const_iter1(std_set1.begin());
                ft::set<char>::const_iterator  ft_const_end0;
                ft::set<char>::const_iterator  ft_const_end1;

                START = clock();
                ft::swap(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::swap(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                ft_const_end0 = ft_set0.end();
                ft_const_end1 = ft_set1.end();

                if (ft_set0.size() != std_set0.size()
                    || ft_set1.size() != std_set1.size()
                    || !std::equal(ft_const_iter0, ft_const_end1, std_const_iter0)
                    || !std::equal(ft_const_iter1, ft_const_end0, std_const_iter1)) {
                    return KO;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_operator_assign()
{
    title(__func__);
    try {
        // Assigning empty -> empty
        {
            ft::set<std::string>        ft_set0;
            ft::set<std::string> const  ft_set1;
            std::set<std::string>       std_set0;
            std::set<std::string> const std_set1;

            START        = clock();
            ft_set0      = ft_set1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_set0      = std_set1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_set0.size() != std_set0.size()
                || !std::equal(ft_set0.begin(), ft_set0.end(), std_set0.begin())) {
                return KO;
            }
        }
        // Assigning empty -> non-empty
        {
            ft::set<std::string> ft_set0(
                &Array<std::string>::at(0), &Array<std::string>::at(Array<std::string>::len / 2)
            );
            ft::set<std::string> const ft_set1;
            std::set<std::string>      std_set0(
                &Array<std::string>::at(0), &Array<std::string>::at(Array<std::string>::len / 2)
            );
            std::set<std::string> const std_set1;

            START        = clock();
            ft_set0      = ft_set1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_set0      = std_set1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_set0.size() != std_set0.size()
                || !std::equal(ft_set0.begin(), ft_set0.end(), std_set0.begin())) {
                return KO;
            }
        }
        // Assigning non-empty -> empty
        {
            ft::set<std::string>       ft_set0;
            ft::set<std::string> const ft_set1(
                &Array<std::string>::at(Array<std::string>::len / 2),
                &Array<std::string>::at(Array<std::string>::len)
            );
            std::set<std::string>       std_set0;
            std::set<std::string> const std_set1(
                &Array<std::string>::at(Array<std::string>::len / 2),
                &Array<std::string>::at(Array<std::string>::len)
            );

            START        = clock();
            ft_set0      = ft_set1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_set0      = std_set1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_set0.size() != std_set0.size()
                || !std::equal(ft_set0.begin(), ft_set0.end(), std_set0.begin())) {
                return KO;
            }
        }
        // Assigning non-empty -> non-empty
        {
            ft::set<std::string> ft_set0(
                &Array<std::string>::at(0), &Array<std::string>::at(Array<std::string>::len / 2)
            );
            ft::set<std::string> const ft_set1(
                &Array<std::string>::at(Array<std::string>::len / 2),
                &Array<std::string>::at(Array<std::string>::len)
            );
            std::set<std::string> std_set0(
                &Array<std::string>::at(0), &Array<std::string>::at(Array<std::string>::len / 2)
            );
            std::set<std::string> const std_set1(
                &Array<std::string>::at(Array<std::string>::len / 2),
                &Array<std::string>::at(Array<std::string>::len)
            );

            START        = clock();
            ft_set0      = ft_set1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_set0      = std_set1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_set0.size() != std_set0.size()
                || !std::equal(ft_set0.begin(), ft_set0.end(), std_set0.begin())) {
                return KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_operator_equivalent()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i8>  ft_set0;
        ft::set<i8>  ft_set1;
        std::set<i8> std_set0;
        std::set<i8> std_set1;
        bool         ft_ret;
        bool         std_ret;

        for (idx = 0; idx < Array<i8>::len; ++idx) {
            // Key difference
            {
                ft_set0.insert(Array<i8>::at(idx) + 1);
                ft_set1.insert(Array<i8>::at(idx) - 1);
                std_set0.insert(Array<i8>::at(idx) + 1);
                std_set1.insert(Array<i8>::at(idx) - 1);

                START        = clock();
                ft_ret       = ft::operator==(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator==(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_set0.erase(Array<i8>::at(idx) + 1);
                ft_set1.erase(Array<i8>::at(idx) - 1);
                std_set0.erase(Array<i8>::at(idx) + 1);
                std_set1.erase(Array<i8>::at(idx) - 1);
            }
            // Size difference
            {
                ft_set0.insert(Array<i8>::at(idx));
                std_set0.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator==(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator==(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_set1.insert(Array<i8>::at(idx));
                std_set1.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator==(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator==(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_operator_different()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i8>  ft_set0;
        ft::set<i8>  ft_set1;
        std::set<i8> std_set0;
        std::set<i8> std_set1;
        bool         ft_ret;
        bool         std_ret;

        for (idx = 0; idx < Array<i8>::len; ++idx) {
            // Key difference
            {
                ft_set0.insert(Array<i8>::at(idx) + 1);
                ft_set1.insert(Array<i8>::at(idx) - 1);
                std_set0.insert(Array<i8>::at(idx) + 1);
                std_set1.insert(Array<i8>::at(idx) - 1);

                START        = clock();
                ft_ret       = ft::operator!=(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator!=(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_set0.erase(Array<i8>::at(idx) + 1);
                ft_set1.erase(Array<i8>::at(idx) - 1);
                std_set0.erase(Array<i8>::at(idx) + 1);
                std_set1.erase(Array<i8>::at(idx) - 1);
            }
            // Size difference
            {
                ft_set0.insert(Array<i8>::at(idx));
                std_set0.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator!=(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator!=(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_set1.insert(Array<i8>::at(idx));
                std_set1.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator!=(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator!=(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_operator_lower()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i8>  ft_set0;
        ft::set<i8>  ft_set1;
        std::set<i8> std_set0;
        std::set<i8> std_set1;
        bool         ft_ret;
        bool         std_ret;

        for (idx = 0; idx < Array<i8>::len; ++idx) {
            // Key difference
            {
                ft_set0.insert(Array<i8>::at(idx) + 1);
                ft_set1.insert(Array<i8>::at(idx) - 1);
                std_set0.insert(Array<i8>::at(idx) + 1);
                std_set1.insert(Array<i8>::at(idx) - 1);

                START        = clock();
                ft_ret       = ft::operator<(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_set0.erase(Array<i8>::at(idx) + 1);
                ft_set1.erase(Array<i8>::at(idx) - 1);
                std_set0.erase(Array<i8>::at(idx) + 1);
                std_set1.erase(Array<i8>::at(idx) - 1);
            }
            // Size difference
            {
                ft_set0.insert(Array<i8>::at(idx));
                std_set0.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator<(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_set1.insert(Array<i8>::at(idx));
                std_set1.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator<(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_operator_greater()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i8>  ft_set0;
        ft::set<i8>  ft_set1;
        std::set<i8> std_set0;
        std::set<i8> std_set1;
        bool         ft_ret;
        bool         std_ret;

        for (idx = 0; idx < Array<i8>::len; ++idx) {
            // Key difference
            {
                ft_set0.insert(Array<i8>::at(idx) + 1);
                ft_set1.insert(Array<i8>::at(idx) - 1);
                std_set0.insert(Array<i8>::at(idx) + 1);
                std_set1.insert(Array<i8>::at(idx) - 1);

                START        = clock();
                ft_ret       = ft::operator>(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_set0.erase(Array<i8>::at(idx) + 1);
                ft_set1.erase(Array<i8>::at(idx) - 1);
                std_set0.erase(Array<i8>::at(idx) + 1);
                std_set1.erase(Array<i8>::at(idx) - 1);
            }
            // Size difference
            {
                ft_set0.insert(Array<i8>::at(idx));
                std_set0.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator>(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_set1.insert(Array<i8>::at(idx));
                std_set1.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator>(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_operator_lower_or_equivalent()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i8>  ft_set0;
        ft::set<i8>  ft_set1;
        std::set<i8> std_set0;
        std::set<i8> std_set1;
        bool         ft_ret;
        bool         std_ret;

        for (idx = 0; idx < Array<i8>::len; ++idx) {
            // Key difference
            {
                ft_set0.insert(Array<i8>::at(idx) + 1);
                ft_set1.insert(Array<i8>::at(idx) - 1);
                std_set0.insert(Array<i8>::at(idx) + 1);
                std_set1.insert(Array<i8>::at(idx) - 1);

                START        = clock();
                ft_ret       = ft::operator<=(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<=(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_set0.erase(Array<i8>::at(idx) + 1);
                ft_set1.erase(Array<i8>::at(idx) - 1);
                std_set0.erase(Array<i8>::at(idx) + 1);
                std_set1.erase(Array<i8>::at(idx) - 1);
            }
            // Size difference
            {
                ft_set0.insert(Array<i8>::at(idx));
                std_set0.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator<=(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<=(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_set1.insert(Array<i8>::at(idx));
                std_set1.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator<=(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<=(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_operator_greater_or_equivalent()
{
    u32 idx;

    title(__func__);
    try {
        ft::set<i8>  ft_set0;
        ft::set<i8>  ft_set1;
        std::set<i8> std_set0;
        std::set<i8> std_set1;
        bool         ft_ret;
        bool         std_ret;

        for (idx = 0; idx < Array<i8>::len; ++idx) {
            // Key difference
            {
                ft_set0.insert(Array<i8>::at(idx) + 1);
                ft_set1.insert(Array<i8>::at(idx) - 1);
                std_set0.insert(Array<i8>::at(idx) + 1);
                std_set1.insert(Array<i8>::at(idx) - 1);

                START        = clock();
                ft_ret       = ft::operator>=(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>=(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_set0.erase(Array<i8>::at(idx) + 1);
                ft_set1.erase(Array<i8>::at(idx) - 1);
                std_set0.erase(Array<i8>::at(idx) + 1);
                std_set1.erase(Array<i8>::at(idx) - 1);
            }
            // Size difference
            {
                ft_set0.insert(Array<i8>::at(idx));
                std_set0.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator>=(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>=(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_set1.insert(Array<i8>::at(idx));
                std_set1.insert(Array<i8>::at(idx));

                START        = clock();
                ft_ret       = ft::operator>=(ft_set0, ft_set1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>=(std_set0, std_set1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

u8 test_set()
{
    TestFn const tests[] = {
        __test_constructor_default,
        __test_constructor_range,
        __test_constructor_copy,
        __test_default_template_type_Compare,
        __test_default_template_type_Alloc,
        __test_type_key_type,
        __test_type_value_type,
        __test_type_key_compare,
        __test_type_value_compare,
        __test_type_allocator_type,
        __test_type_reference,
        __test_type_const_reference,
        __test_type_pointer,
        __test_type_const_pointer,
        __test_function_max_size,
        __test_function_key_comp,
        __test_function_value_comp,
        __test_function_size,
        __test_function_empty,
        __test_function_begin_constant,
        __test_function_begin_mutable,
        __test_function_end_constant,
        __test_function_end_mutable,
        __test_function_rbegin_constant,
        __test_function_rbegin_mutable,
        __test_function_rend_constant,
        __test_function_rend_mutable,
        __test_type_iterator,
        __test_type_const_iterator,
        __test_type_reverse_iterator,
        __test_type_const_reverse_iterator,
        __test_function_insert_range,
        __test_function_insert_single,
        __test_function_insert_single_hint,
        __test_function_erase_range,
        __test_function_erase_single_position,
        __test_function_erase_single_key,
        __test_function_clear,
        __test_function_find_constant,
        __test_function_find_mutable,
        __test_function_count,
        __test_function_lower_bound_constant,
        __test_function_lower_bound_mutable,
        __test_function_upper_bound_constant,
        __test_function_upper_bound_mutable,
        __test_function_equal_range_constant,
        __test_function_equal_range_mutable,
        __test_function_swap,
        __test_operator_assign,
        __test_operator_equivalent,
        __test_operator_different,
        __test_operator_lower,
        __test_operator_greater,
        __test_operator_lower_or_equivalent,
        __test_operator_greater_or_equivalent,
        NULL
    };
    u32                   koCount;
    u32                   idx;
    struct timespec const delay = {SLEEP_TIME_SEC, SLEEP_TIME_NANOSEC};

    nanosleep(&delay, NULL);

    std::cerr << LIGHT_BLUE_FG;
    std::cout << "###################################################" << '\n';
    std::cout << "##                      SET                      ##" << '\n';
    std::cout << "###################################################" << '\n';
    std::cerr << RESET;

    for (koCount = 0, idx = 0; tests[idx]; ++idx) {
        nanosleep(&delay, NULL);

        switch (tests[idx]()) {
        case IMPL_OK:
            std::cerr << GREEN_FG;
            std::cout << "[OK]";
            std::cerr << RESET;
            break;

        case ISO_OK:
            std::cerr << YELLOW_FG;
            std::cout << "[OK]";
            std::cerr << RESET;
            break;

        case KO:
            std::cerr << MAGENTA_FG;
            std::cout << "[KO]";
            std::cerr << RESET;
            ++koCount;
            break;
        }
        if (!RATIOS.empty()) {
            std::cout << ' ';
            benchmark_best_case();
            std::cout << ' ';
            benchmark_worst_case();
            std::cout << ' ';
            benchmark_average_case();
            RATIOS.clear();
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    return koCount;
}

#endif
