#include "graphics.hh" // SET_FOREGROUND_RED,GRAPHICS_RESET
#include "tests.hh" // tester::{CATEGORIES,CATEGORIES_LEN}
#include "type/fundamentals.hh" // tester::t_u{8,size}
#include "type/pointers.hh" // tester::t_char_mut_ptr
#include "type/str.hh" // tester::t_str
#include "type/test/category.hh" // tester::test::t_category_fn_ptr
#include "type/test/status.hh" // tester::test::FAILURE
#include <cstddef> // NULL
#include <cstdlib> // srand
#include <cstring> // strstr
#include <ctime> // clock_t, time_t, time
#include <iomanip> // std::setprecision, std::fixed
#include <iostream> // std::{cerr, cout}
#include <map> // std::map

using std::cout;
using std::fixed;
using std::make_pair;
using std::map;
using std::setprecision;
using tester::CATEGORIES;
using tester::CATEGORIES_LEN;
using tester::t_char_mut_ptr;
using tester::t_str;
using tester::t_u8;
using tester::t_u8_mut;
using tester::t_usize_mut;
using tester::test::FAILURE;
using tester::test::t_category_fn_ptr;

inline static t_u8 run_default_categories()
{
    t_u8_mut failure_count = 0;

    for (t_usize_mut i = 0; i < CATEGORIES_LEN; ++i) {
        if (CATEGORIES[i].run_by_default && CATEGORIES[i](NULL) == FAILURE) {
            ++failure_count;
        }
    }
    return failure_count;
}

inline static t_u8 run_specific_categories(
    char *const *categories __attribute__((nonnull))
)
{
    t_u8_mut                                      failure_count = 0;
    map<t_str, t_category_fn_ptr>                 tests;
    map<t_str, t_category_fn_ptr>::const_iterator iter;

    for (t_usize_mut i = 0; i < CATEGORIES_LEN; ++i) {
        tests.insert(make_pair(CATEGORIES[i].name, CATEGORIES[i].function));
    }
    for (t_usize_mut i = 1; categories[i]; ++i) {
        char *subcategories = strstr(categories[i], "::");

        if (subcategories) {
            subcategories[0]  = 0;
            subcategories    += 2;
        }
        iter = tests.find(categories[i]);
        if (iter == tests.end()) {
            SET_FOREGROUND_RED;
            cout << "ERROR";
            RESET_GRAPHICS;
            cout << ": '" << categories[i] << "' tests not found\n";
        }
        else if (iter->second(subcategories) == FAILURE) {
            ++failure_count;
        }
    }
    return failure_count;
}

int main(
    int const ac, t_char_mut_ptr *av
)
{
    cout << setprecision(2) << fixed;
    srand(time(NULL));

    if (ac == 1) {
        return !!run_default_categories();
    }
    return !!run_specific_categories(av);
}
