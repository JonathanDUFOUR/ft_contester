#ifndef TYPE_TEST_SUBCATEGORY_HH
#define TYPE_TEST_SUBCATEGORY_HH

#include "type/fundamentals.hh" // tester::t_bool
#include "type/pointers.hh" // tester::t_char_ptr
#include "type/test/benchmark/ratio_multiset.hh" // tester::test::benchmark::t_ratio_multiset_mut
#include "type/test/status.hh" // tester::test::t_status

namespace tester { namespace test {

using benchmark::t_ratio_multiset_mut;

typedef t_status (*subcategory_fn_ptr)(t_ratio_multiset_mut &);

typedef subcategory_fn_ptr const t_subcategory_fn_ptr;
typedef subcategory_fn_ptr       t_subcategory_fn_ptr_mut;

struct subcategory {
    t_char_ptr           name;
    t_subcategory_fn_ptr function;
    t_bool               run_by_default;

    t_status operator()(
        t_ratio_multiset_mut &ratios
    ) const
    {
        return function(ratios);
    }
};

typedef subcategory const t_subcategory;
typedef subcategory       t_subcategory_mut;

}} // namespace tester::test

#endif
