#ifndef TYPE_TRAITS_HH
#define TYPE_TRAITS_HH

namespace tester {

template <typename T, T value>
struct integral_constant {
    static T const s_value = value;

    operator T() const { return s_value; }
};

// clang-format off

typedef integral_constant<bool, false> const t_false;
typedef integral_constant<bool,  true> const t_true ;

template <typename T> struct is_pointer     :public t_false{};
template <typename T> struct is_pointer<T*> :public t_true {};

template <typename T0, typename T1> struct is_same       :public t_false{};
template <typename T>               struct is_same<T, T> :public t_true {};

template <typename T> struct make_const_pointee;
template <typename T> struct make_const_pointee<T*> {typedef T const* type;};

template <typename T> struct make_const_referent;
template <typename T> struct make_const_referent<T&>{typedef T const& type;};

// clang-format on

} // namespace tester

#endif
