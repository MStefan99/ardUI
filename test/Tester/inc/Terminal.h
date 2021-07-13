//
// Created by MStefan99 on 17.3.21.
//

#ifndef ARDUI_TERMINAL_H
#define ARDUI_TERMINAL_H

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
#define UNDERLINED "\033[4m"

#define NO_WEIGHT "\033[22m"
#define NO_ITALIC "\033[23m"
#define NO_UNDERLINE "\033[24m"

#define NC "\033[39m"
#define RED "\033[38;5;1m"
#define GREEN "\033[38;5;2m"
#define YELLOW "\033[38;5;3m"
#define BLUE "\033[38;5;4m"

#define BG_NC "\033[49m"
#define BG_RED "\033[48;5;1m"
#define BG_GREEN "\033[48;5;2m"
#define BG_YELLOW "\033[48;5;3m"
#define BG_BLUE "\033[48;5;4m"

#endif //ARDUI_TERMINAL_H
