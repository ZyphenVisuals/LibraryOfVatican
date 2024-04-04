#ifndef STRUCTS_HEADER
#define STRUCTS_HEADER

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

Account account_constructor(char *surname, char *name);

Book book_constructor(char *title, char *author, char *publisher, unsigned int year, unsigned int quantity);

#endif