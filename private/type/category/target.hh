#ifndef TYPE_CATEGORY_TARGET_HH
#define TYPE_CATEGORY_TARGET_HH

#include "type/category/function.hh"

namespace tester { namespace category {

struct t_target {
    t_function m_function;
    t_name_set m_subtargets;
    bool       m_run_by_default;

    t_target(
        t_function const &function, bool const run_by_default
    )
    : m_function(function), m_run_by_default(run_by_default)
    {}
};

}} // namespace tester::category

#endif
