#include <stdlib.h>
#include <string.h>

typedef struct account
{
    char *surname;
    char *name;
} Account;

typedef struct book
{
    char *title;
    char *author;
    char *publisher;
    unsigned int year;
    unsigned int quantity;
} Book;

Account account_constructor(char *surname, char *name)
{
    Account acc;
    acc.surname = malloc(strlen(surname) + 1);
    strcpy(acc.surname, surname);
    acc.name = malloc(strlen(name) + 1);
    strcpy(acc.name, name);
    return acc;
}

Book book_constructor(char *title, char *author, char *publisher, unsigned int year, unsigned int quantity)
{
    Book b;
    b.title = malloc(strlen(title) + 1);
    strcpy(b.title, title);
    b.author = malloc(strlen(author) + 1);
    strcpy(b.author, author);
    b.publisher = malloc(strlen(publisher) + 1);
    strcpy(b.publisher, publisher);
    b.year = year;
    b.quantity = quantity;
    return b;
}