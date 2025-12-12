#include "delay.hh"
#include "title.hh"
#include "type/benchmark/ratio_multiset.hh"
#include "type/status.hh"
#include "type/title/low_level.hh"
#include "utility.hpp"
#include <iostream>

#define CANDIDATE ft::make_pair
#define REFERENCE std::make_pair

namespace tester { namespace utility { namespace pair {

using benchmark::t_ratio_multiset;
using std::cout;
using std::exception;

t_status run_tests(
    t_ratio_multiset &ratios
)
{
    (void)ratios;
    nanosleep(&delay, NULL);
    title::print(title::t_low_level("pair"));
    try {
        // return test_each_type(ratios);
        return SUCCESS;
    }
    catch (exception const &e) {
        cout << "Exception: " << e.what() << '\n';
        return FAILURE;
    }
}

}}} // namespace tester::utility::pair
