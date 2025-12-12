#ifndef TYPE_TITLE_HIGH_LEVEL_HH
#define TYPE_TITLE_HIGH_LEVEL_HH

#include <string>

namespace tester { namespace title {

struct t_high_level {
    std::string m_text;

    t_high_level(
        std::string const &text
    )
    : m_text(text)
    {}
};

}} // namespace tester::title

#endif
