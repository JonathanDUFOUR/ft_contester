// #define DISABLE
#ifndef DISABLE

# include "algorithm.hpp" // ft::{equal,lexicographical_compare}
# include "graphics.hh" // GRAPHICS_RESET,SET_FOREGROUND_{GREEN,RED,RGB}
# include "iterator/restrictor/input.hh" // tester::input_iterator_restrictor
# include "tester.hh" // tester::{delay,title}
# include "type/fundamentals.hh" // tester::t_{i32,u{16,size{,_mut}}}
# include "type/pointers.hh" // tester::t_{i32,u16,str}_ptr
# include "type/range.hh" // tester::range
# include "type/str.hh" // tester::t_str
# include "type/test/benchmark/ratio_multiset.hh" // tester::test::benchmark::t_ratio_multiset_mut
# include "type/test/status.hh" // tester::test::{FAILURE,SUCCESS,t_status}
# include "type/test/subcategory.hh" // tester::test::t_subcategory
# include <algorithm> // std::{equal,lexicographical_compare}
# include <ctime> // {clock,time}_t,clock,nanosleep
# include <exception> // std::exception
# include <functional> // std::{{,not_}equal_to,greater{,_equal},less{,_equal}}
# include <iostream> // std::c{err,out}
# include <map> // std::map
# include <utility> // std::{,make_}pair

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
using std::make_pair;
using std::map;
using std::not_equal_to;
using std::pair;

static t_i32 I32_ARRAY_A[] = {-54321, -4321, -321, -21, -1, 0, 1, 21, 321, 4321};
static t_i32 I32_ARRAY_B[] = {-54321, -4321, -321, -21, -1, 0, 1, 21, 321, 43210};

static t_u16 U16_ARRAY_A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
static t_u16 U16_ARRAY_B[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 31};

static t_str STR_ARRAY_A[] = {
    "Half-past twelve",
    "And I'm watching the late show in my flat all alone",
    "How I hate to spend the evening on my own",
    "Autumn winds",
    "Blowing outside the window as I look around the room",
    "And it makes me so depressed to see the gloom",
    "There's not a soul out there",
    "No one to hear my prayer",
    "Gimme, gimme, gimme a man after midnight",
    "Won't somebody help me chase the shadows away ?"
};
static t_str STR_ARRAY_B[] = {
    "Half-past twelve",
    "And I'm watching the late show in my flat all alone",
    "How I hate to spend the evening on my own",
    "Autumn winds",
    "Blowing outside the window as I look around the room",
    "And it makes me so depressed to see the gloom",
    "There's not a soul out there",
    "No one to hear my prayer",
    "Gimme, gimme, gimme a man after midnight",
    "Won't somebody help me chase the shadows away?"
};
static t_usize I32_ARRAY_A_LEN = sizeof(I32_ARRAY_A) / sizeof(I32_ARRAY_A[0]);
static t_usize I32_ARRAY_B_LEN = sizeof(I32_ARRAY_B) / sizeof(I32_ARRAY_B[0]);
static t_usize U16_ARRAY_A_LEN = sizeof(U16_ARRAY_A) / sizeof(U16_ARRAY_A[0]);
static t_usize U16_ARRAY_B_LEN = sizeof(U16_ARRAY_B) / sizeof(U16_ARRAY_B[0]);
static t_usize STR_ARRAY_A_LEN = sizeof(STR_ARRAY_A) / sizeof(STR_ARRAY_A[0]);
static t_usize STR_ARRAY_B_LEN = sizeof(STR_ARRAY_B) / sizeof(STR_ARRAY_B[0]);

namespace equal {

enum e_range { EMPTY, ONLY1, WHOLE, RANGES_LEN };

template <typename T>
class c_context
{
# define SELF c_context

private: /* types */
    typedef T const         *t_ptr_mut;
    typedef equal_to<T>      t_eq;
    typedef not_equal_to<T>  t_ne;
    typedef less<T>          t_lt;
    typedef less_equal<T>    t_le;
    typedef greater<T>       t_gt;
    typedef greater_equal<T> t_ge;

public: /* types */
    typedef T const *const                             t_ptr;
    typedef input_iterator_restrictor<t_ptr_mut> const t_iterator;

public: /* fields */
    t_ptr m_a_ptr_1st;
    t_ptr m_b_ptr_1st;
    t_ptr m_b_ptr_2nd;
    t_ptr m_b_ptr_end;

