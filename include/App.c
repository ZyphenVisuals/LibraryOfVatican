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

    unsigned int selection = render_menu(4, choices);

    switch (selection)
    {
    case 3:
        stop_app(0);
        break;

    default:
        break;
    }
    stop_app(1);

    return;
}