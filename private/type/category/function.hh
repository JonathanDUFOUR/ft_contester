#ifndef TYPE_CATEGORY_FUNCTION_HH
#define TYPE_CATEGORY_FUNCTION_HH

#include "type/category/name_set.hh"
#include "type/status.hh"

namespace tester { namespace category {

typedef t_status (*t_function)(t_name_set const &);

}} // namespace tester::category

#endif
