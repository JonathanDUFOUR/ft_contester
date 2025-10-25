#define DISABLE
#ifndef DISABLE

# include "benchmark.hh"
# include "colors.hh"
# include "headers.hh"
# include "iterator/requirements_check.hh"
# include "iterator/restrictor/forward_iterator_restrictor.hh"
# include "iterator/restrictor/random_access_iterator_restrictor.hh"
# include "test_status.hh"
# include "tester.hh"
# include "type_traits.hh"
# include "types/array.hh"
# include VECTOR_HEADER
# include <cmath>
// #include <cstdlib>
// #include <cstring>
// #include <ctime>
# include <fstream>
// #include <iomanip>
# include <iostream>
// #include <iterator>
# include <stdint.h>
# include <string>
# include <vector>

# pragma region[default template type Alloc]

inline static u8 default_template_type_Alloc()
{
    title(__func__);

    typedef ft::vector<float>                         vec_type_0;
    typedef ft::vector<float, std::allocator<float> > vec_type_1;

    if (!tester::is_same<vec_type_0, vec_type_1>::value) {
        return KO;
    }

    return IMPL_OK;
}

# pragma endregion
# pragma region[constructors]
# pragma region[default]

inline static u8 C_default()
{
    int ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        START = clock();
        ft::vector<int> const ft_vec;
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START = clock();
        std::vector<int> const std_vec;
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (sizeof(ft_vec) != sizeof(std_vec) || memcmp(&ft_vec, &std_vec, sizeof(ft_vec))) {
            ret = ISO_OK;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[copy]

inline static u8 C_copy()
{
    int ret;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
# pragma region[from default]
        {
            ft::vector<u16> const  ft_vec0;
            std::vector<u16> const std_vec0;

            START = clock();
            ft::vector<u16> const ft_vec1(ft_vec0);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<u16> const std_vec1(std_vec0);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec1) != sizeof(std_vec1)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[from filled]
        {
            tester::forward_iterator_restrictor<u16 const *> const it0(&Array<u16>::inner[0]);
            tester::forward_iterator_restrictor<u16 const *> const it1(
                &Array<u16>::inner[Array<u16>::len]
            );
            ft::vector<u16> const  ft_vec0(it0, it1);
            std::vector<u16> const std_vec0(it0, it1);

            START = clock();
            ft::vector<u16> const ft_vec1(ft_vec0);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<u16> const std_vec1(std_vec0);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec1) != sizeof(std_vec1)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma endregion
# pragma region[non-trivial copy required]
# pragma region[from default]
        {
            ft::vector<std::string> const  ft_vec0;
            std::vector<std::string> const std_vec0;

            START = clock();
            ft::vector<std::string> const ft_vec1(ft_vec0);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<std::string> const std_vec1(std_vec0);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec1) != sizeof(std_vec1)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[from filled]
        {
            tester::forward_iterator_restrictor<std::string const *> const it0(
                &Array<std::string>::inner[0]
            );
            tester::forward_iterator_restrictor<std::string const *> const it1(
                &Array<std::string>::inner[Array<std::string>::len]
            );
            ft::vector<std::string> const  ft_vec0(it0, it1);
            std::vector<std::string> const std_vec0(it0, it1);

            START = clock();
            ft::vector<std::string> const ft_vec1(ft_vec0);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<std::string> const std_vec1(std_vec0);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec1) != sizeof(std_vec1)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[fill]

inline static u8 C_fill()
{
    int ret;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
# pragma region[null size & default value]
        {
            START = clock();
            ft::vector<char> const ft_vec(0LU);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<char> const std_vec(0LU);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec) || memcmp(&ft_vec, &std_vec, sizeof(ft_vec))) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[null size & defined value]
        {
            START = clock();
            ft::vector<char> const ft_vec(0LU, 'A');
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<char> const std_vec(0LU, 'A');
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[non-null size & default value]
        {
            START = clock();
            ft::vector<char> const ft_vec(21LU);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<char> const std_vec(21LU);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[non-null size & defined value]
        {
            START = clock();
            ft::vector<char> const ft_vec(42LU, 42);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<char> const std_vec(42LU, 42);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma endregion
# pragma region[trivially copyable & ambiguous]
# pragma region[null size & defined value]
        {
            START = clock();
            ft::vector<char> const ft_vec(static_cast<char>(0LU), 'A');
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<char> const std_vec(static_cast<char>(0LU), 'A');
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[non-null size & defined value]
        {
            START = clock();
            ft::vector<char> const ft_vec(static_cast<char>(42LU), 42);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<char> const std_vec(static_cast<char>(42LU), 42);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma endregion
# pragma region[non-trivial copy required]
# pragma region[null size & default value]
        {
            START = clock();
            ft::vector<std::string> const ft_vec(0LU);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<std::string> const std_vec(0LU);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec) || memcmp(&ft_vec, &std_vec, sizeof(ft_vec))) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[non-null size & default value]
        {
            START = clock();
            ft::vector<std::string> const ft_vec(21LU);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<std::string> const std_vec(21LU);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[null size & defined value]
        {
            START = clock();
            ft::vector<std::string> const ft_vec(0LU, std::string("pouic"));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<std::string> const std_vec(0LU, std::string("pouic"));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[non-null size & defined value]
        {
            START = clock();
            ft::vector<std::string> const ft_vec(42LU, std::string("Hello World !"));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<std::string> const std_vec(42LU, std::string("Hello World !"));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[range]

inline static u8 C_range()
{
    int ret;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
# pragma region[range of input_iterator_restrictor]
        {
            tester::input_iterator_restrictor<u16 const *> const it0(&Array<u16>::inner[0]);
            tester::input_iterator_restrictor<u16 const *> const it1(&Array<u16>::inner[0]);

            START = clock();
            ft::vector<u16> const ft_vec(it0, it1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<u16> const std_vec(it0, it1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[range of forward_iterator_restrictor]
        {
            tester::forward_iterator_restrictor<void const *const *> const it;

            START = clock();
            ft::vector<void const *> const ft_vec(it, it);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<void const *> const std_vec(it, it);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[range of random_access_iterator_restrictor]
        {
            tester::random_access_iterator_restrictor<u16 const *> const it0(&Array<u16>::inner[0]);
            tester::random_access_iterator_restrictor<u16 const *> const it1(
                &Array<u16>::inner[Array<u16>::len]
            );

            START = clock();
            ft::vector<u16> const ft_vec(it0, it1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<u16> const std_vec(it0, it1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[range of char const *]
        {
            START = clock();
            ft::vector<char> const ft_vec(
                Array<char>::inner, &Array<char>::inner[Array<char>::len]
            );
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<char> const std_vec(
                Array<char>::inner, &Array<char>::inner[Array<char>::len]
            );
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma endregion
# pragma region[trivially copyable & force naive iteration along the range]
        {
            std::ifstream ifs0(Array<Filename>::inner[Array<Filename>::len - 1]);
            std::ifstream ifs1(Array<Filename>::inner[Array<Filename>::len - 1]);
            std::istream_iterator<char> const it0(ifs0);
            std::istream_iterator<char> const it1(ifs1);
            std::istream_iterator<char> const end_of_stream;

            START = clock();
            ft::vector<char> const ft_vec(it0, end_of_stream);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<char> const std_vec(it1, end_of_stream);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[non-trivial copy required]
# pragma region[range of input_iterator_restrictor]
        {
            tester::input_iterator_restrictor<std::string const *> const it0(
                &Array<std::string>::inner[0]
            );
            tester::input_iterator_restrictor<std::string const *> const it1(
                &Array<std::string>::inner[0]
            );

            START = clock();
            ft::vector<std::string> const ft_vec(it0, it1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<std::string> const std_vec(it0, it1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[range of forward_iterator_restrictor]
        {
            tester::forward_iterator_restrictor<std::string const *> const it0;
            tester::forward_iterator_restrictor<std::string const *> const it1;

            START = clock();
            ft::vector<std::string> const ft_vec(it0, it1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<std::string> const std_vec(it0, it1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[range of random_access_iterator_restrictor]
        {
            tester::random_access_iterator_restrictor<std::string const *> const it0(
                &Array<std::string>::inner[0]
            );
            tester::random_access_iterator_restrictor<std::string const *> const it1(
                &Array<std::string>::inner[Array<std::string>::len]
            );

            START = clock();
            ft::vector<std::string> const ft_vec(it0, it1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<std::string> const std_vec(it0, it1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma region[range of std::string const *]
        {
            START = clock();
            ft::vector<std::string> const ft_vec(
                &Array<std::string>::inner[0], &Array<std::string>::inner[Array<std::string>::len]
            );
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::vector<std::string> const std_vec(
                &Array<std::string>::inner[0], &Array<std::string>::inner[Array<std::string>::len]
            );
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_vec) != sizeof(std_vec)) {
                ret = ISO_OK;
            }
        }
# pragma endregion
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma endregion
# pragma region[members]
# pragma region[types]
# pragma region[allocator_type]

inline static u8 MT_allocator_type()
{
    title(__func__);

    typedef ft::vector<i64, std::allocator<i64> > vec_type;

    if (!tester::is_same<vec_type::allocator_type, std::allocator<i64> >::value) {
        return KO;
    }

    return IMPL_OK;
}

# pragma endregion
# pragma region[const_iterator]

inline static u8 MT_const_iterator()
{
    int ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::vector<int>  ft_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        std::vector<int> std_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        ft::vector<int>::iterator const        ft_mid(&ft_vec[ft_vec.size() / 2]);
        std::vector<int>::iterator const       std_mid(&std_vec[std_vec.size() / 2]);
        ft::vector<int>::const_iterator const  ft_cmid(ft_mid);
        std::vector<int>::const_iterator const std_cmid(std_mid);
        ft::vector<int>::const_iterator        ft_cit;
        std::vector<int>::const_iterator       std_cit;

        if (sizeof(ft_cit) != sizeof(std_cit)) {
            ret = ISO_OK;
        }

        for (ft_cit = ft_vec.begin(), std_cit = std_vec.begin();
             ft_cit != ft_vec.end() && std_cit != std_vec.end();
             ++ft_cit, ++std_cit) {
            RandomAccessIteratorCheck(ft_cit);
            RandomAccessIteratorCheck(std_cit);

            if ((ft_cit - ft_mid) != (std_cit - std_mid)
                || (ft_cit - ft_cmid) != (std_cit - std_cmid)
                || (ft_cit < ft_mid) != (std_cit < std_mid)
                || (ft_cit < ft_cmid) != (std_cit < std_cmid)
                || (ft_cit > ft_mid) != (std_cit > std_mid)
                || (ft_cit > ft_cmid) != (std_cit > std_cmid)
                || (ft_cit <= ft_mid) != (std_cit <= std_mid)
                || (ft_cit <= ft_cmid) != (std_cit <= std_cmid)
                || (ft_cit >= ft_mid) != (std_cit >= std_mid)
                || (ft_cit >= ft_cmid) != (std_cit >= std_cmid)
                || *ft_cit != *std_cit
                || ft_cit[0] != std_cit[0]) {
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

# pragma endregion
# pragma region[const_pointer]

inline static u8 MT_const_pointer()
{
    title(__func__);

    typedef ft::vector<i64, std::allocator<i64> > vec_type;

    if (!tester::is_same<vec_type::const_pointer, std::allocator<i64>::const_pointer>::value) {
        return KO;
    }

    return IMPL_OK;
}

# pragma endregion
# pragma region[const_reference]

inline static u8 MT_const_reference()
{
    title(__func__);

    typedef ft::vector<i64, std::allocator<i64> > vec_type;

    if (!tester::is_same<vec_type::const_reference, std::allocator<i64>::const_reference>::value) {
        return KO;
    }

    return IMPL_OK;
}

# pragma endregion
# pragma region[const_reverse_iterator]

inline static u8 MT_const_reverse_iterator()
{
    int ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::vector<int> const  ft_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        std::vector<int> const std_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        ft::vector<int>::const_reverse_iterator  ft_crit;
        std::vector<int>::const_reverse_iterator std_crit;

        if (sizeof(ft_crit) != sizeof(std_crit)) {
            ret = ISO_OK;
        }

        for (ft_crit = ft_vec.rbegin(), std_crit = std_vec.rbegin();
             ft_crit != ft_vec.rend() && std_crit != std_vec.rend();
             ++ft_crit, ++std_crit) {
            RandomAccessIteratorCheck(ft_crit);
            RandomAccessIteratorCheck(std_crit);

            if ((ft_crit - ft_vec.rend()) != (std_crit - std_vec.rend())
                || (ft_crit < ft_vec.rend()) != (std_crit < std_vec.rend())
                || (ft_crit > ft_vec.rend()) != (std_crit > std_vec.rend())
                || (ft_crit <= ft_vec.rend()) != (std_crit <= std_vec.rend())
                || (ft_crit >= ft_vec.rend()) != (std_crit >= std_vec.rend())
                || *ft_crit != *std_crit
                || ft_crit[0] != std_crit[0]) {
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

# pragma endregion
# pragma region[iterator]

inline static u8 MT_iterator()
{
    int ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::vector<int>  ft_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        std::vector<int> std_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        ft::vector<int>::iterator const        ft_mid(&ft_vec[ft_vec.size() / 2]);
        std::vector<int>::iterator const       std_mid(&std_vec[std_vec.size() / 2]);
        ft::vector<int>::const_iterator const  ft_cmid(ft_mid);
        std::vector<int>::const_iterator const std_cmid(std_mid);
        ft::vector<int>::iterator              ft_it;
        std::vector<int>::iterator             std_it;

        if (sizeof(ft_it) != sizeof(std_it)) {
            ret = ISO_OK;
        }

        for (ft_it = ft_vec.begin(), std_it = std_vec.begin();
             ft_it != ft_vec.end() && std_it != std_vec.end();
             ++ft_it, ++std_it) {
            RandomAccessIteratorCheck(ft_it);
            RandomAccessIteratorCheck(std_it);

            if ((ft_it - ft_mid) != (std_it - std_mid)
                || (ft_it - ft_cmid) != (std_it - std_cmid)
                || (ft_it < ft_mid) != (std_it < std_mid)
                || (ft_it < ft_cmid) != (std_it < std_cmid)
                || (ft_it > ft_mid) != (std_it > std_mid)
                || (ft_it > ft_cmid) != (std_it > std_cmid)
                || (ft_it <= ft_mid) != (std_it <= std_mid)
                || (ft_it <= ft_cmid) != (std_it <= std_cmid)
                || (ft_it >= ft_mid) != (std_it >= std_mid)
                || (ft_it >= ft_cmid) != (std_it >= std_cmid)
                || (*ft_it)++ != (*std_it)++
                || ++(ft_it[0]) != ++(std_it[0])
                || (*ft_it)-- != (*std_it)--
                || --(ft_it[0]) != --(std_it[0])) {
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

# pragma endregion
# pragma region[pointer]

inline static u8 MT_pointer()
{
    title(__func__);

    typedef ft::vector<i64, std::allocator<i64> > vec_type;

    if (!tester::is_same<vec_type::pointer, std::allocator<i64>::pointer>::value) {
        return KO;
    }

    return IMPL_OK;
}

# pragma endregion
# pragma region[reference]

inline static u8 MT_reference()
{
    title(__func__);

    typedef ft::vector<i64, std::allocator<i64> > vec_type;

    if (!tester::is_same<vec_type::reference, std::allocator<i64>::reference>::value) {
        return KO;
    }

    return IMPL_OK;
}

# pragma endregion
# pragma region[reverse_iterator]

inline static u8 MT_reverse_iterator()
{
    int ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::vector<int>  ft_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        std::vector<int> std_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        ft::vector<int>::reverse_iterator const        ft_rend(ft_vec.rend());
        std::vector<int>::reverse_iterator const       std_rend(std_vec.rend());
        ft::vector<int>::const_reverse_iterator const  ft_crend(ft_vec.rend());
        std::vector<int>::const_reverse_iterator const std_crend(std_vec.rend());
        ft::vector<int>::reverse_iterator              ft_rit;
        std::vector<int>::reverse_iterator             std_rit;

        if (sizeof(ft_rit) != sizeof(std_rit)) {
            ret = ISO_OK;
        }

        for (ft_rit = ft_vec.rbegin(), std_rit = std_vec.rbegin();
             ft_rit != ft_vec.rend() && std_rit != std_vec.rend();
             ++ft_rit, ++std_rit) {
            RandomAccessIteratorCheck(ft_rit);
            RandomAccessIteratorCheck(std_rit);

            if ((ft_rit - ft_rend) != (std_rit - std_rend)
                || (ft_rit - ft_crend) != (std_rit - std_crend)
                || (ft_rit < ft_rend) != (std_rit < std_rend)
                || (ft_rit < ft_crend) != (std_rit < std_crend)
                || (ft_rit > ft_rend) != (std_rit > std_rend)
                || (ft_rit > ft_crend) != (std_rit > std_crend)
                || (ft_rit <= ft_rend) != (std_rit <= std_rend)
                || (ft_rit <= ft_crend) != (std_rit <= std_crend)
                || (ft_rit >= ft_rend) != (std_rit >= std_rend)
                || (ft_rit >= ft_crend) != (std_rit >= std_crend)
                || (*ft_rit)++ != (*std_rit)++
                || ++(ft_rit[0]) != ++(std_rit[0])
                || (*ft_rit)-- != (*std_rit)--
                || --(ft_rit[0]) != --(std_rit[0])) {
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

# pragma endregion
# pragma region[value_type]

inline static u8 MT_value_type()
{
    title(__func__);

    typedef ft::vector<i64, std::allocator<i64> > vec_type;

    if (!tester::is_same<vec_type::ValueType, i64>::value) {
        return KO;
    }

    return IMPL_OK;
}

# pragma endregion
# pragma endregion
# pragma region[functions]
# pragma region[assign]
# pragma region[fill]

inline static u8 MF_assign_fill()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
        {
            ft::vector<double>  ft_vec(7LU, NAN);
            std::vector<double> std_vec(7LU, NAN);

            for (idx = 0U; idx < Array<f64>::len; ++idx) {
                START = clock();
                ft_vec.assign(idx * idx, Array<f64>::inner[idx]);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.assign(idx * idx, Array<f64>::inner[idx]);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[trivially copyable & ambiguous]
        {
            ft::vector<i64>  ft_vec(7LU, 42L);
            std::vector<i64> std_vec(7LU, 42L);

            for (idx = 0U; idx < Array<i64>::len; ++idx) {
                START = clock();
                ft_vec.assign(static_cast<i64>(idx * idx), Array<i64>::inner[idx]);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.assign(static_cast<i64>(idx * idx), Array<i64>::inner[idx]);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[non-trivial copy required]
        {
            ft::vector<std::string>  ft_vec(7LU, std::string("Koala"));
            std::vector<std::string> std_vec(7LU, std::string("Koala"));

            for (idx = 0U; idx < Array<std::string>::len; ++idx) {
                START = clock();
                ft_vec.assign(idx * idx, Array<std::string>::inner[idx]);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.assign(idx * idx, Array<std::string>::inner[idx]);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[range]

inline static u8 MF_assign_range()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
        {
            ft::vector<double>  ft_vec(7LU, NAN);
            std::vector<double> std_vec(7LU, NAN);

            for (idx = 0U; idx < Array<f64>::len; ++idx) {
                START = clock();
                ft_vec.assign(
                    &Array<f64>::inner[idx / 2 + (idx % 2)],
                    &Array<f64>::inner[Array<f64>::len - idx / 2 - !(idx % 2)]
                );
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.assign(
                    &Array<f64>::inner[idx / 2 + (idx % 2)],
                    &Array<f64>::inner[Array<f64>::len - idx / 2 - !(idx % 2)]
                );
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[trivially copyable & force naive iteration along the range]
        {
            ft::vector<char>  ft_vec(7LU, '+');
            std::vector<char> std_vec(7LU, '+');

            for (idx = 0U; idx < Array<Filename>::len; ++idx) {
                std::ifstream               ifs0(Array<Filename>::inner[idx]);
                std::ifstream               ifs1(Array<Filename>::inner[idx]);
                std::istream_iterator<char> it0(ifs0);
                std::istream_iterator<char> it1(ifs1);
                std::istream_iterator<char> end_of_stream;

                START = clock();
                ft_vec.assign(it0, end_of_stream);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.assign(it1, end_of_stream);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[non-trivial copy required]
        {
            ft::vector<std::string>  ft_vec(7LU, std::string("Koala"));
            std::vector<std::string> std_vec(7LU, std::string("Koala"));

            for (idx = 0U; idx < Array<std::string>::len; ++idx) {
                START = clock();
                ft_vec.assign(
                    &Array<std::string>::inner[idx / 2 + (idx % 2)],
                    &Array<std::string>::inner[10 - idx / 2 - !(idx % 2)]
                );
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.assign(
                    &Array<std::string>::inner[idx / 2 + (idx % 2)],
                    &Array<std::string>::inner[10 - idx / 2 - !(idx % 2)]
                );
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma endregion
# pragma region[at]
# pragma region[constant]

inline static u8 MF_at()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<int> const  ft_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        std::vector<int> const std_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);

# pragma region[within bounds]
        for (idx = 0U; idx < Array<i32>::len; ++idx) {
            START              = clock();
            int const &ft_ret  = ft_vec.at(idx);
            DURATION_FT        = clock() - START;
            DURATION_FT       += !DURATION_FT;

            START               = clock();
            int const &std_ret  = std_vec.at(idx);
            DURATION_STD        = clock() - START;
            DURATION_STD       += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
# pragma endregion
# pragma region[out of bounds]
        try {
            ft_vec.at(42LU);
        }
        catch (std::out_of_range const &e) {
            goto at_constant_out_of_bounds_ok;
        }
        return KO;
    at_constant_out_of_bounds_ok:;
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma region[mutable]

inline static u8 MF_at_mut()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<int>  ft_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        std::vector<int> std_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);

# pragma region[within bounds]
        for (idx = 0U; idx < Array<i32>::len; ++idx) {
            START        = clock();
            int &ft_ret  = ft_vec.at(idx);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            int &std_ret  = std_vec.at(idx);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
# pragma endregion
# pragma region[out of bounds]
        try {
            ++ft_vec.at(42LU);
        }
        catch (std::out_of_range const &e) {
            goto at_constant_out_of_bounds_ok;
        }
        return KO;
    at_constant_out_of_bounds_ok:;
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma endregion
# pragma region[back]
# pragma region[constant]

inline static u8 MF_back()
{
    u32 idx;

    title(__func__);
    try {
        for (idx = 1U; idx <= Array<i32>::len; ++idx) {
            ft::vector<int> const  ft_vec(&Array<i32>::inner[0], &Array<i32>::inner[idx]);
            std::vector<int> const std_vec(&Array<i32>::inner[0], &Array<i32>::inner[idx]);

            START              = clock();
            int const &ft_ret  = ft_vec.back();
            DURATION_FT        = clock() - START;
            DURATION_FT       += !DURATION_FT;

            START               = clock();
            int const &std_ret  = std_vec.back();
            DURATION_STD        = clock() - START;
            DURATION_STD       += !DURATION_STD;

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

# pragma endregion
# pragma region[mutable]

inline static u8 MF_back_mut()
{
    u32 idx;

    title(__func__);
    try {
        for (idx = 1U; idx <= Array<i32>::len; ++idx) {
            ft::vector<int>  ft_vec(&Array<i32>::inner[0], &Array<i32>::inner[idx]);
            std::vector<int> std_vec(&Array<i32>::inner[0], &Array<i32>::inner[idx]);

            START        = clock();
            int &ft_ret  = ft_vec.back();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            int &std_ret  = std_vec.back();
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

# pragma endregion
# pragma endregion
# pragma region[begin]
# pragma region[constant]

inline static u8 MF_begin()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<char>::const_iterator  ft_ret;
        std::vector<char>::const_iterator std_ret;

        for (idx = 0U; idx < Array<Filename>::len; ++idx) {
            std::ifstream                     ifs0(Array<Filename>::inner[idx]);
            std::ifstream                     ifs1(Array<Filename>::inner[idx]);
            std::istream_iterator<char> const it0(ifs0);
            std::istream_iterator<char> const it1(ifs1);
            std::istream_iterator<char> const end_of_stream;
            ft::vector<char> const            ft_vec(it0, end_of_stream);
            std::vector<char> const           std_vec(it1, end_of_stream);

            START        = clock();
            ft_ret       = ft_vec.begin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.begin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.size() && std_vec.size() && *ft_ret != *std_ret) {
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

# pragma endregion
# pragma region[mutable]

inline static u8 MF_begin_mut()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<char>::iterator  ft_ret;
        std::vector<char>::iterator std_ret;

        for (idx = 0U; idx < Array<Filename>::len; ++idx) {
            std::ifstream                     ifs0(Array<Filename>::inner[idx]);
            std::ifstream                     ifs1(Array<Filename>::inner[idx]);
            std::istream_iterator<char> const it0(ifs0);
            std::istream_iterator<char> const it1(ifs1);
            std::istream_iterator<char> const end_of_stream;
            ft::vector<char>                  ft_vec(it0, end_of_stream);
            std::vector<char>                 std_vec(it1, end_of_stream);

            START        = clock();
            ft_ret       = ft_vec.begin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.begin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.size() && std_vec.size() && *ft_ret != *std_ret) {
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

# pragma endregion
# pragma endregion
# pragma region[capacity]

inline static u8 MF_capacity()
{
    int    ret;
    size_t n;

    title(__func__);
    ret = IMPL_OK;
    try {
        for (n = 0LU; n < 10LU; ++n) {
            ft::vector<float> const       ft_vec(n, 3.14f);
            std::vector<float> const      std_vec(n, 3.14f);
            ft::vector<float>::size_type  ft_ret;
            std::vector<float>::size_type std_ret;

            START        = clock();
            ft_ret       = ft_vec.capacity();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.capacity();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                ret = ISO_OK;
            }
            if (ft_ret < n) {
                ret = KO;
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[clear]

inline static u8 MF_clear()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
        for (idx = 0U; idx < Array<std::string>::len; ++idx) {
            ft::vector<std::string> ft_vec(
                &Array<std::string>::inner[0], &Array<std::string>::inner[idx]
            );
            std::vector<std::string> std_vec(
                &Array<std::string>::inner[0], &Array<std::string>::inner[idx]
            );

            START = clock();
            ft_vec.clear();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_vec.clear();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.capacity() != std_vec.capacity()) {
                return ISO_OK;
            }
            if (ft_vec.size() != std_vec.size()) {
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

# pragma endregion
# pragma region[empty]

inline static u8 MF_empty()
{
    size_t n;

    title(__func__);
    try {
        for (n = 0LU; n < 10LU; ++n) {
            ft::vector<std::string> const  ft_vec(n * (n % 2), std::string("Hello World"));
            std::vector<std::string> const std_vec(n * (n % 2), std::string("Hello World"));
            bool                           ft_ret;
            bool                           std_ret;

            START        = clock();
            ft_ret       = ft_vec.empty();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.empty();
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

# pragma endregion
# pragma region[end]
# pragma region[constant]

inline static u8 MF_end()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<char>::const_iterator  ft_ret;
        std::vector<char>::const_iterator std_ret;

        for (idx = 0U; idx < Array<Filename>::len; ++idx) {
            std::ifstream                     ifs0(Array<Filename>::inner[idx]);
            std::ifstream                     ifs1(Array<Filename>::inner[idx]);
            std::istream_iterator<char> const it0(ifs0);
            std::istream_iterator<char> const it1(ifs1);
            std::istream_iterator<char> const end_of_stream;
            ft::vector<char> const            ft_vec(it0, end_of_stream);
            std::vector<char> const           std_vec(it1, end_of_stream);

            START        = clock();
            ft_ret       = ft_vec.end();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.end();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.size() && std_vec.size() && *--ft_ret != *--std_ret) {
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

# pragma endregion
# pragma region[mutable]

inline static u8 MF_end_mut()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<char>::iterator  ft_ret;
        std::vector<char>::iterator std_ret;

        for (idx = 0U; idx < Array<Filename>::len; ++idx) {
            std::ifstream                     ifs0(Array<Filename>::inner[idx]);
            std::ifstream                     ifs1(Array<Filename>::inner[idx]);
            std::istream_iterator<char> const it0(ifs0);
            std::istream_iterator<char> const it1(ifs1);
            std::istream_iterator<char> const end_of_stream;
            ft::vector<char>                  ft_vec(it0, end_of_stream);
            std::vector<char>                 std_vec(it1, end_of_stream);

            START        = clock();
            ft_ret       = ft_vec.end();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.end();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.size() && std_vec.size() && *--ft_ret != *--std_ret) {
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

# pragma endregion
# pragma endregion
# pragma region[erase]
# pragma region[range]

inline static u8 MF_erase_range()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::vector<u8>                  ft_vec;
        std::vector<u8>                 std_vec;
        ft::vector<u8>::const_iterator  ft_ret;
        std::vector<u8>::const_iterator std_ret;

        for (idx = 0U; idx < Array<u8>::len; ++idx) {
            ft_vec.insert(ft_vec.end(), &Array<u8>::inner[idx], &Array<u8>::inner[Array<u8>::len]);
            std_vec.insert(
                std_vec.end(), &Array<u8>::inner[idx], &Array<u8>::inner[Array<u8>::len]
            );

            START        = clock();
            ft_ret       = ft_vec.erase(ft_vec.begin() + idx, ft_vec.begin() + idx * 2);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.erase(std_vec.begin() + idx, std_vec.begin() + idx * 2);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.capacity() != std_vec.capacity()) {
                ret = ISO_OK;
            }
            if (ft_vec.size() != std_vec.size()
                || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())
                || ft_ret - ft_vec.begin() != std_ret - std_vec.begin()) {
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

# pragma endregion
# pragma region[single]

inline static u8 MF_erase_single()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::vector<u8>                  ft_vec;
        std::vector<u8>                 std_vec;
        ft::vector<u8>::const_iterator  ft_ret;
        std::vector<u8>::const_iterator std_ret;

        for (idx = 0U; idx < Array<u8>::len; ++idx) {
            ft_vec.insert(ft_vec.end(), &Array<u8>::inner[idx], &Array<u8>::inner[Array<u8>::len]);
            std_vec.insert(
                std_vec.end(), &Array<u8>::inner[idx], &Array<u8>::inner[Array<u8>::len]
            );

            START        = clock();
            ft_ret       = ft_vec.erase(ft_vec.begin() + idx);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.erase(std_vec.begin() + idx);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.capacity() != std_vec.capacity()) {
                ret = ISO_OK;
            }
            if (ft_vec.size() != std_vec.size()
                || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())
                || ft_ret - ft_vec.begin() != std_ret - std_vec.begin()) {
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

# pragma endregion
# pragma endregion
# pragma region[front]
# pragma region[constant]

inline static u8 MF_front()
{
    u32 idx;

    title(__func__);
    try {
        for (idx = 0U; idx < Array<i32>::len; ++idx) {
            ft::vector<int> const ft_vec(
                &Array<i32>::inner[idx], &Array<i32>::inner[Array<i32>::len]
            );
            std::vector<int> const std_vec(
                &Array<i32>::inner[idx], &Array<i32>::inner[Array<i32>::len]
            );

            START              = clock();
            int const &ft_ret  = ft_vec.front();
            DURATION_FT        = clock() - START;
            DURATION_FT       += !DURATION_FT;

            START               = clock();
            int const &std_ret  = std_vec.front();
            DURATION_STD        = clock() - START;
            DURATION_STD       += !DURATION_STD;

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

# pragma endregion
# pragma region[mutable]

inline static u8 MF_front_mut()
{
    u32 idx;

    title(__func__);
    try {
        for (idx = 0U; idx < Array<i32>::len; ++idx) {
            ft::vector<int>  ft_vec(&Array<i32>::inner[idx], &Array<i32>::inner[Array<i32>::len]);
            std::vector<int> std_vec(&Array<i32>::inner[idx], &Array<i32>::inner[Array<i32>::len]);

            START        = clock();
            int &ft_ret  = ft_vec.front();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            int &std_ret  = std_vec.front();
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

# pragma endregion
# pragma endregion
# pragma region[get_allocator]

inline static u8 MF_get_allocator()
{
    title(__func__);
    try {
        ft::vector<char> const            ft_vec;
        std::vector<char> const           std_vec;
        ft::vector<char>::allocator_type  ft_ret;
        std::vector<char>::allocator_type std_ret;

        START        = clock();
        ft_ret       = ft_vec.get_allocator();
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START         = clock();
        std_ret       = std_vec.get_allocator();
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (ft_ret != std_ret) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma region[insert]
# pragma region[fill]

inline static u8 MF_insert_fill()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
        {
            ft::vector<float>  ft_vec;
            std::vector<float> std_vec;

            for (idx = 0U; idx < Array<f32>::len; ++idx) {
                START = clock();
                ft_vec.insert(
                    ft_vec.begin() + ft_vec.size() / 2,
                    Array<f32>::len - idx,
                    Array<f32>::inner[idx]
                );
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.insert(
                    std_vec.begin() + std_vec.size() / 2,
                    Array<f32>::len - idx,
                    Array<f32>::inner[idx]
                );
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[trivially copyable & ambiguous]
        {
            ft::vector<int>  ft_vec;
            std::vector<int> std_vec;

            for (idx = 0U; idx < Array<i32>::len; ++idx) {
                START = clock();
                ft_vec.insert(
                    ft_vec.begin() + ft_vec.size() / 2,
                    static_cast<int>(Array<i32>::len - idx),
                    Array<i32>::inner[idx]
                );
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.insert(
                    std_vec.begin() + std_vec.size() / 2,
                    static_cast<int>(Array<i32>::len - idx),
                    Array<i32>::inner[idx]
                );
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[non-trivial copy required]
        {
            ft::vector<std::string>  ft_vec;
            std::vector<std::string> std_vec;

            for (idx = 0U; idx < Array<std::string>::len; ++idx) {
                START = clock();
                ft_vec.insert(
                    ft_vec.begin() + ft_vec.size() / 2,
                    Array<std::string>::len - idx,
                    Array<std::string>::inner[idx]
                );
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.insert(
                    std_vec.begin() + std_vec.size() / 2,
                    Array<std::string>::len - idx,
                    Array<std::string>::inner[idx]
                );
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[range]

inline static u8 MF_insert_range()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
        {
            ft::vector<float>  ft_vec;
            std::vector<float> std_vec;

            for (idx = 0U; idx < Array<f32>::len; ++idx) {
                START = clock();
                ft_vec.insert(
                    ft_vec.begin() + ft_vec.size() / 2, Array<f32>::inner, &Array<f32>::inner[idx]
                );
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.insert(
                    std_vec.begin() + std_vec.size() / 2, Array<f32>::inner, &Array<f32>::inner[idx]
                );
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[trivially copyable & force naive iteration along the range]
        {
            ft::vector<char>  ft_vec;
            std::vector<char> std_vec;

            for (idx = 0U; idx < Array<Filename>::len; ++idx) {
                std::ifstream               ifs0(Array<Filename>::inner[idx]);
                std::ifstream               ifs1(Array<Filename>::inner[idx]);
                std::istream_iterator<char> it0(ifs0);
                std::istream_iterator<char> it1(ifs1);
                std::istream_iterator<char> end_of_stream;

                START = clock();
                ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, it0, end_of_stream);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.insert(std_vec.begin() + std_vec.size() / 2, it1, end_of_stream);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[non-trivial copy required]
        {
            ft::vector<std::string>  ft_vec;
            std::vector<std::string> std_vec;

            for (idx = 0U; idx < Array<std::string>::len; ++idx) {
                START = clock();
                ft_vec.insert(
                    ft_vec.begin() + ft_vec.size() / 2,
                    Array<std::string>::inner,
                    &Array<std::string>::inner[idx]
                );
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.insert(
                    std_vec.begin() + std_vec.size() / 2,
                    Array<std::string>::inner,
                    &Array<std::string>::inner[idx]
                );
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[single]

inline static u8 MF_insert_single()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
        {
            ft::vector<float>                  ft_vec;
            std::vector<float>                 std_vec;
            ft::vector<float>::const_iterator  ft_ret;
            std::vector<float>::const_iterator std_ret;

            for (idx = 0U; idx < Array<f32>::len; ++idx) {
                START  = clock();
                ft_ret = ft_vec.insert(ft_vec.begin() + ft_vec.size() / 2, Array<f32>::inner[idx]);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_ret =
                    std_vec.insert(std_vec.begin() + std_vec.size() / 2, Array<f32>::inner[idx]);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())
                    || ft_ret - ft_vec.begin() != std_ret - std_vec.begin()) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[non-trivial copy required]
        {
            ft::vector<std::string>                  ft_vec;
            std::vector<std::string>                 std_vec;
            ft::vector<std::string>::const_iterator  ft_ret;
            std::vector<std::string>::const_iterator std_ret;

            for (idx = 0U; idx < Array<std::string>::len; ++idx) {
                START  = clock();
                ft_ret = ft_vec.insert(
                    ft_vec.begin() + ft_vec.size() / 2, Array<std::string>::inner[idx]
                );
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START   = clock();
                std_ret = std_vec.insert(
                    std_vec.begin() + std_vec.size() / 2, Array<std::string>::inner[idx]
                );
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())
                    || ft_ret - ft_vec.begin() != std_ret - std_vec.begin()) {
                    return KO;
                }
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma endregion
# pragma region[max_size]

inline static u8 MF_max_size()
{
    int ret;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[vector<i8>]
        {
            ft::vector<i8> const       ft_vec;
            std::vector<i8> const      std_vec;
            ft::vector<i8>::size_type  ft_ret;
            std::vector<i8>::size_type std_ret;

            START        = clock();
            ft_ret       = ft_vec.max_size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.max_size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                ret = ISO_OK;
            }
            if ((ft_ret == ft_vec.get_allocator().max_size())
                != (std_ret == std_vec.get_allocator().max_size())) {
                ret = KO;
            }
        }
# pragma endregion
# pragma region[vector<u32>]
        {
            ft::vector<u32> const       ft_vec;
            std::vector<u32> const      std_vec;
            ft::vector<u32>::size_type  ft_ret;
            std::vector<u32>::size_type std_ret;

            START        = clock();
            ft_ret       = ft_vec.max_size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.max_size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                ret = ISO_OK;
            }
            if ((ft_ret == ft_vec.get_allocator().max_size())
                != (std_ret == std_vec.get_allocator().max_size())) {
                ret = KO;
            }
        }
# pragma endregion
# pragma region[vector<std::pair<f64, i64> >]
        {
            ft::vector<std::pair<long double, i64> > const       ft_vec;
            std::vector<std::pair<long double, i64> > const      std_vec;
            ft::vector<std::pair<long double, i64> >::size_type  ft_ret;
            std::vector<std::pair<long double, i64> >::size_type std_ret;

            START        = clock();
            ft_ret       = ft_vec.max_size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.max_size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                ret = ISO_OK;
            }
            if ((ft_ret == ft_vec.get_allocator().max_size())
                != (std_ret == std_vec.get_allocator().max_size())) {
                ret = KO;
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[pop_back]

inline static u8 MF_pop_back()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::vector<int>  ft_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);
        std::vector<int> std_vec(&Array<i32>::inner[0], &Array<i32>::inner[Array<i32>::len]);

        for (idx = 0U; idx < Array<i32>::len; ++idx) {
            START = clock();
            ft_vec.pop_back();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_vec.pop_back();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.capacity() != std_vec.capacity()) {
                return ISO_OK;
            }
            if (ft_vec.size() != std_vec.size()
                || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
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

# pragma endregion
# pragma region[push_back]

inline static u8 MF_push_back()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
        {
            ft::vector<long double>  ft_vec;
            std::vector<long double> std_vec;

            for (idx = 0U; idx < Array<f128>::len; ++idx) {
                START = clock();
                ft_vec.push_back(Array<f128>::inner[idx]);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.push_back(Array<f128>::inner[idx]);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[non-trivial copy required]
        {
            ft::vector<std::string>  ft_vec;
            std::vector<std::string> std_vec;

            for (idx = 0U; idx < Array<std::string>::len; ++idx) {
                START = clock();
                ft_vec.push_back(Array<std::string>::inner[idx]);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.push_back(Array<std::string>::inner[idx]);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[rbegin]
# pragma region[constant]

inline static u8 MF_rbegin()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<char>::const_reverse_iterator  ft_ret;
        std::vector<char>::const_reverse_iterator std_ret;

        for (idx = 0U; idx < Array<Filename>::len; ++idx) {
            std::ifstream                     ifs0(Array<Filename>::inner[idx]);
            std::ifstream                     ifs1(Array<Filename>::inner[idx]);
            std::istream_iterator<char> const it0(ifs0);
            std::istream_iterator<char> const it1(ifs1);
            std::istream_iterator<char> const end_of_stream;
            ft::vector<char> const            ft_vec(it0, end_of_stream);
            std::vector<char> const           std_vec(it1, end_of_stream);

            START        = clock();
            ft_ret       = ft_vec.rbegin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.rbegin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.size() && std_vec.size() && *ft_ret != *std_ret) {
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

# pragma endregion
# pragma region[mutable]

inline static u8 MF_rbegin_mut()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<char>::reverse_iterator  ft_ret;
        std::vector<char>::reverse_iterator std_ret;

        for (idx = 0U; idx < Array<Filename>::len; ++idx) {
            std::ifstream                     ifs0(Array<Filename>::inner[idx]);
            std::ifstream                     ifs1(Array<Filename>::inner[idx]);
            std::istream_iterator<char> const it0(ifs0);
            std::istream_iterator<char> const it1(ifs1);
            std::istream_iterator<char> const end_of_stream;
            ft::vector<char>                  ft_vec(it0, end_of_stream);
            std::vector<char>                 std_vec(it1, end_of_stream);

            START        = clock();
            ft_ret       = ft_vec.rbegin();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.rbegin();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.size() && std_vec.size() && *ft_ret != *std_ret) {
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

# pragma endregion
# pragma endregion
# pragma region[rend]
# pragma region[constant]

inline static u8 MF_rend()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<char>::const_reverse_iterator  ft_ret;
        std::vector<char>::const_reverse_iterator std_ret;

        for (idx = 0U; idx < Array<Filename>::len; ++idx) {
            std::ifstream                     ifs0(Array<Filename>::inner[idx]);
            std::ifstream                     ifs1(Array<Filename>::inner[idx]);
            std::istream_iterator<char> const it0(ifs0);
            std::istream_iterator<char> const it1(ifs1);
            std::istream_iterator<char> const end_of_stream;
            ft::vector<char> const            ft_vec(it0, end_of_stream);
            std::vector<char> const           std_vec(it1, end_of_stream);

            START        = clock();
            ft_ret       = ft_vec.rend();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.rend();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.size() && std_vec.size() && *--ft_ret != *--std_ret) {
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

# pragma endregion
# pragma region[mutable]

inline static u8 MF_rend_mut()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<char>::reverse_iterator  ft_ret;
        std::vector<char>::reverse_iterator std_ret;

        for (idx = 0U; idx < Array<Filename>::len; ++idx) {
            std::ifstream                     ifs0(Array<Filename>::inner[idx]);
            std::ifstream                     ifs1(Array<Filename>::inner[idx]);
            std::istream_iterator<char> const it0(ifs0);
            std::istream_iterator<char> const it1(ifs1);
            std::istream_iterator<char> const end_of_stream;
            ft::vector<char>                  ft_vec(it0, end_of_stream);
            std::vector<char>                 std_vec(it1, end_of_stream);

            START        = clock();
            ft_ret       = ft_vec.rend();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.rend();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.size() && std_vec.size() && *--ft_ret != *--std_ret) {
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

# pragma endregion
# pragma endregion
# pragma region[reserve]

inline static u8 MF_reserve()
{
    int    ret;
    size_t n;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::vector<u16>  ft_vec(&Array<u16>::inner[0], &Array<u16>::inner[Array<u16>::len]);
        std::vector<u16> std_vec(&Array<u16>::inner[0], &Array<u16>::inner[Array<u16>::len]);

# pragma region[normal usage]
        {
            for (n = 0LU; n < 100LU; n += 10LU) {
                START = clock();
                ft_vec.reserve(n);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std_vec.reserve(n);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_vec.capacity() != std_vec.capacity()) {
                    if (ft_vec.capacity() < n) {
                        return KO;
                    }
                    ret = ISO_OK;
                }
                if (ft_vec.size() != std_vec.size()
                    || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                    return KO;
                }
            }
        }
# pragma endregion
# pragma region[overlimits usage]
        {
            try {
                ft_vec.reserve(ft_vec.max_size() + 42LU);
            }
            catch (std::length_error const &e) {
                goto reserve_overlimits_ok;
            }
            return KO;
        reserve_overlimits_ok:

            if (ft_vec.capacity() != std_vec.capacity()) {
                if (ft_vec.capacity() < ft_vec.size()) {
                    return KO;
                }
                ret = ISO_OK;
            }
            if (ft_vec.size() != std_vec.size()
                || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                return KO;
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[resize]

inline static u8 MF_resize()
{
    int    ret;
    size_t n;

    title(__func__);
    ret = IMPL_OK;
    try {
        ft::vector<int>  ft_vec;
        std::vector<int> std_vec;

        for (n = 0LU; n < Array<i32>::len; ++n) {
            START = clock();
            ft_vec.resize(n * n, Array<i32>::inner[n]);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_vec.resize(n * n, Array<i32>::inner[n]);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.capacity() != std_vec.capacity()) {
                if (ft_vec.capacity() < n * n) {
                    return KO;
                }
                ret = ISO_OK;
            }
            if (ft_vec.size() != std_vec.size()
                || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
                return KO;
            }
        }
        for (--n; n; --n) {
            START = clock();
            ft_vec.resize(n * n);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_vec.resize(n * n);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec.capacity() != std_vec.capacity()) {
                if (ft_vec.capacity() < n * n) {
                    return KO;
                }
                ret = ISO_OK;
            }
            if (ft_vec.size() != std_vec.size()
                || !std::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin())) {
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

# pragma endregion
# pragma region[size]

inline static u8 MF_size()
{
    size_t n;

    title(__func__);
    try {
        for (n = 0LU; n < 10LU; ++n) {
            ft::vector<u8> const       ft_vec(n, 42U);
            std::vector<u8> const      std_vec(n, 42U);
            ft::vector<u8>::size_type  ft_ret;
            std::vector<u8>::size_type std_ret;

            START        = clock();
            ft_ret       = ft_vec.size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_vec.size();
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

# pragma endregion
# pragma region[swap]

inline static u8 MF_swap()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
        {
            ft::vector<u32>  ft_vec0(&Array<u32>::inner[0], &Array<u32>::inner[Array<u32>::len]);
            std::vector<u32> std_vec0(&Array<u32>::inner[0], &Array<u32>::inner[Array<u32>::len]);
            ft::vector<u32>  ft_vec1;
            std::vector<u32> std_vec1;

            for (idx = 0U; idx < Array<u32>::len * 2; ++idx) {
                ft_vec1.insert(ft_vec1.begin(), Array<u32>::inner[idx / 2]);
                std_vec1.insert(std_vec1.begin(), Array<u32>::inner[idx / 2]);
            }

            START = clock();
            ft_vec0.swap(ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_vec0.swap(std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec0.capacity() != std_vec0.capacity()) {
                if (ft_vec0.capacity() < ft_vec0.size()) {
                    return KO;
                }
                ret = ISO_OK;
            }
            if (ft_vec0.size() != std_vec0.size()
                || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin())
                || ft_vec1.size() != std_vec1.size()
                || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin())) {
                return KO;
            }
        }
# pragma endregion
# pragma region[non-trivial copy required]
        {
            ft::vector<std::string> ft_vec0(
                &Array<std::string>::inner[0], &Array<std::string>::inner[Array<std::string>::len]
            );
            std::vector<std::string> std_vec0(
                &Array<std::string>::inner[0], &Array<std::string>::inner[Array<std::string>::len]
            );
            ft::vector<std::string>  ft_vec1;
            std::vector<std::string> std_vec1;

            for (idx = 0U; idx < Array<std::string>::len * 2; ++idx) {
                ft_vec1.insert(ft_vec1.begin(), Array<std::string>::inner[idx / 2]);
                std_vec1.insert(std_vec1.begin(), Array<std::string>::inner[idx / 2]);
            }

            START = clock();
            ft_vec0.swap(ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_vec0.swap(std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec0.capacity() != std_vec0.capacity()) {
                if (ft_vec0.capacity() < ft_vec0.size()) {
                    return KO;
                }
                ret = ISO_OK;
            }
            if (ft_vec0.size() != std_vec0.size()
                || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin())
                || ft_vec1.size() != std_vec1.size()
                || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin())) {
                return KO;
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma endregion
# pragma region[operators]
# pragma region[assign]

inline static u8 MO_assign()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
        {
            ft::vector<double>  ft_vec0(&Array<f64>::inner[0], &Array<f64>::inner[Array<f64>::len]);
            std::vector<double> std_vec0(
                &Array<f64>::inner[0], &Array<f64>::inner[Array<f64>::len]
            );
            ft::vector<double>  ft_vec1;
            std::vector<double> std_vec1;

            for (idx = 0U; idx < Array<f64>::len * 2; ++idx) {
                ft_vec1.insert(ft_vec1.begin() + idx / 2, Array<f64>::inner[idx / 2]);
                std_vec1.insert(std_vec1.begin() + idx / 2, Array<f64>::inner[idx / 2]);
            }

            START        = clock();
            ft_vec0      = ft_vec1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_vec0      = std_vec1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec0.capacity() != std_vec0.capacity()) {
                if (ft_vec0.capacity() < ft_vec0.size()) {
                    return KO;
                }
                ret = ISO_OK;
            }
            if (ft_vec0.size() != std_vec0.size()
                || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin())) {
                return KO;
            }
        }
# pragma endregion
# pragma region[non-trivial copy required]
        {
            ft::vector<std::string> ft_vec0(
                &Array<std::string>::inner[0], &Array<std::string>::inner[Array<std::string>::len]
            );
            std::vector<std::string> std_vec0(
                &Array<std::string>::inner[0], &Array<std::string>::inner[Array<std::string>::len]
            );
            ft::vector<std::string>  ft_vec1;
            std::vector<std::string> std_vec1;

            for (idx = 0U; idx < Array<std::string>::len * 2; ++idx) {
                ft_vec1.insert(ft_vec1.begin() + idx / 2, Array<std::string>::inner[idx / 2]);
                std_vec1.insert(std_vec1.begin() + idx / 2, Array<std::string>::inner[idx / 2]);
            }

            START        = clock();
            ft_vec0      = ft_vec1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_vec0      = std_vec1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec0.capacity() != std_vec0.capacity()) {
                if (ft_vec0.capacity() < ft_vec0.size()) {
                    return KO;
                }
                ret = ISO_OK;
            }
            if (ft_vec0.size() != std_vec0.size()
                || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin())) {
                return KO;
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion
# pragma region[subscript]
# pragma region[constant]

inline static u8 MO_subscript()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<i64> const ft_vector(&Array<i64>::inner[0], &Array<i64>::inner[Array<i64>::len]);
        std::vector<i64> const std_vector(
            &Array<i64>::inner[0], &Array<i64>::inner[Array<i64>::len]
        );

        for (idx = 0U; idx < 10U; ++idx) {
            START              = clock();
            i64 const &ft_ref  = ft_vector[idx];
            DURATION_FT        = clock() - START;
            DURATION_FT       += !DURATION_FT;

            START               = clock();
            i64 const &std_ref  = std_vector[idx];
            DURATION_STD        = clock() - START;
            DURATION_STD       += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ref != std_ref) {
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

# pragma endregion
# pragma region[mutable]

inline static u8 MO_subscript_mut()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<i64>  ft_vector(&Array<i64>::inner[0], &Array<i64>::inner[Array<i64>::len]);
        std::vector<i64> std_vector(&Array<i64>::inner[0], &Array<i64>::inner[Array<i64>::len]);

        for (idx = 0U; idx < 10U; ++idx) {
            START        = clock();
            i64 &ft_ref  = ft_vector[idx];
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            i64 &std_ref  = std_vector[idx];
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ref != std_ref) {
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

# pragma endregion
# pragma endregion
# pragma region[eq]

inline static u8 MO_eq()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<std::string>  ft_vec0;
        ft::vector<std::string>  ft_vec1;
        std::vector<std::string> std_vec0;
        std::vector<std::string> std_vec1;
        bool                     ft_ret;
        bool                     std_ret;

        for (idx = 0U; idx < Array<std::string>::len; ++idx) {
            START        = clock();
            ft_ret       = ft::operator==(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator==(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec0.push_back(Array<std::string>::inner[idx]);
            std_vec0.push_back(Array<std::string>::inner[idx]);

            START        = clock();
            ft_ret       = ft::operator==(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator==(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec1.push_back(Array<std::string>::inner[idx]);
            std_vec1.push_back(Array<std::string>::inner[idx]);
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma region[ne]

inline static u8 MO_ne()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<std::string>  ft_vec0;
        ft::vector<std::string>  ft_vec1;
        std::vector<std::string> std_vec0;
        std::vector<std::string> std_vec1;
        bool                     ft_ret;
        bool                     std_ret;

        for (idx = 0U; idx < Array<std::string>::len; ++idx) {
            START        = clock();
            ft_ret       = ft::operator!=(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator!=(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec0.push_back(Array<std::string>::inner[idx]);
            std_vec0.push_back(Array<std::string>::inner[idx]);

            START        = clock();
            ft_ret       = ft::operator!=(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator!=(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec1.push_back(Array<std::string>::inner[idx]);
            std_vec1.push_back(Array<std::string>::inner[idx]);
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma region[lt]

inline static u8 MO_lt()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<std::string>  ft_vec0;
        ft::vector<std::string>  ft_vec1;
        std::vector<std::string> std_vec0;
        std::vector<std::string> std_vec1;
        bool                     ft_ret;
        bool                     std_ret;

        for (idx = 0U; idx < Array<std::string>::len; ++idx) {
            START        = clock();
            ft_ret       = ft::operator<(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec0.push_back(Array<std::string>::inner[idx]);
            std_vec0.push_back(Array<std::string>::inner[idx]);

            START        = clock();
            ft_ret       = ft::operator<(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec1.push_back(Array<std::string>::inner[idx]);
            std_vec1.push_back(Array<std::string>::inner[idx]);
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma region[gt]

inline static u8 MO_gt()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<std::string>  ft_vec0;
        ft::vector<std::string>  ft_vec1;
        std::vector<std::string> std_vec0;
        std::vector<std::string> std_vec1;
        bool                     ft_ret;
        bool                     std_ret;

        for (idx = 0U; idx < Array<std::string>::len; ++idx) {
            START        = clock();
            ft_ret       = ft::operator>(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec0.push_back(Array<std::string>::inner[idx]);
            std_vec0.push_back(Array<std::string>::inner[idx]);

            START        = clock();
            ft_ret       = ft::operator>(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec1.push_back(Array<std::string>::inner[idx]);
            std_vec1.push_back(Array<std::string>::inner[idx]);
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma region[le]

inline static u8 MO_le()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<std::string>  ft_vec0;
        ft::vector<std::string>  ft_vec1;
        std::vector<std::string> std_vec0;
        std::vector<std::string> std_vec1;
        bool                     ft_ret;
        bool                     std_ret;

        for (idx = 0U; idx < Array<std::string>::len; ++idx) {
            START        = clock();
            ft_ret       = ft::operator<=(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec0.push_back(Array<std::string>::inner[idx]);
            std_vec0.push_back(Array<std::string>::inner[idx]);

            START        = clock();
            ft_ret       = ft::operator<=(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec1.push_back(Array<std::string>::inner[idx]);
            std_vec1.push_back(Array<std::string>::inner[idx]);
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma region[ge]

inline static u8 MO_ge()
{
    u32 idx;

    title(__func__);
    try {
        ft::vector<std::string>  ft_vec0;
        ft::vector<std::string>  ft_vec1;
        std::vector<std::string> std_vec0;
        std::vector<std::string> std_vec1;
        bool                     ft_ret;
        bool                     std_ret;

        for (idx = 0U; idx < Array<std::string>::len; ++idx) {
            START        = clock();
            ft_ret       = ft::operator>=(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec0.push_back(Array<std::string>::inner[idx]);
            std_vec0.push_back(Array<std::string>::inner[idx]);

            START        = clock();
            ft_ret       = ft::operator>=(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            ft_vec1.push_back(Array<std::string>::inner[idx]);
            std_vec1.push_back(Array<std::string>::inner[idx]);
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma endregion
# pragma endregion
# pragma region[swap]

inline static u8 swap()
{
    int ret;
    u32 idx;

    title(__func__);
    ret = IMPL_OK;
    try {
# pragma region[trivially copyable]
        {
            ft::vector<u32>  ft_vec0(&Array<u32>::inner[0], &Array<u32>::inner[Array<u32>::len]);
            std::vector<u32> std_vec0(&Array<u32>::inner[0], &Array<u32>::inner[Array<u32>::len]);
            ft::vector<u32>  ft_vec1;
            std::vector<u32> std_vec1;

            for (idx = 0U; idx < Array<u32>::len * 2; ++idx) {
                ft_vec1.insert(ft_vec1.begin(), Array<u32>::inner[idx / 2]);
                std_vec1.insert(std_vec1.begin(), Array<u32>::inner[idx / 2]);
            }

            START = clock();
            ft::swap(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::swap(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec0.capacity() != std_vec0.capacity()) {
                if (ft_vec0.capacity() < ft_vec0.size()) {
                    return KO;
                }
                ret = ISO_OK;
            }
            if (ft_vec0.size() != std_vec0.size()
                || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin())
                || ft_vec1.size() != std_vec1.size()
                || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin())) {
                return KO;
            }
        }
# pragma endregion
# pragma region[non-trivial copy required]
        {
            ft::vector<std::string> ft_vec0(
                &Array<std::string>::inner[0], &Array<std::string>::inner[Array<std::string>::len]
            );
            std::vector<std::string> std_vec0(
                &Array<std::string>::inner[0], &Array<std::string>::inner[Array<std::string>::len]
            );
            ft::vector<std::string>  ft_vec1;
            std::vector<std::string> std_vec1;

            for (idx = 0U; idx < Array<std::string>::len * 2; ++idx) {
                ft_vec1.insert(ft_vec1.begin(), Array<std::string>::inner[idx / 2]);
                std_vec1.insert(std_vec1.begin(), Array<std::string>::inner[idx / 2]);
            }

            START = clock();
            ft::swap(ft_vec0, ft_vec1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::swap(std_vec0, std_vec1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_vec0.capacity() != std_vec0.capacity()) {
                if (ft_vec0.capacity() < ft_vec0.size()) {
                    return KO;
                }
                ret = ISO_OK;
            }
            if (ft_vec0.size() != std_vec0.size()
                || !std::equal(ft_vec0.begin(), ft_vec0.end(), std_vec0.begin())
                || ft_vec1.size() != std_vec1.size()
                || !std::equal(ft_vec1.begin(), ft_vec1.end(), std_vec1.begin())) {
                return KO;
            }
        }
# pragma endregion
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

# pragma endregion

u8 test_vector()
{
    TestFn const tests[] = {
# pragma region[tests]
        default_template_type_Alloc,
# pragma region[constructors]
        C_default,
        C_copy,
        C_fill,
        C_range,
# pragma endregion
# pragma region[members]
# pragma region[types]
        MT_allocator_type,
        MT_const_iterator,
        MT_const_pointer,
        MT_const_reference,
        MT_const_reverse_iterator,
        MT_iterator,
        MT_pointer,
        MT_reference,
        MT_reverse_iterator,
        MT_value_type,
# pragma endregion
# pragma region[functions]
        MF_assign_fill,
        MF_assign_range,
        MF_at,
        MF_at_mut,
        MF_back,
        MF_back_mut,
        MF_begin,
        MF_begin_mut,
        MF_capacity,
        MF_clear,
        MF_empty,
        MF_end,
        MF_end_mut,
        MF_erase_range,
        MF_erase_single,
        MF_front,
        MF_front_mut,
        MF_get_allocator,
        MF_insert_fill,
        MF_insert_range,
        MF_insert_single,
        MF_max_size,
        MF_pop_back,
        MF_push_back,
        MF_rbegin,
        MF_rbegin_mut,
        MF_rend,
        MF_rend_mut,
        MF_reserve,
        MF_resize,
        MF_size,
        MF_swap,
# pragma endregion
# pragma region[operators]
        MO_assign,
        MO_subscript,
        MO_subscript_mut,
        MO_eq,
        MO_ne,
        MO_lt,
        MO_gt,
        MO_le,
        MO_ge,
# pragma endregion
# pragma endregion
        swap,
        NULL
# pragma endregion
    };
    u8                    koCount;
    u32                   idx;
    struct timespec const delay = {SLEEP_TIME_SEC, SLEEP_TIME_NANOSEC};

    nanosleep(&delay, NULL);

    std::cerr << LIGHT_BLUE_FG;
    std::cout << "####################################################" << '\n';
    std::cout << "##                     VECTOR                     ##" << '\n';
    std::cout << "####################################################" << '\n';
    std::cerr << RESET;

    for (koCount = 0U, idx = 0U; tests[idx]; ++idx) {
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
            std::cerr << RED_FG;
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
