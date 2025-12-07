#include "categories.hh"
#include "graphics.hh"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>

using std::cout;
using std::fixed;
using std::setprecision;

namespace tester {

using std::cerr;
using std::make_pair;
using std::pair;
using std::string;

inline static size_t run_default_categories()
{
    size_t             failure_count = 0;
    subcategory::t_set subcategories;

    subcategories.insert("*");
    for (size_t i = 0; i < CATEGORIES_LEN; ++i) {
        if (CATEGORIES[i].run_by_default && CATEGORIES[i](subcategories) == FAILURE) {
            ++failure_count;
        }
    }
    return failure_count;
}

inline static size_t run_specific_categories(
    size_t ac, char *const *const av __attribute__((nonnull))
)
{
    typedef std::map<string, pair<category::t_fn, subcategory::t_set> > t_target_map;

    t_target_map valid_targets;

    for (size_t i = 0; i < CATEGORIES_LEN; ++i) {
        valid_targets.insert(
            make_pair(CATEGORIES[i].name, make_pair(CATEGORIES[i].function, subcategory::t_set()))
        );
    }
    while (--ac) {
        string const                 arg       = av[ac];
        string::size_type const      separator = arg.find("::");
        string const                 category  = arg.substr(0, separator);
        t_target_map::iterator const target    = valid_targets.find(category);

        if (target == valid_targets.end()) {
            cerr << SGR(FOREGROUND_RED);
            cout << "ERROR";
            cerr << SGR();
            cout << ": '" << category << "' category not found\n";
            continue;
        }
        target->second.second.insert(separator == string::npos ? "*" : arg.substr(separator + 2));
    }
    size_t failure_count = 0;

    for (t_target_map::const_iterator itr = valid_targets.begin(); itr != valid_targets.end();
         ++itr) {
        if (itr->second.second.empty()) {
            continue;
        }
        if (itr->second.first(itr->second.second) == FAILURE) {
            ++failure_count;
        }
    }
    return failure_count;
}

} // namespace tester

int main(
    int const ac, char *const *const av
)
{
    cout << setprecision(2) << fixed;
    srand(time(NULL));

    if (ac == 1) {
        return !!tester::run_default_categories();
    }
    return !!tester::run_specific_categories(ac, av);
}
