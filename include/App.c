#include "Structs.h"
#include "Renderer.h"
#include "LogUtils.h"
#include "App.h"
#include "BookManager.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_app(Account *acc, char *datapath)
{
    setup_screen();

    char *choices[] = {
        "Search books",
        "Return books",
        "Donate a book",
        "Quit"};

    unsigned int selection;
    while ((selection = render_menu(4, choices, "Main Menu")) != 3)
    {
        if (selection == 0)
        {
            Book *books;

            char *labels[] = {
                "Title",
                "Author",
                "Publisher",
                "Year"};
            char **book_data = render_form(4, labels, "Donate book");
            if (book_data != NULL)
            {
                Book book = book_constructor(book_data[0], book_data[1], book_data[2], book_data[3], book_data[3]);

                char *folder = "inventory/";
                char *path = malloc(strlen(datapath) + strlen(folder) + 1);
                strcpy(path, datapath);
                strcat(path, folder);

                unsigned int books_count = search_books(book, path, books);
            }
        }
        if (selection == 1)
        {
            render_alert("Alert", "Womp womp");
        }
        if (selection == 2)
        {
            char *labels[] = {
                "Title",
                "Author",
                "Publisher",
                "Year"};
            char **book_data = render_form(4, labels, "Donate book");
            if (book_data != NULL)
            {
                Book book = book_constructor(book_data[0], book_data[1], book_data[2], book_data[3], book_data[3]);
                donate_book(book, datapath);
            }
        }
    }

    stop_app(0);

    return;
}