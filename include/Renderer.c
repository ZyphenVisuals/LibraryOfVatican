#include <curses.h>
#include <menu.h>
#include <form.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>

#include "Renderer.h"

void stop_app(int sig)
{
    endwin();
    exit(sig);
}

void setup_screen()
{
    signal(SIGINT, stop_app); /* arrange interrupts to terminate */

    initscr();            /* initialize the curses library */
    keypad(stdscr, TRUE); /* enable keyboard mapping */
    cbreak();             /* take input chars one at a time, no wait for \n */
    noecho();             /* don't echo input */
    curs_set(0);

    start_color();                        /* Enable color */
    init_pair(1, COLOR_RED, COLOR_BLACK); /* Select colors */
    wbkgd(stdscr, COLOR_PAIR(1));         /* Apply colors */
    refresh();
    return;
}

void render_footer(const char *fmt, ...)
{
    char *footer = malloc(64);
    va_list args;
    va_start(args, fmt);
    vsprintf(footer, fmt, args);
    va_end(args);
    mvprintw(LINES - 2, 2, footer);
    refresh();
    return;
}

ITEM **items_from_strings(unsigned int count, char *choices[])
{
    ITEM **items;

    items = (ITEM **)calloc(count + 1, sizeof(ITEM *));

    for (int i = 0; i < count; ++i)
        items[i] = new_item(choices[i], choices[i]);
    items[count] = (ITEM *)NULL;

    return items;
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
    int length, x, y;
    float temp;

    if (win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if (startx != 0)
        x = startx;
    if (starty != 0)
        y = starty;
    if (width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - length) / 2;
    x = startx + (int)temp;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}

unsigned int get_max_length(unsigned int count, char **choices)
{
    unsigned int max = strlen(choices[0]);
    for (unsigned int i = 1; i < count; i++)
    {
        unsigned int l = strlen(choices[i]);
        if (l > max)
            max = l;
    }
    return max;
}

int render_menu(unsigned int count, char **choices, char *title)
{

    int max_el_length = get_max_length(count, choices);
    if (strlen(title) > max_el_length)
    {
        max_el_length = strlen(title);
    }
    max_el_length += 3; /* a little padding */

    ITEM **items = items_from_strings(count, choices);

    WINDOW *window = newwin(4 + count, max_el_length + 5, (LINES / 2) - (count / 2) - 2, (COLS / 2) - (max_el_length / 2) - 2);
    keypad(window, TRUE);

    MENU *menu = new_menu(items);    /* Initialize menu*/
    menu_opts_off(menu, O_SHOWDESC); /* Disable descriptions*/

    /* Set main window and sub window */
    set_menu_win(menu, window);
    set_menu_sub(menu, derwin(window, count, max_el_length + 3, 3, 1));

    /* Set menu mark to the string " * " */
    set_menu_mark(menu, " =>");

    /* Print a border around the main window and print a title */
    box(window, 0, 0);
    print_in_middle(window, 1, 0, max_el_length + 5, title, COLOR_PAIR(1));
    mvwaddch(window, 2, 0, ACS_LTEE);
    mvwhline(window, 2, 1, ACS_HLINE, max_el_length + 3);
    mvwaddch(window, 2, max_el_length + 4, ACS_RTEE);

    post_menu(menu);

    render_footer("ENTER to select.");

    refresh();

    int c;
    while (c = wgetch(window))
    {
        switch (c)
        {
        case KEY_DOWN:
            menu_driver(menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(menu, REQ_UP_ITEM);
            break;
        case 10: // newline, enter doesn't work
            unpost_menu(menu);
            clear();
            refresh();
            return item_index(current_item(menu));
        }
    }
}

char **render_form(unsigned int count, char **fields, char *title)
{
    curs_set(1);

    int max_el_length = get_max_length(count, fields);

    char **res = malloc(count * sizeof(char *));
    FIELD **field = malloc((count + 1) * sizeof(FIELD *));
    FORM *form;
    WINDOW *window;
    int ch, rows, cols;

    /* Initialize the fields */
    for (int i = 0; i < count; i++)
    {
        field[i] = new_field(1, 50, 2 + i * 2, 1, 0, 0);
        set_field_back(field[i], A_UNDERLINE);
    }
    field[count] = NULL; // fields must be null terminated. see man page

    /* Create the form and post it */
    form = new_form(field);

    /* Calculate the area required for the form */
    scale_form(form, &rows, &cols);

    /* Create the window to be associated with the form */
    /* Bonus: auto centering */
    window = newwin(rows + 4, cols + 4 + max_el_length, (LINES / 2) - (rows / 2) - 2, (COLS / 2) - (cols / 2) - (max_el_length / 2) - 2);
    keypad(window, TRUE);

    /* Set main window and sub window */
    set_form_win(form, window);
    set_form_sub(form, derwin(window, rows, cols, 2, max_el_length + 2));

    /* Print a border around the main window and print a title */
    box(window, 0, 0);
    print_in_middle(window, 1, 0, cols + 4 + max_el_length, title, COLOR_PAIR(1));

    /* Print labels */
    for (int i = 0; i < count; i++)
    {
        mvwprintw(window, 4 + i * 2, 2, fields[i]);
    }

    post_form(form);
    wrefresh(window);

    render_footer("ENTER to submit. F2 to go back.");

    refresh();

    form_driver(form, REQ_FIRST_FIELD);

    /* Loop through to get user requests */
    while ((ch = wgetch(window)))
    {
        switch (ch)
        {
        case KEY_DOWN:
            form_driver(form, REQ_NEXT_FIELD);
            form_driver(form, REQ_END_LINE);
            break;
        case KEY_UP:
            form_driver(form, REQ_PREV_FIELD);
            form_driver(form, REQ_END_LINE);
            break;
        case KEY_BACKSPACE:
            form_driver(form, REQ_DEL_PREV);
            break;
        case 10: // newline, enter doesn't work
            form_driver(form, REQ_VALIDATION);
            for (int i = 0; i < count; i++)
            {
                res[i] = malloc(strlen(field_buffer(field[i], 0)) + 1);
                strcpy(res[i], field_buffer(field[i], 0));
                free_field(field[i]);
            }
            unpost_form(form);
            free_form(form);
            clear();
            curs_set(0);
            refresh();
            return res;
        case KEY_F(2):
            unpost_form(form);
            free_form(form);
            clear();
            curs_set(0);
            refresh();
            return NULL;
        default:
            /* If this is a normal character, it gets */
            /* Printed				  */
            if (ch == (char)ch)
                form_driver(form, ch);
            break;
        }
    }
}

void render_alert(char *title, char *message)
{
    unsigned int max_length = strlen(message);
    if (strlen(title) > max_length)
        max_length = strlen(title);

    // auto fit and auto center
    WINDOW *window = newwin(5, max_length + 4, (LINES / 2) - 3, (COLS / 2) - (max_length / 2) - 2);
    keypad(window, TRUE);

    box(window, 0, 0);
    print_in_middle(window, 1, 0, max_length + 4, title, COLOR_PAIR(1));
    mvwaddch(window, 2, 0, ACS_LTEE);
    mvwhline(window, 2, 1, ACS_HLINE, 38);
    mvwaddch(window, 2, max_length + 3, ACS_RTEE);

    mvwprintw(window, 3, 2, "%s", message);

    render_footer("ENTER to continue.");

    refresh();

    int c;
    while (c = wgetch(window))
    {
        switch (c)
        {
        case 10: // newline, enter doesn't work
            clear();
            refresh();
            return;
        }
    }

    return;
}