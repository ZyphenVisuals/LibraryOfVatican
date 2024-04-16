#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

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

unsigned int search_books(Book search, char *searchPath, Book *books)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(searchPath);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] != '.')
            {
                char *filePath = malloc(strlen(searchPath) + strlen(dir->d_name) + 1);
                strcpy(filePath, searchPath);
                strcat(filePath, dir->d_name);
                char *quantity = malloc(10);
                FILE *f = fopen(filePath, "r");
                fscanf(f, "%s", quantity);
                Book book = book_deserialize(dir->d_name, quantity);
                free(filePath);
                free(quantity);
                fclose(f);
            }
        }
        closedir(d);
    }
    return 0;
}
