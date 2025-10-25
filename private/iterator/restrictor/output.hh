#ifndef ITERATOR_RESTRICTOR_OUTPUT_HH
#define ITERATOR_RESTRICTOR_OUTPUT_HH

#include <iterator> // std::{iterator_traits,output_iterator_tag}

namespace tester {

using std::iterator_traits;
using std::output_iterator_tag;

template <typename OuptutIterator>
class output_iterator_restrictor
{
#define SELF output_iterator_restrictor

private:
    typedef OuptutIterator const            t_iterator;
    typedef OuptutIterator                  t_iterator_mut;
    typedef SELF const                      t_self;
    typedef SELF                            t_self_mut;
    typedef iterator_traits<t_iterator_mut> t_traits;

public:
    typedef output_iterator_tag                iterator_category;
    typedef typename t_traits::difference_type difference_type;
    typedef typename t_traits::value_type      value_type;
    typedef typename t_traits::reference       reference;
    typedef typename t_traits::pointer         pointer;

protected:
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

    // ┏━━━━━━━━━━━┓
    // ┃ Operators ┃
    // ┗━━━━━━━━━━━┛

    reference operator*() { return *m_iter; }

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
        ++this->m_iter;
        return *this;
    }

    //! \warning Caller pointing to the post-last element is undefined behavior.
    //!
    t_self operator++(
        int
    )
    {
        return output_iterator_restrictor(this->m_iter++);
    }

#undef SELF
};

} // namespace tester

#endif
