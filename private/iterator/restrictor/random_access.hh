#ifndef ITERATOR_RESTRICTOR_RANDOM_ACCESS_HH
#define ITERATOR_RESTRICTOR_RANDOM_ACCESS_HH

#include "type_traits.hh" // tester::{t_{false,true},is_pointer}
#include <iterator> // std::{iterator_traits,random_access_iterator_tag}

namespace tester {

using std::iterator_traits;
using std::random_access_iterator_tag;

template <typename RandomAccessIterator>
class random_access_iterator_restrictor
{
#define SELF random_access_iterator_restrictor

private:
    typedef RandomAccessIterator const      t_iterator;
    typedef RandomAccessIterator            t_iterator_mut;
    typedef SELF const                      t_self;
    typedef SELF                            t_self_mut;
    typedef iterator_traits<t_iterator_mut> t_traits;

public:
    typedef random_access_iterator_tag         iterator_category;
    typedef typename t_traits::difference_type difference_type;
    typedef typename t_traits::value_type      value_type;
    typedef typename t_traits::reference       reference;
    typedef typename t_traits::pointer         pointer;

private:
    t_iterator_mut m_iter;

public:
    // ┏━━━━━━━━━━━━━━┓
    // ┃ Constructors ┃
    // ┗━━━━━━━━━━━━━━┛

    //! \brief (Default|Wrap) constructor.
    //!
    SELF(
        t_iterator &iter = t_iterator()
    )
    : m_iter(iter)
    {}

    //! \brief Copy constructor.
    //!
    SELF(
        t_self &other
    )
    : m_iter(other.m_iter)
    {}

private:
    // ┏━━━━━━━━━┓
    // ┃ Methods ┃
    // ┗━━━━━━━━━┛

    pointer dispatch_arrow_operator(
        t_false
    ) const
    {
        return m_iter.operator->();
    }

    pointer dispatch_arrow_operator(
        t_true
    ) const
    {
        return m_iter;
    }

    // ┏━━━━━━━━━━━┓
    // ┃ Operators ┃
    // ┗━━━━━━━━━━━┛

    bool operator==(
        t_self &rhs
    ) const
    {
        return m_iter == rhs.m_iter;
    }

    bool operator!=(
        t_self &rhs
    ) const
    {
        return m_iter != rhs.m_iter;
    }

    bool operator<(
        t_self &rhs
    ) const
    {
        return m_iter < rhs.m_iter;
    }

    bool operator>(
        t_self &rhs
    ) const
    {
        return m_iter > rhs.m_iter;
    }

    bool operator<=(
        t_self &rhs
    ) const
    {
        return m_iter <= rhs.m_iter;
    }

    bool operator>=(
        t_self &rhs
    ) const
    {
        return m_iter >= rhs.m_iter;
    }

    reference operator*() const { return *m_iter; }

    reference operator[](
        difference_type const offset
    ) const
    {
        return m_iter[offset];
    }

    pointer operator->() const { return dispatch_arrow_operator(is_pointer<t_iterator>()); }

    t_self_mut &operator=(
        t_self &rhs
    )
    {
        m_iter = rhs.m_iter;
        return *this;
    }

    t_self_mut &operator++()
    {
        ++m_iter;
        return *this;
    }

    t_self operator++(
        int
    )
    {
        return t_self(m_iter++);
    }

    t_self_mut &operator--()
    {
        --m_iter;
        return *this;
    }

    t_self operator--(
        int
    )
    {
        return t_self(m_iter--);
    }

    t_self_mut &operator+=(
        difference_type const rhs
    )
    {
        m_iter += rhs;
        return *this;
    }

    t_self_mut &operator-=(
        difference_type const rhs
    )
    {
        m_iter -= rhs;
        return *this;
    }

    t_self operator+(
        difference_type const rhs
    ) const
    {
        return t_self(m_iter + rhs);
    }

    t_self operator-(
        difference_type const rhs
    ) const
    {
        return t_self(m_iter - rhs);
    }

    difference_type operator-(
        t_self &rhs
    )
    {
        return m_iter - rhs.m_iter;
    }

#undef SELF
};

template <typename RandomAccessIterator>
inline random_access_iterator_restrictor<RandomAccessIterator> operator+(
    typename random_access_iterator_restrictor<RandomAccessIterator>::difference_type const lhs,
    random_access_iterator_restrictor<RandomAccessIterator> const                          &rhs
)
{
    return rhs + lhs;
}

} // namespace tester

#endif
