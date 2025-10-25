#ifndef TYPE_TEST_BENCHMARK_RATIO_MULTISET_HH
#define TYPE_TEST_BENCHMARK_RATIO_MULTISET_HH

#include "graphics.hh" // {RESET_GRAPHICS,SET_{BACKGROUND_RGB,FOREGROUND_{GREEN,RED,YELLOW},INTENSITY_BOLD}}
#include "type/fundamentals.hh" // tester::t_float{,_mut}
#include <iomanip> // std::setw
#include <iostream> // std::cout
#include <numeric> // std::accumulate
#include <set> // std::multiset

namespace tester { namespace test { namespace benchmark {

using std::accumulate;
using std::cout;
using std::multiset;
using std::setw;

class ratio_multiset : public multiset<t_float_mut>
{
private:
    // ┏━━━━━━━━━┓
    // ┃ Methods ┃
    // ┗━━━━━━━━━┛

#define SET_FIELD_WIDTH   setw(5)
#define RESET_FIELD_WIDTH setw(0)

    void print_fancy_ratio(
        t_float ratio
    ) const
    {

        if (ratio > 20) {
            SET_FOREGROUND_RED;
            cout << SET_FIELD_WIDTH << ratio << RESET_FIELD_WIDTH << "x slower";
            RESET_GRAPHICS;
            return;
        }
        if (ratio > 10) {
            SET_FOREGROUND_YELLOW;
            cout << SET_FIELD_WIDTH << ratio << RESET_FIELD_WIDTH << "x slower";
            RESET_GRAPHICS;
            return;
        }
        if (ratio > 1) {
            SET_FOREGROUND_GREEN;
            cout << SET_FIELD_WIDTH << ratio << RESET_FIELD_WIDTH << "x slower";
            RESET_GRAPHICS;
            return;
        }
        SET_INTENSITY_BOLD;
        SET_FOREGROUND_BRIGHT_GREEN;
        SET_BACKGROUND_MAGENTA;
        ENABLE_BLINK;
        cout << SET_FIELD_WIDTH << 1 / ratio << RESET_FIELD_WIDTH << "x faster";
        RESET_GRAPHICS;
    }

#undef SET_FIELD_WIDTH
#undef RESET_FIELD_WIDTH

public:
    void print() const
    {
        if (!empty()) {
            print_best();
            cout << ' ';
            print_mean();
            cout << ' ';
            print_worst();
        }
    }

    void print_best() const
    {
        cout << "(best: ";
        print_fancy_ratio(*begin());
        cout << ')';
    }

    void print_mean() const
    {
        cout << "(mean: ";
        print_fancy_ratio(accumulate(begin(), end(), 0) / static_cast<float>(size()));
        cout << ')';
    }

    void print_worst() const
    {
        cout << "(worst: ";
        print_fancy_ratio(*rbegin());
        cout << ')';
    }

    void add_entry(
        time_t const candidate_duration, time_t const reference_duration
    )
    {
        t_float candidate = static_cast<t_float>(candidate_duration + !candidate_duration);
        t_float reference = static_cast<t_float>(reference_duration + !reference_duration);

        insert(candidate / reference);
    }
};

typedef ratio_multiset const t_ratio_multiset;
typedef ratio_multiset       t_ratio_multiset_mut;

}}} // namespace tester::test::benchmark

#endif
