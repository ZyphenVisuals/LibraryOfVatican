#ifndef RENDERER
#define RENDERER

/**
 * @brief Initializes ncurses
 *
 */
void setup_screen();

/**
 * @brief Changes the current footer using a format string
 *
 * @param fmt Format
 * @param ... Variables used in fmt
 */
void render_footer(const char *fmt, ...);

/**
 * @brief Renders a simple, single choice menu on the screen with the given choices
 *
 * @param count Amount of items in array
 * @param choices Array of strings representing the choices
 * @return int The index of the selected choice
 */

int render_menu(unsigned int count, char *choices[]);

/**
 * @brief Gracefully shuts down the app
 *
 * @param sig
 */
void stop_app(int sig);

#endif