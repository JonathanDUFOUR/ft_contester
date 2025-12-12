#ifndef DELAY_HH
#define DELAY_HH

#include <ctime>

namespace tester {

timespec const delay = {
    .tv_sec  = 0,
    .tv_nsec = 0,
};

} // namespace tester

#endif
