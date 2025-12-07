#ifndef TESTER_HH
#define TESTER_HH

#include <ctime>
#include <string>

namespace tester {

#define PADDING 33

timespec const delay = {
    .tv_sec  = 0,
    .tv_nsec = 0,
};

void title(std::string const s);

} // namespace tester

#endif
