#ifndef TYPE_TEST_BENCHMARK_RATIO_MULTISET_HH
#define TYPE_TEST_BENCHMARK_RATIO_MULTISET_HH

#include <ctime>
#include <set>

namespace tester { namespace benchmark {

class t_ratio_multiset : public std::multiset<float>
{
private: // methods
    void fancy_print(float const ratio) const;
    void print_best() const;
    void print_mean() const;
    void print_worst() const;

public: // methods
    void add_entry(time_t const candidate_duration, time_t const reference_duration);
    void print() const;
};

}} // namespace tester::benchmark

#endif
