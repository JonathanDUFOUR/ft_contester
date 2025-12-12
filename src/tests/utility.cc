#include "targets/utility.hh"
#include "graphics.hh"
#include "type/category.hh"
#include "type/status.hh"
#include "type/subcategory.hh"
#include <iostream>
#include <map>
#include <string>

namespace tester { namespace utility {

using benchmark::t_ratio_multiset;
using std::cerr;
using std::cout;
using std::map;
using std::set;
using std::string;

inline static t_status run_subcategory(
    subcategory::t_function const &function
)
{
    t_ratio_multiset ratios;
    t_status const   result = function(ratios);

    if (result == SUCCESS) {
        cerr << SGR(FOREGROUND_GREEN);
        cout << "ok";
        cerr << SGR();
        cout << "     ";
        ratios.print();
    }
    else {
        cerr << SGR(FOREGROUND_RED);
        cout << "failed";
        cerr << SGR();
    }
    cout << '\n';
    return result;
}

inline static t_status run_all_subcategories()
{
    size_t failure_count = 0;

    for (size_t i = 0; i < SUBCATEGORIES_LEN; ++i) {
        if (run_subcategory(SUBCATEGORIES[i].function) == FAILURE) {
            ++failure_count;
        }
    }
    return failure_count ? FAILURE : SUCCESS;
}

inline static t_status run_default_subcategories()
{
    size_t failure_count = 0;

    for (size_t i = 0; i < SUBCATEGORIES_LEN; ++i) {
        if (!SUBCATEGORIES[i].run_by_default) {
            continue;
        }
        if (run_subcategory(SUBCATEGORIES[i].function) == FAILURE) {
            ++failure_count;
        }
    }
    return failure_count ? FAILURE : SUCCESS;
}

inline static t_status run_specific_subcategories(
    category::t_name_set const &targets
)
{
    typedef map<string, subcategory::t_function> t_target_map;

    t_target_map     valid_targets;
    t_ratio_multiset ratios;
    size_t           failure_count = 0;

    for (size_t i = 0; i < SUBCATEGORIES_LEN; ++i) {
        valid_targets.insert(std::make_pair(SUBCATEGORIES[i].name, SUBCATEGORIES[i].function));
    }
    for (set<string>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr) {
        t_target_map::const_iterator const target = valid_targets.find(*itr);

        if (target == valid_targets.end()) {
            cerr << SGR(FOREGROUND_RED);
            cout << "ERROR";
            cerr << SGR();
            cout << ": '" << *itr << "' subcategory not found\n";
            continue;
        }
        if (run_subcategory(target->second) == FAILURE) {
            ++failure_count;
        }
    }
    return failure_count ? FAILURE : SUCCESS;
}

t_status run_tests(
    category::t_name_set const &targets
)
{
    cerr << SGR(
        TEXT_BOLD
        FOREGROUND_BRIGHT_BLUE
    );
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "┃                     UTILITY                     ┃\n";
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
    cerr << SGR();

    if (targets.find("#all") != targets.end()) {
        return run_all_subcategories();
    }
    if (targets.find("#default") != targets.end()) {
        return run_default_subcategories();
    }
    return run_specific_subcategories(targets);
}

}} // namespace tester::utility
