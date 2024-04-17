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
        "Borrow books",
        "Return books",
        "Donate books",
        "Quit"};

    unsigned int selection;
    while ((selection = render_menu(4, choices, "Main Menu")) != 3)
    {
        if (selection == 0)
        {
            char *labels[] = {
                "Title",
                "Author",
                "Publisher",
                "Year"};
            char **book_data = render_form(4, labels, "Search books");
            if (book_data != NULL)
            {
                Book book = book_constructor(book_data[0], book_data[1], book_data[2], book_data[3], book_data[3]);

                char *folder = "inventory/";
                char *path = malloc(strlen(datapath) + strlen(folder) + 1);
                strcpy(path, datapath);
                strcat(path, folder);

                unsigned int books_count;
                Book *books = search_books(book, path, &books_count);

                char **choices = malloc((books_count + 1) * sizeof(char *));
                choices[0] = "Back";
                for (int i = 0; i < books_count; i++)
                {
                    choices[i + 1] = book_pretty(books[i]);
                }

                unsigned int choice = render_menu(books_count + 1, choices, "Available books");
                if (choice != 0)
                {
                    choice--;

                    if (borrow_book(books[choice], acc, datapath))
                    {
                        render_alert("Error", "An error has occured.");
                    }
                    else
                    {
                        render_alert("Success", "Book added to your account.");
                    }
                }
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
                if (book_filled(book))
                {
                    donate_book(book, datapath);
                    render_alert("Success", "Thank you for your donation!");
                }
                else
                {
                    render_alert("Error", "Please fill in all fields.");
                }
            }
        }
    }

    stop_app(0);

    return;
}