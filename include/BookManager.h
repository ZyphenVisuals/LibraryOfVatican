#ifndef BOOKMANAGER
#define BOOKMANAGER

#include "Structs.h"

/**
 * @brief Adds a new book to the inventory. If the book already exists, increases its amount.
 *
 * @param book Book object to save. Quantity is ignored.
 * @param datapath Path to the persistent data storage
 * @return char - 0 for success, other for failure
 */
char donate_book(Book book, char *datapath);

/**
 * @brief Searches for books based on fields. Fields left empty are ignored.
 *
 * @param search Book object to filter. Quantity is ignored.
 * @param datapath Path to search
 * @param books Array of strings where to add the results
 * @return unsigned int - Number of books returned
 */
unsigned int search_books(Book search, char *datapath, Book *books);

#endif