    t_iterator m_a_iter_1st;
    t_iterator m_b_iter_1st;
    t_iterator m_b_iter_2nd;
    t_iterator m_b_iter_end;

    t_eq m_eq;
    t_ne m_ne;
    t_lt m_lt;
    t_le m_le;
    t_gt m_gt;
    t_ge m_ge;

public: /* constructor */
    SELF(
        t_ptr a_array, t_ptr b_array, t_usize b_array_len
    )
    : m_a_ptr_1st(&a_array[0])
    , m_b_ptr_1st(&b_array[0])
    , m_b_ptr_2nd(&b_array[1])
    , m_b_ptr_end(&b_array[b_array_len])
    , m_a_iter_1st(m_a_ptr_1st)
    , m_b_iter_1st(m_b_ptr_1st)
    , m_b_iter_2nd(m_b_ptr_2nd)
    , m_b_iter_end(m_b_ptr_end)
    , m_eq()
    , m_ne()
    , m_lt()
    , m_le()
    , m_gt()
    , m_ge()
    {}

# undef SELF
};

template <typename InputIterator>
inline static pair<t_bool, time_t> test_case(
    // clang-format off
    bool (&function)(
        InputIterator, InputIterator, InputIterator
    ),
    // clang-format on
    s_range<InputIterator const> const &range,
    InputIterator const                &other_first
)
{
    clock_t const start    = clock();
    t_bool        ret      = function(range.first, range.ptend, other_first);
    time_t const  duration = clock() - start;

    return make_pair(ret, duration);
}

template <typename InputIterator, typename BinaryPredicate>
inline static pair<t_bool, time_t> test_case(
    // clang-format off
    bool (&function)(
        InputIterator, InputIterator, InputIterator, BinaryPredicate
    ),
    // clang-format on
    s_range<InputIterator const> const &range,
    InputIterator const                &other_first,
    BinaryPredicate const              &cmp
)
{
    clock_t const start    = clock();
    t_bool        ret      = function(range.first, range.ptend, other_first, cmp);
    time_t const  duration = clock() - start;

    return make_pair(ret, duration);
}

# define CANDIDATE ft::equal
# define REFERENCE std::equal

template <typename InputIterator>
inline static t_status test_each_case(
    t_ratio_multiset_mut               &ratios,
    s_range<InputIterator const> const &range,
    InputIterator const                &other_first
)
{
    pair<t_bool, time_t> const candidate[] = {
        test_case(CANDIDATE, range, range.first),
        test_case(CANDIDATE, range, other_first),
    };
    pair<t_bool, time_t> const reference[] = {
        test_case(REFERENCE, range, range.first),
        test_case(REFERENCE, range, other_first),
    };
    t_usize len = sizeof(candidate) / sizeof(candidate[0]);

    for (t_usize_mut i = 0; i < len; ++i) {
        if (candidate[i].first != reference[i].first) {
            return FAILURE;
        }
        ratios.add_entry(candidate[i].second, reference[i].second);
    }
    return SUCCESS;
}

template <typename InputIterator, typename BinaryPredicate>
inline static t_status test_each_case(
    t_ratio_multiset_mut               &ratios,
    s_range<InputIterator const> const &range,
    InputIterator const                &other_first,
    BinaryPredicate const              &cmp
)
{
    pair<t_bool, time_t> const candidate[] = {
        test_case(CANDIDATE, range, range.first, cmp),
        test_case(CANDIDATE, range, other_first, cmp),
    };
    pair<t_bool, time_t> const reference[] = {
        test_case(REFERENCE, range, range.first, cmp),
        test_case(REFERENCE, range, other_first, cmp),
    };
    t_usize len = sizeof(candidate) / sizeof(candidate[0]);

    for (t_usize_mut i = 0; i < len; ++i) {
        if (candidate[i].first != reference[i].first) {
            return FAILURE;
        }
        ratios.add_entry(candidate[i].second, reference[i].second);
    }
    return SUCCESS;
}

# undef CANDIDATE
# undef REFERENCE

template <typename T, typename InputIterator>
inline static t_status test_each_overload(
    t_ratio_multiset_mut               &ratios,
    c_context<T> const                 &context,
    s_range<InputIterator const> const &range,
    InputIterator const                &other_first
)
{
    t_status results[] = {
        // equal(first0, ptend0, first1)
        test_each_case(ratios, range, other_first),

        // equal(first0, ptend0, first1, cmp)
        test_each_case(ratios, range, other_first, context.m_eq),
        test_each_case(ratios, range, other_first, context.m_ne),
        test_each_case(ratios, range, other_first, context.m_lt),
        test_each_case(ratios, range, other_first, context.m_le),
        test_each_case(ratios, range, other_first, context.m_gt),
        test_each_case(ratios, range, other_first, context.m_ge),
    };
    t_usize results_len = sizeof(results) / sizeof(results[0]);

    for (t_usize_mut i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

template <typename T>
inline static t_status test_each_range(
    t_ratio_multiset_mut &ratios, c_context<T> const &context
)
{
    typedef s_range<typename c_context<T>::t_ptr> const      t_ptr_range;
    typedef s_range<typename c_context<T>::t_iterator> const t_iterator_range;

    t_ptr_range ptr_ranges[RANGES_LEN] = {
        [EMPTY] = t_ptr_range(context.m_b_ptr_1st, context.m_b_ptr_1st),
        [ONLY1] = t_ptr_range(context.m_b_ptr_1st, context.m_b_ptr_2nd),
        [WHOLE] = t_ptr_range(context.m_b_ptr_1st, context.m_b_ptr_end),
    };
    t_iterator_range iter_ranges[RANGES_LEN] = {
        [EMPTY] = t_iterator_range(context.m_b_iter_1st, context.m_b_iter_1st),
        [ONLY1] = t_iterator_range(context.m_b_iter_1st, context.m_b_iter_2nd),
        [WHOLE] = t_iterator_range(context.m_b_iter_1st, context.m_b_iter_end),
    };
    t_status results[] = {
        test_each_overload(ratios, context, ptr_ranges[EMPTY], context.m_a_ptr_1st),
        test_each_overload(ratios, context, ptr_ranges[ONLY1], context.m_a_ptr_1st),
        test_each_overload(ratios, context, ptr_ranges[WHOLE], context.m_a_ptr_1st),

        test_each_overload(ratios, context, iter_ranges[EMPTY], context.m_a_iter_1st),
        test_each_overload(ratios, context, iter_ranges[ONLY1], context.m_a_iter_1st),
        test_each_overload(ratios, context, iter_ranges[WHOLE], context.m_a_iter_1st),
    };
    t_usize results_len = sizeof(results) / sizeof(results[0]);

    for (t_usize_mut i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

inline static t_status test_each_type(
    t_ratio_multiset_mut &ratios
)
{
    typedef c_context<t_i32_mut> const t_i32_context;
    typedef c_context<t_u16_mut> const t_u16_context;
    typedef c_context<t_str_mut> const t_str_context;

    t_i32_context i32_context(&I32_ARRAY_A[0], &I32_ARRAY_B[0], I32_ARRAY_B_LEN);
    t_u16_context u16_context(&U16_ARRAY_A[0], &U16_ARRAY_B[0], U16_ARRAY_B_LEN);
    t_str_context str_context(&STR_ARRAY_A[0], &STR_ARRAY_B[0], STR_ARRAY_B_LEN);

    t_status results[] = {
        test_each_range(ratios, i32_context),
        test_each_range(ratios, u16_context),
        test_each_range(ratios, str_context),
    };
    t_usize results_len = sizeof(results) / sizeof(results[0]);

    for (t_usize_mut i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

inline t_status run_tests(
    t_ratio_multiset_mut &ratios
)
{
    nanosleep(&delay, NULL);
    title("equal");
    try {
        return test_each_type(ratios);
    }
    catch (exception const &e) {
        cerr << "Exception: " << e.what() << '\n';
        return FAILURE;
    }
}

}; // namespace equal

namespace lexicographical_compare {

enum e_range { EMPTY, ONLY1, WHOLE, RANGES_LEN };

template <typename T>
class c_context
{
# define SELF c_context

private: /* types */
    typedef T const         *t_ptr_mut;
    typedef equal_to<T>      t_eq;
    typedef not_equal_to<T>  t_ne;
    typedef less<T>          t_lt;
    typedef less_equal<T>    t_le;
    typedef greater<T>       t_gt;
    typedef greater_equal<T> t_ge;

public: /* types */
    typedef T const *const                             t_ptr;
    typedef input_iterator_restrictor<t_ptr_mut> const t_iterator;

public: /* fields */
    t_ptr m_a_ptr_1st;
    t_ptr m_a_ptr_2nd;
    t_ptr m_a_ptr_end;
    t_ptr m_b_ptr_1st;
    t_ptr m_b_ptr_2nd;
    t_ptr m_b_ptr_end;

    t_iterator m_a_iter_1st;
    t_iterator m_a_iter_2nd;
    t_iterator m_a_iter_end;
    t_iterator m_b_iter_1st;
    t_iterator m_b_iter_2nd;
    t_iterator m_b_iter_end;

    t_eq m_eq;
    t_ne m_ne;
    t_lt m_lt;
    t_le m_le;
    t_gt m_gt;
    t_ge m_ge;

public: /* constructor */
    SELF(
        t_ptr a_array, t_usize a_array_len, t_ptr b_array, t_usize b_array_len
    )
    : m_a_ptr_1st(&a_array[0])
    , m_a_ptr_2nd(&a_array[1])
    , m_a_ptr_end(&a_array[a_array_len])
    , m_b_ptr_1st(&b_array[0])
    , m_b_ptr_2nd(&b_array[1])
    , m_b_ptr_end(&b_array[b_array_len])
    , m_a_iter_1st(m_a_ptr_1st)
    , m_a_iter_2nd(m_a_ptr_2nd)
    , m_a_iter_end(m_a_ptr_end)
    , m_b_iter_1st(m_b_ptr_1st)
    , m_b_iter_2nd(m_b_ptr_2nd)
    , m_b_iter_end(m_b_ptr_end)
    , m_eq()
    , m_ne()
    , m_lt()
    , m_le()
    , m_gt()
    , m_ge()
    {}

# undef SELF
};

template <typename InputIterator0, typename InputIterator1>
inline static pair<t_bool, time_t> test_case(
    // clang-format off
    bool (&function)(
        InputIterator0, InputIterator0, InputIterator1, InputIterator1
    ),
    // clang-format on
    s_range<InputIterator0> const &range0,
    s_range<InputIterator1> const &range1
)
{
    clock_t const start    = clock();
    t_bool        ret      = function(range0.first, range0.ptend, range1.first, range1.ptend);
    time_t const  duration = clock() - start;

    return make_pair(ret, duration);
}

template <typename InputIterator0, typename InputIterator1, typename BinaryPredicate>
inline static pair<t_bool, time_t> test_case(
    // clang-format off
    bool (&function)(
        InputIterator0, InputIterator0, InputIterator1, InputIterator1, BinaryPredicate
    ),
    // clang-format on
    s_range<InputIterator0> const &range0,
    s_range<InputIterator1> const &range1,
    BinaryPredicate const         &cmp
)
{
    clock_t const start    = clock();
    t_bool        ret      = function(range0.first, range0.ptend, range1.first, range1.ptend, cmp);
    time_t const  duration = clock() - start;

    return make_pair(ret, duration);
}

# define CANDIDATE ft::lexicographical_compare
# define REFERENCE std::lexicographical_compare

template <typename InputIterator0, typename InputIterator1>
inline static t_status test_each_case(
    t_ratio_multiset_mut          &ratios,
    s_range<InputIterator0> const &range0,
    s_range<InputIterator1> const &range1
)
{
    typedef pair<t_bool, time_t> const t_case;

    t_case candidate[] = {
        test_case(CANDIDATE, range0, range0),
        test_case(CANDIDATE, range0, range1),
    };
    t_case reference[] = {
        test_case(REFERENCE, range0, range0),
        test_case(REFERENCE, range0, range1),
    };
    t_usize len = sizeof(candidate) / sizeof(candidate[0]);

    for (t_usize_mut i = 0; i < len; ++i) {
        if (candidate[i].first != reference[i].first) {
            return FAILURE;
        }
        ratios.add_entry(candidate[i].second, reference[i].second);
    }
    return SUCCESS;
}

template <typename InputIterator0, typename InputIterator1, typename BinaryPredicate>
inline static t_status test_each_case(
    t_ratio_multiset_mut          &ratios,
    s_range<InputIterator0> const &range0,
    s_range<InputIterator1> const &range1,
    BinaryPredicate const         &cmp
)
{
    typedef pair<t_bool, time_t> const t_case;

    t_case candidate[] = {
        test_case(CANDIDATE, range0, range0, cmp),
        test_case(CANDIDATE, range0, range1, cmp),
    };
    t_case reference[] = {
        test_case(REFERENCE, range0, range0, cmp),
        test_case(REFERENCE, range0, range1, cmp),
    };
    t_usize len = sizeof(candidate) / sizeof(candidate[0]);

    for (t_usize_mut i = 0; i < len; ++i) {
        if (candidate[i].first != reference[i].first) {
            return FAILURE;
        }
        ratios.add_entry(candidate[i].second, reference[i].second);
    }
    return SUCCESS;
}

# undef CANDIDATE
# undef REFERENCE

template <typename T, typename InputIterator0, typename InputIterator1>
inline static t_status test_each_overload(
    t_ratio_multiset_mut          &ratios,
    c_context<T> const            &context,
    s_range<InputIterator0> const &range0,
    s_range<InputIterator1> const &range1
)
{
    t_status results[] = {
        // lexicographical_compare(first0, ptend0, first1, ptend1)
        test_each_case(ratios, range0, range1),

        // lexicographical_compare(first0, ptend0, first1, ptend1, cmp)
        test_each_case(ratios, range0, range1, context.m_eq),
        test_each_case(ratios, range0, range1, context.m_ne),
        test_each_case(ratios, range0, range1, context.m_lt),
        test_each_case(ratios, range0, range1, context.m_le),
        test_each_case(ratios, range0, range1, context.m_gt),
        test_each_case(ratios, range0, range1, context.m_ge),
    };
    t_usize results_len = sizeof(results) / sizeof(results[0]);

    for (t_usize_mut i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

template <typename T, typename InputIterator>
inline static t_status test_each_range1(
    t_ratio_multiset_mut &ratios, c_context<T> const &context, s_range<InputIterator> const &range
)
{
    typedef s_range<typename c_context<T>::t_ptr> const      t_ptr_range;
    typedef s_range<typename c_context<T>::t_iterator> const t_iterator_range;

    t_ptr_range ptr_ranges[RANGES_LEN] = {
        [EMPTY] = t_ptr_range(context.m_b_ptr_1st, context.m_b_ptr_1st),
        [ONLY1] = t_ptr_range(context.m_b_ptr_1st, context.m_b_ptr_2nd),
        [WHOLE] = t_ptr_range(context.m_b_ptr_1st, context.m_b_ptr_end),
    };
    t_iterator_range iter_ranges[RANGES_LEN] = {
        [EMPTY] = t_iterator_range(context.m_b_iter_1st, context.m_b_iter_1st),
        [ONLY1] = t_iterator_range(context.m_b_iter_1st, context.m_b_iter_2nd),
        [WHOLE] = t_iterator_range(context.m_b_iter_1st, context.m_b_iter_end),
    };
    t_status results[] = {
        test_each_overload(ratios, context, range, ptr_ranges[EMPTY]),
        test_each_overload(ratios, context, range, ptr_ranges[ONLY1]),
        test_each_overload(ratios, context, range, ptr_ranges[WHOLE]),

        test_each_overload(ratios, context, range, iter_ranges[EMPTY]),
        test_each_overload(ratios, context, range, iter_ranges[ONLY1]),
        test_each_overload(ratios, context, range, iter_ranges[WHOLE]),
    };
    t_usize results_len = sizeof(results) / sizeof(results[0]);

    for (t_usize_mut i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

template <typename T>
inline static t_status test_each_range0(
    t_ratio_multiset_mut &ratios, c_context<T> const &context
)
{
    typedef s_range<typename c_context<T>::t_ptr> const      t_ptr_range;
    typedef s_range<typename c_context<T>::t_iterator> const t_iterator_range;

    t_ptr_range ptr_ranges[RANGES_LEN] = {
        [EMPTY] = t_ptr_range(context.m_a_ptr_1st, context.m_a_ptr_1st),
        [ONLY1] = t_ptr_range(context.m_a_ptr_1st, context.m_a_ptr_2nd),
        [WHOLE] = t_ptr_range(context.m_a_ptr_1st, context.m_a_ptr_end),
    };
    t_iterator_range iter_ranges[RANGES_LEN] = {
        [EMPTY] = t_iterator_range(context.m_a_iter_1st, context.m_a_iter_1st),
        [ONLY1] = t_iterator_range(context.m_a_iter_1st, context.m_a_iter_2nd),
        [WHOLE] = t_iterator_range(context.m_a_iter_1st, context.m_a_iter_end),
    };
    t_status results[] = {
        test_each_range1(ratios, context, ptr_ranges[EMPTY]),
        test_each_range1(ratios, context, ptr_ranges[ONLY1]),
        test_each_range1(ratios, context, ptr_ranges[WHOLE]),

        test_each_range1(ratios, context, iter_ranges[EMPTY]),
        test_each_range1(ratios, context, iter_ranges[ONLY1]),
        test_each_range1(ratios, context, iter_ranges[WHOLE]),
    };
    t_usize results_len = sizeof(results) / sizeof(results[0]);

    for (t_usize_mut i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

inline static t_status test_each_type(
    t_ratio_multiset_mut &ratios __attribute__((unused))
)
{
    typedef c_context<t_i32_mut> const t_i32_context;
    typedef c_context<t_u16_mut> const t_u16_context;
    typedef c_context<t_str_mut> const t_str_context;

    t_i32_context i32_context(&I32_ARRAY_A[0], I32_ARRAY_A_LEN, &I32_ARRAY_B[0], I32_ARRAY_B_LEN);
    t_u16_context u16_context(&U16_ARRAY_A[0], U16_ARRAY_A_LEN, &U16_ARRAY_B[0], U16_ARRAY_B_LEN);
    t_str_context str_context(&STR_ARRAY_A[0], STR_ARRAY_A_LEN, &STR_ARRAY_B[0], STR_ARRAY_B_LEN);

    t_status results[] = {
        test_each_range0(ratios, i32_context),
        test_each_range0(ratios, u16_context),
        test_each_range0(ratios, str_context),
    };
    t_usize results_len = sizeof(results) / sizeof(results[0]);

    for (t_usize_mut i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

inline t_status run_tests(
    t_ratio_multiset_mut &ratios
)
{
    nanosleep(&delay, NULL);
    title("lexicographical_compare");
    try {
        return test_each_type(ratios);
    }
    catch (exception const &e) {
        cerr << "Exception: " << e.what() << '\n';
        return FAILURE;
    }
}

} // namespace lexicographical_compare

namespace swap {

template <typename T>
class c_context
{
# define SELF c_context

public: /* fields */
    T m_a;
    T m_b;

public: /* constructor */
    SELF(
        T const &a, T const &b
    )
    : m_a(a), m_b(b)
    {}

# undef SELF
};

template <typename T>
inline static pair<pair<T, T>, time_t> test_case(
    void (&function)(T &, T &), c_context<T> context
)
{
    clock_t const start = clock();
    function(context.m_a, context.m_b);
    time_t const duration = clock() - start;

    return make_pair(make_pair(context.m_a, context.m_b), duration);
}

# define CANDIDATE ft::swap
# define REFERENCE std::swap

template <typename T>
inline static t_status test_each_case(
    t_ratio_multiset_mut &ratios, c_context<T> const &context
)
{
    typedef pair<pair<T, T>, time_t> const t_case;

    t_case candidate[] = {
        test_case(CANDIDATE, context),
    };
    t_case reference[] = {
        test_case(REFERENCE, context),
    };
    t_usize len = sizeof(candidate) / sizeof(candidate[0]);

    for (t_usize_mut i = 0; i < len; ++i) {
        if (candidate[i].first != reference[i].first) {
            return FAILURE;
        }
        ratios.add_entry(candidate[i].second, reference[i].second);
    }
    return SUCCESS;
    {}
}

# undef CANDIDATE
# undef REFERENCE

inline static t_status test_each_type(
    t_ratio_multiset_mut &ratios
)
{
    typedef c_context<t_i32_mut> const t_i32_context;
    typedef c_context<t_u16_mut> const t_u16_context;
    typedef c_context<t_str_mut> const t_str_context;

    t_i32_context i32_context(125, -42);
    t_u16_context u16_context(~0, 0);
    t_str_context str_context("foo", "bar");

    t_status const results[] = {
        test_each_case(ratios, i32_context),
        test_each_case(ratios, u16_context),
        test_each_case(ratios, str_context),
    };
    t_usize results_len = sizeof(results) / sizeof(results[0]);

    for (t_usize_mut i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

inline t_status run_tests(
    t_ratio_multiset_mut &ratios
)
{
    nanosleep(&delay, NULL);
    title("swap");
    try {
        return test_each_type(ratios);
    }
    catch (exception const &e) {
        cerr << "Exception: " << e.what() << '\n';
        return FAILURE;
    }
}

} // namespace swap

static t_subcategory SUBCATEGORIES[] = {
    {"equal",                   equal::run_tests,                   true},
    {"lexicographical_compare", lexicographical_compare::run_tests, true},
    {"swap",                    swap::run_tests,                    true},
};
static t_usize SUBCATEGORIES_LEN = sizeof(SUBCATEGORIES) / sizeof(SUBCATEGORIES[0]);

inline static t_u8 run_default_subcategories()
{
    t_u8_mut             failure_count = 0;
    t_ratio_multiset_mut ratios;

    for (t_usize_mut i = 0; i < SUBCATEGORIES_LEN; ++i) {
        if (!SUBCATEGORIES[i].run_by_default) {
            continue;
        }
        if (SUBCATEGORIES[i](ratios) == SUCCESS) {
            SET_FOREGROUND_GREEN;
            cout << "ok     ";
        }
        else {
            SET_FOREGROUND_RED;
            cout << "failed ";
            ++failure_count;
        }
        RESET_GRAPHICS;
        ratios.print();
        cout << '\n';
        ratios.clear();
    }
    return failure_count;
}

inline static t_u8 run_specific_subcategory(
    t_str subcategory
)
{
    t_u8_mut                                         failure_count = 0;
    t_ratio_multiset_mut                             ratios;
    map<t_str, t_subcategory_fn_ptr>                 tests;
    map<t_str, t_subcategory_fn_ptr>::const_iterator iter;

    for (t_usize_mut i = 0; i < SUBCATEGORIES_LEN; ++i) {
        tests.insert(make_pair(SUBCATEGORIES[i].name, SUBCATEGORIES[i].function));
    }
    iter = tests.find(subcategory);
    if (iter == tests.end()) {
        SET_FOREGROUND_RED;
        cout << "ERROR";
        RESET_GRAPHICS;
        cout << ": '" << subcategory << "' subcategory not found\n";
        return 0;
    }
    if (iter->second(ratios) == SUCCESS) {
        SET_FOREGROUND_GREEN;
        cout << "ok     ";
    }
    else {
        SET_FOREGROUND_RED;
        cout << "failed ";
        ++failure_count;
    }
    RESET_GRAPHICS;
    ratios.print();
    cout << '\n';
    return failure_count;
}

t_status algorithm(
    t_char_ptr subcategory
)
{
    SET_FOREGROUND_BRIGHT_BLUE;
    SET_INTENSITY_BOLD;
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "┃                    ALGORITHM                    ┃\n";
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
    SET_INTENSITY_NORMAL;
    RESET_GRAPHICS;

    if (!subcategory) {
        return run_default_subcategories() ? FAILURE : SUCCESS;
    }
    return run_specific_subcategory(subcategory) ? FAILURE : SUCCESS;
}
}} // namespace tester::test

#endif
