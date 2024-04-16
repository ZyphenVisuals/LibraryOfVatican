#ifndef BOOKMANAGER
#define BOOKMANAGER

#include "Structs.h"

/**
 * @brief Adds a new book to the inventory. If the book already exists, increases its amount.
 *
 * @param title
 * @param author
 * @param publisher
 * @param year
 * @param datapath Path to the persistent data storage
 * @return char - 0 for success, other for failure
 */
char donate_book(Book book, char *datapath);

/**
 * @brief Searches for books based on fields. Fields left empty are ignored.
 *
 * @param book Book object to save
 * @param datapath Path to the persistent data storage
 * @param books Array of strings where to add the results
 * @return unsigned int - Number of books returned
 */
unsigned int search_books(char *title, char *author, char *publisher, char *year, char *datapath, Book *books);

#endif