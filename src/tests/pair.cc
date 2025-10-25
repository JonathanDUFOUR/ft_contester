#define DISABLE
#ifndef DISABLE

# include "benchmark.hh"
# include "colors.hh"
# include "headers.hh"
# include "test_status.hh"
# include "tester.hh"
# include "type_traits.hh"
# include "types/array.hh"
# include "types/numerics.hh"
# include PAIR_HEADER
# include MAKE_PAIR_HEADER
# include <cstring>
# include <ctime>
# include <iostream>

inline static u8 __test_constructor()
{
    int ret;

    title(__func__);
    ret = IMPL_OK;
    try {
        // Default constructor
        {
            START = clock();
            ft::Pair<int, u32> const ft_pair;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::pair<int, u32> const std_pair;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (sizeof(ft_pair) != sizeof(std_pair)
                || memcmp(&ft_pair, &std_pair, sizeof(ft_pair))) {
                ret = ISO_OK;
            }
            if (ft_pair.first != std_pair.first || ft_pair.second != std_pair.second) {
                return KO;
            }
        }
        // Parameters constructor
        {
            START = clock();
            ft::Pair<u32, int> const ft_pair(42U, -42);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::pair<u32, int> const std_pair(42U, -42);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (sizeof(ft_pair) != sizeof(std_pair)
                || memcmp(&ft_pair, &std_pair, sizeof(ft_pair))) {
                ret = ISO_OK;
            }
            if (ft_pair.first != std_pair.first || ft_pair.second != std_pair.second) {
                return KO;
            }
        }
        // Copy constructor
        {
            // Default pair
            {
                ft::Pair<char const, char const> const  ft_pair0;
                std::pair<char const, char const> const std_pair0;

                START = clock();
                ft::Pair<char const, char const> const ft_pair1(ft_pair0);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::pair<char const, char const> const std_pair1(std_pair0);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

                if (sizeof(ft_pair1) != sizeof(std_pair1)
                    || memcmp(&ft_pair1, &std_pair1, sizeof(ft_pair1))) {
                    ret = ISO_OK;
                }
                if (ft_pair1.first != std_pair1.first || ft_pair1.second != std_pair1.second) {
                    return KO;
                }
            }
            // Filled pair
            {
                ft::Pair<char const, char const> const  ft_pair0('!', '?');
                std::pair<char const, char const> const std_pair0('!', '?');

                START = clock();
                ft::Pair<char, char> const ft_pair1(ft_pair0);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::pair<char, char> const std_pair1(std_pair0);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

                if (sizeof(ft_pair1) != sizeof(std_pair1)
                    || memcmp(&ft_pair1, &std_pair1, sizeof(ft_pair1))) {
                    ret = ISO_OK;
                }
                if (ft_pair1.first != std_pair1.first || ft_pair1.second != std_pair1.second) {
                    return KO;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return ret;
}

inline static u8 __test_type_first_type()
{
    title(__func__);
    try {
        typedef ft::Pair<f128, char> pair_type;

        if (!tester::is_same<pair_type::first_type, f128>::value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_type_second_type()
{
    title(__func__);
    try {
        typedef ft::Pair<f128, char> pair_type;

        if (!tester::is_same<pair_type::second_type, char>::value) {
            return KO;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

inline static u8 __test_function_make_pair()
{
    u32 idx;

    title(__func__);
    try {
        ft::Pair<u64, std::string>  ft_pair;
        std::pair<u64, std::string> std_pair;

        for (idx = 0U; idx < Array<u64>::len && idx < Array<std::string>::len; ++idx) {
            START        = clock();
            ft_pair      = ft::make_pair(Array<u64>::at(idx), Array<std::string>::at(idx));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_pair      = std::make_pair(Array<u64>::at(idx), Array<std::string>::at(idx));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_pair.first != std_pair.first || ft_pair.second != std_pair.second) {
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
    title(__func__);
    try {
        // Assigning mutable -> mutable
        {
            ft::Pair<i8, std::string>        ft_pair0(-1, "Hello World");
            ft::Pair<i8, std::string> const  ft_pair1(55, "How are you today ?");
            std::pair<i8, std::string>       std_pair0(-1, "Hello World");
            std::pair<i8, std::string> const std_pair1(55, "How are you today ?");

            START        = clock();
            ft_pair0     = ft_pair1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_pair0     = std_pair1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_pair0.first != std_pair0.first || ft_pair0.second != std_pair0.second) {
                return KO;
            }
        }
        // Assigning constant -> mutable
        {
            ft::Pair<i8, std::string>                    ft_pair0(-1, "Hello World");
            ft::Pair<i8 const, std::string const> const  ft_pair1(55, "How are you today ?");
            std::pair<i8, std::string>                   std_pair0(-1, "Hello World");
            std::pair<i8 const, std::string const> const std_pair1(55, "How are you today ?");

            START        = clock();
            ft_pair0     = ft_pair1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_pair0     = std_pair1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_pair0.first != std_pair0.first || ft_pair0.second != std_pair0.second) {
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
    title(__func__);
    try {
        // first == first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator==(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator==(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second != second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 209U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 209U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator==(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator==(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first != first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.22f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.22f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator==(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator==(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first != first | second != second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.22f, 209U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.22f, 209U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator==(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator==(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

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

inline static u8 __test_operator_different()
{
    title(__func__);
    try {
        // first == first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator!=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator!=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second != second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 209U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 209U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator!=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator!=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first != first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.22f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.22f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator!=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator!=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first != first | second != second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.22f, 209U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.22f, 209U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator!=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator!=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

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

inline static u8 __test_operator_lower()
{
    title(__func__);
    try {
        // first < first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first < first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 201U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first < first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(21.12f, 201U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 201U);
            std::pair<f32, u8> const std_pair0(21.12f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 201U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(21.12f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 201U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 201U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

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

inline static u8 __test_operator_greater()
{
    title(__func__);
    try {
        // first < first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first < first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 201U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first < first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(21.12f, 201U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 201U);
            std::pair<f32, u8> const std_pair0(21.12f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 201U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(21.12f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 201U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 201U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

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

inline static u8 __test_operator_lower_or_equivalent()
{
    title(__func__);
    try {
        // first < first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first < first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 201U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first < first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(21.12f, 201U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 201U);
            std::pair<f32, u8> const std_pair0(21.12f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 201U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(21.12f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 201U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 201U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator<=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator<=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

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

inline static u8 __test_operator_greater_or_equivalent()
{
    title(__func__);
    try {
        // first < first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first < first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 201U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first < first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(21.12f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(21.12f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(21.12f, 201U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 201U);
            std::pair<f32, u8> const std_pair0(21.12f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 201U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first > first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(21.12f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(21.12f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second < second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 201U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 201U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second > second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 201U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 201U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }
        }
        // first == first | second == second
        {
            ft::Pair<f32, u8> const  ft_pair0(12.21f, 210U);
            ft::Pair<f32, u8> const  ft_pair1(12.21f, 210U);
            std::pair<f32, u8> const std_pair0(12.21f, 210U);
            std::pair<f32, u8> const std_pair1(12.21f, 210U);
            bool                     ft_ret;
            bool                     std_ret;

            START        = clock();
            ft_ret       = ft::operator>=(ft_pair0, ft_pair1);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std::operator>=(std_pair0, std_pair1);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<f32>(DURATION_FT) / static_cast<f32>(DURATION_STD));

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

u8 test_pair()
{
    TestFn const tests[] = {
        __test_constructor,
        __test_type_first_type,
        __test_type_second_type,
        __test_function_make_pair,
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
    std::cout << "####################################################" << '\n';
    std::cout << "##                      PAIR                      ##" << '\n';
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
