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

/**
 * @brief Transforms an array of strings into an array of menu items
 *
 * @param count Length of the original array
 * @param choices Original array of strings
 * @return ITEM** New array of menu items
 */
ITEM **items_from_strings(unsigned int count, char *choices[])
{
    ITEM **items;

    items = (ITEM **)calloc(count + 1, sizeof(ITEM *));

    for (int i = 0; i < count; ++i)
        items[i] = new_item(choices[i], choices[i]);
    items[count] = (ITEM *)NULL;

    return items;
}

/**
 * @brief Renders a simple, single choice menu on the screen with the given choices
 *
 * @param count Amount of items in array
 * @param choices Array of strings representing the choices
 * @return int The index of the selected choice
 */
int render_menu(unsigned int count, char *choices[])
{
    ITEM **items = items_from_strings(count, choices);

    MENU *menu = new_menu(items);    /* Initialize menu*/
    menu_opts_off(menu, O_SHOWDESC); /* Disable descriptions*/

    post_menu(menu);
    refresh();

    int c;
    while (c = getch())
    {
        switch (c)
        {
        case KEY_DOWN:
            menu_driver(menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(menu, REQ_UP_ITEM);
            break;
        }
    }
}