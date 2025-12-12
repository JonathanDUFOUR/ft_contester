#ifndef TYPE_TEST_SUBCATEGORY_HH
#define TYPE_TEST_SUBCATEGORY_HH

#include "type/benchmark/ratio_multiset.hh"
#include "type/status.hh"

namespace tester { namespace subcategory {

typedef t_status (*t_function)(benchmark::t_ratio_multiset &);

struct type {
    char const      *name;
    t_function const function;
    bool             run_by_default;

    t_status operator()(
        benchmark::t_ratio_multiset &ratios
    ) const
    {
        return function(ratios);
    }
};

}} // namespace tester::subcategory

#endif
