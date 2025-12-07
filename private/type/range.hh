#ifndef TYPE_RANGE_HH
#define TYPE_RANGE_HH

namespace tester {

template <typename InputIterator>
struct range {
    InputIterator first;
    InputIterator ptend;

    range(
        InputIterator const &first, InputIterator const &ptend
    )
    : first(first), ptend(ptend)
    {}
};

} // namespace tester

#endif
