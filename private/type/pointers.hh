#ifndef TYPE_POINTERS_HH
#define TYPE_POINTERS_HH

#include "type/fundamentals.hh" // tester::t_{bool,char,{i,u}{8,16,32,64,size},float,double,long_double}{,_mut}
#include "type/str.hh" // tester::str{,_mut}

namespace tester {

typedef t_bool *const            t_bool_ptr;
typedef t_bool                  *t_bool_ptr_mut;
typedef t_bool_mut *const        t_bool_mut_ptr;
typedef t_bool_mut              *t_bool_mut_ptr_mut;
typedef t_char *const            t_char_ptr;
typedef t_char                  *t_char_ptr_mut;
typedef t_char_mut *const        t_char_mut_ptr;
typedef t_char_mut              *t_char_mut_ptr_mut;
typedef t_i8 *const              t_i8_ptr;
typedef t_i8                    *t_i8_ptr_mut;
typedef t_i8_mut *const          t_i8_mut_ptr;
typedef t_i8_mut                *t_i8_mut_ptr_mut;
typedef t_i16 *const             t_i16_ptr;
typedef t_i16                   *t_i16_ptr_mut;
typedef t_i16_mut *const         t_i16_mut_ptr;
typedef t_i16_mut               *t_i16_mut_ptr_mut;
typedef t_i32 *const             t_i32_ptr;
typedef t_i32                   *t_i32_ptr_mut;
typedef t_i32_mut *const         t_i32_mut_ptr;
typedef t_i32_mut               *t_i32_mut_ptr_mut;
typedef t_i64 *const             t_i64_ptr;
typedef t_i64                   *t_i64_ptr_mut;
typedef t_i64_mut *const         t_i64_mut_ptr;
typedef t_i64_mut               *t_i64_mut_ptr_mut;
typedef t_isize *const           t_isize_ptr;
typedef t_isize                 *t_isize_ptr_mut;
typedef t_isize_mut *const       t_isize_mut_ptr;
typedef t_isize_mut             *t_isize_mut_ptr_mut;
typedef t_u8 *const              t_u8_ptr;
typedef t_u8                    *t_u8_ptr_mut;
typedef t_u8_mut *const          t_u8_mut_ptr;
typedef t_u8_mut                *t_u8_mut_ptr_mut;
typedef t_u16 *const             t_u16_ptr;
typedef t_u16                   *t_u16_ptr_mut;
typedef t_u16_mut *const         t_u16_mut_ptr;
typedef t_u16_mut               *t_u16_mut_ptr_mut;
typedef t_u32 *const             t_u32_ptr;
typedef t_u32                   *t_u32_ptr_mut;
typedef t_u32_mut *const         t_u32_mut_ptr;
typedef t_u32_mut               *t_u32_mut_ptr_mut;
typedef t_u64 *const             t_u64_ptr;
typedef t_u64                   *t_u64_ptr_mut;
typedef t_u64_mut *const         t_u64_mut_ptr;
typedef t_u64_mut               *t_u64_mut_ptr_mut;
typedef t_usize *const           t_usize_ptr;
typedef t_usize                 *t_usize_ptr_mut;
typedef t_usize_mut *const       t_usize_mut_ptr;
typedef t_usize_mut             *t_usize_mut_ptr_mut;
typedef t_float *const           t_float_ptr;
typedef t_float                 *t_float_ptr_mut;
typedef t_float_mut *const       t_float_mut_ptr;
typedef t_float_mut             *t_float_mut_ptr_mut;
typedef t_double *const          t_double_ptr;
typedef t_double                *t_double_ptr_mut;
typedef t_double_mut *const      t_double_mut_ptr;
typedef t_double_mut            *t_double_mut_ptr_mut;
typedef t_long_double *const     t_long_double_ptr;
typedef t_long_double           *t_long_double_ptr_mut;
typedef t_long_double_mut *const t_long_double_mut_ptr;
typedef t_long_double_mut       *t_long_double_mut_ptr_mut;

typedef t_str *const     t_str_ptr;
typedef t_str           *t_str_ptr_mut;
typedef t_str_mut *const t_str_mut_ptr;
typedef t_str_mut       *t_str_mut_ptr_mut;

} // namespace tester

#endif
