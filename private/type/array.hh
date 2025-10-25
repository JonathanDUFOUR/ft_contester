#ifndef TYPE_ARRAY_HH
#define TYPE_ARRAY_HH

#include "type/fundamentals.hh" // t_usize

namespace tester {

template <typename T>
struct array {
    static T const s_inner[];
    static t_usize s_len;

    static T const &at(t_usize i);
};

template <typename T>
T const &array<T>::at(
    t_usize i
)
{
    return s_inner[i];
}

template <typename T>
t_usize array<T>::s_len = sizeof(array<T>::s_inner) / sizeof(T);

} // namespace tester

#endif
