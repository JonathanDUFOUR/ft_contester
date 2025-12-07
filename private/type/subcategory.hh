#ifndef TYPE_TEST_SUBCATEGORY_HH
#define TYPE_TEST_SUBCATEGORY_HH

#include "type/benchmark/ratio_multiset.hh"
#include "type/status.hh"
#include <string>

namespace tester { namespace subcategory {

typedef std::set<std::string> t_set;

typedef t_status (*t_fn)(benchmark::t_ratio_multiset &);

struct type {
    char const *name;
    t_fn const  function;
    bool        run_by_default;

    t_status operator()(
        benchmark::t_ratio_multiset &ratios
    ) const
    {
        return function(ratios);
    }
};

}} // namespace tester::subcategory

#endif
