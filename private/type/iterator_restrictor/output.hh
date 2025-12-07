#ifndef ITERATOR_RESTRICTOR_OUTPUT_HH
#define ITERATOR_RESTRICTOR_OUTPUT_HH

#include <iterator>

namespace tester {

template <typename OuptutIterator>
class output_iterator_restrictor
{
private: // types
    typedef OuptutIterator                   t_iterator;
    typedef output_iterator_restrictor       t_self;
    typedef std::iterator_traits<t_iterator> t_traits;

public: // types
    typedef std::output_iterator_tag           iterator_category;
    typedef typename t_traits::difference_type difference_type;
    typedef typename t_traits::value_type      value_type;
    typedef typename t_traits::reference       reference;
    typedef typename t_traits::pointer         pointer;

private: // fields
    t_iterator m_itr;

public: // constructors
    //! \brief Wrap constructor.
    //!
    output_iterator_restrictor(
        t_iterator const &itr
    )
    : m_itr(itr)
    {}

    //! \brief Copy constructor.
    //!
    output_iterator_restrictor(
        t_self const &other
    )
    : m_itr(other.m_itr)
    {}

public: // operators
    reference operator*() { return *m_itr; }

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
        ++this->m_itr;
        return *this;
    }

    //! \warning Caller pointing to the past-the-end element before incrementing
    //!          is undefined behavior.
    //!
    t_self operator++(
        int
    )
    {
        return t_self(this->m_itr++);
    }
};

} // namespace tester

#endif
