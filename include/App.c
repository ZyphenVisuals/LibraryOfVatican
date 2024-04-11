#include "Structs.h"
#include "Renderer.h"
#include "LogUtils.h"

#include <unistd.h>

void run_app(Account *acc, char *datapath)
{
    setup_screen();
    render_footer("Hello, %s %s!", acc->surname, acc->name);

    char *choices[] = {
        "Search for books",
        "Return books",
        "Donate a book",
        "Quit"};

    render_menu(4, choices);

    return;
}