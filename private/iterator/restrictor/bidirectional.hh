#ifndef ITERATOR_RESTRICTOR_BIDIRECTIONAL_HH
#define ITERATOR_RESTRICTOR_BIDIRECTIONAL_HH

#include "type_traits.hh" // tester::{t_{false,true},is_pointer}
#include <iterator> // std::{iterator_traits,bidirectional_iterator_tag}

namespace tester {

using std::bidirectional_iterator_tag;
using std::iterator_traits;

template <typename BidirectionalIterator>
class bidirectional_iterator_restrictor
{
#define SELF bidirectional_iterator_restrictor

private:
    typedef BidirectionalIterator const t_iterator;
    typedef BidirectionalIterator       t_iterator_mut;
    typedef SELF const                  t_self;
    typedef SELF                        t_self_mut;
    typedef iterator_traits<t_iterator> t_traits;

public:
    typedef bidirectional_iterator_tag         iterator_category;
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

    reference operator*() const { return *m_iter; }

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

#undef SELF
};

} // namespace tester

#endif
