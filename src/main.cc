#include "categories.hh"
#include "error.hh"
#include "type/category/name.hh"
#include "type/category/name_set.hh"
#include "type/category/target.hh"
#include "type/category/target_map.hh"
#include "type/error/target_not_found.hh"
#include "type/status.hh"
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>

using std::cout;
using std::fixed;
using std::setprecision;

namespace tester {

using std::for_each;
using std::make_pair;
using std::setw; // DEBUG
using std::string;

inline static void prepare_valid_targets(
    category::t_target_map &targets
)
{
    for (size_t i = 0; i < HOW_MANY_CATEGORIES; ++i) {
        targets.insert(make_pair(
            CATEGORIES[i].name,
            category::t_target(CATEGORIES[i].function, CATEGORIES[i].run_by_default)
        ));
    }
}

inline static void propagate_tag_all(
    category::t_target_map::value_type &target
)
{
    target.second.m_subtargets.clear();
    target.second.m_subtargets.insert("/a");
}

inline static void propagate_tag_default(
    category::t_target_map::value_type &target
)
{
    if (target.second.m_run_by_default) {
        target.second.m_subtargets.insert("/d");
    }
}

//! \return `true` if the entire target processing can stop here, `false` otherwise
//!
inline static bool process_target_name(
    category::t_name const &raw_target_name, category::t_target_map &targets
)
{
    category::t_name::size_type const      separator   = raw_target_name.find("::");
    category::t_name const                 target_name = raw_target_name.substr(0, separator);
    category::t_target_map::iterator const target      = targets.find(target_name);

    if (target_name == "/a" || target_name == "/all") {
        for_each(targets.begin(), targets.end(), propagate_tag_all);
        return true;
    }
    if (target_name == "/d" || target_name == "/default") {
        for_each(targets.begin(), targets.end(), propagate_tag_default);
        return false;
    }
    if (target == targets.end()) {
        error::print(error::t_target_not_found(target_name));
        return false;
    }
    target->second.m_subtargets.insert(
        separator == category::t_name::npos ? "/d" : raw_target_name.substr(separator + 2)
    );
    return false;
}

inline static void record_targets_to_run(
    category::t_name_set const &target_names, category::t_target_map &targets
)
{
    typedef category::t_name_set::const_iterator t_iterator;

    for (t_iterator itr = target_names.begin(); itr != target_names.end(); ++itr) {
        if (process_target_name(*itr, targets)) {
            break;
        }
    }
}

inline static void print_target(
    category::t_target const &target
)
{
    typedef category::t_name_set::const_iterator t_iterator;

    cout << "{ run_by_default: " << target.m_run_by_default << ", subtargets: [ ";
    for (t_iterator itr = target.m_subtargets.begin(); itr != target.m_subtargets.end(); ++itr) {
        cout << *itr << ' ';
    }
    cout << "] }";
}

inline static void print_targets(
    category::t_target_map const &targets
)
{
    typedef category::t_target_map::const_iterator t_iterator;

    cout << "targets: [\n";
    for (t_iterator itr = targets.begin(); itr != targets.end(); ++itr) {
        category::t_name const   &target_name = itr->first;
        category::t_target const &target      = itr->second;

        cout << setw(11) << target_name << ": ";
        print_target(target);
        cout << '\n';
    }
    cout << "]\n";
}

inline static t_status run_targets(
    category::t_target_map &targets
)
{
    typedef category::t_target_map::const_iterator t_iterator;

    t_status overall_status = SUCCESS;

    for (t_iterator itr = targets.begin(); itr != targets.end(); ++itr) {
        category::t_target const &target = itr->second;

        if (!target.m_subtargets.empty() && target.m_function(target.m_subtargets) == FAILURE) {
            overall_status = FAILURE;
        }
    }
    return overall_status;
}

inline static t_status run_tests(
    category::t_name_set const &target_names
)
{
    category::t_target_map targets;

    prepare_valid_targets(targets);
    record_targets_to_run(target_names, targets);
    print_targets(targets);
    return run_targets(targets);
}

} // namespace tester

int main(
    int const ac, char const *const *const av
)
{
    cout << setprecision(2) << fixed;
    srand(time(NULL));

    tester::category::t_name_set target_names(&av[1], &av[ac]);

    if (target_names.empty()) {
        target_names.insert("/d");
    }
    return tester::run_tests(target_names);
}
