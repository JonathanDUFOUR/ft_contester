#ifndef TYPE_RANGE_HH
#define TYPE_RANGE_HH

namespace tester {

template <typename InputIterator>
struct s_range {
#define SELF s_range

    InputIterator first;
    InputIterator ptend;

    SELF(
        InputIterator const &first, InputIterator const &ptend
    )
    : first(first), ptend(ptend)
    {}

#undef SELF
};

} // namespace tester

#endif
