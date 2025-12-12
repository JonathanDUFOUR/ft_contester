#include "title.hh"
#include "graphics.hh"
#include "type/title/high_level.hh"
#include "type/title/low_level.hh"
#include <iomanip>
#include <iostream>

namespace tester { namespace title {

using std::cerr;
using std::cout;
using std::left;
using std::setw;
using std::string;

template <>
void print(
    t_high_level const &title
)
{
    string horizontal_line;

    for (size_t i = 0; i < title.m_text.length() + 2; ++i) {
        horizontal_line += "━";
    }

    cerr << SGR(
        TEXT_BOLD
        FOREGROUND_BRIGHT_BLUE
    );
    cout << "┏" << horizontal_line << "┓\n";
    cout << "┃ " << title.m_text << " ┃\n";
    cout << "┗" << horizontal_line << "┛\n";
    cerr << SGR();
}

template <>
void print(
    t_low_level const &title
)
{
    static int const FWIDTH = 33;

    cout << setw(FWIDTH) << left << title.m_text << ": ";
}

}} // namespace tester::title
