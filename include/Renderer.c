#include <curses.h>
#include <menu.h>
#include <signal.h>
#include <stdlib.h>

/**
 * @brief Gracefully shuts down ncurses
 *
 * @param sig
 */
void finish(int sig)
{
    endwin();
    exit(0);
}

/**
 * @brief Initializes ncurses
 *
 */
void setup_screen()
{
    signal(SIGINT, finish); /* arrange interrupts to terminate */

    initscr();            /* initialize the curses library */
    keypad(stdscr, TRUE); /* enable keyboard mapping */
    cbreak();             /* take input chars one at a time, no wait for \n */
    noecho();             /* don't echo input */

    start_color();                        /* Enable color */
    init_pair(1, COLOR_RED, COLOR_BLACK); /* Select colors */
    wbkgd(stdscr, COLOR_PAIR(1));         /* Apply colors */
    refresh();
    return;
}

/**
 * @brief Changes the current footer using a format string
 *
 * @param fmt Format
 * @param ... Variables used in fmt
 */
void render_footer(const char *fmt, ...)
{
    char *footer = malloc(64);
    va_list args;
    va_start(args, fmt);
    vsprintf(footer, fmt, args);
    va_end(args);
    mvprintw(LINES - 2, 0, footer);
    refresh();
    return;
}
