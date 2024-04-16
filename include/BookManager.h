#ifndef BOOKMANAGER
#define BOOKMANAGER

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
char donate_book(char *title, char *author, char *publisher, char *year, char *datapath);

#endif