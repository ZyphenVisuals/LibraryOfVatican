#include "Structs.h"
#include "Renderer.h"

#include <unistd.h>

void run_app(Account *acc, char *datapath)
{
    setup_screen();
    render_footer("Hello, %s %s!", acc->surname, acc->name);
    sleep(10);
    return;
}