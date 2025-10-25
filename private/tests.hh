#ifndef TESTS_HH
#define TESTS_HH

#include "type/fundamentals.hh" // t_usize
#include "type/pointers.hh" // t_char_ptr
#include "type/test/category.hh" // tester::tests::category

namespace tester {

using test::t_category;

namespace test {

#define DECLARE(fn_name) t_status fn_name(t_char_ptr subcategory)

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

#undef DECLARE

} // namespace test

static t_category const CATEGORIES[] = {
    // Sequence containers
    // {"list",           test::list,           true},
    // {"deque",          test::deque,          true},
    // {"vector",         test::vector,         true},

    // Associative containers
    // {"map",            test::map,            true},
    // {"set",            test::set,            true},
    // {"multimap",       test::multimap,       true},
    // {"multiset",       test::multiset,       true},

    // Container adaptors
    // {"queue",          test::queue,          true},
    // {"priority_queue", test::priority_queue, true},
    // {"stack",          test::stack,          true},

    // Others
    {"algorithm", test::algorithm, true},
    // {"is_integral",    test::is_integral,    true},
    // {"iterator",       test::iterator,       true},
    // {"red_black_tree", test::red_black_tree, true},
    // {"utility",        test::utility,        true},
};

static t_usize const CATEGORIES_LEN = sizeof(CATEGORIES) / sizeof(CATEGORIES[0]);

} // namespace tester

#endif
