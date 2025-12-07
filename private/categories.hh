#ifndef TESTS_HH
#define TESTS_HH

#include "type/category.hh"

#define DECLARE(category)                                                  \
    namespace category { t_status run_tests(subcategory::t_set const &); }
#define TEST(category) #category, category::run_tests

namespace tester {

// Sequence containers
DECLARE(list);
DECLARE(deque);
DECLARE(vector);

// Associative containers
DECLARE(map);
DECLARE(set);
DECLARE(multimap);
DECLARE(multiset);

// Container adaptors
DECLARE(stack);
DECLARE(queue);
DECLARE(priority_queue);

// Others
DECLARE(algorithm);
DECLARE(is_integral);
DECLARE(iterator);
DECLARE(red_black_tree);
DECLARE(utility);

static category::type const CATEGORIES[] = {
    // Sequence containers
    // {TEST(list),           true},
    // {TEST(deque),          true},
    // {TEST(vector),         true},

    // Associative containers
    // {TEST(map),            true},
    // {TEST(set),            true},
    // {TEST(multimap),       true},
    // {TEST(multiset),       true},

    // Container adaptors
    // {TEST(queue),          true},
    // {TEST(priority_queue), true},
    // {TEST(stack),          true},

    // Others
    {TEST(algorithm), true},
    // {TEST(is_integral),    true},
    // {TEST(iterator),       true},
    // {TEST(red_black_tree), true},
    // {TEST(utility),        true},
};
static size_t const CATEGORIES_LEN = sizeof(CATEGORIES) / sizeof(CATEGORIES[0]);

} // namespace tester

#endif
