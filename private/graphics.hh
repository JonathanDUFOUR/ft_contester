#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <iostream> // std::cerr

#define ESC          "\x1B"
#define CSI          ESC "["
#define SGR(VARIANT) CSI #VARIANT "m" /* Set Graphics Rendition */

#define RESET_GRAPHICS                std::cerr << SGR(0)
#define SET_INTENSITY_BOLD            std::cerr << SGR(1)
#define SET_INTENSITY_DIM             std::cerr << SGR(2)
#define ENABLE_ITALIC                 std::cerr << SGR(3)
#define ENABLE_UNDERLINE              std::cerr << SGR(4)
#define ENABLE_BLINK                  std::cerr << SGR(5)
#define SET_INTENSITY_NORMAL          std::cerr << SGR(22)
#define DISABLE_ITALIC                std::cerr << SGR(23)
#define DISABLE_UNDERLINE             std::cerr << SGR(24)
#define DISABLE_BLINK                 std::cerr << SGR(25)
#define SET_FOREGROUND_BLACK          std::cerr << SGR(30)
#define SET_FOREGROUND_RED            std::cerr << SGR(31)
#define SET_FOREGROUND_GREEN          std::cerr << SGR(32)
#define SET_FOREGROUND_YELLOW         std::cerr << SGR(33)
#define SET_FOREGROUND_BLUE           std::cerr << SGR(34)
#define SET_FOREGROUND_MAGENTA        std::cerr << SGR(35)
#define SET_FOREGROUND_CYAN           std::cerr << SGR(36)
#define SET_FOREGROUND_WHITE          std::cerr << SGR(37)
#define SET_FOREGROUND_RGB(R, G, B)   std::cerr << SGR(38;2;R;G;B)
#define SET_FOREGROUND_ID(ID)         std::cerr << SGR(38;5;ID)
#define SET_FOREGROUND_DEFAULT        std::cerr << SGR(39)
#define SET_BACKGROUND_BLACK          std::cerr << SGR(40)
#define SET_BACKGROUND_RED            std::cerr << SGR(41)
#define SET_BACKGROUND_GREEN          std::cerr << SGR(42)
#define SET_BACKGROUND_YELLOW         std::cerr << SGR(43)
#define SET_BACKGROUND_BLUE           std::cerr << SGR(44)
#define SET_BACKGROUND_MAGENTA        std::cerr << SGR(45)
#define SET_BACKGROUND_CYAN           std::cerr << SGR(46)
#define SET_BACKGROUND_WHITE          std::cerr << SGR(47)
#define SET_BACKGROUND_RGB(R, G, B)   std::cerr << SGR(48;2;R;G;B)
#define SET_BACKGROUND_ID(ID)         std::cerr << SGR(48;5;ID)
#define SET_BACKGROUND_DEFAULT        std::cerr << SGR(49)
#define SET_FOREGROUND_BRIGHT_BLACK   std::cerr << SGR(90)
#define SET_FOREGROUND_BRIGHT_RED     std::cerr << SGR(91)
#define SET_FOREGROUND_BRIGHT_GREEN   std::cerr << SGR(92)
#define SET_FOREGROUND_BRIGHT_YELLOW  std::cerr << SGR(93)
#define SET_FOREGROUND_BRIGHT_BLUE    std::cerr << SGR(94)
#define SET_FOREGROUND_BRIGHT_MAGENTA std::cerr << SGR(95)
#define SET_FOREGROUND_BRIGHT_CYAN    std::cerr << SGR(96)
#define SET_FOREGROUND_BRIGHT_WHITE   std::cerr << SGR(97)
#define SET_BACKGROUND_BRIGHT_BLACK   std::cerr << SGR(100)
#define SET_BACKGROUND_BRIGHT_RED     std::cerr << SGR(101)
#define SET_BACKGROUND_BRIGHT_GREEN   std::cerr << SGR(102)
#define SET_BACKGROUND_BRIGHT_YELLOW  std::cerr << SGR(103)
#define SET_BACKGROUND_BRIGHT_BLUE    std::cerr << SGR(104)
#define SET_BACKGROUND_BRIGHT_MAGENTA std::cerr << SGR(105)
#define SET_BACKGROUND_BRIGHT_CYAN    std::cerr << SGR(106)
#define SET_BACKGROUND_BRIGHT_WHITE   std::cerr << SGR(107)

#endif
