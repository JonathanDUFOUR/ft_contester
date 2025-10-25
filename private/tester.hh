#ifndef TESTER_HH
#define TESTER_HH

#include "type/str.hh" // tester::t_str
#include <ctime> // timespec

namespace tester {

#define PADDING 33

timespec const delay = {
    .tv_sec  = 0,
    .tv_nsec = 0,
};

void title(t_str s);

} // namespace tester

#endif
