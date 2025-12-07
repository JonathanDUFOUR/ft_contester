#ifndef TYPE_TEST_CATEGORY_HH
#define TYPE_TEST_CATEGORY_HH

#include "type/subcategory.hh"

namespace tester { namespace category {

typedef t_status (*t_fn)(subcategory::t_set const &);

struct type {
    char const *name;
    t_fn const  function;
    bool        run_by_default;

    t_status operator()(
        subcategory::t_set const &subcategories
    ) const
    {
        return function(subcategories);
    }
};

}} // namespace tester::category

#endif
