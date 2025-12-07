#ifndef ITERATOR_RESTRICTOR_RANDOM_ACCESS_HH
#define ITERATOR_RESTRICTOR_RANDOM_ACCESS_HH

#include "type_traits.hh"
#include <iterator>

namespace tester {

template <typename RandomAccessIterator>
class random_access_iterator_restrictor
{
private: // types
    typedef RandomAccessIterator              t_iterator;
    typedef random_access_iterator_restrictor t_self;
    typedef std::iterator_traits<t_iterator>  t_traits;

public: // types
    typedef std::random_access_iterator_tag    iterator_category;
    typedef typename t_traits::difference_type difference_type;
    typedef typename t_traits::value_type      value_type;
    typedef typename t_traits::reference       reference;
    typedef typename t_traits::pointer         pointer;

private: // fields
    t_iterator m_itr;

public: // constructors
    //! \brief (Default|Wrap) constructor.
    //!
    random_access_iterator_restrictor(
        t_iterator const &itr = t_iterator()
    )
    : m_itr(itr)
    {}

    //! \brief Copy constructor.
    //!
    random_access_iterator_restrictor(
        t_self const &other
    )
    : m_itr(other.m_itr)
    {}

private: // methods
    pointer dispatch_arrow_operator(
        t_false
    ) const
    {
        return m_itr.operator->();
    }

    pointer dispatch_arrow_operator(
        t_true
    ) const
    {
        return m_itr;
    }

public: // operators
    bool operator==(
        t_self const &rhs
    ) const
    {
        return m_itr == rhs.m_itr;
    }

    bool operator!=(
        t_self const &rhs
    ) const
    {
        return m_itr != rhs.m_itr;
    }

    bool operator<(
        t_self const &rhs
    ) const
    {
        return m_itr < rhs.m_itr;
    }

    bool operator>(
        t_self const &rhs
    ) const
    {
        return m_itr > rhs.m_itr;
    }

    bool operator<=(
        t_self const &rhs
    ) const
    {
        return m_itr <= rhs.m_itr;
    }

    bool operator>=(
        t_self const &rhs
    ) const
    {
        return m_itr >= rhs.m_itr;
    }

    difference_type operator-(
        t_self const &rhs
    ) const
    {
        return m_itr - rhs.m_itr;
    }

    t_self operator+(
        difference_type const rhs
    ) const
    {
        return t_self(m_itr + rhs);
    }

    t_self operator-(
        difference_type const rhs
    ) const
    {
        return t_self(m_itr - rhs);
    }

    reference operator*() const { return *m_itr; }

    reference operator[](
        difference_type const ofs
    ) const
    {
        return m_itr[ofs];
    }

    pointer operator->() const { return dispatch_arrow_operator(is_pointer<t_iterator>()); }

    t_self &operator=(
        t_self const &rhs
    )
    {
        m_itr = rhs.m_itr;
        return *this;
    }

    //! \warning Caller pointing to the past-the-end element before incrementing
    //!          is undefined behavior.
    //!
    t_self &operator++()
    {
        ++m_itr;
        return *this;
    }

    //! \warning Caller pointing to the past-the-end element before incrementing
    //!          is undefined behavior.
    //!
    t_self operator++(
        int
    )
    {
        return t_self(m_itr++);
    }

    //! \warning Caller pointing to the first element before decrementing is undefined behavior.
    //!
    t_self &operator--()
    {
        --m_itr;
        return *this;
    }

    //! \warning Caller pointing to the first element before decrementing is undefined behavior.
    //!
    t_self operator--(
        int
    )
    {
        return t_self(m_itr--);
    }

    //! \warning Caller being less than `rhs` far from the past-the-end element before moving
    //!          is undefined behavior.
    //!
    t_self &operator+=(
        difference_type const rhs
    )
    {
        m_itr += rhs;
        return *this;
    }

    //! \warning Caller being less than `rhs` far from the first element before moving
    //!          is undefined behavior.
    //!
    t_self &operator-=(
        difference_type const rhs
    )
    {
        m_itr -= rhs;
        return *this;
    }
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
