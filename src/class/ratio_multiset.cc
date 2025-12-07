#include "type/benchmark/ratio_multiset.hh"
#include "graphics.hh"
#include <iomanip>
#include <iostream>
#include <numeric>

namespace tester { namespace benchmark {

using std::_Setw;
using std::accumulate;
using std::cerr;
using std::cout;
using std::setw;

// ┏━━━━━━━━━┓
// ┃ Methods ┃
// ┗━━━━━━━━━┛

void t_ratio_multiset::add_entry(
    time_t const candidate_duration, time_t const reference_duration
)
{
    float const candidate = static_cast<float const>(candidate_duration + !candidate_duration);
    float const reference = static_cast<float const>(reference_duration + !reference_duration);

    insert(candidate / reference);
}

void t_ratio_multiset::fancy_print(
    float const ratio
) const
{
    static _Setw const FWIDTH_SET   = setw(5);
    static _Setw const FWIDTH_RESET = setw(0);

    if (ratio > 20) {
        cerr << SGR(FOREGROUND_RED);
        cout << FWIDTH_SET << ratio << FWIDTH_RESET << "x slower";
        cerr << SGR();
        return;
    }
    if (ratio > 10) {
        cerr << SGR(FOREGROUND_YELLOW);
        cout << FWIDTH_SET << ratio << FWIDTH_RESET << "x slower";
        cerr << SGR();
        return;
    }
    if (ratio > 1) {
        cerr << SGR(FOREGROUND_GREEN);
        cout << FWIDTH_SET << ratio << FWIDTH_RESET << "x slower";
        cerr << SGR();
        return;
    }
    cerr << SGR(
        TEXT_BOLD
        BLINK_ON
        BACKGROUND_MAGENTA
        FOREGROUND_BRIGHT_GREEN
    );
    cout << FWIDTH_SET << 1 / ratio << FWIDTH_RESET << "x faster";
    cerr << SGR();
}

void t_ratio_multiset::print_best() const
{
    cout << "(best: ";
    fancy_print(*begin());
    cout << ')';
}

void t_ratio_multiset::print_mean() const
{
    cout << "(mean: ";
    fancy_print(accumulate(begin(), end(), 0) / static_cast<float>(size()));
    cout << ')';
}

void t_ratio_multiset::print_worst() const
{
    cout << "(worst: ";
    fancy_print(*rbegin());
    cout << ')';
}

void t_ratio_multiset::print() const
{
    if (!empty()) {
        print_best();
        cout << ' ';
        print_mean();
        cout << ' ';
        print_worst();
    }
}

}} // namespace tester::benchmark
