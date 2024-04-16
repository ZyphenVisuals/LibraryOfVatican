#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "Structs.h"

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

Account account_constructor(char *surname, char *name)
{
    Account acc;
    acc.surname = malloc(strlen(surname) + 1);
    strcpy(acc.surname, surname);
    acc.name = malloc(strlen(name) + 1);
    strcpy(acc.name, name);
    return acc;
}

Book book_constructor(char *title, char *author, char *publisher, char *year, char *quantity)
{
    title = trim_whitespaces(title);
    author = trim_whitespaces(author);
    publisher = trim_whitespaces(publisher);
    year = trim_whitespaces(year);
    quantity = trim_whitespaces(quantity);

    Book b;
    b.title = malloc(strlen(title) + 1);
    strcpy(b.title, title);
    b.author = malloc(strlen(author) + 1);
    strcpy(b.author, author);
    b.publisher = malloc(strlen(publisher) + 1);
    strcpy(b.publisher, publisher);
    b.year = malloc(strlen(year) + 1);
    strcpy(b.year, year);
    b.quantity = malloc(strlen(quantity) + 1);
    strcpy(b.quantity, quantity);
    return b;
}

char *book_serialize(Book book)
{
    char *serial = malloc(strlen(book.title) + strlen(book.author) + strlen(book.publisher) + strlen(book.year) + 12);
    sprintf(serial, "(%s),(%s),(%s),(%s)", book.title, book.author, book.publisher, book.year);
    return serial;
}