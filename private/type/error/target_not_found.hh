#ifndef TYPE_ERROR_TARGET_NOT_FOUND_HH
#define TYPE_ERROR_TARGET_NOT_FOUND_HH

#include "type/category/name.hh"

namespace tester { namespace error {

struct t_target_not_found {
    category::t_name m_target_name;

    t_target_not_found(
        category::t_name const &target_name
    )
    : m_target_name(target_name)
    {}
};

}} // namespace tester::error

#endif
