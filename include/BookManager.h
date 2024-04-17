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
 * @param books_count Number of books (will be set by function)
 * @return Book* - Array of books
 */
Book *search_books(Book search, char *datapath, unsigned int *books_count);

/**
 * @brief Transfers book from inventory to user account.
 *
 * @param book Book to borrow
 * @param acc Current user account
 * @param datapath Persistent data storage
 * @return char - 0 if succesful, 1 otherwise
 */
char borrow_book(Book book, Account *acc, char *datapath);

#endif