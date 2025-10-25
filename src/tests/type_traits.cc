#define DISABLE
#ifndef DISABLE

# include "type_traits.hh" // {false, true}_type, is_same
# include "graphics.hh" // FG_{GREEN, RED, RGB}, GRAPHICS_RESET
# include "iterator/restrictor/input.hh" // input_iterator_restrictor
# include "tester.hh" // FAILURE, SUCCESS, delay, status, title
# include "type_traits.hpp" // ft::{is_integral, false_type, true_type}
# include "types/str.hh" // str
# include <iostream> // std::{cerr, cout}

namespace tester {
namespace test {
namespace type_traits {

using std::cerr;
using std::cout;

namespace integral_constant {
template <typename T>
inline static status test_variant(
    T const &value
)
{
    typedef ft::integral_constant<T, value> const variant;

    return !sizeof(variant)
                && is_same<typename variant::type, T>()
                && variant::s_value == value
                && variant() == value
             ? SUCCESS
             : FAILURE;
}

# define TEST_COUNT 5

inline status run_tests()
{
    title("integral_constant");

    status const results[TEST_COUNT] = {
        test_variant(42),
        test_variant(true),
        test_variant('-'),
        test_variant(3.14),
        test_variant("HelloNoobs"),
    };

    for (usize i = 0; i < TEST_COUNT; ++i) {

        if (results[i] == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

# undef TEST_COUNT

} // namespace integral_constant

inline static u8 check_bool(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<bool> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_char(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<char> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_wchar_t(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<wchar_t> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_i8(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<signed char> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_i16(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<signed short> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_i32(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<signed int> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_i64(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<signed long> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_u8(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<unsigned char> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_u16(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<unsigned short> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_u32(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<unsigned int> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_u64(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<unsigned long> const ie;

        if (!dynamic_cast<ft::true_type const *>(&ie) || ie.value != true) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_void(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<void> const ie;

        if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_pointer(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<void *> const ie;

        if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_f32(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<float> const ie;

        if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_f64(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<double> const ie;

        if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_std_string(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<std::string> const ie;

        if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline static u8 check_ft_input_iterator_restrictor(
    void
)
{
    title(__func__);
    try {
        ft::is_integral<tester::input_iterator_restrictor<u16 const *> > const ie;

        if (!dynamic_cast<ft::false_type const *>(&ie) || ie.value != false) {
            return EXIT_FAILURE;
        }
    }
    catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

u8 test_is_integral(
    void
)
{
    TestFn const tests[] = {
        check_bool,
        check_wchar_t,
        check_char,
        check_i8,
        check_i16,
        check_i32,
        check_i64,
        check_u8,
        check_u16,
        check_u32,
        check_u64,
        check_void,
        check_pointer,
        check_f32,
        check_f64,
        check_std_string,
        check_ft_input_iterator_restrictor,
        NULL
    };
    u8                    koCount = 0;
    struct timespec const delay   = {SLEEP_TIME_SEC, SLEEP_TIME_NANOSEC};

    nanosleep(&delay, NULL);

    std::cerr << LIGHT_BLUE_FG;
    std::cout << "###################################################" << '\n';
    std::cout << "##                  IS_INTEGRAL                  ##" << '\n';
    std::cout << "###################################################" << '\n';
    std::cerr << RESET;

    for (usize i = 0; tests[i]; ++i) {
        nanosleep(&delay, NULL);

        switch (tests[i]()) {
        case EXIT_SUCCESS:
            std::cerr << GREEN_FG;
            std::cout << "[OK]";
            std::cerr << RESET;
            break;

        case EXIT_FAILURE:
            std::cerr << RED_FG;
            std::cout << "[KO]";
            std::cerr << RESET;
            ++koCount;
            break;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    return koCount;
}

#endif
