#ifndef ITERATOR_RESTRICTOR_BIDIRECTIONAL_HH
#define ITERATOR_RESTRICTOR_BIDIRECTIONAL_HH

#include "type_traits.hh"
#include <iterator>

namespace tester {

template <typename BidirectionalIterator>
class bidirectional_iterator_restrictor
{
private: // types
    typedef BidirectionalIterator             t_iterator;
    typedef bidirectional_iterator_restrictor t_self;
    typedef std::iterator_traits<t_iterator>  t_traits;

public: // types
    typedef std::bidirectional_iterator_tag    iterator_category;
    typedef typename t_traits::difference_type difference_type;
    typedef typename t_traits::value_type      value_type;
    typedef typename t_traits::reference       reference;
    typedef typename t_traits::pointer         pointer;

private: // fields
    t_iterator m_itr;

public: // constructors
    //! \brief (Default|Wrap) constructor.
    //!
    bidirectional_iterator_restrictor(
        t_iterator const &itr = t_iterator()
    )
    : m_itr(itr)
    {}

    //! \brief Copy constructor.
    //!
    bidirectional_iterator_restrictor(
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

    reference operator*() const { return *m_itr; }

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
};

} // namespace tester

#endif
