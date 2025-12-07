#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#define ESC "\x1B"
#define CSI ESC "["

// Set Graphics Rendition
#define SGR(VARIANT) CSI VARIANT "m"

#define TEXT_BOLD                 ";1"
#define TEXT_DIM                  ";2"
#define TEXT_NORMAL               ";22"
#define ITALIC_ON                 ";3"
#define ITALIC_OFF                ";23"
#define UNDERLINE_ON              ";4"
#define UNDERLINE_OFF             ";24"
#define BLINK_ON                  ";5"
#define BLINK_OFF                 ";25"
#define FOREGROUND_BLACK          ";30"
#define FOREGROUND_RED            ";31"
#define FOREGROUND_GREEN          ";32"
#define FOREGROUND_YELLOW         ";33"
#define FOREGROUND_BLUE           ";34"
#define FOREGROUND_MAGENTA        ";35"
#define FOREGROUND_CYAN           ";36"
#define FOREGROUND_WHITE          ";37"
#define FOREGROUND_RGB(R, G, B)   ";38;2;" #R ";" #G ";" #B
#define FOREGROUND_ID(ID)         ";38;5;" #ID
#define FOREGROUND_DEFAULT        ";39"
#define BACKGROUND_BLACK          ";40"
#define BACKGROUND_RED            ";41"
#define BACKGROUND_GREEN          ";42"
#define BACKGROUND_YELLOW         ";43"
#define BACKGROUND_BLUE           ";44"
#define BACKGROUND_MAGENTA        ";45"
#define BACKGROUND_CYAN           ";46"
#define BACKGROUND_WHITE          ";47"
#define BACKGROUND_RGB(R, G, B)   ";48;2;" #R ";" #G ";" #B
#define BACKGROUND_ID(ID)         ";48;5;" #ID
#define BACKGROUND_DEFAULT        ";49"
#define FOREGROUND_BRIGHT_BLACK   ";90"
#define FOREGROUND_BRIGHT_RED     ";91"
#define FOREGROUND_BRIGHT_GREEN   ";92"
#define FOREGROUND_BRIGHT_YELLOW  ";93"
#define FOREGROUND_BRIGHT_BLUE    ";94"
#define FOREGROUND_BRIGHT_MAGENTA ";95"
#define FOREGROUND_BRIGHT_CYAN    ";96"
#define FOREGROUND_BRIGHT_WHITE   ";97"
#define BACKGROUND_BRIGHT_BLACK   ";100"
#define BACKGROUND_BRIGHT_RED     ";101"
#define BACKGROUND_BRIGHT_GREEN   ";102"
#define BACKGROUND_BRIGHT_YELLOW  ";103"
#define BACKGROUND_BRIGHT_BLUE    ";104"
#define BACKGROUND_BRIGHT_MAGENTA ";105"
#define BACKGROUND_BRIGHT_CYAN    ";106"
#define BACKGROUND_BRIGHT_WHITE   ";107"

#endif
