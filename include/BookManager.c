#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// https://gist.github.com/alan-mushi/c8a6f34d1df18574f643
char *trim_whitespaces(char *str)
{
    char *end;

    // trim leading space
    while (isspace(*str))
        str++;

    if (*str == 0) // all spaces?
        return str;

    // trim trailing space
    end = str + strnlen(str, 128) - 1;

    while (end > str && isspace(*end))
        end--;

    // write new null terminator
    *(end + 1) = '\0';

    return str;
}

char donate_book(char *title, char *author, char *publisher, char *year, char *datapath)
{
    title = trim_whitespaces(title);
    author = trim_whitespaces(author);
    publisher = trim_whitespaces(publisher);
    year = trim_whitespaces(year);
    char *folder = "inventory/";
    char *filename = malloc(strlen(title) + strlen(author) + strlen(publisher) + strlen(year) + 12);
    sprintf(filename, "(%s),(%s),(%s),(%s)", title, author, publisher, year);
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
