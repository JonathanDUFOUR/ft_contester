#ifndef TARGETS_ALGORITHM_HH
#define TARGETS_ALGORITHM_HH

#include "type/subcategory.hh"

#define DECLARE(category_name)                                                     \
    namespace category_name { t_status run_tests(benchmark::t_ratio_multiset &); }
#define TARGET(category_name) #category_name, category_name::run_tests

namespace tester { namespace algorithm {

DECLARE(equal);
DECLARE(lexicographical_compare);
DECLARE(swap);

static subcategory::type const TARGETS[] = {
    {TARGET(equal),                   false},
    {TARGET(lexicographical_compare), false},
    {TARGET(swap),                    false},
};
static size_t const HOW_MANY_TARGETS = sizeof(TARGETS) / sizeof(TARGETS[0]);

}} // namespace tester::algorithm

#endif
