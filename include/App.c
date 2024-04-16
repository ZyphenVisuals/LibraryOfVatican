#include "Structs.h"
#include "Renderer.h"
#include "LogUtils.h"
#include "App.h"

#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>

void run_app(Account *acc, char *datapath)
{
    setup_screen();
    render_footer("Hello, %s %s!", acc->surname, acc->name);

    char *choices[] = {
        "Search for books",
        "Return books",
        "Donate a book",
        "Quit"};

    unsigned int selection;
    while ((selection = render_menu(4, choices, "Main Menu")) != 3)
    {
        if (selection == 2)
        {
            char *labels[] = {
                "Title",
                "Author",
                "Publisher",
                "Year"};
            render_form(4, labels, "Donate book");
        }
    }

    stop_app(0);

    return;
}