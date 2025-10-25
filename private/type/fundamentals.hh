#ifndef TYPE_FUNDAMENTALS_HH
#define TYPE_FUNDAMENTALS_HH

#include <stdint.h> // {,u}int{8,16,32,64}_t
#include <sys/types.h> // {,s}size_t

namespace tester {

typedef bool const        t_bool;
typedef bool              t_bool_mut;
typedef char const        t_char;
typedef char              t_char_mut;
typedef int8_t const      t_i8;
typedef int8_t            t_i8_mut;
typedef int16_t const     t_i16;
typedef int16_t           t_i16_mut;
typedef int32_t const     t_i32;
typedef int32_t           t_i32_mut;
typedef int64_t const     t_i64;
typedef int64_t           t_i64_mut;
typedef ssize_t const     t_isize;
typedef ssize_t           t_isize_mut;
typedef uint8_t const     t_u8;
typedef uint8_t           t_u8_mut;
typedef uint16_t const    t_u16;
typedef uint16_t          t_u16_mut;
typedef uint32_t const    t_u32;
typedef uint32_t          t_u32_mut;
typedef uint64_t const    t_u64;
typedef uint64_t          t_u64_mut;
typedef size_t const      t_usize;
typedef size_t            t_usize_mut;
typedef float const       t_float;
typedef float             t_float_mut;
typedef double const      t_double;
typedef double            t_double_mut;
typedef long double const t_long_double;
typedef long double       t_long_double_mut;

} // namespace tester

#endif
