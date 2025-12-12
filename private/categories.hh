#ifndef TESTS_HH
#define TESTS_HH

#include "type/category.hh"

#define DECLARE(category_name)                                                    \
    namespace category_name { t_status run_tests(category::t_name_set const &); }
#define CATEGORY(category_name) #category_name, category_name::run_tests

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
    // {CATEGORY(list),           true},
    // {CATEGORY(deque),          true},
    // {CATEGORY(vector),         true},

    // Associative containers
    // {CATEGORY(map),            true},
    // {CATEGORY(set),            true},
    // {CATEGORY(multimap),       true},
    // {CATEGORY(multiset),       true},

    // Container adaptors
    // {CATEGORY(queue),          true},
    // {CATEGORY(priority_queue), true},
    // {CATEGORY(stack),          true},

    // Others
    {CATEGORY(algorithm), false},

    // {CATEGORY(is_integral),    true},
    // {CATEGORY(iterator),       true},
    // {CATEGORY(red_black_tree), true},
    {CATEGORY(utility),   true },
};
static size_t const HOW_MANY_CATEGORIES = sizeof(CATEGORIES) / sizeof(CATEGORIES[0]);

} // namespace tester

#endif
