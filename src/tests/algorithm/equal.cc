#include "algorithm.hpp"
#include "delay.hh"
#include "title.hh"
#include "type/benchmark/ratio_multiset.hh"
#include "type/iterator_restrictor/input.hh"
#include "type/range.hh"
#include "type/status.hh"
#include "type/title/low_level.hh"
#include <iostream>

#define CANDIDATE ft::equal
#define REFERENCE std::equal

namespace tester { namespace algorithm { namespace equal {

using benchmark::t_ratio_multiset;
using std::cout;
using std::equal_to;
using std::exception;
using std::greater;
using std::greater_equal;
using std::less;
using std::less_equal;
using std::make_pair;
using std::not_equal_to;
using std::pair;
using std::string;

static int32_t const I32_A[] = {-54321, -4321, -321, -21, -1, 0, 1, 21, 321, 4321};
static int32_t const I32_B[] = {-54321, -4321, -321, -21, -1, 0, 1, 21, 321, 43210};

static uint16_t const U16_A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
static uint16_t const U16_B[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 31};

static string const STR_A[] = {
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
static string const STR_B[] = {
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
static size_t const I32_B_LEN = sizeof(I32_B) / sizeof(I32_B[0]);
static size_t const U16_B_LEN = sizeof(U16_B) / sizeof(U16_B[0]);
static size_t const STR_B_LEN = sizeof(STR_B) / sizeof(STR_B[0]);

enum e_range {
    EMPTY,
    ONLY1,
    WHOLE,

    RANGES_LEN
};

template <typename T>
class context
{
private: /* types */
    typedef equal_to<T>      t_eq;
    typedef not_equal_to<T>  t_ne;
    typedef less<T>          t_lt;
    typedef less_equal<T>    t_le;
    typedef greater<T>       t_gt;
    typedef greater_equal<T> t_ge;

public: /* types */
    typedef T const                         *t_ptr;
    typedef input_iterator_restrictor<t_ptr> t_itr;

public: /* fields */
    t_ptr m_a_ptr_1st;
    t_ptr m_a_ptr_2nd;
    t_ptr m_a_ptr_end;
    t_ptr m_b_ptr_1st;

    t_itr m_a_itr_1st;
    t_itr m_a_itr_2nd;
    t_itr m_a_itr_end;
    t_itr m_b_itr_1st;

    t_eq m_eq;
    t_ne m_ne;
    t_lt m_lt;
    t_le m_le;
    t_gt m_gt;
    t_ge m_ge;

public: /* constructor */
    context(
        t_ptr const a_array, t_ptr const b_array, size_t const b_array_len
    )
    : m_a_ptr_1st(&a_array[0])
    , m_a_ptr_2nd(&a_array[1])
    , m_a_ptr_end(&a_array[b_array_len])
    , m_b_ptr_1st(&b_array[0])

    , m_a_itr_1st(m_a_ptr_1st)
    , m_a_itr_2nd(m_a_ptr_2nd)
    , m_a_itr_end(m_a_ptr_end)
    , m_b_itr_1st(m_b_ptr_1st)

    , m_eq()
    , m_ne()
    , m_lt()
    , m_le()
    , m_gt()
    , m_ge()
    {}
};

template <typename InputIterator>
inline static pair<bool, time_t> test_case(
    bool (&function)(//
        InputIterator, InputIterator, InputIterator
    ),
    range<InputIterator> const &range0,
    InputIterator const        &first1
)
{
    clock_t const start    = clock();
    bool const    ret      = function(range0.first, range0.ptend, first1);
    time_t const  duration = clock() - start;

    return make_pair(ret, duration);
}

template <typename InputIterator, typename BinaryPredicate>
inline static pair<bool, time_t> test_case(
    bool (&function)(//
        InputIterator, InputIterator, InputIterator, BinaryPredicate
    ),
    range<InputIterator> const &range0,
    InputIterator const        &first1,
    BinaryPredicate const      &cmp
)
{
    clock_t const start    = clock();
    bool const    ret      = function(range0.first, range0.ptend, first1, cmp);
    time_t const  duration = clock() - start;

    return make_pair(ret, duration);
}

template <typename InputIterator>
inline static t_status test_each_case(
    t_ratio_multiset &ratios, range<InputIterator> const &range0, InputIterator const &first1
)
{
    static size_t const HOW_MANY_CASES = 2;

    pair<bool, time_t> const candidate[HOW_MANY_CASES] = {
        test_case(CANDIDATE, range0, range0.first),
        test_case(CANDIDATE, range0, first1),
    };
    pair<bool, time_t> const reference[HOW_MANY_CASES] = {
        test_case(REFERENCE, range0, range0.first),
        test_case(REFERENCE, range0, first1),
    };

    for (size_t i = 0; i < HOW_MANY_CASES; ++i) {
        if (candidate[i].first != reference[i].first) {
            return FAILURE;
        }
        ratios.add_entry(candidate[i].second, reference[i].second);
    }
    return SUCCESS;
}

template <typename InputIterator, typename BinaryPredicate>
inline static t_status test_each_case(
    t_ratio_multiset           &ratios,
    range<InputIterator> const &range0,
    InputIterator const        &first1,
    BinaryPredicate const      &cmp
)
{
    static size_t const HOW_MANY_CASES = 2;

    pair<bool, time_t> const candidate[HOW_MANY_CASES] = {
        test_case(CANDIDATE, range0, range0.first, cmp),
        test_case(CANDIDATE, range0, first1, cmp),
    };
    pair<bool, time_t> const reference[HOW_MANY_CASES] = {
        test_case(REFERENCE, range0, range0.first, cmp),
        test_case(REFERENCE, range0, first1, cmp),
    };

    for (size_t i = 0; i < HOW_MANY_CASES; ++i) {
        if (candidate[i].first != reference[i].first) {
            return FAILURE;
        }
        ratios.add_entry(candidate[i].second, reference[i].second);
    }
    return SUCCESS;
}

template <typename T, typename InputIterator>
inline static t_status test_each_overload(
    t_ratio_multiset           &ratios,
    context<T> const           &ctxt,
    range<InputIterator> const &range0,
    InputIterator const        &first1
)
{
    t_status const results[] = {
        // equal(first0, ptend0, first1)
        test_each_case(ratios, range0, first1),

        // equal(first0, ptend0, first1, cmp)
        test_each_case(ratios, range0, first1, ctxt.m_eq),
        test_each_case(ratios, range0, first1, ctxt.m_ne),
        test_each_case(ratios, range0, first1, ctxt.m_lt),
        test_each_case(ratios, range0, first1, ctxt.m_le),
        test_each_case(ratios, range0, first1, ctxt.m_gt),
        test_each_case(ratios, range0, first1, ctxt.m_ge),
    };
    size_t const results_len = sizeof(results) / sizeof(results[0]);

    for (size_t i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

template <typename T>
inline static t_status test_each_range(
    t_ratio_multiset &ratios, context<T> const &ctxt
)
{
    typedef range<typename context<T>::t_ptr> t_ptr_range;
    typedef range<typename context<T>::t_itr> t_itr_range;

    t_ptr_range const ptr_ranges[RANGES_LEN] = {
        [EMPTY] = t_ptr_range(ctxt.m_a_ptr_1st, ctxt.m_a_ptr_1st),
        [ONLY1] = t_ptr_range(ctxt.m_a_ptr_1st, ctxt.m_a_ptr_2nd),
        [WHOLE] = t_ptr_range(ctxt.m_a_ptr_1st, ctxt.m_a_ptr_end),
    };
    t_itr_range const itr_ranges[RANGES_LEN] = {
        [EMPTY] = t_itr_range(ctxt.m_a_itr_1st, ctxt.m_a_itr_1st),
        [ONLY1] = t_itr_range(ctxt.m_a_itr_1st, ctxt.m_a_itr_2nd),
        [WHOLE] = t_itr_range(ctxt.m_a_itr_1st, ctxt.m_a_itr_end),
    };
    t_status const results[] = {
        test_each_overload(ratios, ctxt, ptr_ranges[EMPTY], ctxt.m_b_ptr_1st),
        test_each_overload(ratios, ctxt, ptr_ranges[ONLY1], ctxt.m_b_ptr_1st),
        test_each_overload(ratios, ctxt, ptr_ranges[WHOLE], ctxt.m_b_ptr_1st),

        test_each_overload(ratios, ctxt, itr_ranges[EMPTY], ctxt.m_b_itr_1st),
        test_each_overload(ratios, ctxt, itr_ranges[ONLY1], ctxt.m_b_itr_1st),
        test_each_overload(ratios, ctxt, itr_ranges[WHOLE], ctxt.m_b_itr_1st),
    };
    size_t const results_len = sizeof(results) / sizeof(results[0]);

    for (size_t i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

inline static t_status test_each_type(
    t_ratio_multiset &ratios
)
{
    context<int32_t> const  i32_ctxt(&I32_A[0], &I32_B[0], I32_B_LEN);
    context<uint16_t> const u16_ctxt(&U16_A[0], &U16_B[0], U16_B_LEN);
    context<string> const   str_ctxt(&STR_A[0], &STR_B[0], STR_B_LEN);

    t_status const results[] = {
        test_each_range(ratios, i32_ctxt),
        test_each_range(ratios, u16_ctxt),
        test_each_range(ratios, str_ctxt),
    };
    size_t const results_len = sizeof(results) / sizeof(results[0]);

    for (size_t i = 0; i < results_len; ++i) {
        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

t_status run_tests(
    t_ratio_multiset &ratios
)
{
    nanosleep(&delay, NULL);
    title::print(title::t_low_level("equal"));
    try {
        return test_each_type(ratios);
    }
    catch (exception const &e) {
        cout << "Exception: " << e.what() << '\n';
        return FAILURE;
    }
}

}}} // namespace tester::algorithm::equal
