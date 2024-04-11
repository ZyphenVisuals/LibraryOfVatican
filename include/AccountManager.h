#ifndef ACCOUNT_MANAGER_HEADER
#define ACCOUNT_MANAGER_HEADER

#include "Structs.h"

/**
 * @brief Save an account to persistent storage
 *
 * @param acc account to save
 * @param datapath persistent storage location
 * @return char - 0 if succesful, 1 otherwise
 */
char create_account(Account *acc, char *datapath);

/**
 * @brief Log into an account
 *
 * @param acc account to log into
 * @param datapath persistent storage location
 * @return char - 0 if succesful, 1 otherwise
 */
char login(Account *acc, char *datapath);

#endif