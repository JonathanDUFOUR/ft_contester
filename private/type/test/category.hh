#ifndef TYPE_TEST_CATEGORY_HH
#define TYPE_TEST_CATEGORY_HH

#include "type/fundamentals.hh" // tester::t_bool
#include "type/pointers.hh" // tester::t_char_ptr
#include "type/test/status.hh" // tester::test::t_status

namespace tester { namespace test {

typedef t_status (*category_fn_ptr)(t_char_ptr subcategories);

typedef category_fn_ptr const t_category_fn_ptr;
typedef category_fn_ptr       t_category_fn_ptr_mut;

struct category {
    t_char_ptr        name;
    t_category_fn_ptr function;
    t_bool            run_by_default;

    t_status operator()(
        t_char_ptr subcategories
    ) const
    {
        return function(subcategories);
    }
};

typedef category const t_category;
typedef category       t_category_mut;

}} // namespace tester::test

#endif
