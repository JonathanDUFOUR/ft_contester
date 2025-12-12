#ifndef SUBCATEGORIES_UTILITY_HH
#define SUBCATEGORIES_UTILITY_HH

#include "type/subcategory.hh"

#define DECLARE(subcategory)                                                     \
    namespace subcategory { t_status run_tests(benchmark::t_ratio_multiset &); }
#define TEST(subcategory) #subcategory, subcategory::run_tests

namespace tester { namespace utility {

DECLARE(pair);
DECLARE(make_pair);

static subcategory::type const SUBCATEGORIES[] = {
    {TEST(pair),      true},
    {TEST(make_pair), true},
};
static size_t const SUBCATEGORIES_LEN = sizeof(SUBCATEGORIES) / sizeof(SUBCATEGORIES[0]);

}} // namespace tester::utility

#endif
