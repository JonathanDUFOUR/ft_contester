#ifndef TYPE_CATEGORY_HH
#define TYPE_CATEGORY_HH

#include "type/category/function.hh"

namespace tester { namespace category {

struct type {
    t_name     name;
    t_function function;
    bool       run_by_default;
};

}} // namespace tester::category

#endif
