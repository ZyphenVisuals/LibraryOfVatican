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
    while ((selection = render_menu(4, choices)) != 3)
    {
        //
    }

    stop_app(0);

    return;
}