#define DISABLE
#ifndef DISABLE

# include "map.hpp"
# include "type/test/benchmark/ratio_multiset.hh"
# include "utility.hpp"
# include <ctime>
# include <exception>
# include <map>
# include <utility>

namespace tester { namespace test {

template <typename T0, typename T1>
struct equal_to {
    bool operator()(
        ft::pair<T0, T1> const &a, std::pair<T0, T1> const &b
    ) const
    {
        return a.first == b.first && a.second == b.second;
    }
};

namespace constructor {

template <typename Map>
inline static Map test_variant(
    time_t &duration
)
{
    clock_t const start = clock();
    Map const     map   = Map();

    duration  = clock() - start;
    duration += !duration;
    return map;
}

template <typename Map, typename InputIterator>
inline static Map test_variant(
    time_t &duration, InputIterator first, InputIterator ptend
)
{
    clock_t const start = clock();
    Map const     map   = Map(first, ptend);

    duration  = clock() - start;
    duration += !duration;
    return map;
}

template <typename Map>
inline static Map test_variant(
    time_t &duration, Map const &other
)
{
    clock_t const start = clock();
    Map const     map   = Map(other);

    duration  = clock() - start;
    duration += !duration;
    return map;
}
} // namespace constructor

inline static u8 __test_constructor_default()
{
    i32 ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        START = clock();
        ft::map<i32, i32> const ft_map;
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START = clock();
        std::map<i32, i32> const std_map;
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (sizeof(ft_map) != sizeof(std_map) || memcmp(&ft_map, &std_map, sizeof(ft_map))) {
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
            std::vector<ft::Pair<i32, u8> >  ft_vec;
            std::vector<std::pair<i32, u8> > std_vec;

            for (size_t i = 0; i < Array<i32>::len && i < Array<u8>::len; ++i) {
                ft_vec.push_back(ft::Pair<i32, u8>(Array<i32>::at(i), Array<u8>::at(i)));
                std_vec.push_back(std::pair<i32, u8>(Array<i32>::at(i), Array<u8>::at(i)));
            }

            tester::input_iterator_restrictor<std::vector<ft::Pair<i32, u8> >::iterator> const
                ft_it0(ft_vec.begin());
            tester::input_iterator_restrictor<std::vector<ft::Pair<i32, u8> >::iterator> const
                ft_it1(ft_vec.end());
            tester::input_iterator_restrictor<std::vector<std::pair<i32, u8> >::iterator> const
                std_it0(std_vec.begin());
            tester::input_iterator_restrictor<std::vector<std::pair<i32, u8> >::iterator> const
                std_it1(std_vec.end());

            START = clock();
            std::map<i32, u8> const std_map(std_it0, std_it1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            START = clock();
            ft::map<i32, u8> const ft_map(ft_it0, ft_it1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_map) != sizeof(std_map)) {
                ret = ISO_OK;
            }
        }
        // Range of forward_iterator_restrictor
        {
            tester::forward_iterator_restrictor<ft::Pair<i32, void *> const *> const  ft_it;
            tester::forward_iterator_restrictor<std::pair<i32, void *> const *> const std_it;

            START = clock();
            ft::map<i32, void *> const ft_map(ft_it, ft_it);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::map<i32, void *> const std_map(std_it, std_it);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_map) != sizeof(std_map)) {
                ret = ISO_OK;
            }
        }
        // Range of random_access_iterator_restrictor
        {
            std::vector<ft::Pair<u32, i64> >  ft_vec;
            std::vector<std::pair<u32, i64> > std_vec;

            for (size_t i = 0; i < Array<u32>::len && i < Array<i64>::len; ++i) {
                ft_vec.push_back(ft::Pair<u32, i64>(Array<u32>::at(i), Array<i64>::at(i)));
                std_vec.push_back(std::pair<u32, i64>(Array<u32>::at(i), Array<i64>::at(i)));
            }

            tester::random_access_iterator_restrictor<
                std::vector<ft::Pair<u32, i64> >::iterator
            > const ft_it0(ft_vec.begin());
            tester::random_access_iterator_restrictor<
                std::vector<ft::Pair<u32, i64> >::iterator
            > const ft_it1(ft_vec.end());
            tester::random_access_iterator_restrictor<
                std::vector<std::pair<u32, i64> >::iterator
            > const std_it0(std_vec.begin());
            tester::random_access_iterator_restrictor<
                std::vector<std::pair<u32, i64> >::iterator
            > const std_it1(std_vec.end());

            START = clock();
            ft::map<u32, i64> const ft_map(ft_it0, ft_it1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::map<u32, i64> const std_map(std_it0, std_it1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_map) != sizeof(std_map)) {
                ret = ISO_OK;
            }
        }
        // Range of Pair *
        {
            std::vector<ft::Pair<char, i32> >  ft_vec;
            std::vector<std::pair<char, i32> > std_vec;

            for (size_t i = 0; i < Array<char>::len && i < Array<i32>::len; ++i) {
                ft_vec.push_back(ft::Pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
                std_vec.push_back(std::pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
            }

            START = clock();
            ft::map<i32, char> const ft_map(ft_vec.begin().base(), &*ft_vec.end().base());
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::map<i32, char> const std_map(std_vec.begin().base(), &*std_vec.end().base());
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_map) != sizeof(std_map)) {
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
    size_t i;
    i32    ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        // Default map
        {
            ft::map<float, std::string> const  ft_map0;
            std::map<float, std::string> const std_map0;

            START = clock();
            ft::map<float, std::string> const ft_map1(ft_map0);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::map<float, std::string> const std_map1(std_map0);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_map1) != sizeof(std_map1)) {
                ret = ISO_OK;
            }
        }
        // Filled map
        {
            std::vector<ft::Pair<float, std::string> >  ft_vec;
            std::vector<std::pair<float, std::string> > std_vec;

            for (i = 0; i < Array<f32>::len && i < Array<std::string>::len; ++i) {
                ft_vec.push_back(
                    ft::Pair<float, std::string>(Array<f32>::at(i), Array<std::string>::at(i))
                );
                std_vec.push_back(
                    std::pair<float, std::string>(Array<f32>::at(i), Array<std::string>::at(i))
                );
            }

            ft::map<float, std::string> const  ft_map0(ft_vec.begin(), ft_vec.end());
            std::map<float, std::string> const std_map0(std_vec.begin(), std_vec.end());

            START = clock();
            ft::map<float, std::string> const ft_map1(ft_map0);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::map<float, std::string> const std_map1(std_map0);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            if (sizeof(ft_map1) != sizeof(std_map1)) {
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

    typedef ft::map<float, i16>                    map_type_0;
    typedef ft::map<float, i16, std::less<float> > map_type_1;

    if (!tester::is_same<map_type_0, map_type_1>::value) {
        return KO;
    }

    return IMPL_OK;
}

inline static u8 __test_default_template_type_Alloc()
{
    title(__func__);

    typedef ft::map<float, i16> map_type_0;
    typedef ft::map<float, i16, std::less<float>, std::allocator<ft::Pair<float const, i16> > >
        map_type_1;

    if (!tester::is_same<map_type_0, map_type_1>::value) {
        return KO;
    }

    return IMPL_OK;
}

inline static u8 __test_type_key_type()
{
    title(__func__);
    try {
        typedef ft::map<i64, f128> map_type;

        if (!tester::is_same<map_type::key_type, i64>::value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_mapped_type()
{
    title(__func__);
    try {
        typedef ft::map<i64, f128> map_type;

        if (!tester::is_same<map_type::mapped_type, f128>::value) {
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
        typedef ft::map<i64, f128> map_type;

        if (!tester::is_same<map_type::ValueType, ft::Pair<i64 const, f128> >::value) {
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
        typedef ft::map<i64, f128, std::less<i32> > map_type;

        if (!tester::is_same<map_type::key_compare, std::less<i32> >::value) {
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
        typedef ft::map<i64, f128, std::less<i32>, std::allocator<char> > map_type;

        if (!tester::is_same<map_type::allocator_type, std::allocator<char> >::value) {
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
        typedef ft::map<i64, f128, std::less<i32>, std::allocator<char> > map_type;

        if (!tester::is_same<map_type::reference, std::allocator<char>::reference>::value) {
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
        typedef ft::map<i64, f128, std::less<i32>, std::allocator<char> > map_type;

        if (!tester::is_same<map_type::const_reference, std::allocator<char>::const_reference>::
                value) {
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
        typedef ft::map<i64, f128, std::less<i32>, std::allocator<char> > map_type;

        if (!tester::is_same<map_type::pointer, std::allocator<char>::pointer>::value) {
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
        typedef ft::map<i64, f128, std::less<i32>, std::allocator<char> > map_type;

        if (!tester::is_same<map_type::const_pointer, std::allocator<char>::const_pointer>::value) {
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
        // Map of u8 | i8
        {
            ft::map<u8, i8> const       ft_map;
            std::map<u8, i8> const      std_map;
            ft::map<u8, i8>::size_type  ft_ret;
            std::map<u8, i8>::size_type std_ret;

            START        = clock();
            ft_ret       = ft_map.max_size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.max_size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                ret = ISO_OK;
            }
        }
        // Map of signed long i32 | unsigned long i32
        {
            ft::map<i64, u64> const       ft_map;
            std::map<i64, u64> const      std_map;
            ft::map<i64, u64>::size_type  ft_ret;
            std::map<i64, u64>::size_type std_ret;

            START        = clock();
            ft_ret       = ft_map.max_size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.max_size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                ret = ISO_OK;
            }
        }
        // Map of f128 | std::string
        {
            ft::map<f128, std::string> const       ft_map;
            std::map<f128, std::string> const      std_map;
            ft::map<f128, std::string>::size_type  ft_ret;
            std::map<f128, std::string>::size_type std_ret;

            START        = clock();
            ft_ret       = ft_map.max_size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.max_size();
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
    size_t i;

    title(__func__);
    try {
        // std::less
        {
            ft::map<char, i64, std::less<char> > const         ft_map;
            std::map<char, i64, std::less<char> > const        std_map;
            ft::map<char, i64, std::less<char> >::key_compare  ft_ret;
            std::map<char, i64, std::less<char> >::key_compare std_ret;

            START        = clock();
            ft_ret       = ft_map.key_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.key_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (i = 1; i < Array<char>::len; ++i) {
                if (ft_ret(Array<char>::at(i - 1), Array<char>::at(i))
                    != std_ret(Array<char>::at(i - 1), Array<char>::at(i))) {
                    return KO;
                }
            }
        }
        // std::less_equal
        {
            ft::map<char, i64, std::less_equal<char> > const         ft_map;
            std::map<char, i64, std::less_equal<char> > const        std_map;
            ft::map<char, i64, std::less_equal<char> >::key_compare  ft_ret;
            std::map<char, i64, std::less_equal<char> >::key_compare std_ret;

            START        = clock();
            ft_ret       = ft_map.key_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.key_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (i = 1; i < Array<char>::len; ++i) {
                if (ft_ret(Array<char>::at(i - 1), Array<char>::at(i))
                    != std_ret(Array<char>::at(i - 1), Array<char>::at(i))) {
                    return KO;
                }
            }
        }
        // std::greater
        {
            ft::map<char, i64, std::greater<char> > const         ft_map;
            std::map<char, i64, std::greater<char> > const        std_map;
            ft::map<char, i64, std::greater<char> >::key_compare  ft_ret;
            std::map<char, i64, std::greater<char> >::key_compare std_ret;

            START        = clock();
            ft_ret       = ft_map.key_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.key_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (i = 1; i < Array<char>::len; ++i) {
                if (ft_ret(Array<char>::at(i - 1), Array<char>::at(i))
                    != std_ret(Array<char>::at(i - 1), Array<char>::at(i))) {
                    return KO;
                }
            }
        }
        // std::greater_equal
        {
            ft::map<char, i64, std::greater_equal<char> > const         ft_map;
            std::map<char, i64, std::greater_equal<char> > const        std_map;
            ft::map<char, i64, std::greater_equal<char> >::key_compare  ft_ret;
            std::map<char, i64, std::greater_equal<char> >::key_compare std_ret;

            START        = clock();
            ft_ret       = ft_map.key_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.key_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (i = 1; i < Array<char>::len; ++i) {
                if (ft_ret(Array<char>::at(i - 1), Array<char>::at(i))
                    != std_ret(Array<char>::at(i - 1), Array<char>::at(i))) {
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
    size_t i;

    title(__func__);
    try {
        // std::less
        {
            ft::map<char, i64, std::less<char> > const  ft_map;
            std::map<char, i64, std::less<char> > const std_map;

            START                                                       = clock();
            ft::map<char, i64, std::less<char> >::value_compare ft_ret  = ft_map.value_comp();
            DURATION_FT                                                 = clock() - START;
            DURATION_FT                                                += !DURATION_FT;

            START                                                         = clock();
            std::map<char, i64, std::less<char> >::value_compare std_ret  = std_map.value_comp();
            DURATION_STD                                                  = clock() - START;
            DURATION_STD                                                 += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (i = 1; i < Array<char>::len && i < Array<i64>::len; ++i) {
                ft::map<char, i64, std::less<char> >::ValueType const ft_val0(
                    Array<char>::at(i - 1), Array<i64>::at(i - 1)
                );
                ft::map<char, i64, std::less<char> >::ValueType const ft_val1(
                    Array<char>::at(i), Array<i64>::at(i)
                );
                std::map<char, i64, std::less<char> >::ValueType const std_val0(
                    Array<char>::at(i - 1), Array<i64>::at(i - 1)
                );
                std::map<char, i64, std::less<char> >::ValueType const std_val1(
                    Array<char>::at(i), Array<i64>::at(i)
                );

                if (ft_ret(ft_val0, ft_val1) != std_ret(std_val0, std_val1)) {
                    return KO;
                }
            }
        }
        // std::less_equal
        {
            ft::map<char, i64, std::less_equal<char> > const  ft_map;
            std::map<char, i64, std::less_equal<char> > const std_map;

            START                                                             = clock();
            ft::map<char, i64, std::less_equal<char> >::value_compare ft_ret  = ft_map.value_comp();
            DURATION_FT                                                       = clock() - START;
            DURATION_FT                                                      += !DURATION_FT;

            START = clock();
            std::map<char, i64, std::less_equal<char> >::value_compare std_ret =
                std_map.value_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (i = 1; i < Array<char>::len && i < Array<i64>::len; ++i) {
                ft::map<char, i64, std::less_equal<char> >::ValueType const ft_val0(
                    Array<char>::at(i - 1), Array<i64>::at(i - 1)
                );
                ft::map<char, i64, std::less_equal<char> >::ValueType const ft_val1(
                    Array<char>::at(i), Array<i64>::at(i)
                );
                std::map<char, i64, std::less_equal<char> >::ValueType const std_val0(
                    Array<char>::at(i - 1), Array<i64>::at(i - 1)
                );
                std::map<char, i64, std::less_equal<char> >::ValueType const std_val1(
                    Array<char>::at(i), Array<i64>::at(i)
                );

                if (ft_ret(ft_val0, ft_val1) != std_ret(std_val0, std_val1)) {
                    return KO;
                }
            }
        }
        // std::greater
        {
            ft::map<char, i64, std::greater<char> > const  ft_map;
            std::map<char, i64, std::greater<char> > const std_map;

            START                                                          = clock();
            ft::map<char, i64, std::greater<char> >::value_compare ft_ret  = ft_map.value_comp();
            DURATION_FT                                                    = clock() - START;
            DURATION_FT                                                   += !DURATION_FT;

            START                                                            = clock();
            std::map<char, i64, std::greater<char> >::value_compare std_ret  = std_map.value_comp();
            DURATION_STD                                                     = clock() - START;
            DURATION_STD                                                    += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (i = 1; i < Array<char>::len && i < Array<i64>::len; ++i) {
                ft::map<char, i64, std::greater<char> >::ValueType const ft_val0(
                    Array<char>::at(i - 1), Array<i64>::at(i - 1)
                );
                ft::map<char, i64, std::greater<char> >::ValueType const ft_val1(
                    Array<char>::at(i), Array<i64>::at(i)
                );
                std::map<char, i64, std::greater<char> >::ValueType const std_val0(
                    Array<char>::at(i - 1), Array<i64>::at(i - 1)
                );
                std::map<char, i64, std::greater<char> >::ValueType const std_val1(
                    Array<char>::at(i), Array<i64>::at(i)
                );

                if (ft_ret(ft_val0, ft_val1) != std_ret(std_val0, std_val1)) {
                    return KO;
                }
            }
        }
        // std::greater_equal
        {
            ft::map<char, i64, std::greater_equal<char> > const  ft_map;
            std::map<char, i64, std::greater_equal<char> > const std_map;

            START = clock();
            ft::map<char, i64, std::greater_equal<char> >::value_compare ft_ret =
                ft_map.value_comp();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::map<char, i64, std::greater_equal<char> >::value_compare std_ret =
                std_map.value_comp();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            for (i = 1; i < Array<char>::len && i < Array<i64>::len; ++i) {
                ft::map<char, i64, std::greater_equal<char> >::ValueType const ft_val0(
                    Array<char>::at(i - 1), Array<i64>::at(i - 1)
                );
                ft::map<char, i64, std::greater_equal<char> >::ValueType const ft_val1(
                    Array<char>::at(i), Array<i64>::at(i)
                );
                std::map<char, i64, std::greater_equal<char> >::ValueType const std_val0(
                    Array<char>::at(i - 1), Array<i64>::at(i - 1)
                );
                std::map<char, i64, std::greater_equal<char> >::ValueType const std_val1(
                    Array<char>::at(i), Array<i64>::at(i)
                );

                if (ft_ret(ft_val0, ft_val1) != std_ret(std_val0, std_val1)) {
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
    size_t i;

    title(__func__);
    try {
        std::list<ft::Pair<u16, f64> >  ft_lst;
        std::list<std::pair<u16, f64> > std_lst;
        ft::map<u16, f64>::size_type    ft_ret;
        std::map<u16, f64>::size_type   std_ret;

        for (i = 0; i < Array<u16>::len && i < Array<f64>::len; ++i) {
            ft::map<u16, f64> const  ft_map(ft_lst.begin(), ft_lst.end());
            std::map<u16, f64> const std_map(std_lst.begin(), std_lst.end());

            START        = clock();
            ft_ret       = ft_map.size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_lst.push_back(ft::Pair<u16, f64>(Array<u16>::at(i), Array<f64>::at(i)));
            std_lst.push_back(std::pair<u16, f64>(Array<u16>::at(i), Array<f64>::at(i)));
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<u32, std::string> >  ft_vec;
        std::vector<std::pair<u32, std::string> > std_vec;
        bool                                      ft_ret;
        bool                                      std_ret;

        for (i = 0; i < Array<u32>::len && i < Array<std::string>::len; ++i) {
            ft_vec.push_back(
                ft::Pair<u32, std::string>(Array<u32>::at(i), Array<std::string>::at(i))
            );
            std_vec.push_back(
                std::pair<u32, std::string>(Array<u32>::at(i), Array<std::string>::at(i))
            );
        }

        for (i = 0; i < Array<u32>::len && i < Array<std::string>::len; ++i) {
            ft::map<u32, std::string> const  ft_map(&ft_vec[i * (i % 2)], &ft_vec[i]);
            std::map<u32, std::string> const std_map(&std_vec[i * (i % 2)], &std_vec[i]);

            START        = clock();
            ft_ret       = ft_map.empty();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.empty();
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i32> >  ft_vec;
        std::vector<std::pair<char, i32> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i32>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
            std_vec.push_back(std::pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
        }

        ft::map<char, i32>::const_iterator  ft_ret;
        std::map<char, i32>::const_iterator std_ret;

        for (i = 1; i < ft_vec.size() && i < std_vec.size(); ++i) {
            ft::map<char, i32> const  ft_map(&ft_vec[i - 1], &*ft_vec.end());
            std::map<char, i32> const std_map(&std_vec[i - 1], &*std_vec.end());

            START        = clock();
            ft_ret       = ft_map.begin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.begin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret->first != std_ret->first || ft_ret->second != std_ret->second) {
                return KO;
            }
        }

        ft::map<char, i32> const  ft_map;
        std::map<char, i32> const std_map;

        START        = clock();
        ft_ret       = ft_map.begin();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_map.begin();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_begin_mutable()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i32> >  ft_vec;
        std::vector<std::pair<char, i32> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i32>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
            std_vec.push_back(std::pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
        }

        ft::map<char, i32>::iterator  ft_ret;
        std::map<char, i32>::iterator std_ret;

        for (i = 1; i < ft_vec.size() && i < std_vec.size(); ++i) {
            ft::map<char, i32>  ft_map(&ft_vec[i - 1], &*ft_vec.end());
            std::map<char, i32> std_map(&std_vec[i - 1], &*std_vec.end());

            START        = clock();
            ft_ret       = ft_map.begin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.begin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret->first != std_ret->first || ++ft_ret->second != ++std_ret->second) {
                return KO;
            }
        }

        ft::map<char, i32>  ft_map;
        std::map<char, i32> std_map;

        START        = clock();
        ft_ret       = ft_map.begin();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_map.begin();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_end_constant()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i32> >  ft_vec;
        std::vector<std::pair<char, i32> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i32>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
            std_vec.push_back(std::pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
        }

        ft::map<char, i32>::const_iterator  ft_ret;
        std::map<char, i32>::const_iterator std_ret;

        for (i = 1; i < ft_vec.size() && i < std_vec.size(); ++i) {
            ft::map<char, i32> const  ft_map(&ft_vec[0], &ft_vec[i]);
            std::map<char, i32> const std_map(&std_vec[0], &std_vec[i]);

            START        = clock();
            ft_ret       = ft_map.end();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.end();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            --ft_ret;
            --std_ret;

            if (ft_ret->first != std_ret->first || ft_ret->second != std_ret->second) {
                return KO;
            }
        }

        ft::map<char, i32> const  ft_map;
        std::map<char, i32> const std_map;

        START        = clock();
        ft_ret       = ft_map.end();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_map.end();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_end_mutable()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i32> >  ft_vec;
        std::vector<std::pair<char, i32> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i32>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
            std_vec.push_back(std::pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
        }

        ft::map<char, i32>::iterator  ft_ret;
        std::map<char, i32>::iterator std_ret;

        for (i = 1; i < ft_vec.size() && i < std_vec.size(); ++i) {
            ft::map<char, i32>  ft_map(&ft_vec[0], &ft_vec[i]);
            std::map<char, i32> std_map(&std_vec[0], &std_vec[i]);

            START        = clock();
            ft_ret       = ft_map.end();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.end();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            --ft_ret;
            --std_ret;

            if (ft_ret->first != std_ret->first || ++ft_ret->second != ++std_ret->second) {
                return KO;
            }
        }

        ft::map<char, i32>  ft_map;
        std::map<char, i32> std_map;

        START        = clock();
        ft_ret       = ft_map.end();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_map.end();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_rbegin_constant()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i32> >  ft_vec;
        std::vector<std::pair<char, i32> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i32>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
            std_vec.push_back(std::pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
        }

        ft::map<char, i32>::const_reverse_iterator  ft_ret;
        std::map<char, i32>::const_reverse_iterator std_ret;

        for (i = 1; i < ft_vec.size() && i < std_vec.size(); ++i) {
            ft::map<char, i32> const  ft_map(&ft_vec[0], &ft_vec[i]);
            std::map<char, i32> const std_map(&std_vec[0], &std_vec[i]);

            START        = clock();
            ft_ret       = ft_map.rbegin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.rbegin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret->first != std_ret->first || ft_ret->second != std_ret->second) {
                return KO;
            }
        }

        ft::map<char, i32> const  ft_map;
        std::map<char, i32> const std_map;

        START        = clock();
        ft_ret       = ft_map.rbegin();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_map.rbegin();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_rbegin_mutable()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i32> >  ft_vec;
        std::vector<std::pair<char, i32> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i32>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
            std_vec.push_back(std::pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
        }

        ft::map<char, i32>::reverse_iterator  ft_ret;
        std::map<char, i32>::reverse_iterator std_ret;

        for (i = 1; i < ft_vec.size() && i < std_vec.size(); ++i) {
            ft::map<char, i32>  ft_map(&ft_vec[0], &ft_vec[i]);
            std::map<char, i32> std_map(&std_vec[0], &std_vec[i]);

            START        = clock();
            ft_ret       = ft_map.rbegin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.rbegin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret->first != std_ret->first || ++ft_ret->second != ++std_ret->second) {
                return KO;
            }
        }

        ft::map<char, i32>  ft_map;
        std::map<char, i32> std_map;

        START        = clock();
        ft_ret       = ft_map.rbegin();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_map.rbegin();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_rend_constant()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i32> >  ft_vec;
        std::vector<std::pair<char, i32> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i32>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
            std_vec.push_back(std::pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
        }

        ft::map<char, i32>::const_reverse_iterator  ft_ret;
        std::map<char, i32>::const_reverse_iterator std_ret;

        for (i = 1; i < ft_vec.size() && i < std_vec.size(); ++i) {
            ft::map<char, i32> const  ft_map(&ft_vec[i - 1], &*ft_vec.end());
            std::map<char, i32> const std_map(&std_vec[i - 1], &*std_vec.end());

            START        = clock();
            ft_ret       = ft_map.rend();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.rend();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            --ft_ret;
            --std_ret;

            if (ft_ret->first != std_ret->first || ft_ret->second != std_ret->second) {
                return KO;
            }
        }

        ft::map<char, i32> const  ft_map;
        std::map<char, i32> const std_map;

        START        = clock();
        ft_ret       = ft_map.rend();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_map.rend();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_rend_mutable()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i32> >  ft_vec;
        std::vector<std::pair<char, i32> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i32>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
            std_vec.push_back(std::pair<char, i32>(Array<char>::at(i), Array<i32>::at(i)));
        }

        ft::map<char, i32>::reverse_iterator  ft_ret;
        std::map<char, i32>::reverse_iterator std_ret;

        for (i = 1; i < ft_vec.size() && i < std_vec.size(); ++i) {
            ft::map<char, i32>  ft_map(&ft_vec[i - 1], &*ft_vec.end());
            std::map<char, i32> std_map(&std_vec[i - 1], &*std_vec.end());

            START        = clock();
            ft_ret       = ft_map.rend();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.rend();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            --ft_ret;
            --std_ret;

            if (ft_ret->first != std_ret->first || ++ft_ret->second != ++std_ret->second) {
                return KO;
            }
        }

        ft::map<char, i32>  ft_map;
        std::map<char, i32> std_map;

        START        = clock();
        ft_ret       = ft_map.rend();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_map.rend();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_iterator()
{
    size_t i;
    i32    ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        std::vector<ft::Pair<float, i8> >  ft_vec;
        std::vector<std::pair<float, i8> > std_vec;

        for (i = 0; i < Array<f32>::len && i < Array<i8>::len; ++i) {
            ft_vec.push_back(ft::Pair<float, i8>(Array<f32>::at(i), Array<i8>::at(i)));
            std_vec.push_back(std::pair<float, i8>(Array<f32>::at(i), Array<i8>::at(i)));
        }

        ft::map<float, i8>            ft_map(ft_vec.begin(), ft_vec.end());
        std::map<float, i8>           std_map(std_vec.begin(), std_vec.end());
        ft::map<float, i8>::iterator  ft_it;
        std::map<float, i8>::iterator std_it;

        if (sizeof(ft_it) != sizeof(std_it)) {
            ret = ISO_OK;
        }

        for (ft_it = ft_map.begin(), std_it = std_map.begin(), i = 0;
             ft_it != ft_map.end() && std_it != std_map.end();
             ++ft_it, ++std_it, ++i) {
            if (i) {
                tester::check_bidirectional_iterator_requirements(ft_it);
                tester::check_bidirectional_iterator_requirements(std_it);
            }

            if ((ft_it->first != std_it->first)
                || (ft_it->second)++ != (std_it->second)++
                || ++(ft_it->second) != ++(std_it->second)
                || (ft_it->second)-- != (std_it->second)--
                || --(ft_it->second) != --(std_it->second)) {
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
    size_t i;
    i32    ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        std::vector<ft::Pair<float, i8> >  ft_vec;
        std::vector<std::pair<float, i8> > std_vec;

        for (i = 0; i < Array<f32>::len && i < Array<i8>::len; ++i) {
            ft_vec.push_back(ft::Pair<float, i8>(Array<f32>::at(i), Array<i8>::at(i)));
            std_vec.push_back(std::pair<float, i8>(Array<f32>::at(i), Array<i8>::at(i)));
        }

        ft::map<float, i8>                  ft_map(ft_vec.begin(), ft_vec.end());
        std::map<float, i8>                 std_map(std_vec.begin(), std_vec.end());
        ft::map<float, i8>::const_iterator  ft_it;
        std::map<float, i8>::const_iterator std_it;

        if (sizeof(ft_it) != sizeof(std_it)) {
            ret = ISO_OK;
        }

        for (ft_it = ft_map.begin(), std_it = std_map.begin(), i = 0;
             ft_it != ft_map.end() && std_it != std_map.end();
             ++ft_it, ++std_it) {
            if (i) {
                tester::check_bidirectional_iterator_requirements(ft_it);
                tester::check_bidirectional_iterator_requirements(std_it);
            }

            if (ft_it->first != std_it->first || ft_it->second != std_it->second) {
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
    size_t i;
    i32    ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        std::vector<ft::Pair<float, i8> >  ft_vec;
        std::vector<std::pair<float, i8> > std_vec;

        for (i = 0; i < Array<f32>::len && i < Array<i8>::len; ++i) {
            ft_vec.push_back(ft::Pair<float, i8>(Array<f32>::at(i), Array<i8>::at(i)));
            std_vec.push_back(std::pair<float, i8>(Array<f32>::at(i), Array<i8>::at(i)));
        }

        ft::map<float, i8>                    ft_map(ft_vec.begin(), ft_vec.end());
        std::map<float, i8>                   std_map(std_vec.begin(), std_vec.end());
        ft::map<float, i8>::reverse_iterator  ft_rit;
        std::map<float, i8>::reverse_iterator std_it;

        if (sizeof(ft_rit) != sizeof(std_it)) {
            ret = ISO_OK;
        }

        for (ft_rit = ft_map.rbegin(), std_it = std_map.rbegin(), i = 0;
             ft_rit != ft_map.rend() && std_it != std_map.rend();
             ++ft_rit, ++std_it, ++i) {
            if (i) {
                tester::check_bidirectional_iterator_requirements(ft_rit);
                tester::check_bidirectional_iterator_requirements(std_it);
            }

            if ((ft_rit->first != std_it->first)
                || (ft_rit->second)++ != (std_it->second)++
                || ++(ft_rit->second) != ++(std_it->second)
                || (ft_rit->second)-- != (std_it->second)--
                || --(ft_rit->second) != --(std_it->second)) {
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
    size_t i;
    i32    ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        std::vector<ft::Pair<float, i8> >  ft_vec;
        std::vector<std::pair<float, i8> > std_vec;

        for (i = 0; i < Array<f32>::len && i < Array<i8>::len; ++i) {
            ft_vec.push_back(ft::Pair<float, i8>(Array<f32>::at(i), Array<i8>::at(i)));
            std_vec.push_back(std::pair<float, i8>(Array<f32>::at(i), Array<i8>::at(i)));
        }

        ft::map<float, i8>                          ft_map(ft_vec.begin(), ft_vec.end());
        std::map<float, i8>                         std_map(std_vec.begin(), std_vec.end());
        ft::map<float, i8>::const_reverse_iterator  ft_crit;
        std::map<float, i8>::const_reverse_iterator std_crit;

        if (sizeof(ft_crit) != sizeof(std_crit)) {
            ret = ISO_OK;
        }

        for (ft_crit = ft_map.rbegin(), std_crit = std_map.rbegin(), i = 0;
             ft_crit != ft_map.rend() && std_crit != std_map.rend();
             ++ft_crit, ++std_crit) {
            if (i) {
                tester::check_bidirectional_iterator_requirements(ft_crit);
                tester::check_bidirectional_iterator_requirements(std_crit);
            }

            if (ft_crit->first != std_crit->first || ft_crit->second != std_crit->second) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<std::string, u64> >  ft_vec;
        std::vector<std::pair<std::string, u64> > std_vec;
        ft::map<std::string, u64>                 ft_map;
        std::map<std::string, u64>                std_map;

        for (i = 0; i < Array<std::string>::len && i < Array<u64>::len; ++i) {
            ft_vec.push_back(
                ft::Pair<std::string, u64>(Array<std::string>::at(i), Array<u64>::at(i))
            );
            std_vec.push_back(
                std::pair<std::string, u64>(Array<std::string>::at(i), Array<u64>::at(i))
            );
        }

        for (i = 1; i < Array<std::string>::len && i < Array<u64>::len; ++i) {
            START = clock();
            ft_map.insert(&ft_vec[i - 1], &ft_vec[i + 1]);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_map.insert(&std_vec[i - 1], &std_vec[i + 1]);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_map.size() != std_map.size()
                || !std::equal(
                    ft_map.begin(), ft_map.end(), std_map.begin(), cmp<std::string, u64>
                )) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<std::string, u64> >              ft_vec;
        std::vector<std::pair<std::string, u64> >             std_vec;
        ft::map<std::string, u64>                             ft_map;
        std::map<std::string, u64>                            std_map;
        ft::Pair<ft::map<std::string, u64>::iterator, bool>   ft_ret;
        std::pair<std::map<std::string, u64>::iterator, bool> std_ret;

        for (i = 0; i < Array<std::string>::len && i < Array<u64>::len; ++i) {
            ft_vec.push_back(
                ft::Pair<std::string, u64>(Array<std::string>::at(i), Array<u64>::at(i))
            );
            std_vec.push_back(
                std::pair<std::string, u64>(Array<std::string>::at(i), Array<u64>::at(i))
            );
        }

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); ++i) {
            START        = clock();
            ft_ret       = ft_map.insert(ft_vec[i]);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.insert(std_vec[i]);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret.first->first != std_ret.first->first
                || ft_ret.first->second != std_ret.first->second
                || ft_ret.second != std_ret.second
                || ft_map.size() != std_map.size()
                || !std::equal(
                    ft_map.begin(), ft_map.end(), std_map.begin(), cmp<std::string, u64>
                )) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<std::string, u64> >  ft_vec;
        std::vector<std::pair<std::string, u64> > std_vec;
        ft::map<std::string, u64>                 ft_map;
        std::map<std::string, u64>                std_map;
        ft::map<std::string, u64>::iterator       ft_ret;
        std::map<std::string, u64>::iterator      std_ret;

        for (i = 0; i < Array<std::string>::len && i < Array<u64>::len; ++i) {
            ft_vec.push_back(
                ft::Pair<std::string, u64>(Array<std::string>::at(i), Array<u64>::at(i))
            );
            std_vec.push_back(
                std::pair<std::string, u64>(Array<std::string>::at(i), Array<u64>::at(i))
            );
        }

        START = clock();
        ft_map.insert(
            ft_map.begin(), ft::Pair<std::string, u64>(std::string("dedicated to lmartin"), 42)
        );
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START = clock();
        std_map.insert(
            std_map.begin(), std::pair<std::string, u64>(std::string("dedicated to lmartin"), 42)
        );
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        ft_ret  = ft_map.begin();
        std_ret = std_map.begin();
        for (i = 0; i < ft_vec.size() * 3 && i < std_vec.size() * 3; ++i) {
            switch (i % 3) {
            case 0:
                START        = clock();
                ft_ret       = ft_map.insert(ft_ret, ft_vec[i / 3]);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std_map.insert(std_ret, std_vec[i / 3]);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;
                break;

            case 1:
                START        = clock();
                ft_ret       = ft_map.insert(ft_map.begin(), *++ft_map.begin());
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std_map.insert(std_map.begin(), *++std_map.begin());
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;
                break;

            case 2:
                START        = clock();
                ft_ret       = ft_map.insert(ft_map.end(), *++ft_map.rbegin());
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std_map.insert(std_map.end(), *++std_map.rbegin());
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;
                break;
            }

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret->first != std_ret->first
                || ft_ret->second != std_ret->second
                || ft_map.size() != std_map.size()
                || !std::equal(
                    ft_map.begin(), ft_map.end(), std_map.begin(), cmp<std::string, u64>
                )) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i64> >  ft_vec;
        std::vector<std::pair<char, i64> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i64>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i64>(Array<char>::at(i), Array<i64>::at(i)));
            std_vec.push_back(std::pair<char, i64>(Array<char>::at(i), Array<i64>::at(i)));
        }

        ft::map<char, i64>            ft_map(ft_vec.begin(), ft_vec.end());
        std::map<char, i64>           std_map(std_vec.begin(), std_vec.end());
        ft::map<char, i64>::iterator  ft_it0;
        ft::map<char, i64>::iterator  ft_it1;
        std::map<char, i64>::iterator std_it0;
        std::map<char, i64>::iterator std_it1;

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); i += 2) {
            ft_it0  = ft_map.begin();
            std_it0 = std_map.begin();
            std::advance(ft_it0, ft_map.size() / 2 - 1);
            std::advance(std_it0, std_map.size() / 2 - 1);
            ft_it1  = ft_it0;
            std_it1 = std_it0;
            std::advance(ft_it1, 2);
            std::advance(std_it1, 2);

            START = clock();
            ft_map.erase(ft_it0, ft_it1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_map.erase(std_it0, std_it1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_map.size() != std_map.size()
                || !std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), cmp<char, i64>)) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i64> >  ft_vec;
        std::vector<std::pair<char, i64> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i64>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i64>(Array<char>::at(i), Array<i64>::at(i)));
            std_vec.push_back(std::pair<char, i64>(Array<char>::at(i), Array<i64>::at(i)));
        }

        ft::map<char, i64>  ft_map(ft_vec.begin(), ft_vec.end());
        std::map<char, i64> std_map(std_vec.begin(), std_vec.end());

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); ++i) {
            START = clock();
            ft_map.erase(ft_map.begin());
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_map.erase(std_map.begin());
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_map.size() != std_map.size()
                || !std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), cmp<char, i64>)) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, i64> >  ft_vec;
        std::vector<std::pair<char, i64> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<i64>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, i64>(Array<char>::at(i), Array<i64>::at(i)));
            std_vec.push_back(std::pair<char, i64>(Array<char>::at(i), Array<i64>::at(i)));
        }

        ft::map<char, i64>  ft_map(ft_vec.begin(), ft_vec.end());
        std::map<char, i64> std_map(std_vec.begin(), std_vec.end());
        size_t              ft_ret;
        size_t              std_ret;

        for (i = 0; i < ft_vec.size() * 2 && i < std_vec.size() * 2; ++i) {
            START        = clock();
            ft_ret       = ft_map.erase(Array<char>::at(i / 2));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.erase(Array<char>::at(i / 2));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret
                || ft_map.size() != std_map.size()
                || !std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), cmp<char, i64>)) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i32, u8> >  ft_vec;
        std::vector<std::pair<i32, u8> > std_vec;

        for (i = 0; i < Array<i32>::len && i < Array<u8>::len; ++i) {
            ft_vec.push_back(ft::Pair<i32, u8>(Array<i32>::at(i), Array<u8>::at(i)));
            std_vec.push_back(std::pair<i32, u8>(Array<i32>::at(i), Array<u8>::at(i)));
        }

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); ++i) {
            ft::map<i32, u8>  ft_map(&ft_vec[0], &ft_vec[i]);
            std::map<i32, u8> std_map(&std_vec[0], &std_vec[i]);

            START = clock();
            ft_map.clear();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_map.clear();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_map.size() != std_map.size()
                || !std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), cmp<i32, u8>)) {
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
    size_t i;
    float  nb;

    title(__func__);
    try {
        std::vector<ft::Pair<float, std::string> >  ft_vec;
        std::vector<std::pair<float, std::string> > std_vec;

        for (i = 0; i < Array<f32>::len && i < Array<std::string>::len; ++i) {
            ft_vec.push_back(
                ft::Pair<float, std::string>(Array<f32>::at(i), Array<std::string>::at(i))
            );
            std_vec.push_back(
                std::pair<float, std::string>(Array<f32>::at(i), Array<std::string>::at(i))
            );
        }

        ft::map<float, std::string> const            ft_map(ft_vec.begin(), ft_vec.end());
        std::map<float, std::string> const           std_map(std_vec.begin(), std_vec.end());
        ft::map<float, std::string>::const_iterator  ft_ret;
        std::map<float, std::string>::const_iterator std_ret;

        for (i = 0; i < Array<f32>::len * 2 && i < Array<std::string>::len * 2; ++i) {
            if (i % 2) {
                nb = static_cast<float>(rand());
                while (std::find(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len), nb)
                       != &Array<f32>::at(Array<f32>::len)) {
                    nb = static_cast<float>(rand());
                }
            }
            else {
                nb = Array<f32>::at(i / 2);
            }

            START        = clock();
            ft_ret       = ft_map.find(nb);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.find(nb);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_map.end()) != (std_ret == std_map.end())
                || (ft_ret != ft_map.end()
                    && (ft_ret->first != std_ret->first || ft_ret->second != std_ret->second))) {
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
    size_t i;
    float  nb;

    title(__func__);
    try {
        std::vector<ft::Pair<float, std::string> >  ft_vec;
        std::vector<std::pair<float, std::string> > std_vec;

        for (i = 0; i < Array<f32>::len && i < Array<std::string>::len; ++i) {
            ft_vec.push_back(
                ft::Pair<float, std::string>(Array<f32>::at(i), Array<std::string>::at(i))
            );
            std_vec.push_back(
                std::pair<float, std::string>(Array<f32>::at(i), Array<std::string>::at(i))
            );
        }

        ft::map<float, std::string>            ft_map(ft_vec.begin(), ft_vec.end());
        std::map<float, std::string>           std_map(std_vec.begin(), std_vec.end());
        ft::map<float, std::string>::iterator  ft_ret;
        std::map<float, std::string>::iterator std_ret;

        for (i = 0; i < Array<f32>::len * 2 && i < Array<std::string>::len * 2; ++i) {
            if (i % 2) {
                nb = static_cast<float>(rand());
                while (std::find(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len), nb)
                       != &Array<f32>::at(Array<f32>::len)) {
                    nb = static_cast<float>(rand());
                }
            }
            else {
                nb = Array<f32>::at(i / 2);
            }

            START        = clock();
            ft_ret       = ft_map.find(nb);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.find(nb);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_map.end()) != (std_ret == std_map.end())
                || (ft_ret != ft_map.end()
                    && (ft_ret->first != std_ret->first
                        || ft_ret->second.append("42") != std_ret->second.append("42")))) {
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
    size_t i;
    float  nb;

    title(__func__);
    try {
        std::vector<ft::Pair<float, std::string> >  ft_vec;
        std::vector<std::pair<float, std::string> > std_vec;

        for (i = 0; i < Array<f32>::len && i < Array<std::string>::len; ++i) {
            ft_vec.push_back(
                ft::Pair<float, std::string>(Array<f32>::at(i), Array<std::string>::at(i))
            );
            std_vec.push_back(
                std::pair<float, std::string>(Array<f32>::at(i), Array<std::string>::at(i))
            );
        }

        ft::map<float, std::string> const       ft_map(ft_vec.begin(), ft_vec.end());
        std::map<float, std::string> const      std_map(std_vec.begin(), std_vec.end());
        ft::map<float, std::string>::size_type  ft_ret;
        std::map<float, std::string>::size_type std_ret;

        for (i = 0; i < ft_vec.size() * 2 && i < std_vec.size() * 2; ++i) {
            if (i % 2) {
                nb = static_cast<float>(rand());
                while (std::find(&Array<f32>::at(0), &Array<f32>::at(Array<f32>::len), nb)
                       != &Array<f32>::at(Array<f32>::len)) {
                    nb = static_cast<float>(rand());
                }
            }
            else {
                nb = Array<f32>::at(i / 2);
            }

            START        = clock();
            ft_ret       = ft_map.count(nb);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.count(nb);
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i64, f128> >  ft_vec;
        std::vector<std::pair<i64, f128> > std_vec;

        for (i = 0; i < Array<i64>::len && i < Array<f128>::len; ++i) {
            ft_vec.push_back(ft::Pair<i64, f128>(Array<i64>::at(i), Array<f128>::at(i)));
            std_vec.push_back(std::pair<i64, f128>(Array<i64>::at(i), Array<f128>::at(i)));
        }

        ft::map<i64, f128> const            ft_map(ft_vec.begin(), ft_vec.end());
        std::map<i64, f128> const           std_map(std_vec.begin(), std_vec.end());
        ft::map<i64, f128>::const_iterator  ft_ret;
        std::map<i64, f128>::const_iterator std_ret;

        for (i = 0; i < Array<i64>::len && i < Array<f128>::len; ++i) {
            START        = clock();
            ft_ret       = ft_map.lower_bound(Array<i64>::at(i));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.lower_bound(Array<i64>::at(i));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_map.end()) != (std_ret == std_map.end())
                || (ft_ret != ft_map.end()
                    && (ft_ret->first != std_ret->first || ft_ret->second != std_ret->second))) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i64, f128> >  ft_vec;
        std::vector<std::pair<i64, f128> > std_vec;

        for (i = 0; i < Array<i64>::len && i < Array<f128>::len; ++i) {
            ft_vec.push_back(ft::Pair<i64, f128>(Array<i64>::at(i), Array<f128>::at(i)));
            std_vec.push_back(std::pair<i64, f128>(Array<i64>::at(i), Array<f128>::at(i)));
        }

        ft::map<i64, f128>            ft_map(ft_vec.begin(), ft_vec.end());
        std::map<i64, f128>           std_map(std_vec.begin(), std_vec.end());
        ft::map<i64, f128>::iterator  ft_ret;
        std::map<i64, f128>::iterator std_ret;

        for (i = 0; i < Array<i64>::len && i < Array<f128>::len; ++i) {
            START        = clock();
            ft_ret       = ft_map.lower_bound(Array<i64>::at(i));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.lower_bound(Array<i64>::at(i));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_map.end()) != (std_ret == std_map.end())
                || (ft_ret != ft_map.end()
                    && (ft_ret->first != std_ret->first
                        || --ft_ret->second != --std_ret->second))) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i64, f128> >  ft_vec;
        std::vector<std::pair<i64, f128> > std_vec;

        for (i = 0; i < Array<i64>::len && i < Array<f128>::len; ++i) {
            ft_vec.push_back(ft::Pair<i64, f128>(Array<i64>::at(i), Array<f128>::at(i)));
            std_vec.push_back(std::pair<i64, f128>(Array<i64>::at(i), Array<f128>::at(i)));
        }

        ft::map<i64, f128> const            ft_map(ft_vec.begin(), ft_vec.end());
        std::map<i64, f128> const           std_map(std_vec.begin(), std_vec.end());
        ft::map<i64, f128>::const_iterator  ft_ret;
        std::map<i64, f128>::const_iterator std_ret;

        for (i = 0; i < Array<i64>::len && i < Array<f128>::len; ++i) {
            START        = clock();
            ft_ret       = ft_map.upper_bound(Array<i64>::at(i));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.upper_bound(Array<i64>::at(i));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_map.end()) != (std_ret == std_map.end())
                || (ft_ret != ft_map.end()
                    && (ft_ret->first != std_ret->first || ft_ret->second != std_ret->second))) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i64, f128> >  ft_vec;
        std::vector<std::pair<i64, f128> > std_vec;

        for (i = 0; i < Array<i64>::len && i < Array<f128>::len; ++i) {
            ft_vec.push_back(ft::Pair<i64, f128>(Array<i64>::at(i), Array<f128>::at(i)));
            std_vec.push_back(std::pair<i64, f128>(Array<i64>::at(i), Array<f128>::at(i)));
        }

        ft::map<i64, f128>            ft_map(ft_vec.begin(), ft_vec.end());
        std::map<i64, f128>           std_map(std_vec.begin(), std_vec.end());
        ft::map<i64, f128>::iterator  ft_ret;
        std::map<i64, f128>::iterator std_ret;

        for (i = 0; i < Array<i64>::len && i < Array<f128>::len; ++i) {
            START        = clock();
            ft_ret       = ft_map.upper_bound(Array<i64>::at(i));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.upper_bound(Array<i64>::at(i));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret == ft_map.end()) != (std_ret == std_map.end())
                || (ft_ret != ft_map.end()
                    && (ft_ret->first != std_ret->first
                        || --ft_ret->second != --std_ret->second))) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i16, u32> >  ft_vec;
        std::vector<std::pair<i16, u32> > std_vec;

        for (i = 0; i < Array<i16>::len && i < Array<u32>::len; ++i) {
            ft_vec.push_back(ft::Pair<i16, u32>(Array<i16>::at(i), Array<u32>::at(i)));
            std_vec.push_back(std::pair<i16, u32>(Array<i16>::at(i), Array<u32>::at(i)));
        }

        ft::map<i16, u32> const  ft_map(ft_vec.begin(), ft_vec.end());
        std::map<i16, u32> const std_map(std_vec.begin(), std_vec.end());
        ft::Pair<ft::map<i16, u32>::const_iterator, ft::map<i16, u32>::const_iterator>    ft_ret;
        std::pair<std::map<i16, u32>::const_iterator, std::map<i16, u32>::const_iterator> std_ret;

        for (i = 0; i < Array<i16>::len; ++i) {
            START        = clock();
            ft_ret       = ft_map.equal_range(Array<i16>::at(i));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.equal_range(Array<i16>::at(i));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret.first == ft_map.end()) != (std_ret.first == std_map.end())
                || (ft_ret.first != ft_map.end()
                    && (!std::equal(ft_ret.first, ft_ret.second, std_ret.first, cmp<i16, u32>)))) {
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i16, u32> >  ft_vec;
        std::vector<std::pair<i16, u32> > std_vec;

        for (i = 0; i < Array<i16>::len && i < Array<u32>::len; ++i) {
            ft_vec.push_back(ft::Pair<i16, u32>(Array<i16>::at(i), Array<u32>::at(i)));
            std_vec.push_back(std::pair<i16, u32>(Array<i16>::at(i), Array<u32>::at(i)));
        }

        ft::map<i16, u32>  ft_map(ft_vec.begin(), ft_vec.end());
        std::map<i16, u32> std_map(std_vec.begin(), std_vec.end());
        ft::Pair<ft::map<i16, u32>::iterator, ft::map<i16, u32>::iterator>    ft_ret;
        std::pair<std::map<i16, u32>::iterator, std::map<i16, u32>::iterator> std_ret;

        for (i = 0; i < Array<i16>::len; ++i) {
            START        = clock();
            ft_ret       = ft_map.equal_range(Array<i16>::at(i));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_map.equal_range(Array<i16>::at(i));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if ((ft_ret.first == ft_map.end()) != (std_ret.first == std_map.end())
                || (ft_ret.first != ft_map.end()
                    && (--ft_ret.first->second != --std_ret.first->second
                        || !std::equal(
                            ft_ret.first, ft_ret.second, std_ret.first, cmp<i16, u32>
                        )))) {
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

inline static u8 __test_function_swap_member()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, float> >  ft_vec;
        std::vector<std::pair<char, float> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<f32>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, float>(Array<char>::at(i), Array<f32>::at(i)));
            std_vec.push_back(std::pair<char, float>(Array<char>::at(i), Array<f32>::at(i)));
        }

        // Swapping empty | empty
        {
            ft::map<char, float>                  ft_map0;
            ft::map<char, float>                  ft_map1;
            std::map<char, float>                 std_map0;
            std::map<char, float>                 std_map1;
            ft::map<char, float>::const_iterator  ft_cit0(ft_map0.begin());
            ft::map<char, float>::const_iterator  ft_cit1(ft_map1.begin());
            std::map<char, float>::const_iterator std_cit0(std_map0.begin());
            std::map<char, float>::const_iterator std_cit1(std_map1.begin());
            ft::map<char, float>::const_iterator  ft_cend0;
            ft::map<char, float>::const_iterator  ft_cend1;

            START = clock();
            ft_map0.swap(ft_map1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_map0.swap(std_map1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            ft_cend0 = ft_map0.end();
            ft_cend1 = ft_map1.end();

            if (ft_map0.size() != std_map0.size()
                || ft_map1.size() != std_map1.size()
                || (!ft_map0.empty() && !std::equal(ft_cit1, ft_cend0, std_cit1, cmp<char, float>))
                || (!ft_map1.empty()
                    && !std::equal(ft_cit0, ft_cend1, std_cit0, cmp<char, float>))) {
                return KO;
            }
        }
        // Swapping empty | non-empty
        {
            ft::map<char, float>  ft_map0;
            ft::map<char, float>  ft_map1(&ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]);
            std::map<char, float> std_map0;
            std::map<char, float> std_map1(&std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]);
            ft::map<char, float>::const_iterator  ft_cit0(ft_map0.begin());
            ft::map<char, float>::const_iterator  ft_cit1(ft_map1.begin());
            std::map<char, float>::const_iterator std_cit0(std_map0.begin());
            std::map<char, float>::const_iterator std_cit1(std_map1.begin());
            ft::map<char, float>::const_iterator  ft_cend0;
            ft::map<char, float>::const_iterator  ft_cend1;

            START = clock();
            ft_map0.swap(ft_map1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_map0.swap(std_map1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            ft_cend0 = ft_map0.end();
            ft_cend1 = ft_map1.end();

            if (ft_map0.size() != std_map0.size()
                || ft_map1.size() != std_map1.size()
                || (!ft_map0.empty() && !std::equal(ft_cit1, ft_cend0, std_cit1, cmp<char, float>))
                || (!ft_map1.empty()
                    && !std::equal(ft_cit0, ft_cend1, std_cit0, cmp<char, float>))) {
                return KO;
            }
        }
        // Swapping non-empty | empty
        {
            ft::map<char, float>  ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
            ft::map<char, float>  ft_map1;
            std::map<char, float> std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
            std::map<char, float> std_map1;
            ft::map<char, float>::const_iterator  ft_cit0(ft_map0.begin());
            ft::map<char, float>::const_iterator  ft_cit1(ft_map1.begin());
            std::map<char, float>::const_iterator std_cit0(std_map0.begin());
            std::map<char, float>::const_iterator std_cit1(std_map1.begin());
            ft::map<char, float>::const_iterator  ft_cend0;
            ft::map<char, float>::const_iterator  ft_cend1;

            START = clock();
            ft_map0.swap(ft_map1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_map0.swap(std_map1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            ft_cend0 = ft_map0.end();
            ft_cend1 = ft_map1.end();

            if (ft_map0.size() != std_map0.size()
                || ft_map1.size() != std_map1.size()
                || (!ft_map0.empty() && !std::equal(ft_cit1, ft_cend0, std_cit1, cmp<char, float>))
                || (!ft_map1.empty()
                    && !std::equal(ft_cit0, ft_cend1, std_cit0, cmp<char, float>))) {
                return KO;
            }
        }
        // Swapping non-empty | non-empty
        {
            ft::map<char, float>  ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
            ft::map<char, float>  ft_map1(&ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]);
            std::map<char, float> std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
            std::map<char, float> std_map1(&std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]);
            ft::map<char, float>::const_iterator  ft_cit0(ft_map0.begin());
            ft::map<char, float>::const_iterator  ft_cit1(ft_map1.begin());
            std::map<char, float>::const_iterator std_cit0(std_map0.begin());
            std::map<char, float>::const_iterator std_cit1(std_map1.begin());
            ft::map<char, float>::const_iterator  ft_cend0;
            ft::map<char, float>::const_iterator  ft_cend1;

            START = clock();
            ft_map0.swap(ft_map1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_map0.swap(std_map1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            ft_cend0 = ft_map0.end();
            ft_cend1 = ft_map1.end();

            if (ft_map0.size() != std_map0.size()
                || ft_map1.size() != std_map1.size()
                || (!ft_map0.empty() && !std::equal(ft_cit1, ft_cend0, std_cit1, cmp<char, float>))
                || (!ft_map1.empty()
                    && !std::equal(ft_cit0, ft_cend1, std_cit0, cmp<char, float>))) {
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

inline static u8 __test_function_swap_non_member()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<char, float> >  ft_vec;
        std::vector<std::pair<char, float> > std_vec;

        for (i = 0; i < Array<char>::len && i < Array<f32>::len; ++i) {
            ft_vec.push_back(ft::Pair<char, float>(Array<char>::at(i), Array<f32>::at(i)));
            std_vec.push_back(std::pair<char, float>(Array<char>::at(i), Array<f32>::at(i)));
        }

        // Swapping empty | empty
        {
            ft::map<char, float>                  ft_map0;
            ft::map<char, float>                  ft_map1;
            std::map<char, float>                 std_map0;
            std::map<char, float>                 std_map1;
            ft::map<char, float>::const_iterator  ft_cit0(ft_map0.begin());
            ft::map<char, float>::const_iterator  ft_cit1(ft_map1.begin());
            std::map<char, float>::const_iterator std_cit0(std_map0.begin());
            std::map<char, float>::const_iterator std_cit1(std_map1.begin());
            ft::map<char, float>::const_iterator  ft_cend0;
            ft::map<char, float>::const_iterator  ft_cend1;

            START = clock();
            ft::swap(ft_map0, ft_map1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::swap(std_map0, std_map1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            ft_cend0 = ft_map0.end();
            ft_cend1 = ft_map1.end();

            if (ft_map0.size() != std_map0.size()
                || ft_map1.size() != std_map1.size()
                || (!ft_map0.empty() && !std::equal(ft_cit1, ft_cend0, std_cit1, cmp<char, float>))
                || (!ft_map1.empty()
                    && !std::equal(ft_cit0, ft_cend1, std_cit0, cmp<char, float>))) {
                return KO;
            }
        }
        // Swapping empty | non-empty
        {
            ft::map<char, float>  ft_map0;
            ft::map<char, float>  ft_map1(&ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]);
            std::map<char, float> std_map0;
            std::map<char, float> std_map1(&std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]);
            ft::map<char, float>::const_iterator  ft_cit0(ft_map0.begin());
            ft::map<char, float>::const_iterator  ft_cit1(ft_map1.begin());
            std::map<char, float>::const_iterator std_cit0(std_map0.begin());
            std::map<char, float>::const_iterator std_cit1(std_map1.begin());
            ft::map<char, float>::const_iterator  ft_cend0;
            ft::map<char, float>::const_iterator  ft_cend1;

            START = clock();
            ft::swap(ft_map0, ft_map1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::swap(std_map0, std_map1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            ft_cend0 = ft_map0.end();
            ft_cend1 = ft_map1.end();

            if (ft_map0.size() != std_map0.size()
                || ft_map1.size() != std_map1.size()
                || (!ft_map0.empty() && !std::equal(ft_cit1, ft_cend0, std_cit1, cmp<char, float>))
                || (!ft_map1.empty()
                    && !std::equal(ft_cit0, ft_cend1, std_cit0, cmp<char, float>))) {
                return KO;
            }
        }
        // Swapping non-empty | empty
        {
            ft::map<char, float>  ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
            ft::map<char, float>  ft_map1;
            std::map<char, float> std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
            std::map<char, float> std_map1;
            ft::map<char, float>::const_iterator  ft_cit0(ft_map0.begin());
            ft::map<char, float>::const_iterator  ft_cit1(ft_map1.begin());
            std::map<char, float>::const_iterator std_cit0(std_map0.begin());
            std::map<char, float>::const_iterator std_cit1(std_map1.begin());
            ft::map<char, float>::const_iterator  ft_cend0;
            ft::map<char, float>::const_iterator  ft_cend1;

            START = clock();
            ft::swap(ft_map0, ft_map1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::swap(std_map0, std_map1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            ft_cend0 = ft_map0.end();
            ft_cend1 = ft_map1.end();

            if (ft_map0.size() != std_map0.size()
                || ft_map1.size() != std_map1.size()
                || (!ft_map0.empty() && !std::equal(ft_cit1, ft_cend0, std_cit1, cmp<char, float>))
                || (!ft_map1.empty()
                    && !std::equal(ft_cit0, ft_cend1, std_cit0, cmp<char, float>))) {
                return KO;
            }
        }
        // Swapping non-empty | non-empty
        {
            ft::map<char, float>  ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
            ft::map<char, float>  ft_map1(&ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]);
            std::map<char, float> std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
            std::map<char, float> std_map1(&std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]);
            ft::map<char, float>::const_iterator  ft_cit0(ft_map0.begin());
            ft::map<char, float>::const_iterator  ft_cit1(ft_map1.begin());
            std::map<char, float>::const_iterator std_cit0(std_map0.begin());
            std::map<char, float>::const_iterator std_cit1(std_map1.begin());
            ft::map<char, float>::const_iterator  ft_cend0;
            ft::map<char, float>::const_iterator  ft_cend1;

            START = clock();
            ft::swap(ft_map0, ft_map1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::swap(std_map0, std_map1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            ft_cend0 = ft_map0.end();
            ft_cend1 = ft_map1.end();

            if (ft_map0.size() != std_map0.size()
                || ft_map1.size() != std_map1.size()
                || (!ft_map0.empty() && !std::equal(ft_cit1, ft_cend0, std_cit1, cmp<char, float>))
                || (!ft_map1.empty()
                    && !std::equal(ft_cit0, ft_cend1, std_cit0, cmp<char, float>))) {
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

inline static u8 __test_operator_assign()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<std::string, u8> >  ft_vec;
        std::vector<std::pair<std::string, u8> > std_vec;

        for (i = 0; i < Array<std::string>::len && i < Array<u8>::len; ++i) {
            ft_vec.push_back(
                ft::Pair<std::string, u8>(Array<std::string>::at(i), Array<u8>::at(i))
            );
            std_vec.push_back(
                std::pair<std::string, u8>(Array<std::string>::at(i), Array<u8>::at(i))
            );
        }

        // Assigning empty -> empty
        {
            ft::map<std::string, u8>        ft_map0;
            ft::map<std::string, u8> const  ft_map1;
            std::map<std::string, u8>       std_map0;
            std::map<std::string, u8> const std_map1;

            START        = clock();
            ft_map0      = ft_map1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_map0      = std_map1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_map0.size() != std_map0.size()
                || !std::equal(
                    ft_map0.begin(), ft_map0.end(), std_map0.begin(), cmp<std::string, u8>
                )) {
                return KO;
            }
        }
        // Assigning empty -> non-empty
        {
            ft::map<std::string, u8>        ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
            ft::map<std::string, u8> const  ft_map1;
            std::map<std::string, u8>       std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
            std::map<std::string, u8> const std_map1;

            START        = clock();
            ft_map0      = ft_map1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_map0      = std_map1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_map0.size() != std_map0.size()
                || !std::equal(
                    ft_map0.begin(), ft_map0.end(), std_map0.begin(), cmp<std::string, u8>
                )) {
                return KO;
            }
        }
        // Assigning non-empty -> empty
        {
            ft::map<std::string, u8>       ft_map0;
            ft::map<std::string, u8> const ft_map1(
                &ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]
            );
            std::map<std::string, u8>       std_map0;
            std::map<std::string, u8> const std_map1(
                &std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]
            );

            START        = clock();
            ft_map0      = ft_map1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_map0      = std_map1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_map0.size() != std_map0.size()
                || !std::equal(
                    ft_map0.begin(), ft_map0.end(), std_map0.begin(), cmp<std::string, u8>
                )) {
                return KO;
            }
        }
        // Assigning non-empty -> non-empty
        {
            ft::map<std::string, u8>       ft_map0(&ft_vec[0], &ft_vec[ft_vec.size() / 2]);
            ft::map<std::string, u8> const ft_map1(
                &ft_vec[ft_vec.size() / 2], &ft_vec[ft_vec.size()]
            );
            std::map<std::string, u8>       std_map0(&std_vec[0], &std_vec[std_vec.size() / 2]);
            std::map<std::string, u8> const std_map1(
                &std_vec[std_vec.size() / 2], &std_vec[std_vec.size()]
            );

            START        = clock();
            ft_map0      = ft_map1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_map0      = std_map1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_map0.size() != std_map0.size()
                || !std::equal(
                    ft_map0.begin(), ft_map0.end(), std_map0.begin(), cmp<std::string, u8>
                )) {
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

inline static u8 __test_operator_access_constant()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i32, f128> >  ft_vec;
        std::vector<std::pair<i32, f128> > std_vec;

        for (i = 0; i < Array<i32>::len && i < Array<f128>::len; ++i) {
            ft_vec.push_back(ft::Pair<i32, f128>(Array<i32>::at(i), Array<f128>::at(i)));
            std_vec.push_back(std::pair<i32, f128>(Array<i32>::at(i), Array<f128>::at(i)));
        }

        ft::map<i32, f128>  ft_map(ft_vec.begin(), ft_vec.end());
        std::map<i32, f128> std_map(std_vec.begin(), std_vec.end());

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); ++i) {
            ft::map<i32, f128> const  ft_cmap(ft_map);
            std::map<i32, f128> const std_cmap(std_map);

            START               = clock();
            f128 const &ft_ret  = ft_map[ft_vec[i].first];
            DURATION_FT         = clock() - START;
            DURATION_FT        += !DURATION_FT;

            START                = clock();
            f128 const &std_ret  = std_map[std_vec[i].first];
            DURATION_STD         = clock() - START;
            DURATION_STD        += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret
                || ft_map.size() != std_map.size()
                || !std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), cmp<i32, f128>)) {
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

inline static u8 __test_operator_access_mutable()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i32, f128> >  ft_vec;
        std::vector<std::pair<i32, f128> > std_vec;

        for (i = 0; i < Array<i32>::len && i < Array<f128>::len; ++i) {
            ft_vec.push_back(ft::Pair<i32, f128>(Array<i32>::at(i), Array<f128>::at(i)));
            std_vec.push_back(std::pair<i32, f128>(Array<i32>::at(i), Array<f128>::at(i)));
        }

        ft::map<i32, f128>  ft_map;
        std::map<i32, f128> std_map;

        for (i = 0; i < ft_vec.size(); ++i) {
            // Inserting
            {
                START         = clock();
                f128 &ft_ret  = ft_map[ft_vec[i].first];
                DURATION_FT   = clock() - START;
                DURATION_FT  += !DURATION_FT;

                START          = clock();
                f128 &std_ret  = std_map[std_vec[i].first];
                DURATION_STD   = clock() - START;
                DURATION_STD  += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret
                    || ft_map.size() != std_map.size()
                    || !std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), cmp<i32, f128>)) {
                    return KO;
                }

                ft_ret  = ft_vec[i].second;
                std_ret = std_vec[i].second;

                if (ft_map.size() != std_map.size()
                    || !std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), cmp<i32, f128>)) {
                    return KO;
                }
            }
            // Finding
            {
                START         = clock();
                f128 &ft_ret  = ft_map[ft_vec[i].first];
                DURATION_FT   = clock() - START;
                DURATION_FT  += !DURATION_FT;

                START          = clock();
                f128 &std_ret  = std_map[std_vec[i].first];
                DURATION_STD   = clock() - START;
                DURATION_STD  += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret
                    || ft_map.size() != std_map.size()
                    || !std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), cmp<i32, f128>)) {
                    return KO;
                }

                ft_ret  /= 3;
                std_ret /= 3;

                if (!std::equal(ft_map.begin(), ft_map.end(), std_map.begin(), cmp<i32, f128>)) {
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

inline static u8 __test_operator_equivalent()
{
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i8, u64> >  ft_vec;
        std::vector<std::pair<i8, u64> > std_vec;

        for (i = 0; i < Array<i8>::len && i < Array<u64>::len; ++i) {
            ft_vec.push_back(ft::Pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
            std_vec.push_back(std::pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
        }

        ft::map<i8, u64>  ft_map0;
        ft::map<i8, u64>  ft_map1;
        std::map<i8, u64> std_map0;
        std::map<i8, u64> std_map1;
        bool              ft_ret;
        bool              std_ret;

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); ++i) {
            // Key difference
            {
                ft_map0[ft_vec[i].first + 1]   = ft_vec[i].second;
                ft_map1[ft_vec[i].first - 1]   = ft_vec[i].second;
                std_map0[std_vec[i].first + 1] = std_vec[i].second;
                std_map1[std_vec[i].first - 1] = std_vec[i].second;

                START        = clock();
                ft_ret       = ft::operator==(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator==(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first + 1);
                ft_map1.erase(ft_vec[i].first - 1);
                std_map0.erase(std_vec[i].first + 1);
                std_map1.erase(std_vec[i].first - 1);
            }
            // Mapped value difference
            {
                ft_map0[ft_vec[i].first]   = ft_vec[i].second + 1;
                ft_map1[ft_vec[i].first]   = ft_vec[i].second - 1;
                std_map0[std_vec[i].first] = std_vec[i].second + 1;
                std_map1[std_vec[i].first] = std_vec[i].second - 1;

                START        = clock();
                ft_ret       = ft::operator==(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator==(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first);
                ft_map1.erase(ft_vec[i].first);
                std_map0.erase(std_vec[i].first);
                std_map1.erase(std_vec[i].first);
            }
            // Size difference
            {
                ft_map0.insert(ft_vec[i]);
                std_map0.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator==(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator==(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_map1.insert(ft_vec[i]);
                std_map1.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator==(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator==(std_map0, std_map1);
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i8, u64> >  ft_vec;
        std::vector<std::pair<i8, u64> > std_vec;

        for (i = 0; i < Array<i8>::len && i < Array<u64>::len; ++i) {
            ft_vec.push_back(ft::Pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
            std_vec.push_back(std::pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
        }

        ft::map<i8, u64>  ft_map0;
        ft::map<i8, u64>  ft_map1;
        std::map<i8, u64> std_map0;
        std::map<i8, u64> std_map1;
        bool              ft_ret;
        bool              std_ret;

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); ++i) {
            // Key difference
            {
                ft_map0[ft_vec[i].first + 1]   = ft_vec[i].second;
                ft_map1[ft_vec[i].first - 1]   = ft_vec[i].second;
                std_map0[std_vec[i].first + 1] = std_vec[i].second;
                std_map1[std_vec[i].first - 1] = std_vec[i].second;

                START        = clock();
                ft_ret       = ft::operator!=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator!=(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first + 1);
                ft_map1.erase(ft_vec[i].first - 1);
                std_map0.erase(std_vec[i].first + 1);
                std_map1.erase(std_vec[i].first - 1);
            }
            // Mapped value difference
            {
                ft_map0[ft_vec[i].first]   = ft_vec[i].second + 1;
                ft_map1[ft_vec[i].first]   = ft_vec[i].second - 1;
                std_map0[std_vec[i].first] = std_vec[i].second + 1;
                std_map1[std_vec[i].first] = std_vec[i].second - 1;

                START        = clock();
                ft_ret       = ft::operator!=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator!=(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first);
                ft_map1.erase(ft_vec[i].first);
                std_map0.erase(std_vec[i].first);
                std_map1.erase(std_vec[i].first);
            }
            // Size difference
            {
                ft_map0.insert(ft_vec[i]);
                std_map0.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator!=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator!=(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_map1.insert(ft_vec[i]);
                std_map1.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator!=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator!=(std_map0, std_map1);
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i8, u64> >  ft_vec;
        std::vector<std::pair<i8, u64> > std_vec;

        for (i = 0; i < Array<i8>::len && i < Array<u64>::len; ++i) {
            ft_vec.push_back(ft::Pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
            std_vec.push_back(std::pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
        }

        ft::map<i8, u64>  ft_map0;
        ft::map<i8, u64>  ft_map1;
        std::map<i8, u64> std_map0;
        std::map<i8, u64> std_map1;
        bool              ft_ret;
        bool              std_ret;

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); ++i) {
            // Key difference
            {
                ft_map0[ft_vec[i].first + 1]   = ft_vec[i].second;
                ft_map1[ft_vec[i].first - 1]   = ft_vec[i].second;
                std_map0[std_vec[i].first + 1] = std_vec[i].second;
                std_map1[std_vec[i].first - 1] = std_vec[i].second;

                START        = clock();
                ft_ret       = ft::operator<(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first + 1);
                ft_map1.erase(ft_vec[i].first - 1);
                std_map0.erase(std_vec[i].first + 1);
                std_map1.erase(std_vec[i].first - 1);
            }
            // Mapped value difference
            {
                ft_map0[ft_vec[i].first]   = ft_vec[i].second + 1;
                ft_map1[ft_vec[i].first]   = ft_vec[i].second - 1;
                std_map0[std_vec[i].first] = std_vec[i].second + 1;
                std_map1[std_vec[i].first] = std_vec[i].second - 1;

                START        = clock();
                ft_ret       = ft::operator<(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first);
                ft_map1.erase(ft_vec[i].first);
                std_map0.erase(std_vec[i].first);
                std_map1.erase(std_vec[i].first);
            }
            // Size difference
            {
                ft_map0.insert(ft_vec[i]);
                std_map0.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator<(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_map1.insert(ft_vec[i]);
                std_map1.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator<(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<(std_map0, std_map1);
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i8, u64> >  ft_vec;
        std::vector<std::pair<i8, u64> > std_vec;

        for (i = 0; i < Array<i8>::len && i < Array<u64>::len; ++i) {
            ft_vec.push_back(ft::Pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
            std_vec.push_back(std::pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
        }

        ft::map<i8, u64>  ft_map0;
        ft::map<i8, u64>  ft_map1;
        std::map<i8, u64> std_map0;
        std::map<i8, u64> std_map1;
        bool              ft_ret;
        bool              std_ret;

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); ++i) {
            // Key difference
            {
                ft_map0[ft_vec[i].first + 1]   = ft_vec[i].second;
                ft_map1[ft_vec[i].first - 1]   = ft_vec[i].second;
                std_map0[std_vec[i].first + 1] = std_vec[i].second;
                std_map1[std_vec[i].first - 1] = std_vec[i].second;

                START        = clock();
                ft_ret       = ft::operator>(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first + 1);
                ft_map1.erase(ft_vec[i].first - 1);
                std_map0.erase(std_vec[i].first + 1);
                std_map1.erase(std_vec[i].first - 1);
            }
            // Mapped value difference
            {
                ft_map0[ft_vec[i].first]   = ft_vec[i].second + 1;
                ft_map1[ft_vec[i].first]   = ft_vec[i].second - 1;
                std_map0[std_vec[i].first] = std_vec[i].second + 1;
                std_map1[std_vec[i].first] = std_vec[i].second - 1;

                START        = clock();
                ft_ret       = ft::operator>(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first);
                ft_map1.erase(ft_vec[i].first);
                std_map0.erase(std_vec[i].first);
                std_map1.erase(std_vec[i].first);
            }
            // Size difference
            {
                ft_map0.insert(ft_vec[i]);
                std_map0.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator>(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_map1.insert(ft_vec[i]);
                std_map1.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator>(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>(std_map0, std_map1);
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i8, u64> >  ft_vec;
        std::vector<std::pair<i8, u64> > std_vec;

        for (i = 0; i < Array<i8>::len && i < Array<u64>::len; ++i) {
            ft_vec.push_back(ft::Pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
            std_vec.push_back(std::pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
        }

        ft::map<i8, u64>  ft_map0;
        ft::map<i8, u64>  ft_map1;
        std::map<i8, u64> std_map0;
        std::map<i8, u64> std_map1;
        bool              ft_ret;
        bool              std_ret;

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); ++i) {
            // Key difference
            {
                ft_map0[ft_vec[i].first + 1]   = ft_vec[i].second;
                ft_map1[ft_vec[i].first - 1]   = ft_vec[i].second;
                std_map0[std_vec[i].first + 1] = std_vec[i].second;
                std_map1[std_vec[i].first - 1] = std_vec[i].second;

                START        = clock();
                ft_ret       = ft::operator<=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<=(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first + 1);
                ft_map1.erase(ft_vec[i].first - 1);
                std_map0.erase(std_vec[i].first + 1);
                std_map1.erase(std_vec[i].first - 1);
            }
            // Mapped value difference
            {
                ft_map0[ft_vec[i].first]   = ft_vec[i].second + 1;
                ft_map1[ft_vec[i].first]   = ft_vec[i].second - 1;
                std_map0[std_vec[i].first] = std_vec[i].second + 1;
                std_map1[std_vec[i].first] = std_vec[i].second - 1;

                START        = clock();
                ft_ret       = ft::operator<=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<=(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first);
                ft_map1.erase(ft_vec[i].first);
                std_map0.erase(std_vec[i].first);
                std_map1.erase(std_vec[i].first);
            }
            // Size difference
            {
                ft_map0.insert(ft_vec[i]);
                std_map0.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator<=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<=(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_map1.insert(ft_vec[i]);
                std_map1.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator<=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<=(std_map0, std_map1);
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
    size_t i;

    title(__func__);
    try {
        std::vector<ft::Pair<i8, u64> >  ft_vec;
        std::vector<std::pair<i8, u64> > std_vec;

        for (i = 0; i < Array<i8>::len && i < Array<u64>::len; ++i) {
            ft_vec.push_back(ft::Pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
            std_vec.push_back(std::pair<i8, u64>(Array<i8>::at(i), Array<u64>::at(i)));
        }

        ft::map<i8, u64>  ft_map0;
        ft::map<i8, u64>  ft_map1;
        std::map<i8, u64> std_map0;
        std::map<i8, u64> std_map1;
        bool              ft_ret;
        bool              std_ret;

        for (i = 0; i < ft_vec.size() && i < std_vec.size(); ++i) {
            // Key difference
            {
                ft_map0[ft_vec[i].first + 1]   = ft_vec[i].second;
                ft_map1[ft_vec[i].first - 1]   = ft_vec[i].second;
                std_map0[std_vec[i].first + 1] = std_vec[i].second;
                std_map1[std_vec[i].first - 1] = std_vec[i].second;

                START        = clock();
                ft_ret       = ft::operator>=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>=(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first + 1);
                ft_map1.erase(ft_vec[i].first - 1);
                std_map0.erase(std_vec[i].first + 1);
                std_map1.erase(std_vec[i].first - 1);
            }
            // Mapped value difference
            {
                ft_map0[ft_vec[i].first]   = ft_vec[i].second + 1;
                ft_map1[ft_vec[i].first]   = ft_vec[i].second - 1;
                std_map0[std_vec[i].first] = std_vec[i].second + 1;
                std_map1[std_vec[i].first] = std_vec[i].second - 1;

                START        = clock();
                ft_ret       = ft::operator>=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>=(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }

                ft_map0.erase(ft_vec[i].first);
                ft_map1.erase(ft_vec[i].first);
                std_map0.erase(std_vec[i].first);
                std_map1.erase(std_vec[i].first);
            }
            // Size difference
            {
                ft_map0.insert(ft_vec[i]);
                std_map0.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator>=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>=(std_map0, std_map1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
            // Equivalence
            {
                ft_map1.insert(ft_vec[i]);
                std_map1.insert(std_vec[i]);

                START        = clock();
                ft_ret       = ft::operator>=(ft_map0, ft_map1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>=(std_map0, std_map1);
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

inline status map(
    char_ptr subcategory
)
{
    SET_FOREGROUND_RGB(0, 177, 255);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "┃                       MAP                       ┃\n";
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
    RESET_GRAPHICS;

    if (!subcategory) {
        return run_default_subcategories() ? FAILURE : SUCCESS;
    }
    return run_specific_subcategory(subcategory) ? FAILURE : SUCCESS;
}

}} // namespace tester::test

#endif
