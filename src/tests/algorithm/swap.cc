#include "algorithm.hpp"
#include "delay.hh"
#include "title.hh"
#include "type/benchmark/ratio_multiset.hh"
#include "type/status.hh"
#include "type/title/low_level.hh"
#include <iostream>

#define CANDIDATE ft::swap
#define REFERENCE std::swap

namespace tester { namespace algorithm { namespace swap {

using benchmark::t_ratio_multiset;
using std::cout;
using std::exception;
using std::make_pair;
using std::pair;
using std::string;

template <typename T>
struct context {
    T m_a;
    T m_b;

    context(
        T const &a, T const &b
    )
    : m_a(a), m_b(b)
    {}
};

template <typename T>
inline static pair<pair<T, T>, time_t> test_case(
    void (&function)(//
        T &, T &
    ),
    context<T> ctxt
)
{
    clock_t const start = clock();
    function(ctxt.m_a, ctxt.m_b);
    time_t const duration = clock() - start;

    return make_pair(make_pair(ctxt.m_a, ctxt.m_b), duration);
}

template <typename T>
inline static t_status test_each_case(
    t_ratio_multiset &ratios, context<T> const &ctxt
)
{
    static size_t const HOW_MANY_CASES = 1;

    pair<pair<T, T>, time_t> const candidate[HOW_MANY_CASES] = {
        test_case(CANDIDATE, ctxt),
    };
    pair<pair<T, T>, time_t> const reference[HOW_MANY_CASES] = {
        test_case(REFERENCE, ctxt),
    };

    for (size_t i = 0; i < HOW_MANY_CASES; ++i) {
        if (candidate[i].first != reference[i].first) {
            return FAILURE;
        }
        ratios.add_entry(candidate[i].second, reference[i].second);
    }
    return SUCCESS;
}

inline static t_status test_each_type(
    t_ratio_multiset &ratios
)
{
    context<int32_t> const  i32_ctxt(125, -42);
    context<uint16_t> const u16_ctxt(~0, 0);
    context<string> const   str_ctxt("foo", "bar");

    t_status const results[] = {
        test_each_case(ratios, i32_ctxt),
        test_each_case(ratios, u16_ctxt),
        test_each_case(ratios, str_ctxt),
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
    title::print(title::t_low_level("swap"));
    try {
        return test_each_type(ratios);
    }
    catch (exception const &e) {
        cout << "Exception: " << e.what() << '\n';
        return FAILURE;
    }
}

}}} // namespace tester::algorithm::swap
