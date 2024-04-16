#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Structs.h"

char donate_book(Book book, char *datapath)
{
    char *folder = "inventory/";
    char *filename = book_serialize(book);
    char *filepath = malloc(strlen(datapath) + strlen(filename) + 12);
    sprintf(filepath, "%s%s%s", datapath, folder, filename);
    free(filename);
    FILE *f = fopen(filepath, "r");
    if (f != NULL)
    {
        // if book already exists
        unsigned int amount;
        fscanf(f, "%u", &amount);
        fclose(f);
        f = fopen(filepath, "w");
        fprintf(f, "%d", amount + 1);
        fclose(f);
        free(filepath);
        return 0;
    }
    // if it does not exist
    f = fopen(filepath, "w");
    fprintf(f, "1");
    fclose(f);
    free(filepath);
    return 0;
}
