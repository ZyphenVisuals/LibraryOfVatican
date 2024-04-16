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
    char *year;
    char *quantity;
} Book;

Account account_constructor(char *surname, char *name);

Book book_constructor(char *title, char *author, char *publisher, char *year, char *quantity);

char *book_serialize(Book book);

Book book_deserialize(char *serial, char *quantity);

char book_filled(Book book);

#endif