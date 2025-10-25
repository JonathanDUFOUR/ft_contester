#define DISABLE
#ifndef DISABLE

# include "arrays.hh"
# include "benchmark.hh"
# include "colors.hh"
# include "headers.hh"
# include "iterator/restrictor/random_access_iterator_restrictor.tpp"
# include "numerics.hh"
# include "tester.hh"
# include REVERSE_ITERATOR_HEADER
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <iomanip>
# include <iostream>
# include <limits>

inline static u8 __test_constructor()
{
    u32 idx;

    title(__func__);
    try {
        // Default constructor
        {
            START = clock();
            ft::reverse_iterator<
                tester::random_access_iterator_restrictor<std::ostream const *>
            > const ft_rit;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::reverse_iterator<
                tester::random_access_iterator_restrictor<std::ostream const *>
            > const std_rit;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_rit) != sizeof(std_rit) || memcmp(&ft_rit, &std_rit, sizeof(ft_rit))) {
                return EXIT_FAILURE;
            }
        }
        // Wrap constructor
        {
            for (idx = 0U; idx < Array<i32>::len; ++idx) {
                tester::random_access_iterator_restrictor<i32 const *> const it(
                    &Array<i32>::at(idx)
                );

                START = clock();
                ft::reverse_iterator<tester::random_access_iterator_restrictor<i32 const *> > const
                    ft_rit(it);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::reverse_iterator<tester::random_access_iterator_restrictor<i32 const *> > const
                    std_rit(it);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (sizeof(ft_rit) != sizeof(std_rit)
                    || memcmp(&ft_rit, &std_rit, sizeof(ft_rit))) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Copy constructor
        {
            // Default position
            {
                ft::reverse_iterator<tester::random_access_iterator_restrictor<i32 const *> > const
                    ft_rit0;
                std::reverse_iterator<tester::random_access_iterator_restrictor<i32 const *> > const
                    std_rit0;

                START = clock();
                ft::reverse_iterator<tester::random_access_iterator_restrictor<i32 const *> > const
                    ft_rit1(ft_rit0);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::reverse_iterator<tester::random_access_iterator_restrictor<i32 const *> > const
                    std_rit1(std_rit0);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (sizeof(ft_rit1) != sizeof(std_rit1)
                    || memcmp(&ft_rit1, &std_rit1, sizeof(ft_rit1))) {
                    return EXIT_FAILURE;
                }
            }
            // Defined position
            {
                for (idx = 0U; idx < Array<i32>::len; ++idx) {
                    tester::random_access_iterator_restrictor<i32 const *> const it(
                        &Array<i32>::at(idx)
                    );

                    START = clock();
                    ft::reverse_iterator<
                        tester::random_access_iterator_restrictor<i32 const *>
                    > const ft_rit0(it);
                    DURATION_FT  = clock() - START;
                    DURATION_FT += !DURATION_FT;

                    START = clock();
                    std::reverse_iterator<
                        tester::random_access_iterator_restrictor<i32 const *>
                    > const std_rit0(it);
                    DURATION_STD  = clock() - START;
                    DURATION_STD += !DURATION_STD;

                    RATIOS.insert(
                        static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD)
                    );

                    START = clock();
                    ft::reverse_iterator<
                        tester::random_access_iterator_restrictor<i32 const *>
                    > const ft_rit1(ft_rit0);
                    DURATION_FT  = clock() - START;
                    DURATION_FT += !DURATION_FT;

                    START = clock();
                    std::reverse_iterator<
                        tester::random_access_iterator_restrictor<i32 const *>
                    > const std_rit1(std_rit0);
                    DURATION_STD  = clock() - START;
                    DURATION_STD += !DURATION_STD;

                    RATIOS.insert(
                        static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD)
                    );

                    START = clock();
                    ft::reverse_iterator<
                        tester::random_access_iterator_restrictor<i32 const *> const
                    > const ft_rit2(ft_rit1);
                    DURATION_FT  = clock() - START;
                    DURATION_FT += !DURATION_FT;

                    START = clock();
                    std::reverse_iterator<
                        tester::random_access_iterator_restrictor<i32 const *> const
                    > const std_rit2(std_rit1);
                    DURATION_STD  = clock() - START;
                    DURATION_STD += !DURATION_STD;

                    RATIOS.insert(
                        static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD)
                    );

                    if ((sizeof(ft_rit1) != sizeof(std_rit1))
                        || sizeof(ft_rit2) != sizeof(std_rit2)
                        || (memcmp(&ft_rit0, &ft_rit1, sizeof(ft_rit0))
                            != memcmp(&std_rit0, &std_rit1, sizeof(std_rit0)))
                        || (memcmp(&ft_rit1, &ft_rit2, sizeof(ft_rit1))
                            != memcmp(&std_rit1, &std_rit2, sizeof(std_rit1)))) {
                        return EXIT_FAILURE;
                    }
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

inline static u8 __test_function_base()
{
    u32 idx;

    title(__func__);
    try {
        for (idx = 0U; idx < Array<f64>::len; ++idx) {
            tester::random_access_iterator_restrictor<double const *> const it(
                &Array<f64>::at(idx)
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<double const *> > const
                ft_rit(it);
            std::reverse_iterator<tester::random_access_iterator_restrictor<double const *> > const
                                                                      std_rit(it);
            tester::random_access_iterator_restrictor<double const *> ft_ret;
            tester::random_access_iterator_restrictor<double const *> std_ret;

            START        = clock();
            ft_ret       = ft_rit.base();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_rit.base();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
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
    u32 idx;

    title(__func__);
    try {
        ft::reverse_iterator<tester::random_access_iterator_restrictor<std::string const *> >
            ft_rit0;
        std::reverse_iterator<tester::random_access_iterator_restrictor<std::string const *> >
            std_rit0;

        for (idx = 0U; idx < Array<std::string>::len; ++idx) {
            tester::random_access_iterator_restrictor<std::string *> const it0(
                &Array<std::string>::at(idx)
            );
            tester::random_access_iterator_restrictor<std::string const *> const it1(
                &Array<std::string>::at(idx)
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> > const
                ft_rit1(it0);
            ft::reverse_iterator<
                tester::random_access_iterator_restrictor<std::string const *>
            > const ft_rit2(it1);
            std::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> > const
                std_rit1(it0);
            std::reverse_iterator<
                tester::random_access_iterator_restrictor<std::string const *>
            > const std_rit2(it1);

            START        = clock();
            ft_rit0      = ft_rit1;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_rit0      = std_rit1;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (memcmp(&ft_rit0, &ft_rit1, sizeof(ft_rit0))
                != memcmp(&std_rit0, &std_rit1, sizeof(std_rit0))) {
                return EXIT_FAILURE;
            }

            START        = clock();
            ft_rit0      = ft_rit2;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_rit0      = std_rit2;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (memcmp(&ft_rit0, &ft_rit2, sizeof(ft_rit0))
                != memcmp(&std_rit0, &std_rit2, sizeof(std_rit0))) {
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

inline static u8 __test_operator_dereference()
{
    u32 idx;

    title(__func__);
    try {
        // Mutable access
        {
            for (idx = 1U; idx <= Array<i16>::len; ++idx) {
                tester::random_access_iterator_restrictor<i16 *> const it(&Array<i16>::at(idx));
                ft::reverse_iterator<tester::random_access_iterator_restrictor<i16 *> > const
                    ft_rit(it);
                std::reverse_iterator<tester::random_access_iterator_restrictor<i16 *> > const
                    std_rit(it);

                START        = clock();
                i16 &ft_nb   = *ft_rit;
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                i16 &std_nb   = *std_rit;
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_nb != std_nb) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Constant access
        {
            for (idx = 1U; idx <= Array<i16>::len; ++idx) {
                tester::random_access_iterator_restrictor<i16 const *> const it(
                    &Array<i16>::at(idx)
                );
                ft::reverse_iterator<tester::random_access_iterator_restrictor<i16 const *> > const
                    ft_rit(it);
                std::reverse_iterator<tester::random_access_iterator_restrictor<i16 const *> > const
                    std_rit(it);

                START             = clock();
                i16 const &ft_nb  = *ft_rit;
                DURATION_FT       = clock() - START;
                DURATION_FT      += !DURATION_FT;

                START              = clock();
                i16 const &std_nb  = *std_rit;
                DURATION_STD       = clock() - START;
                DURATION_STD      += !DURATION_STD;

                if (ft_nb != std_nb) {
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

inline static u8 __test_operator_maddress()
{
    u32 idx;

    title(__func__);
    try {
        // Mutable access
        {
            for (idx = 1U; idx <= Array<std::pair<i32, char> >::len; ++idx) {
                tester::random_access_iterator_restrictor<std::pair<i32, char> *> const it(
                    &Array<std::pair<i32, char> >::at(idx)
                );
                ft::reverse_iterator<
                    tester::random_access_iterator_restrictor<std::pair<i32, char> *>
                > const ft_rit(it);
                std::reverse_iterator<
                    tester::random_access_iterator_restrictor<std::pair<i32, char> *>
                > const std_rit(it);

                START          = clock();
                i32 &ft_first  = ft_rit->first;
                DURATION_FT    = clock() - START;
                DURATION_FT   += !DURATION_FT;

                START           = clock();
                i32 &std_first  = std_rit->first;
                DURATION_STD    = clock() - START;
                DURATION_STD   += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_first != std_first) {
                    return EXIT_FAILURE;
                }

                START            = clock();
                char &ft_second  = ft_rit->second;
                DURATION_FT      = clock() - START;
                DURATION_FT     += !DURATION_FT;

                START             = clock();
                char &std_second  = std_rit->second;
                DURATION_STD      = clock() - START;
                DURATION_STD     += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_second != std_second) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Constant access
        {
            for (idx = 1U; idx <= Array<std::pair<i32, char> >::len; ++idx) {
                tester::random_access_iterator_restrictor<std::pair<i32, char> const *> const it(
                    &Array<std::pair<i32, char> >::at(idx)
                );
                ft::reverse_iterator<
                    tester::random_access_iterator_restrictor<std::pair<i32, char> const *>
                > const ft_rit(it);
                std::reverse_iterator<
                    tester::random_access_iterator_restrictor<std::pair<i32, char> const *>
                > const std_rit(it);

                START                = clock();
                i32 const &ft_first  = ft_rit->first;
                DURATION_FT          = clock() - START;
                DURATION_FT         += !DURATION_FT;

                START                 = clock();
                i32 const &std_first  = std_rit->first;
                DURATION_STD          = clock() - START;
                DURATION_STD         += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_first != std_first) {
                    return EXIT_FAILURE;
                }

                START                  = clock();
                char const &ft_second  = ft_rit->second;
                DURATION_FT            = clock() - START;
                DURATION_FT           += !DURATION_FT;

                START                   = clock();
                char const &std_second  = std_rit->second;
                DURATION_STD            = clock() - START;
                DURATION_STD           += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_second != std_second) {
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

inline static u8 __test_operator_increment()
{
    u32 idx;

    title(__func__);
    try {
        // Prefix incrementation
        {
            tester::random_access_iterator_restrictor<u64 const *> it(
                &Array<u64>::at(Array<u64>::len)
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > ft_rit(
                it
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > std_rit(
                it
            );

            for (idx = 1U; idx < Array<u64>::len; ++idx) {
                START = clock();
                ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> >
                    &ft_ret  = ++ft_rit;
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> >
                    &std_ret  = ++std_rit;
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base()) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Postfix incrementation
        {
            tester::random_access_iterator_restrictor<u64 const *> it(
                &Array<u64>::at(Array<u64>::len)
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > ft_rit(
                it
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > std_rit(
                it
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> >  ft_ret;
            std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > std_ret;

            for (idx = 1U; idx > Array<u64>::len; ++idx) {
                START        = clock();
                ft_ret       = ft_rit++;
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std_rit++;
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base()) {
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

inline static u8 __test_operator_decrement()
{
    u32 idx;

    title(__func__);
    try {
        // Prefix decrementation
        {
            tester::random_access_iterator_restrictor<u64 const *> it(&Array<u64>::at(0));
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > ft_rit(
                it
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > std_rit(
                it
            );

            for (idx = 1U; idx < Array<u64>::len; ++idx) {
                START = clock();
                ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> >
                    &ft_ret  = --ft_rit;
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> >
                    &std_ret  = --std_rit;
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base()) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Postfix decrementation
        {
            tester::random_access_iterator_restrictor<u64 const *> it(&Array<u64>::at(0));
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > ft_rit(
                it
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > std_rit(
                it
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> >  ft_ret;
            std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > std_ret;

            for (idx = 1U; idx < Array<u64>::len; ++idx) {
                START        = clock();
                ft_ret       = ft_rit--;
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std_rit--;
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base()) {
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

inline static u8 __test_operator_add_assign()
{
    u32 idx;

    title(__func__);
    try {
        for (idx = 0U; idx < Array<u64>::len; ++idx) {
            tester::random_access_iterator_restrictor<u64 const *> it(
                &Array<u64>::at(Array<u64>::len - 1)
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > ft_rit(
                it
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > std_rit(
                it
            );

            START = clock();
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > &ft_ret =
                ft_rit  += idx;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> >
                &std_ret = std_rit += idx;
            DURATION_STD            = clock() - START;
            DURATION_STD           += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base()) {
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

inline static u8 __test_operator_sub_assign()
{
    u32 idx;

    title(__func__);
    try {
        for (idx = 0U; idx < Array<u64>::len; ++idx) {
            tester::random_access_iterator_restrictor<u64 const *> it(&Array<u64>::at(0));
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > ft_rit(
                it
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > std_rit(
                it
            );

            START = clock();
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> > &ft_ret =
                ft_rit  -= idx;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::reverse_iterator<tester::random_access_iterator_restrictor<u64 const *> >
                &std_ret = std_rit -= idx;
            DURATION_STD            = clock() - START;
            DURATION_STD           += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret.base() != std_ret.base() || ft_rit.base() != std_rit.base()) {
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

inline static u8 __test_operator_add()
{
    u32 idx;

    title(__func__);
    try {
        // Member operator
        {
            tester::random_access_iterator_restrictor<float const *> const it(
                &Array<f32>::at(Array<f32>::len - 1)
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const
                ft_rit(it);
            std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const
                std_rit(it);
            ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > ft_ret;
            std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> >
                std_ret;

            for (idx = 0U; idx < Array<f32>::len; ++idx) {
                START        = clock();
                ft_ret       = ft_rit + idx;
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std_rit + idx;
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret.base() != std_ret.base()) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Non-member operator
        {
            tester::random_access_iterator_restrictor<float const *> const it(
                &Array<f32>::at(Array<f32>::len - 1)
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const
                ft_rit(it);
            std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const
                std_rit(it);
            ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > ft_ret;
            std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> >
                std_ret;

            for (idx = 0U; idx < Array<f32>::len; ++idx) {
                START        = clock();
                ft_ret       = idx + ft_rit;
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = idx + std_rit;
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret.base() != std_ret.base()) {
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

inline static u8 __test_operator_sub()
{
    u32 idx;

    title(__func__);
    try {
        tester::random_access_iterator_restrictor<float const *> const it(&Array<f32>::at(0));
        ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const
            ft_rit(it);
        std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > const
                                                                                        std_rit(it);
        ft::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > ft_ret;
        std::reverse_iterator<tester::random_access_iterator_restrictor<float const *> > std_ret;

        for (idx = 0U; idx < 10U; ++idx) {
            START        = clock();
            ft_ret       = ft_rit - idx;
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_rit - idx;
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret.base() != std_ret.base()) {
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

inline static u8 __test_operator_access()
{
    u32 idx;

    title(__func__);
    try {
        // Mutable access
        {
            tester::random_access_iterator_restrictor<u8 *> const it(
                &Array<u8>::at(Array<u8>::len)
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u8 *> > const ft_rit(it);
            std::reverse_iterator<tester::random_access_iterator_restrictor<u8 *> > const std_rit(
                it
            );

            for (idx = 0U; idx < Array<u8>::len; ++idx) {
                START        = clock();
                u8 &ft_ret   = ft_rit[idx];
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                u8 &std_ret   = std_rit[idx];
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return EXIT_FAILURE;
                }
            }
        }
        // Constant access
        {
            tester::random_access_iterator_restrictor<u8 const *> const it(
                &Array<u8>::at(Array<u8>::len)
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<u8 const *> > const
                ft_rit(it);
            std::reverse_iterator<tester::random_access_iterator_restrictor<u8 const *> > const
                std_rit(it);

            for (idx = 0U; idx < Array<u8>::len; ++idx) {
                START             = clock();
                u8 const &ft_ret  = ft_rit[idx];
                DURATION_FT       = clock() - START;
                DURATION_FT      += !DURATION_FT;

                START              = clock();
                u8 const &std_ret  = std_rit[idx];
                DURATION_STD       = clock() - START;
                DURATION_STD      += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}

inline static u8 __test_operator_distance()
{
    u32 idx0;
    u32 idx1;

    title(__func__);
    try {
        ft::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> >::
            difference_type ft_ret;
        std::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> >::
            difference_type std_ret;

        for (idx0 = 0U; idx0 < Array<std::string>::len; ++idx0) {
            tester::random_access_iterator_restrictor<std::string *> const it0(
                &Array<std::string>::at(idx0)
            );
            ft::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> > const
                ft_rit0(it0);
            std::reverse_iterator<tester::random_access_iterator_restrictor<std::string *> > const
                std_rit0(it0);

            for (idx1 = 0U; idx1 < Array<std::string>::len; ++idx1) {
                tester::random_access_iterator_restrictor<std::string const *> const it1(
                    &Array<std::string>::at(idx1)
                );
                ft::reverse_iterator<
                    tester::random_access_iterator_restrictor<std::string const *> const
                > const ft_rit1(it1);
                std::reverse_iterator<
                    tester::random_access_iterator_restrictor<std::string const *> const
                > const std_rit1(it1);

                START        = clock();
                ft_ret       = ft::operator-(ft_rit0, ft_rit1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator-(std_rit0, std_rit1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
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

inline static u8 __test_operator_equivalent()
{
    u32 idx0;
    u32 idx1;

    title(__func__);
    try {
        bool ft_ret;
        bool std_ret;

        for (idx0 = 0U; idx0 < Array<i32>::len; ++idx0) {
            tester::random_access_iterator_restrictor<i32 *> const it0(&Array<i32>::at(idx0));
            ft::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const ft_rit0(
                it0
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const std_rit0(
                it0
            );

            for (idx1 = 0U; idx1 < Array<i32>::len; ++idx1) {
                tester::random_access_iterator_restrictor<i32 const *> const it1(
                    &Array<i32>::at(idx1)
                );
                ft::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const ft_rit1(it1);
                std::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const std_rit1(it1);

                START        = clock();
                ft_ret       = ft::operator==(ft_rit0, ft_rit1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator==(std_rit0, std_rit1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
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

inline static u8 __test_operator_different()
{
    u32 idx0;
    u32 idx1;

    title(__func__);
    try {
        bool ft_ret;
        bool std_ret;

        for (idx0 = 0U; idx0 < Array<i32>::len; ++idx0) {
            tester::random_access_iterator_restrictor<i32 *> const it0(&Array<i32>::at(idx0));
            ft::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const ft_rit0(
                it0
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const std_rit0(
                it0
            );

            for (idx1 = 0U; idx1 < Array<i32>::len; ++idx1) {
                tester::random_access_iterator_restrictor<i32 const *> const it1(
                    &Array<i32>::at(idx1)
                );
                ft::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const ft_rit1(it1);
                std::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const std_rit1(it1);

                START        = clock();
                ft_ret       = ft::operator!=(ft_rit0, ft_rit1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator!=(std_rit0, std_rit1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
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

inline static u8 __test_operator_lower()
{
    u32 idx0;
    u32 idx1;

    title(__func__);
    try {
        bool ft_ret;
        bool std_ret;

        for (idx0 = 0U; idx0 < Array<i32>::len; ++idx0) {
            tester::random_access_iterator_restrictor<i32 *> const it0(&Array<i32>::at(idx0));
            ft::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const ft_rit0(
                it0
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const std_rit0(
                it0
            );

            for (idx1 = 0U; idx1 < Array<i32>::len; ++idx1) {
                tester::random_access_iterator_restrictor<i32 const *> const it1(
                    &Array<i32>::at(idx1)
                );
                ft::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const ft_rit1(it1);
                std::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const std_rit1(it1);

                START        = clock();
                ft_ret       = ft::operator<(ft_rit0, ft_rit1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<(std_rit0, std_rit1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
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

inline static u8 __test_operator_greater()
{
    u32 idx0;
    u32 idx1;

    title(__func__);
    try {
        bool ft_ret;
        bool std_ret;

        for (idx0 = 0U; idx0 < Array<i32>::len; ++idx0) {
            tester::random_access_iterator_restrictor<i32 *> const it0(&Array<i32>::at(idx0));
            ft::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const ft_rit0(
                it0
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const std_rit0(
                it0
            );

            for (idx1 = 0U; idx1 < Array<i32>::len; ++idx1) {
                tester::random_access_iterator_restrictor<i32 const *> const it1(
                    &Array<i32>::at(idx1)
                );
                ft::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const ft_rit1(it1);
                std::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const std_rit1(it1);

                START        = clock();
                ft_ret       = ft::operator>(ft_rit0, ft_rit1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>(std_rit0, std_rit1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
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

inline static u8 __test_operator_lower_or_equivalent()
{
    u32 idx0;
    u32 idx1;

    title(__func__);
    try {
        bool ft_ret;
        bool std_ret;

        for (idx0 = 0U; idx0 < Array<i32>::len; ++idx0) {
            tester::random_access_iterator_restrictor<i32 *> const it0(&Array<i32>::at(idx0));
            ft::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const ft_rit0(
                it0
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const std_rit0(
                it0
            );

            for (idx1 = 0U; idx1 < Array<i32>::len; ++idx1) {
                tester::random_access_iterator_restrictor<i32 const *> const it1(
                    &Array<i32>::at(idx1)
                );
                ft::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const ft_rit1(it1);
                std::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const std_rit1(it1);

                START        = clock();
                ft_ret       = ft::operator<=(ft_rit0, ft_rit1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<=(std_rit0, std_rit1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
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

inline static u8 __test_operator_greater_or_equivalent()
{
    u32 idx0;
    u32 idx1;

    title(__func__);
    try {
        bool ft_ret;
        bool std_ret;

        for (idx0 = 0U; idx0 < Array<i32>::len; ++idx0) {
            tester::random_access_iterator_restrictor<i32 *> const it0(&Array<i32>::at(idx0));
            ft::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const ft_rit0(
                it0
            );
            std::reverse_iterator<tester::random_access_iterator_restrictor<i32 *> > const std_rit0(
                it0
            );

            for (idx1 = 0U; idx1 < Array<i32>::len; ++idx1) {
                tester::random_access_iterator_restrictor<i32 const *> const it1(
                    &Array<i32>::at(idx1)
                );
                ft::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const ft_rit1(it1);
                std::reverse_iterator<
                    tester::random_access_iterator_restrictor<i32 const *> const
                > const std_rit1(it1);

                START        = clock();
                ft_ret       = ft::operator>=(ft_rit0, ft_rit1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>=(std_rit0, std_rit1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
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

u8 test_reverse_iterator()
{
    TestFn const tests[] = {
        __test_constructor,
        __test_function_base,
        __test_operator_assign,
        __test_operator_dereference,
        __test_operator_maddress,
        __test_operator_increment,
        __test_operator_decrement,
        __test_operator_add_assign,
        __test_operator_sub_assign,
        __test_operator_add,
        __test_operator_sub,
        __test_operator_access,
        __test_operator_distance,
        __test_operator_equivalent,
        __test_operator_different,
        __test_operator_lower,
        __test_operator_greater,
        __test_operator_lower_or_equivalent,
        __test_operator_greater_or_equivalent,
        NULL,
    };
    u32                   koCount;
    u32                   idx;
    struct timespec const delay = {SLEEP_TIME_SEC, SLEEP_TIME_NANOSEC};

    nanosleep(&delay, NULL);

    std::cerr << LIGHT_BLUE_FG;
    std::cout << "####################################################" << '\n';
    std::cout << "##                REVERSE ITERATOR                ##" << '\n';
    std::cout << "####################################################" << '\n';
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
