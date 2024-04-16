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
 * @brief Renders a simple, single choice menu
 *
 * @param count Amount of items in array
 * @param choices Array of strings representing the choices
 * @param title Title of the menu
 * @return int The index of the selected choice
 */

int render_menu(unsigned int count, char **choices, char *title);

/**
 * @brief Renders a simple form
 *
 * @param count Number of fields
 * @param fields Array of strings representing the labels of each field
 * @param title Title of the form
 * @return char** The list of responses, as strings
 */
char **render_form(unsigned int count, char **fields, char *title);

/**
 * @brief Gracefully shuts down the app
 *
 * @param sig
 */
void stop_app(int sig);

#endif