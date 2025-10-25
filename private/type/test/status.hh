#ifndef TYPE_TEST_STATUS_HH
#define TYPE_TEST_STATUS_HH

namespace tester { namespace test {

enum status { SUCCESS, FAILURE };

typedef status const t_status;
typedef status       t_status_mut;

}} // namespace tester::test

#endif
