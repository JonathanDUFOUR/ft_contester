#include "tester.hh"
#include <iostream>
#include <string>

namespace tester {

using std::cout;
using std::string;

void title(
    string s
)
{
    if (s.length() < PADDING) {
        s.append(PADDING - s.length(), ' ');
    }
    cout << s << ": ";
}

} // namespace tester
