#include "subcategories/algorithm.hh"
#include "graphics.hh"
#include <iostream>
#include <map>

namespace tester { namespace algorithm {

using benchmark::t_ratio_multiset;
using std::cerr;
using std::cout;
using std::make_pair;
using std::map;
using std::set;
using std::string;

inline static size_t run_default_subcategories()
{
    t_ratio_multiset ratios;
    size_t           failure_count = 0;

    for (size_t i = 0; i < SUBCATEGORIES_LEN; ++i) {
        if (!SUBCATEGORIES[i].run_by_default) {
            continue;
        }
        if (SUBCATEGORIES[i](ratios) == SUCCESS) {
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
            ++failure_count;
        }
        cout << '\n';
        ratios.clear();
    }
    return failure_count;
}

inline static size_t run_specific_subcategories(
    subcategory::t_set const &targets
)
{
    typedef map<string, subcategory::t_fn> t_target_map;

    t_target_map     valid_targets;
    t_ratio_multiset ratios;
    size_t           failure_count = 0;

    for (size_t i = 0; i < SUBCATEGORIES_LEN; ++i) {
        valid_targets.insert(make_pair(SUBCATEGORIES[i].name, SUBCATEGORIES[i].function));
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
        if (target->second(ratios) == SUCCESS) {
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
            ++failure_count;
        }
        cout << '\n';
    }
    return failure_count;
}

t_status run_tests(
    subcategory::t_set const &targets
)
{
    cerr << SGR(TEXT_BOLD FOREGROUND_BRIGHT_BLUE);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "┃                    ALGORITHM                    ┃\n";
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
    cerr << SGR();

    if (targets.find("*") != targets.end()) {
        return run_default_subcategories() ? FAILURE : SUCCESS;
    }
    return run_specific_subcategories(targets) ? FAILURE : SUCCESS;
}

}} // namespace tester::algorithm
