#include "error.hh"
#include "graphics.hh"
#include "type/error/target_not_found.hh"
#include <iostream>

namespace tester { namespace error {

using std::cerr;
using std::cout;

template <>
void print(
    t_target_not_found const &err
)
{
    cerr << SGR(FOREGROUND_RED);
    cout << "ERROR";
    cerr << SGR();
    cout << ": '" << err.m_target_name << "' target not found\n";
}

}} // namespace tester::error
