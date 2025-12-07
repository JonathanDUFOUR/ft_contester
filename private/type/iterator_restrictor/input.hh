#ifndef ITERATOR_RESTRICTOR_INPUT_HH
#define ITERATOR_RESTRICTOR_INPUT_HH

#include "type_traits.hh"
#include <iterator>

namespace tester {

template <typename InputIterator>
class input_iterator_restrictor
{
private: // types
    typedef InputIterator                    t_iterator;
    typedef input_iterator_restrictor        t_self;
    typedef std::iterator_traits<t_iterator> t_traits;

public: // types
    typedef std::input_iterator_tag                                          iterator_category;
    typedef typename t_traits::difference_type                               difference_type;
    typedef typename t_traits::value_type                                    value_type;
    typedef typename make_const_referent<typename t_traits::reference>::type reference;
    typedef typename make_const_pointee<typename t_traits::pointer>::type    pointer;

private: // fields
    t_iterator m_itr;

public: // constructors
    //! \brief Wrap constructor.
    //!
    input_iterator_restrictor(
        t_iterator const &itr
    )
    : m_itr(itr)
    {}

    //! \brief Copy constructor.
    //!
    input_iterator_restrictor(
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
        return input_iterator_restrictor(m_itr++);
    }
};

} // namespace tester

#endif
