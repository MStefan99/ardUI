//
// Created by MStefan99 on 17.3.21.
//

#ifndef ARDUI_TERMINAL_HPP
#define ARDUI_TERMINAL_HPP

/* To set:
 * Foreground color 38
 * Background color 48
 *
 * Bold 1
 * Light 2
 * Italic 3
 * Underlined 4
 *
 * To reset:
 * All 0
 *
 * Foreground color 39
 * Background color 49
 *
 * Bold/Light 22
 * Italic 23
 * Underline 24
 */

#define RST "\033[0m"

#define BOLD "\033[1m"
#define LIGHT "\033[2m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"

#define NO_WEIGHT "\033[22m"
#define NO_ITALIC "\033[23m"
#define NO_UNDERLINE "\033[24m"

#define FG_NC "\033[39m"
#define FG_BLACK "\033[38;5;0m"
#define FG_WHITE "\033[38;5;15m"
#define FG_RED "\033[38;5;1m"
#define FG_GREEN "\033[38;5;2m"
#define FG_YELLOW "\033[38;5;3m"
#define FG_BLUE "\033[38;5;4m"
#define FG_BRIGHT_RED "\033[38;5;9m"
#define FG_BRIGHT_GREEN "\033[38;5;10m"
#define FG_BRIGHT_YELLOW "\033[38;5;11m"
#define FG_BRIGHT_BLUE "\033[38;5;12m"

#define BG_NC "\033[49m"
#define BG_BLACK "\033[48;5;0m"
#define BG_WHITE "\033[48;5;15m"
#define BG_RED "\033[48;5;1m"
#define BG_GREEN "\033[48;5;2m"
#define BG_YELLOW "\033[48;5;3m"
#define BG_BLUE "\033[48;5;4m"
#define BG_BRIGHT_RED "\033[48;5;9m"
#define BG_BRIGHT_GREEN "\033[48;5;10m"
#define BG_BRIGHT_YELLOW "\033[48;5;11m"
#define BG_BRIGHT_BLUE "\033[48;5;12m"

#endif //ARDUI_TERMINAL_HPP
