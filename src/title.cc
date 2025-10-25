#include "tester.hh" // PADDING
#include "type/str.hh" // tester::t_str_mut
#include <iostream> // std::cout

namespace tester {

using std::cout;

void title(
    t_str_mut s
)
{
    if (s.length() < PADDING) {
        s.append(PADDING - s.length(), ' ');
    }
    cout << s << ": ";
}

} // namespace tester
