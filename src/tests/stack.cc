#define DISABLE
#ifndef DISABLE

# include "arrays.hh"
# include "benchmark.hh"
# include "colors.hh"
# include "headers.hh"
# include "numerics.hh"
# include "test_status.hh"
# include "tester.hh"
# include "type_traits.hh"
# include STACK_HEADER
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <iomanip>
# include <iostream>
# include <stack>
# include <vector>

# pragma region[default template type Container]

inline static u8 default_template_type_Container(
    void
)
{
    title(__func__);

    typedef ft::stack<float>                     sta_type_0;
    typedef ft::stack<float, ft::vector<float> > sta_type_1;

    if (!tester::is_same<sta_type_0, sta_type_1>::value) {
        return KO;
    }

    return IMPL_OK;
}

# pragma endregion
# pragma region[constructors]
# pragma region[default]

inline static u8 C_default(
    void
)
{
    i32              ret;
    std::vector<u32> vec;

    title(__func__);
    ret = IMPL_OK;
    try {
        START = clock();
        ft::stack<i32, std::vector<i32> > ft_sta;
        DURATION_FT  = clock() - START;
        DURATION_FT += !DURATION_FT;

        START = clock();
        std::stack<i32, std::vector<i32> > std_sta;
        DURATION_STD  = clock() - START;
        DURATION_STD += !DURATION_STD;

        RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

        if (sizeof(ft_sta) != sizeof(std_sta) || memcmp(&ft_sta, &std_sta, sizeof(ft_sta))) {
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
# pragma region[wrapper]

inline static u8 C_wrapper(
    void
)
{
    i32              ret;
    std::vector<u32> vec;
    u32              idx;

    title(__func__);
    ret = IMPL_OK;
    try {
        // Empty underlying container
        {
            START = clock();
            ft::stack<u32, std::vector<u32> > ft_sta(vec);
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std::stack<u32, std::vector<u32> > std_sta(vec);
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (sizeof(ft_sta) != sizeof(std_sta) || memcmp(&ft_sta, &std_sta, sizeof(ft_sta))) {
                ret = ISO_OK;
            }
        }
        // Non-empty underlying container
        {
            for (idx = 0U; idx < Array<u32>::len; ++idx) {
                vec.push_back(Array<u32>::at(idx));

                START = clock();
                ft::stack<u32, std::vector<u32> > ft_sta(vec);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START = clock();
                std::stack<u32, std::vector<u32> > std_sta(vec);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (sizeof(ft_sta) != sizeof(std_sta)) {
                    ret = ISO_OK;
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

# pragma endregion
# pragma endregion
# pragma region[members]
# pragma region[types]
# pragma region[container_type]

inline static u8 MT_container_type(
    void
)
{
    title(__func__);
    try {
        typedef ft::stack<i64, std::vector<i64> > sta_type;

        if (!tester::is_same<sta_type::container_type, std::vector<i64> >::value) {
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
# pragma region[size_type]

inline static u8 MT_size_type(
    void
)
{
    title(__func__);
    try {
        typedef ft::stack<i64, std::vector<i64> > sta_type;

        if (!tester::is_same<sta_type::size_type, std::vector<i64>::size_type>::value) {
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
# pragma region[value_type]

inline static u8 MT_value_type(
    void
)
{
    title(__func__);
    try {
        typedef ft::stack<i64, std::vector<i64> > sta_type;

        if (!tester::is_same<sta_type::ValueType, i64>::value) {
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
# pragma endregion
# pragma region[functions]
# pragma region[top]
# pragma region[constant]

inline static u8 MF_top(
    void
)
{
    std::vector<char> vec;
    u32               idx;

    title(__func__);
    try {
        for (idx = 0U; idx < Array<char>::len; ++idx) {
            vec.push_back(Array<char>::at(idx));

            ft::stack<char, std::vector<char> > const  ft_sta(vec);
            std::stack<char, std::vector<char> > const std_sta(vec);

            START               = clock();
            char const &ft_ret  = ft_sta.top();
            DURATION_FT         = clock() - START;
            DURATION_FT        += !DURATION_FT;

            START                = clock();
            char const &std_ret  = std_sta.top();
            DURATION_STD         = clock() - START;
            DURATION_STD        += !DURATION_STD;

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

inline static u8 MF_top_mut(
    void
)
{
    std::vector<char> vec;
    u32               idx;

    title(__func__);
    try {
        for (idx = 0U; idx < Array<char>::len; ++idx) {
            vec.push_back(Array<char>::at(idx));

            ft::stack<char, std::vector<char> >  ft_sta(vec);
            std::stack<char, std::vector<char> > std_sta(vec);

            START         = clock();
            char &ft_ret  = ft_sta.top();
            DURATION_FT   = clock() - START;
            DURATION_FT  += !DURATION_FT;

            START          = clock();
            char &std_ret  = std_sta.top();
            DURATION_STD   = clock() - START;
            DURATION_STD  += !DURATION_STD;

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
# pragma region[push]

inline static u8 MF_push(
    void
)
{
    u32 idx;

    title(__func__);
    try {
        ft::stack<std::string, std::vector<std::string> >  ft_sta;
        std::stack<std::string, std::vector<std::string> > std_sta;

        for (idx = 0U; idx < Array<std::string>::len; ++idx) {
            START = clock();
            ft_sta.push(Array<std::string>::at(idx));
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_sta.push(Array<std::string>::at(idx));
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_sta.top() != std_sta.top()) {
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
# pragma region[pop]

inline static u8 MF_pop(
    void
)
{
    u32 idx;

    title(__func__);
    try {
        ft::stack<float, std::vector<float> >  ft_sta;
        std::stack<float, std::vector<float> > std_sta;

        for (idx = 0U; idx < Array<f32>::len; ++idx) {
            ft_sta.push(Array<f32>::at(idx));
            std_sta.push(Array<f32>::at(idx));
        }
        for (idx = 0U; idx < Array<f32>::len; ++idx) {
            if (ft_sta.top() != std_sta.top()) {
                return KO;
            }
            START = clock();
            ft_sta.pop();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_sta.pop();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));
        }
        for (idx = 0U; idx < Array<f32>::len; ++idx) {
            START = clock();
            ft_sta.pop();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START = clock();
            std_sta.pop();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma region[empty]

inline static u8 MF_empty(
    void
)
{
    u32 idx;

    title(__func__);
    try {
        std::vector<i64> vec;
        bool             ft_ret;
        bool             std_ret;

        for (idx = 0U; idx < Array<i64>::len; ++idx) {
            ft::stack<i64, std::vector<i64> > const  ft_sta(vec);
            std::stack<i64, std::vector<i64> > const std_sta(vec);

            START        = clock();
            ft_ret       = ft_sta.empty();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_sta.empty();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            vec.push_back(Array<i64>::at(idx));
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return KO;
    }
    return IMPL_OK;
}

# pragma endregion
# pragma region[size]

inline static u8 MF_size(
    void
)
{
    u32 idx;

    title(__func__);
    try {
        std::vector<u32>                              vec;
        ft::stack<u32, std::vector<u32> >::size_type  ft_ret;
        std::stack<u32, std::vector<u32> >::size_type std_ret;

        for (idx = 0U; idx < Array<u32>::len; ++idx) {
            ft::stack<u32, std::vector<u32> > const  ft_sta(vec);
            std::stack<u32, std::vector<u32> > const std_sta(vec);

            START        = clock();
            ft_ret       = ft_sta.size();
            DURATION_FT  = clock() - START;
            DURATION_FT += !DURATION_FT;

            START         = clock();
            std_ret       = std_sta.size();
            DURATION_STD  = clock() - START;
            DURATION_STD += !DURATION_STD;

            RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

            if (ft_ret != std_ret) {
                return KO;
            }

            vec.push_back(Array<u32>::at(idx));
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
# pragma region[operators]
# pragma region[eq]

inline static u8 MO_eq(
    void
)
{
    u32 idx;

    title(__func__);
    try {
        std::vector<i32> vec;
        bool             ft_ret;
        bool             std_ret;

        for (idx = 0U; idx < Array<i32>::len; ++idx) {
# pragma region[equivalence]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator==(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator==(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
# pragma region[difference]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);

                vec.push_back(Array<i32>::at(idx));

                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator==(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator==(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
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

inline static u8 MO_ne(
    void
)
{
    u32 idx;

    title(__func__);
    try {
        std::vector<i32> vec;
        bool             ft_ret;
        bool             std_ret;

        for (idx = 0U; idx < Array<i32>::len; ++idx) {
# pragma region[equivalence]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator!=(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator!=(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
# pragma region[difference]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);

                vec.push_back(Array<i32>::at(idx));

                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator!=(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator!=(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
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

inline static u8 MO_lt(
    void
)
{
    u32 idx;

    title(__func__);
    try {
        std::vector<i32> vec;
        bool             ft_ret;
        bool             std_ret;

        for (idx = 0U; idx < Array<i32>::len; ++idx) {
# pragma region[equivalence]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator<(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
# pragma region[difference]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);

                vec.push_back(Array<i32>::at(idx));

                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator<(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
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

inline static u8 MO_gt(
    void
)
{
    u32 idx;

    title(__func__);
    try {
        std::vector<i32> vec;
        bool             ft_ret;
        bool             std_ret;

        for (idx = 0U; idx < Array<i32>::len; ++idx) {
# pragma region[equivalence]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator>(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
# pragma region[difference]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);

                vec.push_back(Array<i32>::at(idx));

                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator>(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
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

inline static u8 MO_le(
    void
)
{
    u32 idx;

    title(__func__);
    try {
        std::vector<i32> vec;
        bool             ft_ret;
        bool             std_ret;

        for (idx = 0U; idx < Array<i32>::len; ++idx) {
# pragma region[equivalence]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator<=(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<=(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
# pragma region[difference]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);

                vec.push_back(Array<i32>::at(idx));

                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator<=(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator<=(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
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

inline static u8 MO_ge(
    void
)
{
    u32 idx;

    title(__func__);
    try {
        std::vector<i32> vec;
        bool             ft_ret;
        bool             std_ret;

        for (idx = 0U; idx < Array<i32>::len; ++idx) {
# pragma region[equivalence]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator>=(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>=(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
# pragma region[difference]
            {
                ft::stack<i32, std::vector<i32> > const  ft_sta0(vec);
                std::stack<i32, std::vector<i32> > const std_sta0(vec);

                vec.push_back(Array<i32>::at(idx));

                ft::stack<i32, std::vector<i32> > const  ft_sta1(vec);
                std::stack<i32, std::vector<i32> > const std_sta1(vec);

                START        = clock();
                ft_ret       = ft::operator>=(ft_sta0, ft_sta1);
                DURATION_FT  = clock() - START;
                DURATION_FT += !DURATION_FT;

                START         = clock();
                std_ret       = std::operator>=(std_sta0, std_sta1);
                DURATION_STD  = clock() - START;
                DURATION_STD += !DURATION_STD;

                RATIOS.insert(static_cast<float>(DURATION_FT) / static_cast<float>(DURATION_STD));

                if (ft_ret != std_ret) {
                    return KO;
                }
            }
# pragma endregion
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

u8 test_stack(
    void
)
{
    TestFn const tests[] = {
# pragma region[tests]
        default_template_type_Container,
# pragma region[constructors]
        C_default,
        C_wrapper,
# pragma endregion
# pragma region[members]
# pragma region[types]
        MT_container_type,
        MT_size_type,
        MT_value_type,
# pragma endregion
# pragma region[functions]
        MF_top,
        MF_top_mut,
        MF_push,
        MF_pop,
        MF_empty,
        MF_size,
# pragma endregion
# pragma region[operators]
        MO_eq,
        MO_ne,
        MO_lt,
        MO_gt,
        MO_le,
        MO_ge,
# pragma endregion
# pragma endregion
        NULL
# pragma endregion
    };
    u32                   koCount;
    u32                   idx;
    struct timespec const delay = {SLEEP_TIME_SEC, SLEEP_TIME_NANOSEC};

    nanosleep(&delay, NULL);

    std::cerr << LIGHT_BLUE_FG;
    std::cout << "###################################################" << '\n';
    std::cout << "##                     STACK                     ##" << '\n';
    std::cout << "###################################################" << '\n';
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
