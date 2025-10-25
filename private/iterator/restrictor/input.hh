#ifndef ITERATOR_RESTRICTOR_INPUT_HH
#define ITERATOR_RESTRICTOR_INPUT_HH

#include "type_traits.hh" // tester::{t_{false,true},is_pointer,make_const_{pointee, referent}}
#include <iterator> // std::{iterator_traits,input_iterator_tag}

namespace tester {

using std::input_iterator_tag;
using std::iterator_traits;

template <typename InputIterator>
class input_iterator_restrictor
{
#define SELF input_iterator_restrictor

private:
    typedef InputIterator const             t_iterator;
    typedef InputIterator                   t_iterator_mut;
    typedef SELF const                      t_self;
    typedef SELF                            t_self_mut;
    typedef iterator_traits<t_iterator_mut> t_traits;

public:
    typedef input_iterator_tag                                               iterator_category;
    typedef typename t_traits::difference_type                               difference_type;
    typedef typename t_traits::value_type                                    value_type;
    typedef typename make_const_referent<typename t_traits::reference>::type reference;
    typedef typename make_const_pointee<typename t_traits::pointer>::type    pointer;

private:
    t_iterator_mut m_iter;

public:
    // ┏━━━━━━━━━━━━━━┓
    // ┃ Constructors ┃
    // ┗━━━━━━━━━━━━━━┛

    //! \brief Wrap constructor.
    //!
    SELF(
        t_iterator &iter
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

public:
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

    //! \warning Caller pointing to the post-last element is undefined behavior.
    //!
    t_self_mut &operator++()
    {
        ++m_iter;
        return *this;
    }

    //! \warning Caller pointing to the post-last element is undefined behavior.
    //!
    t_self operator++(
        int
    )
    {
        return input_iterator_restrictor(m_iter++);
    }

#undef SELF
};

} // namespace tester

#endif
