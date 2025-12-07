#ifndef SUBCATEGORIES_ALGORITHM_HH
#define SUBCATEGORIES_ALGORITHM_HH

#include "type/subcategory.hh"

#define DECLARE(subcategory)                                                     \
    namespace subcategory { t_status run_tests(benchmark::t_ratio_multiset &); }
#define TEST(subcategory) #subcategory, subcategory::run_tests

namespace tester { namespace algorithm {

DECLARE(equal);
DECLARE(lexicographical_compare);
DECLARE(swap);

static subcategory::type const SUBCATEGORIES[] = {
    {TEST(equal),                   true},
    {TEST(lexicographical_compare), true},
    {TEST(swap),                    true},
};
static size_t const SUBCATEGORIES_LEN = sizeof(SUBCATEGORIES) / sizeof(SUBCATEGORIES[0]);

}} // namespace tester::algorithm

#endif
