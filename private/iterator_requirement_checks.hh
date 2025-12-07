#ifndef ITERATOR_REQUIREMENT_CHECKS_HH
#define ITERATOR_REQUIREMENT_CHECKS_HH

#include <iterator>

namespace tester {

using std::iterator_traits;

template <typename InputIterator>
void check_input_iterator_requirements(
    InputIterator &iter
)
{
    InputIterator const a(iter);
    InputIterator const b(iter++);
    InputIterator const c(++iter);
    InputIterator       d(iter);
    bool                cmp __attribute__((unused));

    cmp  = (a == b && *a == *b);
    cmp  = (a != b && *a != *b);
    iter = (d = a);
}

template <typename OutputIterator>
void check_output_iterator_requirements(
    OutputIterator &iter
)
{
    OutputIterator const a(iter);
    OutputIterator const b(iter++);
    OutputIterator const c(++iter);

    iter  = (b = a);
    *iter = *a;
}

template <typename ForwardIterator>
void check_forward_iterator_requirements(
    ForwardIterator &iter
)
{
    ForwardIterator const a;

    ForwardIterator();
    check_input_iterator_requirements(iter);
}

template <typename BidirectionalIterator>
void check_bidirectional_iterator_requirements(
    BidirectionalIterator &iter
)
{
    --BidirectionalIterator(iter)--;
    check_forward_iterator_requirements(iter);
}

template <typename RandomAccessIterator>
void check_random_access_iterator_requirements(
    RandomAccessIterator &iter
)
{
    typedef typename iterator_traits<RandomAccessIterator>::difference_type difference_type;

    RandomAccessIterator const a(iter);
    RandomAccessIterator const b(iter += 2);
    RandomAccessIterator const c(iter -= 2);
    RandomAccessIterator const d(iter + 3);
    RandomAccessIterator const e(iter - 3);
    RandomAccessIterator const f(4 + iter);
    difference_type            ofs __attribute__((unused));
    bool                       cmp __attribute__((unused));

    ofs = (a - f);
    cmp = (a < b);
    cmp = (a > b);
    cmp = (a <= b);
    cmp = (a >= b);
    cmp = (iter[0] == a[0]);

    check_bidirectional_iterator_requirements(iter);
}

} // namespace tester

#endif
